// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#include "SlidingBinsSmoothing.h"

namespace smooth {

   // Copy a coarse histogram into one with finer bin boundaries
   TH1D* RebinToFineTemplate(TH1D &original, TH1D &templatebins)
   {
      TH1D *rebin = new TH1D(templatebins);
      for (Int_t i = 1; i <= rebin->GetNbinsX(); ++i) {
         Int_t bin = original.FindBin(rebin->GetBinCenter(i));
         rebin->SetBinContent(i, original.GetBinContent(bin));
         rebin->SetBinError(i, original.GetBinError(bin));
      }
      return rebin;
   }
   
   // Iterative fitting method
   TH1D* GaussianKernelSmooth(TH1D &original, Double_t minval, Double_t maxval, bool smoothlastbin = true)
   {
      TH1D *temp = new TH1D(original);
   
      Int_t lastbin = temp->FindBin(maxval-1e-4);
      temp->SetBinContent(lastbin+1, temp->GetBinContent(lastbin));
   
      Int_t firstbin = temp->FindBin(minval+1e-4);
      temp->SetBinContent(firstbin-1, temp->GetBinContent(firstbin));
   
      TH1D *smooth = GaussSmoothing(temp, 2, temp->GetBinLowEdge(firstbin), temp->GetBinLowEdge(lastbin+1));
      if (!smoothlastbin) smooth->SetBinContent(lastbin, temp->GetBinContent(lastbin));
   
      delete temp; temp = NULL;
      return smooth;
   }
   
   // significance rebinning
   TH1D* RebinUntilSignificant(TH1D &hist, Double_t minval, Double_t maxval)
   {
      Int_t mini = hist.FindBin(minval+1e-4), maxi = hist.FindBin(maxval-1e-4);
   
      Double_t mu = 0.0, sig = 0.0;
   
      // First start from the left to the right, combining by significance
      Int_t nbins1 = 0;
      Double_t *bins1 = new Double_t[hist.GetNbinsX()+1];
      Double_t *cont1 = new Double_t[hist.GetNbinsX()];
      Double_t *err1 = new Double_t[hist.GetNbinsX()];
   
      Bool_t firstnotzero = kTRUE;
      for (Int_t i = mini; i <= maxi; ++i) {
         if (fabs(hist.GetBinContent(i)) < 1e-6 || hist.GetBinError(i) < 1e-6) continue;
         if (firstnotzero) bins1[0] = hist.GetBinLowEdge(i);
         firstnotzero = kFALSE;
   
         mu += hist.GetBinContent(i)/hist.GetBinError(i)/hist.GetBinError(i);
         sig += 1.0/hist.GetBinError(i)/hist.GetBinError(i);
   
         // Now it's significant!
         if (sig > 0 && fabs(mu)/sqrt(sig) > 2.0 && sqrt(sig)/fabs(mu) < 1.0/sqrt(10.0)) { // 3 sigma sig + <30% error
            nbins1++;
            bins1[nbins1] = hist.GetBinLowEdge(i+1);
            cont1[nbins1-1] = mu/sig;
            err1[nbins1-1] = 1.0/sqrt(sig);
            mu = 0.0;
            sig = 0.0;
         }
      }
      if (bins1[nbins1] != maxval) {
         nbins1++;
         bins1[nbins1] = hist.GetBinLowEdge(maxi+1);
         cont1[nbins1-1] = 0.0;
         err1[nbins1-1] = 1.0/sqrt(sig);
      }
   
      // Second start from the right to the left, combining by significance
      Int_t nbins2 = 0;
      Double_t *bins2 = new Double_t[hist.GetNbinsX()+1];
      Double_t *cont2 = new Double_t[hist.GetNbinsX()];
      Double_t *err2 = new Double_t[hist.GetNbinsX()];
      bins2[0] = hist.GetBinLowEdge(maxi+1);
   
      mu = 0.0, sig = 0.0;
      firstnotzero = kTRUE;
      for (Int_t i = maxi; i >= mini; --i) {
         if (fabs(hist.GetBinContent(i)) < 1e-6 || hist.GetBinError(i) < 1e-6) continue;
         if (firstnotzero) bins2[0] = hist.GetBinLowEdge(i+1);
         firstnotzero = kFALSE;
   
         mu += hist.GetBinContent(i)/hist.GetBinError(i)/hist.GetBinError(i);
         sig += 1.0/hist.GetBinError(i)/hist.GetBinError(i);
   
         if (sig > 0 && fabs(mu)/sqrt(sig) > 2.0 && sqrt(sig)/fabs(mu) < 1.0/sqrt(10.0)) { // 3 sigma sig + <30% error
            nbins2++;
            bins2[nbins2] = hist.GetBinLowEdge(i);
            cont2[nbins2-1] = mu/sig;
            err2[nbins2-1] = 1.0/sqrt(sig);
            mu = 0.0;
            sig = 0.0;
         }
      }
      if (bins2[nbins2] != minval) {
         nbins2++;
         bins2[nbins2] = hist.GetBinLowEdge(mini);
         cont2[nbins2-1] = 0.0;
         err2[nbins2-1] = 1.0/sqrt(sig);
      }
   
      // Check which as more bins, use that one
      Int_t nbins = nbins1;
      Double_t *bins = bins1;
      Double_t *cont = cont1;
      Double_t *err = err1;
   
      if (nbins1 < nbins2) {
         nbins = nbins2;
         Double_t *bins3 = new Double_t[nbins+1];
         Double_t *cont3 = new Double_t[nbins];
         Double_t *err3 = new Double_t[nbins];
         bins3[0] = bins2[nbins];
         for (Int_t i = 0; i < nbins; ++i) {
            bins3[i+1] = bins2[nbins-1-i];
            cont3[i] = cont2[nbins-1-i];
            err3[i] = err2[nbins-1-i];
         }
         bins = bins3;
         cont = cont3;
         err = err3;
         delete [] bins1;
         delete [] cont1;
         delete [] err1;
         delete [] bins2;
         delete [] cont2;
         delete [] err2;
      } else {
         delete [] bins2;
         delete [] cont2;
         delete [] err2;
      }
   
      TString name = TString::Format("%s_sig", hist.GetName());
   
      TH1D *comb = new TH1D(name.Data(), name.Data(), nbins, bins);
      for (Int_t i = 0; i < nbins; ++i) {
         comb->SetBinContent(i+1, cont[i]);
         comb->SetBinError(i+1, err[i]);
      }
   
      delete [] bins;
      delete [] cont;
      delete [] err;
   
      return comb;
   }
   
