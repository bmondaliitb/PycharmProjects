import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Define the 3D function
def f(x, y):
    return -(x**2 + y**2 - 6*x - 6*y + 14)

# Set the number of samples
num_samples = 50000

# Generate random samples within the domain for x and y
x_samples = np.random.uniform(-10, 10, num_samples)
y_samples = np.random.uniform(-10, 10, num_samples)

# Evaluate the function at each sample point
f_samples = f(x_samples, y_samples)

# Find the sample that gives the maximum function value
max_index = np.argmax(f_samples)
max_value = f_samples[max_index]
max_x = x_samples[max_index]
max_y = y_samples[max_index]

# Plotting
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# Create a grid of x, y values for plotting the function surface
x_plot = np.linspace(-10, 10, 100)
y_plot = np.linspace(-10, 10, 100)
x_plot, y_plot = np.meshgrid(x_plot, y_plot)
f_plot = f(x_plot, y_plot)

# Plot the surface
ax.plot_surface(x_plot, y_plot, f_plot, cmap='viridis', alpha=0.6)

# Plot the sampled points
ax.scatter(x_samples, y_samples, f_samples, color='red', s=1)

# Highlight the identified maximum
ax.scatter(max_x, max_y, max_value, color='gold', s=50, label='Identified Maximum')

ax.set_title('Monte Carlo Simulation to Find Maximum')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')
ax.legend()

plt.show()

print(f"Maximum value of the function is approximately {max_value} at (x, y) = ({max_x}, {max_y})")

