import numpy as np
import matplotlib.pyplot as plt

def decay_probability_density(t, lambda_decay):
    """The target decay probability density function, f(t)."""
    return lambda_decay * np.exp(-lambda_decay * t)

def overestimating_function(t, g_max):
    """An overestimating function, g(t), constant and >= max(f(t))."""
    return g_max

def simulate_decay_with_acceptance(lambda_decay, g_max, t_max):
    """Simulate a single decay event, accepting trials with probability f(t)/g(t)."""
    t = 0
    while t < t_max:
        # Generate a trial time increment from the overestimating distribution
        delta_t = -np.log(np.random.uniform()) / g_max
        t_trial = t + delta_t
        
        # Calculate acceptance probability f(t_trial)/g(t_trial)
        acceptance_prob = decay_probability_density(t_trial, lambda_decay) / overestimating_function(t_trial, g_max)
        
        # Accept or reject the trial time
        if np.random.uniform() < acceptance_prob:
            return t_trial  # Accepted decay time
        
        # If rejected, try again without updating t (to simulate continuous time)
    
    return None  # No decay within t_max if loop exits

# Parameters for simulation
lambda_decay = 0.1  # Decay rate
g_max = lambda_decay  # For this example, g_max = lambda, assuming g(t) >= max(f(t))
t_max = 50  # Maximum time to simulate
N0 = 1000  # Initial number of particles

# Simulate decays
decay_times = [simulate_decay_with_acceptance(lambda_decay, g_max, t_max) for _ in range(N0) if simulate_decay_with_acceptance(lambda_decay, g_max, t_max) is not None]

# Visualization
plt.hist(decay_times, bins=50, alpha=0.7, color='blue', edgecolor='black')
plt.title('Histogram of Decay Times with Acceptance Probability')
plt.xlabel('Time')
plt.ylabel('Frequency')
plt.show()

