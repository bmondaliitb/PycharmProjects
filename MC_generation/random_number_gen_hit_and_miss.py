"""
Acceptance and rejection sampling method
Example from Glenn Cowan page 44
"""
import numpy as np

debug = False
def hit_or_miss(f, xmin, xmax, fmax, n_samples=1):
    samples = []
    while len(samples) < n_samples:
        r_1 = np.random.rand()
        r_2 = np.random.rand()
        if debug: 
          print("---")
          print(f"value of r_1 {r_1}")
          print(f"value of r_2 {r_2}")
        x = xmin + r_1 * (xmax - xmin)
        y = r_2 * fmax
        if y < f(x):
            samples.append(x)
    return samples

# Define the target function
def f(x):
    #return x**2
    return (3/8)*(1+x**2)

n_samples = 10000
x_min = -1 
x_max = 1
f_max = 0.75
# Generate samples
samples = hit_or_miss(f, x_min, x_max, f_max, n_samples)

# Plotting the results
import matplotlib.pyplot as plt

x = np.linspace(x_min, x_max, n_samples)
plt.plot(x, f(x), label='f(x) = 3/8(1+x^2)')
plt.hist(samples, bins=30, density=True, alpha=0.6, label='Samples')
plt.legend()
plt.show()

