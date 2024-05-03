import numpy as np
import matplotlib.pyplot as plt

def generate_gaussian_pairs(n_pairs):
    gaussian_pairs = []
    for _ in range(n_pairs):
        R1, R2 = np.random.rand(), np.random.rand()
        z1 = np.sqrt(-2 * np.log(R1)) * np.cos(2 * np.pi * R2)
        z2 = np.sqrt(-2 * np.log(R1)) * np.sin(2 * np.pi * R2)
        gaussian_pairs.append((z1, z2))
    return gaussian_pairs

# Generate pairs
n_pairs = 1000
pairs = generate_gaussian_pairs(n_pairs)

# Unpack pairs for plotting
z1, z2 = zip(*pairs)

# Plotting the results
plt.hist(z1, bins=30, alpha=0.6, density=True, label='z1')
plt.hist(z2, bins=30, alpha=0.6, density=True, label='z2', color='r')
plt.legend()
plt.title('Gaussian-Distributed Numbers')
plt.show()

