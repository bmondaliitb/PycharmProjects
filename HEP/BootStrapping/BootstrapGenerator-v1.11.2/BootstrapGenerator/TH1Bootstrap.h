// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#ifndef TH1Bootstrap_h
#define TH1Bootstrap_h

#ifndef ROOT_Rtypes
#include "Rtypes.h"
#endif

#ifndef ROOT_TNamed
#include "TNamed.h"
#endif

#ifndef ROOT_TMatrixD
#include "TMatrixD.h"
#endif

#ifndef ROOT_TVectorD
#include "TVectorD.h"
#endif

class BootstrapGenerator;
class TBrowser;
class TCollection;
class TF1;
class TH1;
class TH1D;
class TH1F;
class TH1DBootstrap;

class TH1Bootstrap : public TNamed {

private:
   virtual TObject* Clone(const char*) const { return NULL; } // May not use

protected:
   Int_t               fNReplica;
   BootstrapGenerator *fGenerator; //!
   Bool_t              fOwnGen;    //!

protected:
   TH1Bootstrap();
   TH1Bootstrap(const TH1Bootstrap &h1b);
   TH1Bootstrap(const char *name, const char *title, Int_t nreplica, BootstrapGenerator *boot = NULL);

   static void Append(const TH1 &extension, const Bool_t emptybase, TH1 *base);
   virtual void Append(const TH1Bootstrap &hext, const Bool_t emptybase);

public:
   virtual ~TH1Bootstrap();

   virtual TH1* GetNominal() = 0;
   virtual TH1* GetReplica(Int_t i) = 0;

   virtual const TH1* GetNominal() const = 0;
   virtual const TH1* GetReplica(Int_t i) const = 0;

   virtual void     Browse(TBrowser *b);
   virtual Bool_t   GetOwnGenerator() const { return fOwnGen; }
   virtual void     SetOwnGenerator(const Bool_t &owngen) { fOwnGen = owngen; }

   virtual Int_t    Fill(Double_t x, Double_t w, UInt_t RunNumber = 0, UInt_t EventNumber = 0, UInt_t mc_channel_number = 0);
   virtual void     AddBinContent(Int_t bin, Double_t w, UInt_t RunNumber = 0, UInt_t EventNumber = 0, UInt_t mc_channel_number = 0);
   virtual Int_t    GetSize() const;
   virtual Int_t    GetNReplica() const { return fNReplica; }
   virtual Long64_t Merge(TCollection *li);
   virtual Bool_t   IsCompatible(const TH1Bootstrap &h1b) const;
   virtual void     Scale(Double_t c1 = 1, Option_t *option = "");

//#if ROOT_VERSION_CODE >= ROOT_VERSION(5,34,6)
#if ROOT_VERSION_CODE >= 336390
   virtual void     Sumw2(Bool_t flag = kTRUE);
#else
   virtual void     Sumw2();
#endif

//#if ROOT_VERSION_CODE >= ROOT_VERSION(5,34,0)
#if ROOT_VERSION_CODE >= 336384
   virtual Bool_t Divide(const TH1Bootstrap *h1);
   virtual Bool_t Add(const TH1Bootstrap *h1, Double_t c1 = 1);
   virtual Bool_t Multiply(const TH1Bootstrap *h1);
   virtual Bool_t Multiply(TF1 *f1, Double_t c1 = 1);
#else
   virtual void Divide(const TH1Bootstrap *h1);
   virtual void Add(const TH1Bootstrap *h1, Double_t c1 = 1);
   virtual void Multiply(const TH1Bootstrap *h1);
   virtual void Multiply(TF1 *f1, Double_t c1 = 1);
#endif

   // Extra helper functions:
   virtual Double_t GetBootstrapMean(Int_t bin) const;
   virtual Double_t GetBootstrapRMS(Int_t bin) const;
   virtual Double_t GetBootstrapCorel(Int_t bin1, Int_t bin2) const;
   virtual Double_t GetBootstrapCorel(Int_t bin1, const TH1Bootstrap &h2, Int_t bin2) const;

