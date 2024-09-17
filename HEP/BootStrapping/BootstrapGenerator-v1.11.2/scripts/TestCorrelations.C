// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#ifdef __CLING__
R__LOAD_LIBRARY(libBootstrapGenerator.so)
#endif

#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"

void TestCorrelations()
{
#ifdef __CINT__
   gSystem->AddIncludePath(" -I../");
   gSystem->AddIncludePath(" -I../BootstrapGenerator/");
   gROOT->LoadMacro("../Root/BootstrapGenerator.cxx+");
   gROOT->LoadMacro("../Root/TH1Bootstrap.cxx+");
#endif

   TFile *file = NULL;

   // Get the first measurements TH1DBootstrap (could be multiple spectra)
   file = new TFile("bootstrap_incjet.root", "READ");
   TH1DBootstrap *corr = NULL, *temp = NULL;
   file->GetObject("IDSresult_bootstrap_R04_Eta1", temp);

   if (temp == NULL) {
      Printf("Couldn't find inclusive jet bootstrap, exiting.");
      return;
   }

   corr = new TH1DBootstrap(*temp); // Copy to correlation bootstrap

   file->Close(); delete file;

   // Get the second measurements TH1DBootstrap (could be multiple spectra)
   file = new TFile("bootstrap_dijet.root", "READ");
   file->GetObject("IDSresult_bootstrap_R04_Eta1", temp);

   if (temp == NULL) {
      Printf("Couldn't find dijet bootstrap, exiting.");
      return;
   }

   corr->Append(*temp);

   file->Close(); delete file;

   // Get the third measurements TH1DBootstrap (could be multiple spectra)
   file = new TFile("bootstrap_trijet.root", "READ");
   file->GetObject("IDSresult_bootstrap_R04_ystar_00_20", temp);

   if (temp == NULL) {
      Printf("Couldn't find trijet bootstrap, exiting.");
      return;
   }

   corr->Append(*temp);

   file->Close(); delete file;

   // Get covariance / correlation matrices
   TMatrixD *covmatrix = corr->GetCovarianceMatrix();
   TH2D h2(*corr->GetCorrelationMatrix());

   TCanvas c("c", "c", 800, 800);
   h2.Draw("colz");
   c.SaveAs("correlations.png");
}
