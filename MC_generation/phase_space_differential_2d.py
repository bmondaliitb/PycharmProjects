import numpy as np
import matplotlib.pyplot as plt

# Constants
M = 1.0  # Mass of the initial particle, arbitrary units
m1 = 0.2  # Mass of the first final-state particle, arbitrary units
m2 = 0.2  # Mass of the second final-state particle, arbitrary units
N = 10000  # Number of decays to simulate

# Corrected Källén function λ
def kallen_lambda(a2, b2, c2):
    return a2**2 + b2**2 + c2**2 - 2*a2*b2 - 2*a2*c2 - 2*b2*c2

# Magnitude of the three-momentum |p|
p_mag = np.sqrt(kallen_lambda(M**2, m1**2, m2**2)) / (2 * M)

# Energies of the two particles
E1 = (M**2 + m1**2 - m2**2) / (2 * M)
E2 = (M**2 + m2**2 - m1**2) / (2 * M)

# Generate random angles for isotropic decay
theta = np.arccos(1 - 2 * np.random.rand(N))  # theta from 0 to pi
phi = 2 * np.pi * np.random.rand(N)  # phi from 0 to 2pi

# Plotting the distribution of phi
plt.hist(phi, bins=50, density=True)
plt.title('Distribution of $\\phi$ for 2-body decay')
plt.xlabel('$\\phi$ (radians)')
plt.ylabel('Density')
plt.show()

