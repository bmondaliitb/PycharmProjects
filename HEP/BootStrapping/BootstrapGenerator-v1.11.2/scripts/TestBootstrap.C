// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#ifdef __CLING__
R__LOAD_LIBRARY(libBootstrapGenerator.so)
#endif

#include "BootstrapGenerator/BootstrapGenerator.h"
#include "BootstrapGenerator/TH1DBootstrap.h"

#include <cstdio>

#include "TH2D.h"
#include "TRandom.h"
#include "TVector3.h"
#include "TFile.h"
#include "TStopwatch.h"

void TestBootstrap()
{

  Int_t nrep = 1000, nevent = 100000;

  // Book a generator:
  BootstrapGenerator* gen  = new BootstrapGenerator("Gen", "Gen", nrep);

  // Store results:
  TFile f("bs.root","recreate");

  // Book bootstraped histogram:
  TH1DBootstrap *e  = new TH1DBootstrap("P","P",10,0.,10., nrep, gen);
  TH1D      *ehist  = new TH1D("Phist","Phist",10,0.,10.);
  TH1DBootstrap *pt = new TH1DBootstrap("Pt","Pt",10,0.,10., nrep, gen);
  // For "efficiency" too:
  TH1DBootstrap *ef = new TH1DBootstrap("Pe","Pe",10,0.,10., nrep, gen);
  
  // "Systematics"
  TH1DBootstrap *ptu = new TH1DBootstrap("Ptu","Ptu",10,0.,10., nrep, gen);
  TH1DBootstrap *ptd = new TH1DBootstrap("Ptd","Ptd",10,0.,10., nrep, gen);

  // And 2D
  TH2D *ept         = new TH2D("Ppt","PPt",10,0.,10.,10,0.,10.);

  // Generate particles with E between 0 and 10 at random angles:
  TRandom*Rnd = new TRandom();
 
  TStopwatch timegen;
  TStopwatch timefill;
  TStopwatch timerep;

  for ( int i=1; i<nevent; i++) {
    if ( i % 10000 == 0) {
      printf("Passing %d events\n",i);      
    }
    
    
    double p = Rnd->Rndm()*10.;
    double phi = 2*3.141592*Rnd->Rndm();
    double th  = 3.141592*Rnd->Rndm();

    // Detection "efficiency"
    double eff = Rnd->Rndm();

    TVector3 part = TVector3(p*cos(phi)*cos(th),p*sin(phi)*cos(th),p*sin(th));

    // "Systematics"
    TVector3 partU = 1.01*part;
    TVector3 partD = 0.99*part;

    // Update weights:
    timegen.Start(kFALSE);
    gen->Generate(219305,i);
    timegen.Stop();

    // Fill bootstraps
    timefill.Start(kFALSE);
    ehist->Fill(part.Mag(), 1.0);
    timefill.Stop();

    timerep.Start(kFALSE);
    e->Fill(part.Mag(),1.0);
    timerep.Stop();

    // 90% recon. efficiency:
    if (eff > 0.1) {
      ef->Fill(part.Mag(),1.0);
    }

    pt->Fill(part.Pt(),1.0);
    // Systematics:
    ptu->Fill(partU.Pt(),1.0);
    ptd->Fill(partD.Pt(),1.0);

    ept->Fill(part.Mag(),part.Pt(),1.0);

  }

  Printf("Time spent generating:");
  timegen.Print("all");
  Printf("Time spent filling nominal:");
  timefill.Print("all");
  Printf("Time spent filling replicas:");
  timerep.Print("all");

  for (int i=1; i<=10; i++) {
    double vb = e->GetBootstrapMean(i);
    double eb = e->GetBootstrapRMS(i);
    double vs = e->GetNominal()->GetBinContent(i);
    double es = e->GetNominal()->GetBinError(i);
    printf("Value = %7.1f bootstrap value= %7.1f Error = %7.1f bootstrap RMS = %7.1f \n",vs,vb,es,eb);
  }
  for (int i=1; i<=10; i++) {
    double vb = pt->GetBootstrapMean(i);
    double eb = pt->GetBootstrapRMS(i);
    double vs = pt->GetNominal()->GetBinContent(i);
    double es = pt->GetNominal()->GetBinError(i);
    printf("Value = %7.1f bootstrap value= %7.1f Error = %7.1f bootstrap RMS = %7.1f \n",vs,vb,es,eb);
  }

  TH2D* cc= new TH2D("cor","cor",10,0,10.,10,0,10.);

  
  for (int i=1; i<=10; i++) {
    for (int j=1; j<=10; j++) {
      double cor = e->GetBootstrapCorel(i,*pt,j);

      cc->Fill(i-0.5,j-0.5,cor);
    }
  }
  
  // Calculate efficiency with proper uncertrainty:
  TH1DBootstrap *rat = new TH1DBootstrap(*ef);
  rat->SetName("eff");
  rat->SetTitle("eff");
  rat->Divide(e);
  rat->SetErrBootstrapRMS();

  // Calculate systematics with stat. uncertainty:
  ptu->Add(pt,-1.);
  ptd->Add(pt,-1.);
  ptu->Divide(pt);
  ptd->Divide(pt);

  // Also get uncertainty asymmetry with proper stat. uncertainty:
  TH1DBootstrap *asy = new TH1DBootstrap(*ptu);
  asy->SetName("asy");
  asy->SetTitle("asy");
  asy->Add(ptd,1.);
  
  ptu->SetErrBootstrapRMS();
  ptd->SetErrBootstrapRMS();
  asy->SetErrBootstrapRMS();

  // Save plain histograms
  TH1* eresult = e->GetBootstrapResult();

  // Store in a file:
  e->Write();
  eresult->Write();
  ef->Write();
  pt->Write();
  rat->Write();
  ept->Write();
  cc->Write();
  ptu->Write();
  ptd->Write();
  asy->Write();
}
