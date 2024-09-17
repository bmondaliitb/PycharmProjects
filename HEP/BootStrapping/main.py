import numpy as np

def bootstrap_reco_data(reco_data, num_samples):
    bootstrapped_samples = []
    n = len(reco_data)
    for _ in range(num_samples):
        sample = np.random.choice(reco_data, size=n, replace=True)
        bootstrapped_samples.append(sample)
    return bootstrapped_samples

# Example usage
reco_data = np.array([event1, event2, event3, ...])  # your reco level data
num_samples = 1000  # number of bootstrapped samples
bootstrapped_samples = bootstrap_reco_data(reco_data, num_samples)

