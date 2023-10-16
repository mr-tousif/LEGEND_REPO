TRandom3 *ran;
static double xtrigger = 100;
static double tres = 10.0;

static double expGaus(double x, double tau)
{
  double arg1 = (tres * tres / tau - 2. * x) / 2. / tau;
  double arg2 = (tres * tres / tau - x) / sqrt(2) / tres;
  double f =  0.5*TMath::Exp(arg1) * TMath::Erfc(arg2);
  return f;
}

double myExps(Double_t *xx, Double_t *par)
{
  double x = xx[0]-xtrigger;
  return expGaus(x,par[0]) * par[2] * par[1] / par[0];
}
double myExp(Double_t *xx, Double_t *par)
{
  double x = xx[0] - xtrigger;
  if(x<0)
    return 0;
  return par[2] * par[1] * TMath::Exp(-x / par[0]) / par[0];
}

void smear(double tau = 10.)
{
  int ngen = 1.E5;
  double xmax = 40. * tau;
  auto h1 = new TH1F("h1", "test", 1000, 0, xmax);
  double bw = h1->GetBinWidth(0);
  ran = new TRandom3();
  TF1 *f1 = new TF1("myExp", myExp, 0, xmax, 3);
  f1->SetParName(0, "tau");
  f1->SetParameter(0, tau);
  f1->SetParName(1, "norm");
  f1->SetParameter(1, double(ngen));
  f1->SetParName(2,"bw");
  f1->FixParameter(2,bw);
  TF1 *fs = new TF1("myExps", myExps, 0, xmax, 3);
  fs->SetParName(0, "tau");
  fs->SetParameter(0, tau);
  fs->SetParName(1, "norm");
  fs->SetParameter(1, double(ngen));
  fs->SetParName(2, "bw");
  fs->FixParameter(2, bw);
  //
  h1->FillRandom("myExps", ngen);
  h1->Fit(fs, "L", "",0,xmax);
  /*
    for (int i = 0; i < ngen; ++i)
    {
      double r = (xmax - xtrigger)*ran->Rndm() + xtrigger;
      double x = f1->Eval(r);
      //printf(" r %f x %E \n",r,x);
      h1->Fill(r,x);
    }
    */
  printf(" entries %E  h1 int %E f1 int %E  fs int  %E\n", 
    h1->GetEntries(), h1->Integral(1,h1->GetNbinsX()),fs->Integral(0,xmax)/bw,f1->Integral(0,xmax)/bw);
  TCanvas *c = new TCanvas("expTest", "expTest");
  gStyle->SetOptFit(1111111);
  c->SetLogy();
  h1->GetXaxis()->SetRangeUser(0,xmax);
  h1->Draw("");
  //f1->Draw("same");
}
