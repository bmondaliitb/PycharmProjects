## integrate f(x) = cos(x) from [0, pi]
# Area of the rectangle(or area of the domain of the sample space) (width * height)
# we are sampling from [a,b], [-1,1], because cox(x) takes value between -1 and 1.
# at the end, the integration is the ratio of the (N_hits/N_gen)*Area_{sample space}

"""
import numpy as np

def hit_miss_mc_cos_integral(a, b, trials):
    count_hits = 0
    total_area = (b - a) * 2  

    for _ in range(trials):
        x = np.random.uniform(a, b)
        y = np.random.uniform(-1, 1)
        cos_x = np.cos(x)
        
        # Check if the point is under the curve
        #if (cos_x >= 0 and 0 <= y <= cos_x) or (cos_x < 0 and cos_x <= y <= 0):
        if y < cos_x:
            count_hits += 1

    # Estimate the integral
    estimate = (count_hits / trials) * total_area
    return estimate

# Example usage
a = 0
b = np.pi/2
trials = 100000
result = hit_miss_mc_cos_integral(a, b, trials)
print(f"Estimated integral of cos(x) from {a} to {b} is approximately {result}")
"""

import numpy as np
import matplotlib.pyplot as plt

def plot_hit_miss_mc_cos_integral(a, b, trials):
    total_area = (b - a) * 2  

    x_vals = np.linspace(a, b, 400)
    y_vals = np.cos(x_vals)
    
    x_rand = np.random.uniform(a, b, trials)
    y_rand = np.random.uniform(-1, 1, trials)

    hits_x = []
    hits_y = []
    misses_x = []
    misses_y = []

    for i in range(trials):
        x = x_rand[i]
        y = y_rand[i]
        cos_x = np.cos(x)
        
        # Determine if it's a hit or a miss
        if (cos_x >= 0 and 0 <= y <= cos_x) or (cos_x < 0 and cos_x <= y <= 0):
            hits_x.append(x)
            hits_y.append(y)
        else:
            misses_x.append(x)
            misses_y.append(y)

    count_hits = len(hits_x)
    
    # Estimate the integral
    estimate = (count_hits / trials) * total_area
    print(f"Area of the cox(x) between the interval is: {estimate}")


    # Plotting
    plt.figure(figsize=(10, 5))
    plt.plot(x_vals, y_vals, label='cos(x)', color='blue')
    plt.scatter(hits_x, hits_y, color='green', s=10, label='Hits', alpha=0.5)
    plt.scatter(misses_x, misses_y, color='red', s=10, label='Misses', alpha=0.5)
    plt.axhline(0, color='black', linewidth=0.5)
    plt.title('Hit and Miss Monte Carlo Integration of cos(x) from 0 to π')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.ylim(-1, 1)
    plt.xlim(a, b)
    plt.show()

# Parameters
a = 0
b = np.pi/2
trials = 10000  # Using a smaller number for clearer visualization

# Generate the plot
plot_hit_miss_mc_cos_integral(a, b, trials)


