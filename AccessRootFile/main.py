from ROOT import  *

def open_root_file(rootfile, tree_name):
    file = TFile(rootfile)
    tree = file.Get(str(tree_name)) # access metadata tree
    tree.GetEntry(0)
    cutbookkeepers = getattr(tree, "CutBookkeepers")
#    for event in range (0, 1):
#        tree.GetEntry(event)
#        metadata = tree.MetaData.CutBookkeepers.name
#        print(type(metadata))

    return tree





# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    tree = open_root_file("/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/AnalysisTop/ContinuousIntegration/MC/p4174/mc16_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_TOPQ1.e6337_s3126_r9364_p4174/test.pool.root", "MetaData")


