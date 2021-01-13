class Rectange:
    # constructor
    def __init__(self, length, width):
        self.length = length
        self.width = width
        print("A Rectangle instance with length {0} and width {1}".format(self.length, self.width))

    def perimeter(self):
        return 2*(self.length)*(self.width)

    def area(self):
        return (self.length)*(self.width)

    def about(self):
        print("This rectangle is has following values:")
        print("length {}".format(self.length))
        print("width {}".format(self.width))
        print("area {}".format(self.area()))
        print("perimeter {}".format(self.perimeter()))

