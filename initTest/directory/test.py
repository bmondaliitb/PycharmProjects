#from directory import file_path, set_path
#print("value global in test filename :{0}".format(file_path))
#file_path = "run_1"
#set_path(5)


#def run_1():
#    print("value of filename {0}".format(directory.test.filepath))
#    filepath = "run_1"
#    print("value after chaning filename {0}".format(file_path))


from directory.config import config
print("value in config: {0}".format(config.file_path))
config.file_path = "test"