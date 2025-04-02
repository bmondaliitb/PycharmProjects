class Gear2:
    def __init__(self):
        self.gear_state = "neutral"

    def engage(self):
        self.gear_state = "engaged"
        print("Gear2: Engaged.")

    def disengage(self):
        self.gear_state = "disengaged"
        print("Gear2: Disengaged.")
