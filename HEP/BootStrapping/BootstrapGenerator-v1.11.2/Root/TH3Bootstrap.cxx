// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#ifndef BootstrapGenerator_h
#include "BootstrapGenerator/BootstrapGenerator.h"
#endif

#ifndef TH3Bootstrap_h
#include "BootstrapGenerator/TH3Bootstrap.h"
#endif

#ifndef ROOT_TH3D
#include "TH3D.h"
#endif

#ifndef ROOT_TString
#include "TString.h"
#endif

ClassImp(TH3Bootstrap)

//______________________________________________________________________________
TH3Bootstrap::TH3Bootstrap()
: TH1Bootstrap()
{ }

//______________________________________________________________________________
TH3Bootstrap::TH3Bootstrap(const TH3Bootstrap &h3b)
: TH1Bootstrap(h3b)
{ }

//______________________________________________________________________________
TH3Bootstrap::TH3Bootstrap(const char *name, const char *title, Int_t nreplica, BootstrapGenerator *boot)
: TH1Bootstrap(name, title, nreplica, boot)
{ }

//______________________________________________________________________________
TH3Bootstrap::~TH3Bootstrap()
{ }

//______________________________________________________________________________
Int_t TH3Bootstrap::Fill(Double_t x, Double_t y, Double_t z, Double_t w, UInt_t RunNumber, UInt_t EventNumber, UInt_t mc_channel_number)
{
   if (fOwnGen) fGenerator->Generate(RunNumber, EventNumber, mc_channel_number);
   const Int_t *BSWeights = fGenerator->GetWeights();
   for (Int_t i = 0; i < fNReplica; ++i) {
      for (Int_t j = 0; j < BSWeights[i]; ++j) {
         static_cast<TH3*>(GetReplica(i))->Fill(x, y, z, w);
      }
   }
   return static_cast<TH3*>(GetNominal())->Fill(x, y, z, w);
}

//______________________________________________________________________________
Double_t TH3Bootstrap::GetBootstrapMean(Int_t binx, Int_t biny, Int_t binz) const
{ return TH1Bootstrap::GetBootstrapMean(GetNominal()->GetBin(binx, biny, binz)); }

//______________________________________________________________________________
Double_t TH3Bootstrap::GetBootstrapRMS(Int_t binx, Int_t biny, Int_t binz) const
{ return TH1Bootstrap::GetBootstrapRMS(GetNominal()->GetBin(binx, biny, binz)); }

//______________________________________________________________________________
Double_t TH3Bootstrap::GetBootstrapCorel(Int_t binx1, Int_t biny1, Int_t binz1, Int_t binx2, Int_t biny2, Int_t binz2) const
{ return TH1Bootstrap::GetBootstrapCorel(GetNominal()->GetBin(binx1, biny1, binz1), GetNominal()->GetBin(binx2, biny2, binz2)); }

//______________________________________________________________________________
Double_t TH3Bootstrap::GetBootstrapCorel(Int_t binx1, Int_t biny1, Int_t binz1, const TH1Bootstrap &h3, Int_t binx2, Int_t biny2, Int_t binz2) const
{ return TH1Bootstrap::GetBootstrapCorel(GetNominal()->GetBin(binx1, biny1, binz1), h3, GetNominal()->GetBin(binx2, biny2, binz2)); }

