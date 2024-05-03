import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def monte_carlo_integration_circle_visual(func, radius, n_samples):
    # Generate random samples within the square that bounds the circle
    x_samples = np.random.uniform(-radius, radius, n_samples)
    y_samples = np.random.uniform(-radius, radius, n_samples)
    
    # Check which samples are inside the circle
    inside_circle = x_samples**2 + y_samples**2 <= radius**2
    
    # Evaluate the function for points inside the circle
    func_values_inside = func(x_samples[inside_circle], y_samples[inside_circle])
    
    # Compute the average value
    average_value = np.mean(func_values_inside)
    
    # Scale by the area of the circle
    integral_estimate = average_value * np.pi * (radius**2)
    
    return x_samples, y_samples, inside_circle, integral_estimate

# Define the function to integrate
def f(x, y):
    return np.exp(-(x**2 + y**2))

# Parameters
radius = 1  # Radius of the circle
n_samples = 10000  # Number of samples for visualization

# Perform MC integration and get samples
x_samples, y_samples, inside_circle, integral_estimate = monte_carlo_integration_circle_visual(f, radius, n_samples)

# Plotting
fig, ax = plt.subplots(figsize=(8, 8))
ax.scatter(x_samples[inside_circle], y_samples[inside_circle], color='green', s=1, label='Inside Circle')
ax.scatter(x_samples[~inside_circle], y_samples[~inside_circle], color='red', s=1, label='Outside Circle')
circle = plt.Circle((0, 0), radius, edgecolor='blue', facecolor='none')
ax.add_artist(circle)
ax.set_aspect('equal', 'box')
ax.legend()
ax.set_title('Monte Carlo Integration Samples')

# Show the integral estimate
print(f"Estimated integral: {integral_estimate}")

# 3D plot of the function over the unit circle
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')
theta = np.linspace(0, 2 * np.pi, 100)
r = np.linspace(0, 1, 100)
T, R = np.meshgrid(theta, r)
X, Y = R * np.cos(T), R * np.sin(T)
Z = f(X, Y)
ax.plot_surface(X, Y, Z, cmap='viridis', edgecolor='none')
ax.set_title('Function $e^{-(x^2 + y^2)}$ over Unit Circle')
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')

plt.show()