   virtual TMatrixD* GetCovarianceMatrix() const;
   virtual TMatrixD* GetCorrelationMatrix() const;

   virtual void SetValBootstrapMean(); // reset bin contents to bootstrap mean
   virtual void SetErrBootstrapRMS();  // reset bin contents to bootstrap rms

   virtual TH1* GetBootstrapResult(Option_t *option = "") const;

   virtual void SetGenerator(BootstrapGenerator *gen = NULL);
   virtual const BootstrapGenerator* GetGenerator() const;
   virtual const Int_t* ComputeWeights(UInt_t RunNumber, UInt_t EventNumber, UInt_t mc_channel_number);

   virtual void Append(const TH1Bootstrap &hext);
   virtual TH1DBootstrap* FlattenTo1D();

   // Not for public use, but currently can't hide from cling...
   void InitOnFileRead();

   ClassDef(TH1Bootstrap, 13)
};

//______________________________________________________________________________
class TH1DBootstrap : public TH1Bootstrap {

private:
   virtual TObject* Clone(const char*) const { return NULL; } // May not use

protected:
   TH1D         *fHist;
   TH1D        **fHistReplica; //[fNReplica]

public:
   TH1DBootstrap();
   TH1DBootstrap(const TH1DBootstrap &h1b);
   TH1DBootstrap(const TH1D &h1d,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH1DBootstrap(const char *name, const char *title, Int_t nxbins, Double_t xlow, Double_t xup,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH1DBootstrap(const char *name, const char *title, Int_t nxbins, const Float_t *xbins,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH1DBootstrap(const char *name, const char *title, Int_t nxbins, const Double_t *xbins,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH1DBootstrap(const char *name, const char *title, TH1D *nominal, TH1D **replicas,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   virtual ~TH1DBootstrap();

   virtual TH1DBootstrap* Rebin(Int_t ngroup = 2, const char* newname = "", const Double_t *xbins = NULL);

   virtual TH1* GetNominal();
   virtual TH1* GetReplica(Int_t i);

   virtual const TH1* GetNominal() const;
   virtual const TH1* GetReplica(Int_t i) const;

   virtual void SetNominal(const TH1D &h1);
   virtual void SetReplica(Int_t i, const TH1D &h1);

   ClassDef(TH1DBootstrap, 7)
};

//______________________________________________________________________________
class TH1FBootstrap : public TH1Bootstrap {

private:
   virtual TObject* Clone(const char*) const { return NULL; } // May not use

protected:
   TH1F         *fHist;
   TH1F        **fHistReplica; //[fNReplica]

public:
   TH1FBootstrap();
   TH1FBootstrap(const TH1FBootstrap &h1b);
   TH1FBootstrap(const TH1F &h1d,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH1FBootstrap(const char *name, const char *title, Int_t nxbins, Double_t xlow, Double_t xup,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH1FBootstrap(const char *name, const char *title, Int_t nxbins, const Float_t *xbins,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH1FBootstrap(const char *name, const char *title, Int_t nxbins, const Double_t *xbins,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   TH1FBootstrap(const char *name, const char *title, TH1F *nominal, TH1F **replicas,
                 Int_t nreplica, BootstrapGenerator *boot = NULL);
   virtual ~TH1FBootstrap();

   virtual TH1FBootstrap* Rebin(Int_t ngroup = 2, const char* newname = "", const Double_t *xbins = NULL);

   virtual TH1* GetNominal();
   virtual TH1* GetReplica(Int_t i);

   virtual const TH1* GetNominal() const;
   virtual const TH1* GetReplica(Int_t i) const;

   virtual void SetNominal(const TH1F &h1);
   virtual void SetReplica(Int_t i, const TH1F &h1);

   ClassDef(TH1FBootstrap, 1)
};

#endif
