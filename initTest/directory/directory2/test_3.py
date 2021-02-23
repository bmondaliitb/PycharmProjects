from directory.config import config

def run_3():
    print("file name paht {0}".format(config.file_path))
    config.file_path = "run_3"
    print("file name after run 3 paht {0}".format(config.file_path))
