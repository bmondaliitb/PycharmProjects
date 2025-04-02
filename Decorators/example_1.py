#!/usr/bin/env python3
"""
A decorator is just a function that takes another function as an argument,
wraps it inside another function, and returns the wrapper function.
"""

def my_decorator(func):
    def wrapper():
        print("Something is happening before the function is called.")
        func()
        print("Something is happening after the function is called.")
    return wrapper

@my_decorator
def say_hello():
    print("Hello!")

say_hello()
