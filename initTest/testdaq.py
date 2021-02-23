#from directory import test, test_2
#print(test.file_path)
#print(test_2.file_path)
#test.run_1()
#test_2.run_2()

from directory.config import  config
config_obj = config
import directory.test # rodmaster
import directory.test_2 # rodslave
print(config.file_path)

from directory import test_4
test_4.run4()

