import argparse
import os
import re

# creating a dictioanary class
class MergeFiles:

    def __init__(self):
        print ("Class constructed")

    def set_path(self, path=""):
        self.path = path
        if path == "":
            print ("Path is not set!!! path{0}: ".format(path))

    def create_dict(self):
        dict = {}

        # create dictionary for all the file types
        for subdir, subdirs, files in os.walk(self.path):
            # continue if it is subdirs
            if subdirs: continue

            #regex to extract same sample name
            regex_dsid = re.compile([0,9])

            # create a dictionary with all these files
            for file in files:

    def merge_files_of_same_sample(self):

    def print_dict(self):
        pass


# Press the green button in the gutter to run the script.
if __name__ == '__main__':

    parser = argparse.ArgumentParser(description="merge same sample files")
    # Addign arguments
    parser.add_argument('path', type = str, help = 'path to the directory containing files')

    args = parser.parse_args()

    # calling MargeFiles class
    merge_files = MergeFiles()
    merge_files.set_path(args.path)
    merge_files.create_dict()
    merge_files.print_dict()
    merge_files.merge_files_of_same_sample()
