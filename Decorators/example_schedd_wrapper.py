from typing import Callable, Any

class ScheddWrapper:
    def __init__(self):
        self.status = "active"

def schedd_check(func: Callable[["ScheddWrapper"], Any]):  # type: ignore
    def wrapper(schedd: "ScheddWrapper"):
        if schedd.status != "active":
            raise ValueError("Scheduler is not active")
        return func(schedd)  # Call the original function
    return wrapper

@schedd_check
def run_job(schedd: "ScheddWrapper"):
    print("Job is running...")

# Example usage
schedd = ScheddWrapper()
run_job(schedd)  # This will execute without issue

