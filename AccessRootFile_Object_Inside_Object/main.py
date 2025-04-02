import ROOT

# Open the ROOT file
file = ROOT.TFile("tty_pt_stat_scaled_4000ifb.root")

# List all objects in the file
file.ls()


# Get the canvas
canvas = file.Get("c1")  # Assuming "c1" is the TCanvas name
if not canvas:
    print("Canvas not found")
    exit()

# List objects in canvas
canvas.ls()


# Loop through pads inside the canvas
for pad in canvas.GetListOfPrimitives():
    if isinstance(pad, ROOT.TPad):  # Ensure it is a TPad
        print(f"Pad: {pad.GetName()}")
        pad.ls()  # List objects inside the pad
        
        # Step 4: Access objects inside the pad
        for obj in pad.GetListOfPrimitives():
            print(f"  Object: {obj.GetName()}, Type: {obj.ClassName()}")


# Example: Get a specific histogram from a pad
for pad in canvas.GetListOfPrimitives():
    if isinstance(pad, ROOT.TPad):
        for obj in pad.GetListOfPrimitives():
            if isinstance(obj, ROOT.TH1D):  # If object is a histogram
                print(f"Histogram Name: {obj.GetName()}")
                
                # Access histogram properties
                print(f"Entries: {obj.GetEntries()}, Mean: {obj.GetMean()}")
                
            elif isinstance(obj, ROOT.TGraphAsymmErrors):  # If object is a graph
                print(f"Graph Name: {obj.GetName()}, Points: {obj.GetN()}")
                
            elif isinstance(obj, ROOT.TLegend):  # If object is a legend
                print(f"Legend at ({obj.GetX1()}, {obj.GetY1()}) to ({obj.GetX2()}, {obj.GetY2()})")

