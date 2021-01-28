import ROOT
import root_numpy
import numpy as np
import  math

class Histogramming:
    def __init__(self,histName):
        self.histName = histName

    def createHistogram(self, nBin, lowBin, highBin):
        hist = ROOT.TH1F(str(self.histName), str(self.histName), nBin, lowBin, highBin)
        hist.Sumw2()
        return hist

class EtaPhiImage:
    def __init__(self, hist):
        self.hist = hist
        #self.hist_matrix = ROOT.TMatrixD(40, 40, self.hist.GetArray(), "D")
        self.hist_matrix = root_numpy.hist2array(self.hist)
        self.hist_matrix = np.rot90(self.hist_matrix) #rotate by 90 degree

    def get_matrix(self):
        return self.hist_matrix

    ## taking pt and eta of the object
    ## I would want to shift to center
    def center_the_photon(self, eta, phi):
        centerX = 20
        centerY = 20
        eta = truncate((eta/0.2), 0)
        phi = truncate((phi/0.2), 0)
        phi = 40 - (centerY + int(phi) + 1)
        eta = centerX + int(eta)
        # the central bin is 20, 20
        self.hist_matrix[20][20] =  self.hist_matrix[phi][eta] # set the central bin with photon
        self.hist_matrix[phi][eta] = 0 # now set the original position of the photon to zero
        #print(self.hist_matrix[phi][eta])
        return self.hist_matrix

    def get_real_etaphi(self, eta, phi):
        centerX = 20
        centerY = 20
        eta = truncate((eta/0.2), 0)
        phi = truncate((phi/0.2), 0)
        phi = 40 - (centerY + int(phi) + 1)
        eta = centerX + int(eta)

        return eta, phi


    def get_the_coordinateShift(self, eta, phi):
        centerX = 20
        centerY = 20
        eta = truncate((eta / 0.2), 0)
        phi = truncate((phi / 0.2), 0)
        phi = 40 - (centerY + int(phi) + 1)
        eta = centerX + int(eta)
        eta_shift = 20 - eta
        phi_shift = 20 - phi
        return int(eta_shift), int(phi_shift)

    def shift_the_obj(self, shift_eta, shift_phi, eta, phi):
        self.hist_matrix[int(eta) - shift_eta][int(phi) - shift_phi] = self.hist_matrix[int(eta)][int(phi)] # shift the obj
        #self.hist_matrix[int(eta)][int(phi)] = 0 # reset previous value to 0
        #print(self.hist_matrix[int(eta) - shift_eta][int(phi) - shift_phi])
        #print(self.hist_matrix[int(eta)][int(phi)])
        return self.hist_matrix





class ReadRootFile:
    # constructor of this class
    def __init__(self, filePath):
        self.filePath = filePath
        self.fileName = ROOT.TFile.Open(self.filePath, "READ")

    # returns the tree from the root file
    def getTree(self, treeName):
        tree = self.fileName.Get(treeName)
        return tree

    def loopOverTree(self,tree, doStuff):

        print("number of entries in this tree: {}".format(tree.GetEntries()))
        for entryNum in range(0, tree.GetEntries()):
            tree.GetEntry(entryNum)
            doStuff()

    def getVarList(self, tree, var ):
        list = []
        for entryNum in range(0, tree.GetEntries()):
            tree.GetEntry(entryNum)
            # apply the cut
            ph_id_tight = getattr(tree, "ph_id_tight")
            ph_iso_FCT = getattr(tree, "ph_iso_FCT")
            ph_good_index = getattr(tree, "ph_good_index")
            el_var = "el_"+var
            mu_var = "mu_"+var
            ph_var = "ph_"+var
            jet_var = "jet_"+var
            el_var = getattr(tree, el_var)
            mu_var = getattr(tree, mu_var)
            ph_var = getattr(tree, ph_var)
            jet_var = getattr(tree, jet_var)

            emu_2015= getattr(tree, "emu_2015")
            emu_2016= getattr(tree, "emu_2016")
            emu_2017= getattr(tree, "emu_2017")
            emu_2018= getattr(tree, "emu_2018")
            ee_2015 = getattr(tree, "ee_2015")
            ee_2016 = getattr(tree, "ee_2016")
            ee_2017 = getattr(tree, "ee_2017")
            ee_2018 = getattr(tree, "ee_2018")
            mumu_2015 = getattr(tree, "mumu_2015")
            mumu_2016 = getattr(tree, "mumu_2016")
            mumu_2017 = getattr(tree, "mumu_2017")
            mumu_2018 = getattr(tree, "mumu_2018")

            if(not(ph_id_tight[ph_good_index[0]])): continue
            if(not(ph_iso_FCT[ph_good_index[0]])): continue

            #list of el,ph,mu info
            listobjects = []
            if(emu_2015 or emu_2016 or emu_2017 or emu_2018):
                listobjects.append(el_var[0])
                listobjects.append(mu_var[0])
                listobjects.append(ph_var[0])
                listobjects.append(jet_var[0])
                listobjects.append(jet_var[1])
            elif(ee_2015 or ee_2016 or ee_2017 or ee_2018):
                listobjects.append(el_var[0])
                listobjects.append(el_var[1])
                listobjects.append(ph_var[0])
                listobjects.append(jet_var[0])
                listobjects.append(jet_var[1])
            elif (mumu_2015 or mumu_2016 or mumu_2017 or mumu_2018):
                listobjects.append(mu_var[0])
                listobjects.append(mu_var[1])
                listobjects.append(ph_var[0])
                listobjects.append(jet_var[0])
                listobjects.append(jet_var[1])

            list.append(listobjects)

        return list


    def drawVariable(self, histname, variable):
        hist = ReadRootFile.loopOverTree(histname, variable)
        hist.Draw()


def truncate(f, n):
    return math.floor(f * 10 ** n) / 10 ** n