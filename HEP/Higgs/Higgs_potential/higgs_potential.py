import numpy as np
import matplotlib.pyplot as plt

# Define the Higgs potential function with mu^2 < 0 and lambda > 0
def higgs_potential(phi, mu, lam):
    return mu**2 * phi**2 + lam * phi**4

# Parameters: mu^2 is negative, so we set mu = -1, and lambda is positive
mu = -1  # mu^2 < 0
lam = 0.5  # lambda > 0

# Create a range of phi values (expanded range to better visualize the "Mexican hat" shape)
phi = np.linspace(-3.5, 3.5, 500)

# Calculate the potential for each value of phi
V_phi = higgs_potential(phi, mu, lam)

# Plot the potential
plt.figure(figsize=(8, 6))
plt.plot(phi, V_phi, label=r'$V(\phi) = \mu^2 \phi^2 + \lambda \phi^4$', color='blue')
plt.title(r'Higgs Potential: "Mexican Hat" Shape ($\mu^2 < 0$ and $\lambda > 0$)')
plt.xlabel(r'$\phi$')
plt.ylabel(r'$V(\phi)$')
plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.grid(True)
plt.legend()
plt.show()

