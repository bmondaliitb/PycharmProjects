from gear1 import Gear1
from gear2 import Gear2

class Engine:
    def __init__(self):
        self.status = "off"
        self.gear1 = Gear1()
        self.gear2 = Gear2()

    def start(self):
        self.status = "running"
        print("Engine: Started.")

    def stop(self):
        self.status = "stopped"
        print("Engine: Stopped.")

    def engage_gear1(self):
        if self.status == "running":
            self.gear1.engage()
        else:
            print("Engine: Cannot engage Gear1. Engine is off.")

    def engage_gear2(self):
        if self.status == "running":
            self.gear2.engage()
        else:
            print("Engine: Cannot engage Gear2. Engine is off.")
