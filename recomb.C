
Double_t myRecomb(Double_t *x, Double_t *par)
{
   double xx =x[0]-par[1];
   double f=0;
   if(xx<0) return f;
   f = par[0]*pow( 1.+xx/par[2] ,-2);
   return f;
}

// do numerical convolution of recombination function and Gaussian resolution

void recomb(){

  TFile *fout = new TFile("recomb.root","recreate");
  int nsamples = 7500;
  TH1D* hRecomb = new TH1D("hRecomb", "hRecomb", nsamples, 0, nsamples);
  TH1D* hGaus = new TH1D("hGaus", "hGaus", nsamples, 0, nsamples);
  TH1D* hConvolve = new TH1D("hConvolve", "hConvolve", nsamples, 0, nsamples);

  TF1 *fgaus = new TF1("myGaus", "[0]*exp(-0.5*((x-[1])/[2])**2)", 0, nsamples);
  fgaus->SetParameters(1.,1400.,10.0);

  TF1 *frecomb = new TF1("myRecomb",myRecomb, 0, nsamples,3);
  frecomb->SetParameters(0.1,1400.,37.1);

  int nrandom = 10000;
  hGaus->FillRandom("myGaus",nrandom);
  hRecomb->FillRandom("myRecomb",nrandom);

  // numerical convolution
  for(int ibin=0; ibin<hConvolve->GetNbinsX(); ++ibin ) {
    double val=0;
    for(int jbin=0; jbin<hConvolve->GetNbinsX(); ++jbin ) {
      val +=  hRecomb->GetBinContent(jbin)*hGaus->GetBinContent(ibin-jbin);
    }
    val/=double(hConvolve->GetNbinsX());
    // this offset to trigger time I dont quite understand but it has to be here
    hConvolve->SetBinContent(ibin-1400, val);
  }


  fout->Write();
}
