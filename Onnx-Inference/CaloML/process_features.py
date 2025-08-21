import pandas as pd
import numpy as np
import yaml
from typing import Dict
import onnxruntime as ort
from pathlib import Path

# Assuming feature_transformer.py is in the same directory or accessible in PYTHONPATH
from feature_transformer import TRANSFORMATIONS

class FeatureProcessor:
    """
    A class to apply feature transformations to a pandas DataFrame based on a YAML config.
    """

    def __init__(self, config_path: str):
        """
        Initializes the processor by loading and parsing the configuration file.

        Args:
            config_path: The path to the YAML configuration file.
        """
        self.config_path = Path(config_path)
        if not self.config_path.is_file():
            raise FileNotFoundError(f"Configuration file not found at: {self.config_path}")
            
        self.feature_definitions = self._load_feature_definitions()
        print("FeatureProcessor initialized successfully.")

    def _load_feature_definitions(self) -> Dict:
        """Loads the 'features' block from the YAML config."""
        with open(self.config_path, 'r') as f:
            config = yaml.safe_load(f)
        
        features = config.get('data', {}).get('features')
        if not features:
            raise ValueError(f"Could not find 'data.features' block in the config file: {self.config_path}")
        return features

    def transform(self, df: pd.DataFrame) -> pd.DataFrame:
        """
        Applies the configured transformations to the input DataFrame.

        Args:
            df: The input pandas DataFrame with columns matching feature names from the config.

        Returns:
            A new DataFrame with the transformations applied.
        """
        df_transformed = df.copy()
        print(f"\nApplying transformations to {len(df_transformed)} rows...")

        for feature_name, definition in self.feature_definitions.items():
            if feature_name not in df_transformed.columns:
                print(f"  - WARNING: Feature '{feature_name}' from config not found in DataFrame. Skipping.")
                continue

            preprocessing_steps = definition.get('preprocessing', [])
            if not preprocessing_steps:
                continue

            params = definition.get('parameter', [])
            print(f"  - Processing column '{feature_name}'...")
            
            for transform_name in preprocessing_steps:
                transform_func = TRANSFORMATIONS.get(transform_name)

                if not transform_func:
                    print(f"    - WARNING: Transformation '{transform_name}' not found. Skipping.")
                    continue

                try:
                    # Print values that will cause log10 warning
                    if transform_name in ['log', 'log10', 'log2']:
                        invalid_mask = df_transformed[feature_name] <= 0
                        if invalid_mask.any():
                            invalid_values = df_transformed.loc[invalid_mask, feature_name]
                            print(f"    - WARNING: Non-positive values found in '{feature_name}' for '{transform_name}':")
                            print(invalid_values.values)
                    # Apply the function to the entire column (pandas Series)
                    df_transformed[feature_name] = transform_func(df_transformed[feature_name], params)
                    print(f"    - Applied '{transform_name}' successfully.")
                except Exception as e:
                    print(f"    - ERROR applying '{transform_name}' to '{feature_name}': {e}")
                    break # Stop processing this feature if a step fails

        print("\nTransformations complete.")
        return df_transformed

    def run_inference(self, model_path: str, df: pd.DataFrame, input_name: str = 'features') -> list:
        """
        Runs inference on an ONNX model using the provided DataFrame.

        The method reorders the DataFrame columns based on the 'index' in the
        feature config before feeding it to the model.

        Args:
            model_path: Path to the .onnx model file.
            df: The transformed pandas DataFrame.
            input_name: The name of the input layer of the ONNX model.

        Returns:
            A list of numpy arrays representing the model's output.
        """
        if not Path(model_path).is_file():
            raise FileNotFoundError(f"ONNX model not found at: {model_path}")

        print(f"\n--- Running ONNX Inference ---")
        print(f"Model: {model_path}")

        # 1. Sort feature names based on the 'index' from the config
        try:
            sorted_features = sorted(
                self.feature_definitions.items(), 
                key=lambda item: item[1]['index']
            )
            sorted_feature_names = [item[0] for item in sorted_features]
            print(f"Input features ordered by index: {sorted_feature_names}")
        except KeyError as e:
            raise ValueError(f"Feature definition is missing the 'index' key: {e}")

        # 2. Reorder DataFrame and convert to numpy array of type float32
        df_reordered = df[sorted_feature_names]
        input_tensor = df_reordered.to_numpy(dtype=np.float32)
        
        print(f"Input tensor shape: {input_tensor.shape}")

        # 3. Run inference
        session = ort.InferenceSession(model_path)

        output_names = [output.name for output in session.get_outputs()]
        print("ONNX model output keys:", output_names)
        
        # Ensure the provided input_name matches the model's expected input name
        model_input_name = session.get_inputs()[0].name
        if input_name != model_input_name:
             print(f"  - WARNING: Provided input_name '{input_name}' does not match model's expected input '{model_input_name}'. Using model's name.")
             input_name = model_input_name

        input_feed = {input_name: input_tensor}
        
        outputs = session.run(None, input_feed)
        
        print("Inference complete.")
        return outputs
