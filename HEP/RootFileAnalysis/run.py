from engine import Engine

class Run:
    def __init__(self):
        self.engine = Engine()

    def run_sequence(self):
        print("Run: Starting sequence...")
        self.engine.start()
        self.engine.engage_gear1()
        self.engine.engage_gear2()
        print("Run: Sequence completed.")

    def stop_sequence(self):
        print("Run: Stopping sequence...")
        self.engine.stop()
