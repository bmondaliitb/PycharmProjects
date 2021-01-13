class Entity:
    # class constructor
    def __init__(self, name):
        print("Entity class constructed")
        self.name = str(name)

    def print(self):
        print("Hi {0}!".format(self.name))

#buddha = Entity("Buddha")