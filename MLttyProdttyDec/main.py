from ReadRootFile import *
import root_numpy
import numpy as np
import  sys

class Event_variables:
    def __init__(self):
        self.ph_pt = 0
        self.ph_eta = 0
        self.ph_phi = 0
        self.lepton1_pt = 0
        self.lepton1_eta = 0
        self.lepton1_phi = 0
        self.lepton2_pt = 0
        self.lepton2_eta = 0
        self.lepton2_phi = 0




def loop_over_files(rootfiles):
    # Open the root file with ReadRootFile class


    hist = ROOT.TH2D("tty", "phi vs eta", 40, -4.0, 4.0, 40, -4.0, 4.0)
    #hist1 = ROOT.TH2D("tty", "phi vs eta", 60, -4.0, 4.0, 60, -4.0, 4.0)

    # make a list to return the final images in a list format
    shifted_images = []
    for file in rootfiles:
        rootfile_obj = ReadRootFile(file)
        treeNominal = rootfile_obj.getTree("nominal")  # get the nominal tree
        # get pt of lepton1 and lepton2 in form of list
        elmuph_pt = rootfile_obj.getVarList(treeNominal, "pt")  # it returns lists
        elmuph_eta = rootfile_obj.getVarList(treeNominal, "eta")  # it returns lists
        elmuph_phi = rootfile_obj.getVarList(treeNominal, "phi")  # it returns lists

        # printing size of eta and phi. they should be same
        print("size of eta {0}    size of phi {1}".format(len(elmuph_eta), len(elmuph_phi)))

        # make an image containing two leptons and ph in the eta phi space
        for event in range(0, treeNominal.GetEntries()):
            hist.Reset()
            hist.Fill(elmuph_eta[event][0], elmuph_phi[event][0], elmuph_pt[event][0])
            hist.Fill(elmuph_eta[event][1], elmuph_phi[event][1], elmuph_pt[event][1])
            hist.Fill(elmuph_eta[event][2], elmuph_phi[event][2], elmuph_pt[event][2])
            hist.Fill(elmuph_eta[event][3], elmuph_phi[event][3], elmuph_pt[event][3])
            hist.Fill(elmuph_eta[event][4], elmuph_phi[event][4], elmuph_pt[event][4])

            # convert 2d hist to matrix
            image_operation = EtaPhiImage(hist)
            hist_matrix = image_operation.get_matrix()
            # make a new array
            image = np.zeros((80, 80))
            #print(elmuph_pt[event][2])

            etaphoton, phiphoton = image_operation.get_real_etaphi(elmuph_eta[event][2], elmuph_phi[event][2]) # original eta and phi of photon
            shift_etaphoton, shift_phiphoton = image_operation.get_the_coordinateShift(elmuph_eta[event][2],
                                                                           elmuph_phi[event][2])
            for obj in range(0, 5):
                eta, phi = image_operation.get_real_etaphi(elmuph_eta[event][obj], elmuph_phi[event][obj])
                #print("shift eta: {} shift phi {}".format(shift_etaphoton, shift_phiphoton))
                #print(hist_matrix[phi][eta])

                image[phi + shift_phiphoton +20 ][eta + shift_etaphoton + 20] = hist_matrix[phi][eta] # make new image with shifted entries

            shifted_images.append(image)

    return shifted_images



def print_array(hist_matrix):
    for row in range(0,80):
       for col in range(0,80):
           #if(not(hist_matrix[row][col] == 0)):
           print("{:4}".format(hist_matrix[row][col]), end=' ')
           #    print("row: {} col {}".format(row, col))
       print()

def save_images(image, hist1, eventnumber):
    root_numpy.array2hist(image, hist1) # this converts numpy array to histogram
    c = ROOT.TCanvas("c")
    hist1.Draw("colztext")
    c.Print("hist_{}.png".format(eventnumber)) # to print this histogram



if __name__ == '__main__':
    print("রাং")
    rootfiles = ["/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16a_TOPQ1_ttgamma_NLO_prod412112.1.root"]
    #rootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16d_TOPQ1_ttgamma_NLO_prod412112.1.root")
    #rootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16e_TOPQ1_ttgamma_NLO_prod412112.1.root")

    decrootfiles = ["/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16a_TOPQ1_ttgamma_LO_dec412114.1.root"]
    #decrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16d_TOPQ1_ttgamma_LO_dec412114.1.root")
    #decrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16e_TOPQ1_ttgamma_LO_dec412114.1.root")

    shifted_images = loop_over_files(rootfiles)