//______________________________________________________________________________
TH1DBootstrap* TH3Bootstrap::ProjectionX(const char *name, Int_t firstybin, Int_t lastybin, Int_t firstzbin, Int_t lastzbin, Option_t *option) const
{
   return (TH1DBootstrap*)DoProjection(1, name, 0, -1, firstybin, lastybin, firstzbin, lastzbin, Form("x%s",option));
}
//______________________________________________________________________________
TH1DBootstrap* TH3Bootstrap::ProjectionY(const char *name, Int_t firstxbin, Int_t lastxbin, Int_t firstzbin, Int_t lastzbin, Option_t *option) const
{
   return (TH1DBootstrap*)DoProjection(1, name, firstxbin, lastxbin, 0, -1, firstzbin, lastzbin, Form("y%s",option));
}
//______________________________________________________________________________
TH1DBootstrap* TH3Bootstrap::ProjectionZ(const char *name, Int_t firstxbin, Int_t lastxbin, Int_t firstybin, Int_t lastybin, Option_t *option) const
{
   return (TH1DBootstrap*)DoProjection(1, name, firstxbin, -lastxbin, firstybin, lastybin, 0, -1, Form("z%s",option));
}
//______________________________________________________________________________
TH2DBootstrap* TH3Bootstrap::ProjectionXY(const char *name, Int_t firstzbin, Int_t lastzbin, Option_t *option) const
{
   return (TH2DBootstrap*)DoProjection(2, name, 0, -1, 0, -1, firstzbin, lastzbin, Form("yx%s",option)); // x on horizontal axis, y on vertical axis
}
//______________________________________________________________________________
TH2DBootstrap* TH3Bootstrap::ProjectionYZ(const char *name, Int_t firstxbin, Int_t lastxbin, Option_t *option) const
{
   return (TH2DBootstrap*)DoProjection(2, name, firstxbin, lastxbin, 0, -1, 0, -1, Form("zy%s",option)); // y on horizontal axis, z on vertical axis
}
//______________________________________________________________________________
TH2DBootstrap* TH3Bootstrap::ProjectionXZ(const char *name, Int_t firstybin, Int_t lastybin, Option_t *option) const
{
   return (TH2DBootstrap*)DoProjection(2, name, 0, -1, firstybin, lastybin, 0, -1, Form("zx%s",option)); // x on horizontal axis, z on vertical axis
}
//______________________________________________________________________________
TH1Bootstrap* TH3Bootstrap::DoProjection(int dimension, const char *name, Int_t firstxbin, Int_t lastxbin, Int_t firstybin, Int_t lastybin, Int_t firstzbin, Int_t lastzbin, Option_t *option) const
{
   if(dimension != 1 && dimension != 2)
   {
     Printf("wrong output dimension\n");
     return 0;
   }
   // save initial histogram ranges.
   int init_firstxbin = GetNominal()->GetXaxis()->GetFirst();
   int init_lastxbin  = GetNominal()->GetXaxis()->GetLast();
   int init_firstybin = GetNominal()->GetXaxis()->GetFirst();
   int init_lastybin  = GetNominal()->GetXaxis()->GetLast();
   int init_firstzbin = GetNominal()->GetZaxis()->GetFirst();
   int init_lastzbin  = GetNominal()->GetZaxis()->GetLast();

   // create the nominal histogram
   TH1 *proj_nom = 0;
   static_cast<TH3*>((TH1*)GetNominal())->GetXaxis()->SetRange(firstxbin,lastxbin);
   static_cast<TH3*>((TH1*)GetNominal())->GetYaxis()->SetRange(firstybin,lastybin);
   static_cast<TH3*>((TH1*)GetNominal())->GetZaxis()->SetRange(firstzbin,lastzbin);
   proj_nom = static_cast<const TH3*>(GetNominal())->Project3D(option);
   proj_nom->SetDirectory(0);
   static_cast<TH3*>((TH1*)GetNominal())->GetXaxis()->SetRange(init_firstxbin,init_lastxbin);
   static_cast<TH3*>((TH1*)GetNominal())->GetYaxis()->SetRange(init_firstybin,init_lastybin);
   static_cast<TH3*>((TH1*)GetNominal())->GetZaxis()->SetRange(init_firstzbin,init_lastzbin);

   // create the replica histograms
   Int_t nreps = GetNReplica();
   TH1 **proj_reps = new TH1*[nreps];
   for (Int_t i = 0; i < nreps; ++i) {
      static_cast<TH3*>((TH1*)GetReplica(i))->GetXaxis()->SetRange(firstxbin,lastxbin);
      static_cast<TH3*>((TH1*)GetReplica(i))->GetYaxis()->SetRange(firstybin,lastybin);
      static_cast<TH3*>((TH1*)GetReplica(i))->GetZaxis()->SetRange(firstzbin,lastzbin);
      proj_reps[i] = static_cast<const TH3*>(GetReplica(i))->Project3D(option);
      proj_reps[i]->SetDirectory(0);
      static_cast<TH3*>((TH1*)GetReplica(i))->GetXaxis()->SetRange(init_firstxbin,init_lastxbin);
      static_cast<TH3*>((TH1*)GetReplica(i))->GetYaxis()->SetRange(init_firstybin,init_lastybin);
      static_cast<TH3*>((TH1*)GetReplica(i))->GetZaxis()->SetRange(init_firstzbin,init_lastzbin);
   }

   TH1Bootstrap *proj1 = NULL;
   TH2Bootstrap *proj2 = NULL;
   if (fOwnGen)
   {
     if(dimension == 1) proj1 = new TH1DBootstrap(name, name, (TH1D*)proj_nom, (TH1D**)proj_reps, nreps);
     if(dimension == 2) proj2 = new TH2DBootstrap(name, name, (TH2D*)proj_nom, (TH2D**)proj_reps, nreps);
   }
   else
   {
     if(dimension == 1) proj1 = new TH1DBootstrap(name, name, (TH1D*)proj_nom, (TH1D**)proj_reps, nreps, fGenerator);
     if(dimension == 2) proj2 = new TH2DBootstrap(name, name, (TH2D*)proj_nom, (TH2D**)proj_reps, nreps, fGenerator);
   }

   delete proj_nom;
   for (Int_t i = 0; i < nreps; ++i) delete proj_reps[i];
   delete [] proj_reps;

   if(dimension == 1) return proj1;
   if(dimension == 2) return proj2;

   return 0;
}

