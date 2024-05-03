import numpy as np

def exponential_random_number(lambda_param):
    """
    Generate a random number from the exponential distribution with rate lambda_param.
    
    Parameters:
    - lambda_param: The rate parameter of the exponential distribution (λ > 0).
    
    Returns:
    - A random number from the exponential distribution.
    """
    # Generate a uniform random number between 0 and 1
    R = np.random.uniform(0, 1)
    
    # Calculate the inverse CDF (F^-1(R)) to get the exponential random number
    x = -np.log(1 - R) / lambda_param
    
    return x

# Example usage
lambda_param = 1.0  # Rate parameter of the exponential distribution
for i in range(0,100):
  random_number = exponential_random_number(lambda_param)
  print(f"Random number from exponential distribution: {random_number}")

