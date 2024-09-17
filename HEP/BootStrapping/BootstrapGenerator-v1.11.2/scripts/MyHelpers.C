// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

#include "MyHelpers.h"

#include <iostream>

#include "TLatex.h"
#include "TLine.h"
#include "TMarker.h"
#include "TStyle.h"
#include "Rtypes.h"
#include "TColor.h"
#include "TPave.h"

Int_t SetColorPalette() {  // gorgeous palette
  
  std::cout << "Setting gorgeous palette..." << std::endl << std::endl;

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  Int_t start = TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  return start;
}

void DrawLabel(TString txt, double x, double y, double texsize) {

  TLatex tex;
  tex.SetNDC();
  tex.SetTextFont(42);
  tex.SetTextColor(kBlack);
  tex.SetTextSize(texsize);
  tex.SetTextAlign(12);

  tex.DrawLatex(x,y,txt);
  tex.SetTextColor(kBlack);

  return;

}

void DrawBoxLabel(TString txt, double x, double y, int fcolor, int fstyle, int lcolor, double texsize) {

  TLatex tex;
  tex.SetNDC();
  tex.SetTextFont(42);
  tex.SetTextColor(kBlack);
  tex.SetTextSize(texsize);
  tex.SetTextAlign(12);

  TPave b(x-0.02,y-0.018,x+0.02,y+0.016,1,"NDC");
  b.SetFillStyle(fstyle);
  b.SetFillColor(fcolor);
  b.SetLineColor(lcolor);
  b.SetLineWidth(2);
  b.DrawClone();

  tex.DrawLatex(x+0.04,y,txt);
  tex.SetTextColor(kBlack);

  return;

}

void DrawMarkerLabel(TString txt, double x, double y, int style, int color, double size, double texsize, bool noLine, bool yline) {

  TLatex tex;
  tex.SetNDC();
  tex.SetTextFont(42);
  tex.SetTextColor(kBlack);
  tex.SetTextSize(texsize);
  tex.SetTextAlign(12);

  TLine l;
  l.SetLineWidth(2);
  l.SetLineColor(color);
  double cent=0.007;
  if( style==22 || style==26 || style==33 || style==23 ) cent=0.005;
  if( style==1 ) cent=0.0;
  if (!noLine) {
    l.DrawLineNDC(x-0.02,y,x-cent,y);
    l.DrawLineNDC(x+cent,y,x+0.02,y);
  }
  if (yline) {
    l.DrawLineNDC(x, y+0.01, x, y-0.01);
  }

  TMarker m(x,y,style);
  m.SetNDC();
  m.SetMarkerSize(size);
  m.SetMarkerColor(color);
  m.DrawClone();

  tex.DrawLatex(x+0.04,y,txt);
  tex.SetTextColor(kBlack);

  return;

}

void DrawLineLabel(TString txt, double x, double y, int style, int color, int width, double texsize, bool two) {

  TLatex tex;
  tex.SetNDC();
  tex.SetTextFont(42);
  tex.SetTextColor(kBlack);
  tex.SetTextSize(texsize);
  tex.SetTextAlign(12);

  TLine l;
  l.SetLineWidth(2);
  l.SetLineColor(color);
  l.SetLineWidth(width);
  l.SetLineStyle(style);
  if (two) {
    l.DrawLineNDC(x-0.02,y-0.005,x+0.02,y-0.005);
    l.DrawLineNDC(x-0.02,y+0.005,x+0.02,y+0.005);
  } else {
    l.DrawLineNDC(x-0.02,y,x+0.02,y);
  }

  tex.DrawLatex(x+0.04,y,txt);
  tex.SetTextColor(kBlack);

  return;

}