//______________________________________________________________________________
//            TH3DBootstrap methods
//______________________________________________________________________________

ClassImp(TH3DBootstrap)

//______________________________________________________________________________
TH3DBootstrap::TH3DBootstrap()
: TH3Bootstrap()
, fHist(NULL)
, fHistReplica(NULL)
{ }

//______________________________________________________________________________
TH3DBootstrap::TH3DBootstrap(const TH3DBootstrap &h3b)
: TH3Bootstrap(h3b)
{
   fHist = new TH3D(*h3b.fHist);

   if (fNReplica > 0) fHistReplica = new TH3D*[fNReplica];
   for (Int_t i = 0; i < fNReplica; ++i) {
      fHistReplica[i] = new TH3D(*h3b.fHistReplica[i]);
   }
}

//______________________________________________________________________________
TH3DBootstrap::TH3DBootstrap(const TH3D &h3d,
                             Int_t nreplica, BootstrapGenerator *boot)
: TH3Bootstrap(h3d.GetName(), h3d.GetTitle(), nreplica, boot)
{
   fHist = new TH3D(h3d);
   fHist->SetDirectory(0);

   if (fNReplica > 0) fHistReplica = new TH3D*[fNReplica];
   TString repname = "";
   for (Int_t i = 0; i < fNReplica; ++i) {
      fHistReplica[i] = new TH3D(h3d);
      repname = TString::Format("%s_rep%d", h3d.GetName(), i);
      fHistReplica[i]->SetName(repname.Data());
      fHistReplica[i]->SetDirectory(0);
   }
}

//______________________________________________________________________________
TH3DBootstrap::TH3DBootstrap(const char *name, const char *title, Int_t nxbins, const Double_t *xbins, Int_t nybins, const Double_t *ybins,
                             Int_t nzbins, const Double_t *zbins, Int_t nreplica, BootstrapGenerator *boot)
: TH3Bootstrap(name, title, nreplica, boot)
{
   fHist = new TH3D(name, title, nxbins, xbins, nybins, ybins, nzbins, zbins);
   fHist->SetDirectory(0);

   if (fNReplica > 0) fHistReplica = new TH3D*[fNReplica];
   TString repname = "";
   for (Int_t i = 0; i < fNReplica; ++i) {
      repname = TString::Format("%s_rep%d", name, i);
      fHistReplica[i] = new TH3D(repname.Data(), title, nxbins, xbins, nybins, ybins, nzbins, zbins);
      fHistReplica[i]->SetDirectory(0);
   }
}

//______________________________________________________________________________
TH3DBootstrap::TH3DBootstrap(const char *name, const char *title, Int_t nxbins, const Float_t *xbins, Int_t nybins, const Float_t *ybins,
                             Int_t nzbins, const Float_t *zbins, Int_t nreplica, BootstrapGenerator *boot)
