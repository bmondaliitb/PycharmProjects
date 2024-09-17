// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#ifdef __CLING__
R__LOAD_LIBRARY(libBootstrapGenerator.so)
#endif

#include "BootstrapGenerator/BootstrapGenerator.h"
#include "BootstrapGenerator/TH1DBootstrap.h"
#include "BootstrapGenerator/TH2DBootstrap.h"

#include <cstdio>

#include "TH2D.h"
#include "TRandom.h"
#include "TVector3.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TSVDUnfold.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLegend.h"

void UnfoldingExample()
{

   Int_t nrep = 1000, nevent = 100000;

   // Book a generator:
   BootstrapGenerator* gen  = new BootstrapGenerator("Gen", "Gen", nrep);

   // Transfer matrix
   TH2DBootstrap *Adet = new TH2DBootstrap("Adet", "Adet", 10, 0., 10., 10, 0., 10., nrep, gen);

   // Spectra
   TH1DBootstrap *xini = new TH1DBootstrap("xini", "xini", 10, 0., 10., nrep, gen); // Truth spectra
   TH1DBootstrap *bini = new TH1DBootstrap("bini", "bini", 10, 0., 10., nrep, gen); // Reco spectra
   TH1DBootstrap *bdat = new TH1DBootstrap("bini", "bini", 10, 0., 10., nrep, gen); // Data spectra

   // "Systematics"
   TH1DBootstrap *bdatU = new TH1DBootstrap("bdatU", "bdatU", 10, 0., 10., nrep, gen); // Systematic shifts of data Up and
   TH1DBootstrap *bdatD = new TH1DBootstrap("bdatD", "bdatD", 10, 0., 10., nrep, gen); // Down

   // Generate particles with E between 0 and 10 at random angles:
   TRandom *rnd = new TRandom();
 
   for (Int_t i = 1; i < nevent; i++) {
      if (i % 10000 == 0) {
         printf("Passing %d events\n",i);      
      }
      
      Double_t p = rnd->Rndm(1.0)*10.;
      Double_t phi = TMath::TwoPi()*rnd->Rndm();
      Double_t th  = TMath::Pi()*rnd->Rndm();

      // Detector "smearing"
      Double_t psmear = rnd->Gaus(0.98, 0.1); // bias 2%, smear 10%
      Double_t phismear = rnd->Gaus(1., 0.01); // smear 1%
      Double_t thsmear = rnd->Gaus(1., 0.01); // smear 1%

      TVector3 part(p*cos(phi)*cos(th), p*sin(phi)*cos(th), p*sin(th));
      TVector3 reco(psmear*p*cos(phismear*phi)*cos(thsmear*th),
                    psmear*p*sin(phismear*phi)*cos(thsmear*th),
                    psmear*p*sin(thsmear*th));

      // "Systematics" shift of 1%
      TVector3 recoU = 1.01*reco;
      TVector3 recoD = 0.99*reco;

      // Update weights:
      gen->Generate(219305, i);

      xini->Fill(part.Pt(), 1.0);
      if (rnd->Rndm() > 0.05) { // 5% inefficiency in detector reconstruction
         Adet->Fill(reco.Pt(), part.Pt());
         bini->Fill(reco.Pt(), 1.0);
         if (rnd->Rndm() < 0.2) { // Only 20% of the events make the "data" spectrum
            bdat->Fill(reco.Pt(), 1.0);
            bdatU->Fill(recoU.Pt(), 1.0);
            bdatD->Fill(recoD.Pt(), 1.0);
         }
      }

   }

   // Unfolding result
   TH1D  *unfres = NULL;
   TH1D  *unfresU = NULL;
   TH1D  *unfresD = NULL;

   // Unfolding replicas results
   TH1D **unfrep = new TH1D*[nrep];
   TH1D **unfrepU = new TH1D*[nrep];
   TH1D **unfrepD = new TH1D*[nrep];

   // Nominal unfolding
   TSVDUnfold *tsvdunf = new TSVDUnfold((TH1D*)bdat->GetNominal(),
                                        (TH1D*)bini->GetNominal(),
                                        (TH1D*)xini->GetNominal(),
                                        (TH2D*)Adet->GetNominal());
   unfres = tsvdunf->Unfold(6.0); // use kreg = 6.0
   delete tsvdunf;

   tsvdunf = new TSVDUnfold((TH1D*)bdatU->GetNominal(),
                            (TH1D*)bini->GetNominal(),
                            (TH1D*)xini->GetNominal(),
                            (TH2D*)Adet->GetNominal());
   unfresU = tsvdunf->Unfold(6.0); // use kreg = 6.0
   unfresU->Add(unfres, -1); // Make bootstrap of the difference to get error on systematic
   delete tsvdunf;

   tsvdunf = new TSVDUnfold((TH1D*)bdatD->GetNominal(),
                            (TH1D*)bini->GetNominal(),
                            (TH1D*)xini->GetNominal(),
                            (TH2D*)Adet->GetNominal());
   unfresD = tsvdunf->Unfold(6.0); // use kreg = 6.0
   unfresD->Add(unfres, -1); // Make bootstrap of the difference to get error on systematic
   delete tsvdunf;

   // Replica unfolding
   for (Int_t i = 0; i < nrep; ++i) {
      tsvdunf = new TSVDUnfold((TH1D*)bdat->GetReplica(i),
                               (TH1D*)bini->GetReplica(i), // Use replicas of transfer matrix so that
                               (TH1D*)xini->GetReplica(i), // MC uncertainty is included.
                               (TH2D*)Adet->GetReplica(i));
      unfrep[i] = tsvdunf->Unfold(6.0);
      delete tsvdunf;

      tsvdunf = new TSVDUnfold((TH1D*)bdatU->GetReplica(i),
                               (TH1D*)bini->GetNominal(),
                               (TH1D*)xini->GetNominal(),
                               (TH2D*)Adet->GetNominal());
      unfrepU[i] = tsvdunf->Unfold(6.0);
      unfrepU[i]->Add(unfrep[i], -1); // Make bootstrap of the difference to get error on systematic
      delete tsvdunf;

      tsvdunf = new TSVDUnfold((TH1D*)bdatD->GetReplica(i),
                               (TH1D*)bini->GetNominal(),
                               (TH1D*)xini->GetNominal(),
                               (TH2D*)Adet->GetNominal());
      unfrepD[i] = tsvdunf->Unfold(6.0);
      unfrepD[i]->Add(unfrep[i], -1); // Make bootstrap of the difference to get error on systematic
      delete tsvdunf;
   }

   // Collect unfolded result with synchornized replicas
   TH1DBootstrap *unfboot  = new TH1DBootstrap("result", "result", unfres, unfrep, nrep);
   unfboot->SetErrBootstrapRMS(); // Only containts statistical error from data in this example

   // Determine error on systematic shift error
   TH1DBootstrap *unfbootU = new TH1DBootstrap("relSysUp", "sysUp", unfresU, unfrepU, nrep);
   TH1DBootstrap *unfbootD = new TH1DBootstrap("relSysDown", "sysDown", unfresD, unfrepD, nrep);

   unfbootU->SetErrBootstrapRMS();
   unfbootU->Divide(unfboot); // make it relative

   unfbootD->SetErrBootstrapRMS();
   unfbootD->Divide(unfboot);

   // Save unfolded result, with synchronized replicas
   TFile file("unfold.root", "RECREATE");
   unfboot->Write();
   ((TH1D*)unfbootU->GetNominal())->Write();
   ((TH1D*)unfbootD->GetNominal())->Write();
   file.Close();

   // Make a plot showing things work
   TCanvas c("c", "c", 600, 600);

   xini->Scale(1.0/5.0);
   xini->GetNominal()->SetLineColor(kRed);
   xini->GetNominal()->Draw("hist");

   unfboot->GetNominal()->SetLineColor(kBlue);
   unfboot->GetNominal()->Draw("hist same");

   bdat->GetNominal()->Draw("hist same");

   TLegend legunf(0.5, 0.75, 0.9, 0.90);
   legunf.AddEntry(xini->GetNominal(), "True spectra", "l");
   legunf.AddEntry(bdat->GetNominal(), "Reco spectra", "l");
   legunf.AddEntry(unfboot->GetNominal(), "Unfolded spectra", "l");
   legunf.Draw();

   c.SaveAs("unfolding.png");

   TH2D axis("axis", "axis", 1, 0, 10, 1, -0.10, 0.10);
   axis.Draw("axis");

   unfbootU->GetNominal()->SetMarkerStyle(1);
   unfbootU->GetNominal()->SetMarkerColor(kRed);
   unfbootU->GetNominal()->SetLineColor(kRed);
   unfbootU->GetNominal()->Draw("pe same");

   unfbootD->GetNominal()->SetMarkerStyle(1);
   unfbootD->GetNominal()->SetMarkerColor(kBlue);
   unfbootD->GetNominal()->SetLineColor(kBlue);
   unfbootD->GetNominal()->Draw("pe same");

   TLegend legsys(0.2, 0.80, 0.6, 0.90);
   legsys.AddEntry(unfbootU->GetNominal(), "Positive uncertainty shift", "lpe");
   legsys.AddEntry(unfbootD->GetNominal(), "Negative uncertainty shfit", "lpe");
   legsys.Draw();

   c.SaveAs("syserr.png");
   
   delete unfboot; 
}
