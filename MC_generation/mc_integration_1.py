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


"""
Example 2
An illustration of Monte Carlo integration. In this example, the domain D is the inner circle and the domain E is the square. Because the square's area (4) can be easily calculated, the area of the circle (π*1.02) can be estimated by the ratio (0.8) of the points inside the circle (40) to the total number of points (50), yielding an approximation for the circle's area of 4*0.8 = 3.2 ≈ π.
"""

from numpy import random
import numpy as np

throws = 2000
inside_circle = 0
i = 0
radius = 1
while i < throws:
    # Choose random X and Y centered around 0,0
    x = random.uniform(-radius, radius)
    y = random.uniform(-radius, radius)
    # If the point is inside circle, increase variable
    if x**2 + y**2 <= radius**2:
        inside_circle += 1
    i += 1

# Calculate area and print; should be closer to Pi with increasing number of throws
area = (((2 * radius) ** 2) * inside_circle) / throws
print(area)
