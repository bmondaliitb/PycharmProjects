"""
A common and useful example of a decorator is logging—where
we log the execution details of a function, including its name, arguments, and execution time.
"""
import time
import functools


def log_execution(func):
    """A decorator that logs function execution details."""
    @functools.wraps(func)  # Preserves the original function name and docstring
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        print(f"Function '{func.__name__}' called with {args}, {kwargs}")
        print(f"Execution time: {end_time - start_time:.4f} seconds")
        return result
    return wrapper

# Using the decorator
@log_execution
def add(a, b):
    """Returns the sum of two numbers."""
    time.sleep(1)  # Simulate a delay
    return a + b

@log_execution
def greet(name="Guest"):
    """Greets a person."""
    print(f"Hello, {name}!")

# Calling the decorated functions
print(add(5, 10))
greet("Alice")
