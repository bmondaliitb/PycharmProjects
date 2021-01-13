# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

# Python3 program to
# demonstrate instantiating
# a class

# Python3 program to show that we can create
# instance variables inside methods

#================== IMPORTANT ============================
# There are two types of varialbes:
#      class variables and instance variables
# when you create an instance of a class then the __init__ gets executed, its like
# a constructor of a class

# But on the other hand class variables can be accessed without creating a class
# instance. This is common across the all class instances, its like static. if you
# update this in one place it gets updated in all the instances.

# To use this class variable inside the class method you can use Class.classVariable
# the use is same everywhere.

# Instance varialbes are owned by instances of the class. This means that for each object
# or instance of a class, the instance variables are different.
# Unlike class variables instance variables are defined within the methods.




#==============================================================================


# Class for Dog
class Dog:
    # Class Variable
    animal = 'dog'

    # The init method or constructor
    def __init__(self, breed):
        # Instance Variable
        self.breed = breed

    # Adds an instance variable
    def setColor(self, color):
        self.color = color

    # Retrieves instance variable
    def getColor(self):
        return self.color

    # print the state of the animal
    def printAnimal(self):
        print("The {0} is of breed {1} and of color {2}".format(Dog.animal, self.breed, self.color))


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # Driver Code

    Rodger = Dog("pug")
    Rodger.setColor("brown")
    print (Dog.animal)
    Rodger.printAnimal()
