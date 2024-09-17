// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#ifdef __CLING__
#include "MyHelpers.C+"
#endif

#include "Smoothing.h"

void SmoothingExample()
{
   TH1::AddDirectory(kFALSE);
#ifdef __CINT__
   gROOT->LoadMacro("MyHelpers.C");
#endif
   gROOT->SetStyle("ATLAS");

   // Set the x-axis range, 1 bin below and above, where possible.
   Double_t minval = 210.0, maxval = 4270.0;
   TString name = "";

   // Name of input file
   name = "DijetSystematicsExample.root";
   TFile file(name.Data(), "READ");

   // Location of output file and plots
   if (gSystem->mkdir("smoothed") == 0) {
      std::cout << "Made directory: \"smoothed/\"" << std::endl;
   } else {
      std::cout << "Directory \"smoothed/\" already exists." << std::endl;
   }

   name = TString::Format("smoothed/%s.root", name.Data());
   TFile output(name.Data(), "RECREATE");

   // Various useful variables
   Double_t maxup = 0.0, maxdown = 0.0;

   TH1D *temp      = NULL;
   TH1D *up        = NULL, *down        = NULL;
   TH1D *upsig     = NULL, *downsig     = NULL;
   TH1D *upfine    = NULL, *downfine    = NULL;
   TH1D *upsmooth  = NULL, *downsmooth  = NULL;

   // Loop over JES uncertainty components
   for (Int_t jes = 0; jes < 63; jes++) {

      // Get the positive portion of current uncertainty
      name = TString::Format("Syst_jes%d_p10_AU_R04_Eta1", jes);
      file.GetObject(name.Data(), temp);

      if (!temp) {
         Printf("Syst hist '%s' is not present in file", name.Data());
         return;
      }

      temp->SetName(name.Data());

      // Set the unused bins to 0.0
      up = new TH1D(*temp);
      smooth::RemoveUnused(up, minval, maxval, maxup);

      // Get the negative portion of current uncertainty
      name = TString::Format("Syst_jes%d_n10_AU_R04_Eta1", jes);
      file.GetObject(name.Data(), temp);

      if (!temp) {
         Printf("Syst hist '%s' is not present in file", name.Data());
         return;
      }
      temp->SetName(name.Data());

      // Set the unused bins to 0.0
      down = new TH1D(*temp);
      smooth::RemoveUnused(down, minval, maxval, maxdown);

      // If it's just floating point percision jitter from a component which is 0,
      // set it to zero, write, and continue.
      if (fabs(maxup) < 1e-6 && fabs(maxdown) < 1e-6) {
         Printf("exiting, too small");
         smooth::SetZero(up);
         smooth::SetZero(down);
         up->Write();
         down->Write();
         continue;
      }

      // Rebin the histogram by combining neighbors until all bins
      // are significant from 0.
      upsig   = smooth::RebinUntilSignificant(*up, minval, maxval);
      downsig = smooth::RebinUntilSignificant(*down, minval, maxval);

      // Return to fine binning, although with rebinned values.
      upfine   = smooth::RebinToFineTemplate(*upsig, *up);
      downfine = smooth::RebinToFineTemplate(*downsig, *down);

      // Perform Gaussian-kernel smoothing, if necessary
      // For the high-pT e/p uncertainty (comp 56), smoothing isn't neccessary,
      // and doesn't work well due to the steep shape.
      // Simply rebin into original bins here.
      // Note: passing "false" means the last bin won't be smoothed (useful in this case)
      if (jes == 56) {
         upsmooth   = upfine;
         downsmooth = downfine;
      } else {
         upsmooth   = smooth::GaussianKernelSmooth(*upfine, minval, maxval, false);
         downsmooth = smooth::GaussianKernelSmooth(*downfine, minval, maxval, false);
      }

      // Plot the original, rebinned, and smoothed spectra.
      smooth::PlotSyst(up, upsig, upsmooth, down, downsig, downsmooth, jes, minval, maxval, "#font[52]{m}_{12} [GeV]");

      // Write the smoothed spectra to output file.
      upsmooth->SetName(up->GetName());
      upsmooth->SetTitle(up->GetTitle());
      upsmooth->Write();

      downsmooth->SetName(down->GetName());
      downsmooth->SetTitle(down->GetTitle());
      downsmooth->Write();

   }

   output.Close();

}