: TH3Bootstrap(name, title, nreplica, boot)
{
   fHist = new TH3D(name, title, nxbins, xbins, nybins, ybins, nzbins, zbins);
   fHist->SetDirectory(0);

   if (fNReplica > 0) fHistReplica = new TH3D*[fNReplica];
   TString repname = "";
   for (Int_t i = 0; i < fNReplica; ++i) {
      repname = TString::Format("%s_rep%d", name, i);
      fHistReplica[i] = new TH3D(repname.Data(), title, nxbins, xbins, nybins, ybins, nzbins, zbins);
      fHistReplica[i]->SetDirectory(0);
   }
}

//______________________________________________________________________________
TH3DBootstrap::TH3DBootstrap(const char *name, const char *title, Int_t nxbins, Double_t xlow, Double_t xup, Int_t nybins, Double_t ylow, Double_t yup,
                             Int_t nzbins, Double_t zlow, Double_t zup, Int_t nreplica, BootstrapGenerator *boot)
: TH3Bootstrap(name, title, nreplica, boot)
{
   fHist = new TH3D(name, title, nxbins, xlow, xup, nybins, ylow, yup, nzbins, zlow, zup);
   fHist->SetDirectory(0);

   if (fNReplica > 0) fHistReplica = new TH3D*[fNReplica];
   TString repname = "";
   for (Int_t i = 0; i < fNReplica; ++i) {
      repname = TString::Format("%s_rep%d", name, i);
      fHistReplica[i] = new TH3D(repname.Data(), title, nxbins, xlow, xup, nybins, ylow, yup, nzbins, zlow, zup);
      fHistReplica[i]->SetDirectory(0);
   }
}

//______________________________________________________________________________
TH3DBootstrap::TH3DBootstrap(const char *name, const char *title, TH3D *nominal, TH3D **replicas,
                             Int_t nreplica, BootstrapGenerator *boot)
: TH3Bootstrap(name, title, nreplica, boot)
{
   // set the nominal histogram to "nominal"
   if (nominal) {
      fHist = new TH3D(*nominal);
      fHist->SetDirectory(0);
      fHist->SetName(name);
      fHist->SetTitle(title);
   } else {
      Error("TH3DBootstrap", "Pointer to the nominal histogram not provided");
   }

   // set the array of TH3D histograms to "replicas"
   if (fNReplica > 0 && replicas) {
      fHistReplica = new TH3D*[fNReplica];
      TString repname = "";
      for (Int_t i = 0; i < fNReplica; ++i) {
         fHistReplica[i] = new TH3D(*replicas[i]);
         fHistReplica[i]->SetDirectory(0);
         repname = TString::Format("%s_rep%d", name, i);
         fHistReplica[i]->SetName(repname.Data());
         fHistReplica[i]->SetTitle(title);
      }
   } else if (fNReplica > 0 && !replicas) {
       Error("TH3DBootstrap", "Pointer to the array of replicas not provided");
   }
}


//______________________________________________________________________________
TH3DBootstrap::~TH3DBootstrap()
{
   SafeDelete(fHist);
   for (Int_t i = 0; i < fNReplica; ++i) {
      SafeDelete(fHistReplica[i]);
   }
   if (fHistReplica) delete [] fHistReplica;
}

//______________________________________________________________________________
TH1* TH3DBootstrap::GetNominal()
{
   return fHist; }

//______________________________________________________________________________
const TH1* TH3DBootstrap::GetNominal() const
{ return fHist; }

//______________________________________________________________________________
TH1* TH3DBootstrap::GetReplica(Int_t i)
{
   if (i >= fNReplica) {
      Error("GetReplica", "Cannot request replica %d out of %d", i, fNReplica);
      return NULL;
   }
   return fHistReplica[i];
}

//______________________________________________________________________________
const TH1* TH3DBootstrap::GetReplica(Int_t i) const
{ return fHistReplica[i]; }

//______________________________________________________________________________
void TH3DBootstrap::SetNominal(const TH3D &h3)
{
   if (!fHist) fHist = new TH3D(h3);
   else        h3.Copy(*fHist);
}

//______________________________________________________________________________
void TH3DBootstrap::SetReplica(Int_t i, const TH3D &h3)
{
   if (!fHistReplica) return;
   if (!fHistReplica[i]) fHistReplica[i] = new TH3D(h3);
   else                  h3.Copy(*fHistReplica[i]);
}
