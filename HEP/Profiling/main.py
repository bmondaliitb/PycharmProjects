import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import minimize
from scipy.stats import norm

# Simulated observed data
observed = 25  # observed events in signal region
expected_signal = 15  # fixed signal shape (per unit mu)
b_nominal = 10  # nominal background estimate
b_sigma = 2  # uncertainty on background estimate (systematic)


# Define the negative log-likelihood (NLL)
def nll(mu, b):
    # Poisson term for total observed events
    lamb = mu * expected_signal + b
    poisson_term = lamb - observed * np.log(lamb)

    # Gaussian constraint on background
    gauss_term = 0.5 * ((b - b_nominal) / b_sigma) ** 2
    return poisson_term + gauss_term


# Profile likelihood: for each mu, minimize NLL w.r.t. b
mu_values = np.linspace(0, 3, 100)
nll_profile = []

for mu in mu_values:
    result = minimize(lambda b: nll(mu, b[0]), x0=[b_nominal], bounds=[(0, None)])
    nll_profile.append(nll(mu, result.x[0]))

# Normalize NLL so that minimum is at 0
nll_profile = np.array(nll_profile)
nll_profile -= np.min(nll_profile)

# Plotting
plt.plot(mu_values, nll_profile, label="Profile Likelihood")
plt.axhline(0.5, color='red', linestyle='--', label=r'$\Delta$NLL = 0.5 (1$\sigma$)')
plt.xlabel("Signal strength μ")
plt.ylabel("Δ Negative Log-Likelihood")
plt.title("Profile Likelihood Curve")
plt.legend()
plt.grid(True)
plt.show()
