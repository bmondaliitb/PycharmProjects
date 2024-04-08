"""
Monte Carlo methods vary, but tend to follow a particular pattern:

Define a domain of possible inputs
Generate inputs randomly from a probability distribution over the domain
Perform a deterministic computation on the inputs
Aggregate the results

Monte Carlo method applied to approximating the value of π
For example, consider a quadrant (circular sector) inscribed in a unit square. Given that the ratio of their areas is π/4
, the value of π can be approximated using a Monte Carlo method:

Draw a square, then inscribe a quadrant within it
Uniformly scatter a given number of points over the square
Count the number of points inside the quadrant, i.e. having a distance from the origin of less than 1
The ratio of the inside-count and the total-sample-count is an estimate of the ratio of the two areas, 
π/4. Multiply the result by 4 to estimate π.
"""



import random

def approximate_pi(num_samples):
    """
    Approximate the value of π using the Monte Carlo method.

    Parameters:
    - num_samples: The number of random points to generate.

    Returns:
    - The approximate value of π.
    """
    inside_count = 0

    for _ in range(num_samples):
        # Generate random x, y points in the range [-1, 1]
        x, y = random.uniform(-1, 1), random.uniform(-1, 1)
        
        # Check if the point is inside the quadrant
        if x**2 + y**2 <= 1:
            inside_count += 1

    # The ratio of inside_count to num_samples is approximately π/4
    pi_estimate = 4 * inside_count / num_samples
    return pi_estimate

# Example usage
num_samples = 1000000  # Number of samples
estimated_pi = approximate_pi(num_samples)
print(f"Estimated π with {num_samples} samples: {estimated_pi}")

