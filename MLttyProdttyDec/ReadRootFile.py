import ROOT

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
        self.hist_matrix = ROOT.TMatrixD(40+2, 40+2, self.hist.GetArray(), "D")

    def get_matrix(self):
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
        #for entryNum in range(0, tree.GetEntries()):
        for entryNum in range(0, 110):
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
