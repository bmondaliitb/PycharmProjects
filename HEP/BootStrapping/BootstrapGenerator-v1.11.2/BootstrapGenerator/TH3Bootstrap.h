// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#ifndef TH3Bootstrap_h
#define TH3Bootstrap_h

#ifndef TH1Bootstrap_h
#include "BootstrapGenerator/TH1Bootstrap.h"
#endif

#ifndef TH2Bootstrap_h
#include "BootstrapGenerator/TH2Bootstrap.h"
#endif

#ifndef ROOT_Rtypes
#include "Rtypes.h"
#endif

#ifndef ROOT_TNamed
#include "TNamed.h"
#endif

class BootstrapGenerator;
class TH3D;

class TH3Bootstrap : public TH1Bootstrap {
private:
   virtual TObject* Clone(const char*) const { return NULL; } // May not use
   Int_t    Fill(Double_t, Double_t, UInt_t, UInt_t, UInt_t) { return -1; } // May not use
   void     Append(const TH1Bootstrap&) { return; } // May not use for 3-D
   void     Append(const TH1Bootstrap&, const Bool_t) { return; } // May not use for 3-D
   TMatrixD* GetCovarianceMatrix() const { return NULL; } // May not use for 3-D
   TMatrixD* GetCorrelationMatrix() const { return NULL; } // May not use for 3-D


protected:
   TH3Bootstrap();
   TH3Bootstrap(const TH3Bootstrap &h3b);
   TH3Bootstrap(const char *name, const char *title, Int_t nreplica, BootstrapGenerator *boot = NULL);
   virtual ~TH3Bootstrap();

public:
   virtual Int_t   Fill(Double_t x, Double_t y, Double_t z, Double_t w = 1.0, UInt_t RunNumber = 0, UInt_t EventNumber = 0, UInt_t mc_channel_number = 0);

   using TH1Bootstrap::GetBootstrapMean;
   using TH1Bootstrap::GetBootstrapRMS;
   using TH1Bootstrap::GetBootstrapCorel;
   virtual Double_t GetBootstrapMean(Int_t binx, Int_t biny, Int_t binz) const;
   virtual Double_t GetBootstrapRMS(Int_t binx, Int_t biny, Int_t binz) const;
   virtual Double_t GetBootstrapCorel(Int_t binx1, Int_t biny1, Int_t binz1, Int_t binx2, Int_t biny2, Int_t binz2) const;
   virtual Double_t GetBootstrapCorel(Int_t binx1, Int_t biny1, Int_t binz1, const TH1Bootstrap &h3, Int_t binx2, Int_t biny2, Int_t binz2) const;

   virtual TH1DBootstrap* ProjectionX(const char *name = "_px", Int_t firstybin = 0, Int_t lastybin = -1, Int_t firstzbin = 0, Int_t lastzbin = -1, Option_t *option = "") const;
   virtual TH1DBootstrap* ProjectionY(const char *name = "_py", Int_t firstxbin = 0, Int_t lastxbin = -1, Int_t firstzbin = 0, Int_t lastzbin = -1, Option_t *option = "") const;
   virtual TH1DBootstrap* ProjectionZ(const char *name = "_pz", Int_t firstxbin = 0, Int_t lastxbin = -1, Int_t firstybin = 0, Int_t lastybin = -1, Option_t *option = "") const;
   virtual TH2DBootstrap* ProjectionXY(const char *name = "_pxy", Int_t firstzbin = 0, Int_t lastzbin = -1, Option_t *option = "") const;
   virtual TH2DBootstrap* ProjectionYZ(const char *name = "_pyz", Int_t firstxbin = 0, Int_t lastxbin = -1, Option_t *option = "") const;
   virtual TH2DBootstrap* ProjectionXZ(const char *name = "_pxz", Int_t firstybin = 0, Int_t lastybin = -1, Option_t *option = "") const;
   virtual TH1Bootstrap* DoProjection(int dimension, const char *name, Int_t firstxbin, Int_t lastxbin, Int_t firstybin, Int_t lastybin, Int_t firstzbin, Int_t lastzbin, Option_t *option) const;

   ClassDef(TH3Bootstrap, 1)
};

//______________________________________________________________________________
class TH3DBootstrap : public TH3Bootstrap {

private:
   virtual TObject* Clone(const char*) const { return NULL; } // May not use

protected:
   TH3D         *fHist;
   TH3D        **fHistReplica; //[fNReplica]

public:
   TH3DBootstrap();
   TH3DBootstrap(const TH3DBootstrap &h3b);
   TH3DBootstrap(const TH3D &h3d,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH3DBootstrap(const char *name, const char *title, Int_t nxbins, Double_t xlow, Double_t xup, Int_t nybins, Double_t ylow, Double_t yup,
                 Int_t nzbins, Double_t zlow, Double_t zup, Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH3DBootstrap(const char *name, const char *title, Int_t nxbins, const Double_t *xbins, Int_t nybins, const Double_t *ybins,
                 Int_t nzbins, const Double_t *zbins, Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH3DBootstrap(const char *name, const char *title, Int_t nxbins, const Float_t *xbins, Int_t nybins, const Float_t *ybins,
                 Int_t nzbins, const Float_t *zbins, Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH3DBootstrap(const char *name, const char *title, TH3D *nominal, TH3D **replicas,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   virtual ~TH3DBootstrap();

   virtual TH1* GetNominal();
   virtual TH1* GetReplica(Int_t i);

   virtual const TH1* GetNominal() const;
   virtual const TH1* GetReplica(Int_t i) const;

   virtual void SetNominal(const TH3D &h3);
   virtual void SetReplica(Int_t i, const TH3D &h3);

   ClassDef(TH3DBootstrap, 1)
};

#endif
