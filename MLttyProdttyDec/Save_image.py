import h5py

from main import *

def set_name(keys):
    if(len(keys) == 0):
        return "1"
    ints = [int(key) for key in keys]
    m = max(ints)
    return str(m+1)

# load the data from the main function
prodrootfiles = []
prodrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16a_TOPQ1_ttgamma_NLO_prod412112.1.root")
prodrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16d_TOPQ1_ttgamma_NLO_prod412112.1.root")
prodrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16e_TOPQ1_ttgamma_NLO_prod412112.1.root")

decrootfiles = []
decrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16a_TOPQ1_ttgamma_LO_dec412114.1.root")
decrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16d_TOPQ1_ttgamma_LO_dec412114.1.root")
decrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16e_TOPQ1_ttgamma_LO_dec412114.1.root")

# call the loop_over_files which returns a list of all shifted images
tty_prod_shifted_images = []
tty_dec_shifted_images = []

tty_prod_shifted_images = loop_over_files(prodrootfiles) # this is list of numpy array
tty_dec_shifted_images = loop_over_files(decrootfiles)

print("size of tty_prod sample: {}".format(len(tty_prod_shifted_images)))
print("size of tty_dec sample: {}".format(len(tty_dec_shifted_images)))

#print_array(tty_prod_shifted_images[0])
#print(tty_prod_shifted_images[0].shape)
npArrayProd = np.array(tty_prod_shifted_images)
npArrayDec = np.array(tty_dec_shifted_images)

# save images
outputpath_tty_prod = "tty_prod_event_images.h5"
outputpath_tty_dec = "tty_dec_event_images.h5"

with h5py.File(outputpath_tty_prod, "a") as f_prod:
    sname = set_name(f_prod.keys())
    dset = f_prod.create_dataset(sname, data=npArrayProd, chunks = True)

with h5py.File(outputpath_tty_dec, "a") as f_dec:
    sname = set_name(f_dec.keys())
    dset = f_dec.create_dataset(sname, data=npArrayDec, chunks = True)

