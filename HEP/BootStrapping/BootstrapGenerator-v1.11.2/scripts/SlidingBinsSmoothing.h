// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

// perform average with Gaussian kernel
TH1D* GaussSmoothing( TH1D *systH_, Int_t version_, Double_t xMin_ = 0, Double_t xMax_ = 0){

   Int_t firstbin = systH_->GetXaxis()->FindBin(xMin_+1) - 1;
   Int_t lastbin = systH_->GetXaxis()->FindBin(xMax_-1);

   Double_t xMin = systH_->GetBinCenter( firstbin );
   Double_t xMax = systH_->GetBinCenter( lastbin  );

   if (!xMin) xMin = systH_->GetBinCenter( 1 );
   if (!xMax) xMax = systH_->GetBinCenter( systH_->GetNbinsX() );

   Int_t Nbins = systH_->GetXaxis()->FindBin(xMax) - systH_->GetXaxis()->FindBin(xMin) + 1;

   //cout << " Sliding bins over " << Nbins << " small bins " << endl;

   Double_t a=0., b=0.;
   if (version_ == 1) {
      a = 10.; b = 0.3;
   } else if (version_ == 2) {
      a = 10.; b = 0.5;
   } else if (version_ == 3) {
      a = 10.; b = 0.2;
   } else {
      cout << "Problem in smoothing version!" << endl;
      exit(1);
   }

   TH1D *systSmoothH_ = new TH1D( *systH_ );
   for (Int_t i = firstbin; i < lastbin; i++) {
      Double_t sum = 0., xi = 0., wi = 0.;
      xi = systH_->GetBinCenter( i+1 );
      wi = systH_->GetBinWidth( i+1 );
      Double_t totWeightAv = 0;

      Double_t width = a + b*xi;

      for (Int_t j = firstbin; j < lastbin; j++) {
         Double_t xp = 0., yp = 0.;
         xp = systH_->GetBinCenter( j+1 );
         yp = systH_->GetBinContent( j+1 );

         Double_t weight = exp( -pow( (xp-xi)/(0.5*width), 2 ) );
         sum += ( ( xp>=xMin && xp<=xMax ) ? yp : systH_->GetBinContent( i+1 ) ) *weight;
         totWeightAv += weight;
      }

      if (totWeightAv != 0.) systSmoothH_->SetBinContent( i+1, sum/totWeightAv );
   }

   return systSmoothH_;
}

