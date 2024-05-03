import numpy as np
import matplotlib.pyplot as plt

def target_distribution(x):
    """Target distribution f(x) = e^{-x^2}."""
    return np.exp(-x**2)

def overestimating_distribution(x):
    """Overestimating trial distribution g(x), uniform in this case."""
    return 1  # Since f(x) <= 1 for all x in [0, 1]

def sample_from_g(xmin, xmax, n_samples):
    """Sample uniformly from the overestimating distribution."""
    return np.random.uniform(xmin, xmax, n_samples)

def veto_algorithm(target_func, overestimating_func, xmin, xmax, n_samples):
    """Implement the veto algorithm to sample from the target distribution."""
    samples = []
    while len(samples) < n_samples:
        # Step 1: Sample x from the overestimating distribution g(x)
        x = sample_from_g(xmin, xmax, 1)[0]
        
        # Step 2: Calculate the acceptance probability f(x)/g(x)
        acceptance_prob = target_func(x) / overestimating_func(x)
        
        # Step 3: Accept or reject the sample
        if np.random.rand() < acceptance_prob:
            samples.append(x)
    
    return np.array(samples)

# Parameters
xmin = 0
xmax = 1
n_samples = 10000

# Use the veto algorithm to sample from the target distribution
samples = veto_algorithm(target_distribution, overestimating_distribution, xmin, xmax, n_samples)

# Visualization
x_values = np.linspace(xmin, xmax, 1000)
plt.figure(figsize=(10, 6))
plt.hist(samples, bins=30, density=True, alpha=0.6, label='Veto Algorithm Samples')
plt.plot(x_values, target_distribution(x_values), 'r-', lw=2, label='Target Distribution $f(x) = e^{-x^2}$')
plt.legend()
plt.xlabel('x')
plt.ylabel('Density')
plt.title('Sampling from $f(x) = e^{-x^2}$ using the Veto Algorithm')
plt.show()

