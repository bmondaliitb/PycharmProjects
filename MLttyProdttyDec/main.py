from ReadRootFile import *

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




def loop_over_files():
    # Open the root file with ReadRootFile class
    rootfiles = ["/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16a_TOPQ1_ttgamma_NLO_prod412112.1.root"]
    #rootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16d_TOPQ1_ttgamma_NLO_prod412112.1.root")
    #rootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16e_TOPQ1_ttgamma_NLO_prod412112.1.root")

    decrootfiles = ["/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16a_TOPQ1_ttgamma_LO_dec412114.1.root"]
    #decrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16d_TOPQ1_ttgamma_LO_dec412114.1.root")
    #decrootfiles.append("/home/bmondal/lxplus_server/eos/physics_analysis/tty/dilepton_mini_ntuple/mc16e_TOPQ1_ttgamma_LO_dec412114.1.root")

    hist = ROOT.TH2D("tty", "phi vs eta", 40, -4.0, 4.0, 40, -4.0, 4.0)
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
        for event in range(0,50):
            hist.Reset()
            hist.Fill(elmuph_eta[event][0], elmuph_phi[event][0], elmuph_pt[event][0])
            hist.Fill(elmuph_eta[event][1], elmuph_phi[event][1], elmuph_pt[event][1])
            hist.Fill(elmuph_eta[event][2], elmuph_phi[event][2], elmuph_pt[event][2])
            hist.Fill(elmuph_eta[event][3], elmuph_phi[event][3], elmuph_pt[event][3])
            hist.Fill(elmuph_eta[event][4], elmuph_phi[event][4], elmuph_pt[event][4])

            #c = ROOT.TCanvas("c")
            #hist.Draw("colztext")
            #c.Print("hist_{}.png".format(event))

    return hist


if __name__ == '__main__':
    print("রাং")
    hist = loop_over_files()
    # convert 2d hist to matrix
    image_operation = EtaPhiImage(hist)
    hist_matrix = image_operation.get_matrix() # hist matrix is a TMatrix type
    #pritn the matrix
    for i in range(0, 40):
        for j in range(0, 40):
            print(hist_matrix[i, j])

