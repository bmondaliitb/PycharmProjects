import numpy as np
import matplotlib.pyplot as plt

def radioactive_decay_veto_algorithm(lambda_decay, N0, t_max):
    """
    Simulate radioactive decay using the veto algorithm.

    Parameters:
    - lambda_decay: Decay rate parameter (lambda).
    - N0: Initial number of atoms.
    - t_max: Maximum time to simulate.

    Returns:
    - decay_times: Times at which decays occurred.
    """
    decay_times = []  # To store the times of decay events
    N = N0  # Initialize with the initial number of atoms
    t = 0  # Start time

    while N > 0 and t < t_max:
        # Generate time until next decay using the inverse transform sampling method
        # for an exponential distribution with rate N*lambda_decay
        delta_t = -np.log(np.random.uniform()) / (N * lambda_decay)
        t += delta_t  # Update the time of the next decay event
        
        # Apply the veto: In a real scenario, every atom has a chance to decay,
        # but here we simulate the "first" decay event among N atoms.
        if np.random.uniform() < 1.0 / N:
            decay_times.append(t)
            N -= 1  # Decrement the number of atoms

    return decay_times

# Parameters
lambda_decay = 0.05  # Decay rate
N0 = 1000000  # Initial number of atoms
t_max = 100  # Maximum simulation time

# Simulate radioactive decay
decay_times = radioactive_decay_veto_algorithm(lambda_decay, N0, t_max)

# Plotting
plt.figure(figsize=(10, 6))
plt.hist(decay_times, bins=50, alpha=0.7, color='blue', edgecolor='black')
plt.title('Histogram of Decay Times')
plt.xlabel('Time')
plt.ylabel('Number of Decays')
plt.show()

# Plotting the decay curve
times = np.linspace(0, t_max, 1000)
N_t = N0 * np.exp(-lambda_decay * times)
plt.figure(figsize=(10, 6))
plt.plot(times, N_t, label='Theoretical Decay Curve', color='red')
plt.scatter(decay_times, N0 - np.arange(len(decay_times)), marker='.', color='blue', label='Simulated Decays')
plt.title('Radioactive Decay Simulation')
plt.xlabel('Time')
plt.ylabel('Number of Atoms Remaining')
plt.legend()
plt.show()

