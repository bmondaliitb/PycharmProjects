import numpy as np

def hit_or_miss(f, xmin, xmax, fmax, n_samples=1):
    samples = []
    while len(samples) < n_samples:
        x = xmin + np.random.rand() * (xmax - xmin)
        y = np.random.rand() * fmax
        if y < f(x):
            samples.append(x)
    return samples

# Define the target function
def f(x):
    return x**2

# Generate samples
samples = hit_or_miss(f, 0, 1, 1, 1000)

# Plotting the results
import matplotlib.pyplot as plt

x = np.linspace(0, 1, 1000)
plt.plot(x, f(x), label='f(x) = x^2')
plt.hist(samples, bins=30, density=True, alpha=0.6, label='Samples')
plt.legend()
plt.show()

