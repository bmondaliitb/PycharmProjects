import numpy as np
from typing import List, Union, Callable

# Define a type for the input value, which can be a single number or a numpy array
Numeric = Union[float, np.ndarray]


def linear(x: Numeric, params: List[float]) -> Numeric:
    """Applies a linear transformation: offset + slope * x."""
    if len(params) != 2:
        raise ValueError(f"Linear transformation expects 2 parameters [offset, slope], but got {len(params)}.")
    offset, slope = params
    return offset + slope * x


def standard(x: Numeric, params: List[float]) -> Numeric:
    """Applies standardization: (x - mean) / standard_dev."""
    if len(params) != 2:
        raise ValueError(f"Standard transformation expects 2 parameters [mean, std_dev], but got {len(params)}.")
    mean, std_dev = params
    if std_dev == 0:
        # Handle case with zero standard deviation to avoid division by zero
        return x - mean
    return (x - mean) / std_dev


def log(x: Numeric, params: List[float] = None) -> Numeric:
    """Applies natural logarithm: ln(x)."""
    with np.errstate(divide='ignore'): # Ignore warnings for log(0)
        return np.log(x)


def log_ten(x: Numeric, params: List[float] = None) -> Numeric:
    """Applies base-10 logarithm: log10(x)."""
    with np.errstate(divide='ignore'): # Ignore warnings for log10(0)
        return np.log10(x)


def cube_root(x: Numeric, params: List[float] = None) -> Numeric:
    """Applies a signed cube root: |x|^(1/3) * sign(x)."""
    return np.cbrt(x)


def log_standard(x: Numeric, params: List[float]) -> Numeric:
    """Applies standardization on the natural logarithm of x: (ln(x) - mean) / std_dev."""
    if len(params) != 2:
        raise ValueError(f"LogStandard transformation expects 2 parameters [mean, std_dev], but got {len(params)}.")
    
    log_x = log(x)
    return standard(log_x, params)


def log_ten_standard(x: Numeric, params: List[float]) -> Numeric:
    """
    Applies a shift, then log10, then standardization.
    The transformation is: (log10(x - xmin + epsilon) - mean) / std_dev.
    """
    if len(params) != 4:
        raise ValueError(f"LogTenStandard expects 4 parameters [xmin, epsilon, mean, std_dev], but got {len(params)}.")
    
    xmin, epsilon, mean, std_dev = params
    
    # Apply the shift as described: x = x - xmin + epsilon
    x_shifted = x - xmin + epsilon
    
    # Apply log10 and then standardize
    log_x = log_ten(x_shifted)
    return standard(log_x, [mean, std_dev])


def max_absolute(x: Numeric, params: List[float]) -> Numeric:
    """Applies max-absolute scaling: x / |max_value|."""
    if len(params) != 1:
        raise ValueError(f"MaxAbsolute transformation expects 1 parameter [max_value], but got {len(params)}.")
    max_val = params[0]
    if max_val == 0:
        return x # Avoid division by zero
    return x / abs(max_val)


# A dispatcher dictionary to map string names to functions
TRANSFORMATIONS: dict[str, Callable] = {
    "Linear": linear,
    "Standard": standard,
    "Log": log,
    "LogTen": log_ten,
    "CubeRoot": cube_root,
    "LogStandard": log_standard,
    "LogTenStandard": log_ten_standard,
    "MaxAbsolute": max_absolute,
}