   void PlotSyst(const TH1D *up_, const TH1D *up1_, const TH1D *up2_,
                 const TH1D *down_, const TH1D *down1_, const TH1D *down2_, Int_t jes,
                 Double_t minval, Double_t maxval, const char* xname = "#font[52]{m}_{12} [GeV]")
   {
      TH1D up(*up_), up1(*up1_), up2(*up2_);
      TH1D down(*down_), down1(*down1_), down2(*down2_);
   
      TCanvas c("c", "c", 600, 600);
      if (minval > 0) c.SetLogx();
   
      TH2D axis("axis", "axis", 1, 2, 5040, 1, -0.1, 0.1);
      axis.GetXaxis()->SetMoreLogLabels();
      axis.GetXaxis()->SetTitle("#font[52]{m}_{12} [GeV]");
      axis.GetYaxis()->SetTitle("Relative uncertainty [%]");
   
      up.Scale(100.0); up1.Scale(100.0); up2.Scale(100.);
      down.Scale(100.0); down1.Scale(100.0); down2.Scale(100.);
   
      Float_t ymax = 0.0;
      if (fabs(up.GetBinContent(up.GetMaximumBin()))       > ymax) ymax = fabs(up.GetBinContent(up.GetMaximumBin()));
      if (fabs(up.GetBinContent(up.GetMinimumBin()))       > ymax) ymax = fabs(up.GetBinContent(up.GetMinimumBin()));
   
      if (fabs(up1.GetBinContent(up1.GetMaximumBin()))     > ymax) ymax = fabs(up1.GetBinContent(up1.GetMaximumBin()));
      if (fabs(up1.GetBinContent(up1.GetMinimumBin()))     > ymax) ymax = fabs(up1.GetBinContent(up1.GetMinimumBin()));
   
      // if (fabs(up2.GetBinContent(up2.GetMaximumBin()))     > ymax) ymax = fabs(up2.GetBinContent(up2.GetMaximumBin()));
      // if (fabs(up2.GetBinContent(up2.GetMinimumBin()))     > ymax) ymax = fabs(up2.GetBinContent(up2.GetMinimumBin()));
   
      if (fabs(down.GetBinContent(down.GetMaximumBin()))   > ymax) ymax = fabs(down.GetBinContent(down.GetMaximumBin()));
      if (fabs(down.GetBinContent(down.GetMinimumBin()))   > ymax) ymax = fabs(down.GetBinContent(down.GetMinimumBin()));
   
      if (fabs(down1.GetBinContent(down1.GetMaximumBin())) > ymax) ymax = fabs(down1.GetBinContent(down1.GetMaximumBin()));
      if (fabs(down1.GetBinContent(down1.GetMinimumBin())) > ymax) ymax = fabs(down1.GetBinContent(down1.GetMinimumBin()));
   
      // if (fabs(down2.GetBinContent(down2.GetMaximumBin())) > ymax) ymax = fabs(down2.GetBinContent(down2.GetMaximumBin()));
      // if (fabs(down2.GetBinContent(down2.GetMinimumBin())) > ymax) ymax = fabs(down2.GetBinContent(down2.GetMinimumBin()));
   
      if (ymax < 1e-6) return;
   
      axis.SetBins(1, minval, maxval, 1, ymax*-1.3, ymax*1.7);
      axis.Draw("axis");
   
      up.SetMarkerStyle(1);
      up.DrawClone("same pe");
   
      up1.SetLineColor(kRed);
      up1.SetLineStyle(2);
      up1.SetLineWidth(3);
      up1.DrawClone("same hist ][");
   
      up2.SetLineColor(kBlue);
      up2.SetLineStyle(4);
      up2.SetLineWidth(3);
      up2.DrawClone("same hist ][");
   
      down.SetMarkerStyle(1);
      down.DrawClone("same pe");
   
      down1.SetLineColor(kRed);
      down1.SetLineStyle(2);
      down1.SetLineWidth(3);
      down1.DrawClone("same hist ][");
   
      down2.SetLineColor(kBlue);
      down2.SetLineStyle(4);
      down2.SetLineWidth(3);
      down2.DrawClone("same hist ][");
   
      TString name = TString::Format("JES nuisance parameter %d", jes);
      DrawLabel(name.Data(), 0.3, 0.90, 0.040);
      DrawLineLabel("Nominal uncertainty", 0.3, 0.85, 1, kBlack, 3, 0.040);
      DrawLineLabel("Rebin until significant", 0.3, 0.80, 2, kRed, 3, 0.040);
      name = TString::Format("Gaussian kernel smoothing");
      DrawLineLabel(name.Data(), 0.3, 0.75, 4, kBlue, 3, 0.040);
      
      name = TString::Format("smoothed/jes%d.png", jes);
      c.SaveAs(name.Data());
   
      name = TString::Format("smoothed/jes%d.eps", jes);
      c.SaveAs(name.Data());
   }
   
   void SetZero(TH1D *hist)
   {
      for (Int_t i = 1; i <= hist->GetNbinsX(); ++i) hist->SetBinContent(i, 0.0);
   }
   
   void RemoveUnused(TH1D *hist, Double_t minval, Double_t maxval, Double_t &max)
   {
      max = 0.0;
      for (Int_t i = 1; i <= hist->GetNbinsX(); ++i) {
         if (hist->GetBinCenter(i) < minval) {
            hist->SetBinContent(i, 0.0);
            continue;
         }
         if (hist->GetBinCenter(i) > maxval) {
            hist->SetBinContent(i, 0.0);
            continue;
         }
         if (fabs(hist->GetBinContent(i)) > max) max = fabs(hist->GetBinContent(i));
      }
   }

}
