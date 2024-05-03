import numpy as np
import matplotlib.pyplot as plt

# Define the function
def f(x):
    return x**2 - 4*x + 4

# Set the number of samples
num_samples = 1000  # Reduced for clearer visualization

# Generate random samples within the domain
x_samples = np.random.uniform(-10, 10, num_samples)

# Evaluate the function at each sample point
f_samples = f(x_samples)

# Find the sample that gives the minimum function value
min_index = np.argmin(f_samples)
min_value = f_samples[min_index]
min_x = x_samples[min_index]

# Plotting
# Create an array of x values for plotting the function smoothly
x_plot = np.linspace(-10, 10, 400)
f_plot = f(x_plot)

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(x_plot, f_plot, label='f(x) = $x^2 - 4x + 4$', linewidth=2)
plt.scatter(x_samples, f_samples, color='red', s=10, alpha=0.3, label='Sampled Points')
plt.scatter(min_x, min_value, color='green', s=50, label='Identified Minimum')
plt.title('Monte Carlo Simulation to Find Minimum')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend()
plt.grid(True)
plt.show()

print(f"Minimum value of the function is approximately {min_value} at x = {min_x}")

