import numpy as np

# Define the function to integrate
def f(x):
    return np.sin(x)

# Monte Carlo integration
def monte_carlo_integration(func, a, b, n_samples):
    # Generate random samples
    x_samples = np.random.uniform(a, b, n_samples)
    
    # Evaluate the function for all samples
    func_values = func(x_samples)
    
    # Compute the average value
    average_value = np.mean(func_values)
    
    # Scale by the interval width
    integral_estimate = average_value * (b - a)
    
    return integral_estimate

# Parameters
a = 0  # Start of the interval
b = 2 * np.pi  # End of the interval
n_samples = 100000000  # Number of samples

# Perform MC integration
integral_estimate = monte_carlo_integration(f, a, b, n_samples)

print(f"Estimated integral of sin(x) from 0 to 2pi: {integral_estimate}")

