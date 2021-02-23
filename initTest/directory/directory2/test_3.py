import directory.__init__  as init

def run_3():
    print("in test_3/run_3():   file name paht {0}".format(init.file_path))
    init.file_path = "run_3"
    print("in test_3/run_3():  file name after run 3 paht {0}".format(init.file_path))
