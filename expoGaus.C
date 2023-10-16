static double xtrigger = 100;
static double tres = 10.0;

static double expGaus(double x, double tau)
{
  double arg1 = (tres * tres / tau - 2. * x) / 2. / tau;
  double arg2 = (tres * tres / tau - x) / sqrt(2) / tres;
  double f =  0.5*TMath::Exp(arg1) * TMath::Erfc(arg2);
  return f;
}

double Expo(Double_t *xx, Double_t *par)
{
  double x = xx[0]-xtrigger;
  return expGaus(x,par[0]) * par[2] * par[1] / par[0];
}

double Exp(Double_t *xx, Double_t *par)
{
  double x = xx[0] - xtrigger;
  if(x<0)
    return 0;
  return par[2] * par[1] * TMath::Exp(-x / par[0]) / par[0];
}


/*Double_t myfunc(Double_t *x, Double_t *par)
{
   Float_t xx =x[0];
   //Double_t f = TMath::Abs(par[0]*sin(par[1]*xx)/xx);
   Double_t f=par[0]*pow(xx,2)+par[2]*xx;
   return f;

}*/

// function code in C
/*double myfunc(double *x, double *par) {
  double xx=x[0];
  double f=par[0]*xx*xx+par[1]*xx+par[2];
  return f;
}*/



void expoGaus()
/*{
   auto f1 = new TF1("myfunc",myfunc,0,10,2);
   //f1->SetParameters(2,1);
   f1->SetParameter(0,1);
   f1->SetParameter(1,2);
   f1->SetParameter(2,3);
   f1->SetParNames("a","b","c");
   f1->Draw();
}*/
{  
  double tau=10;
  int ngen = 1.E5;
  double xmax = 40. * tau;  
  auto h1 = new TH1F("h1", "test", 1000, 0, xmax);
  double bw = h1->GetBinWidth(0);

  TF1 *f1 = new TF1("f1", Expo, 0, xmax, 3);
  
  f1->SetParName(0, "tau");
  f1->SetParameter(0, tau);
  f1->SetParName(1, "norm");
  f1->SetParameter(1, double(ngen));
  f1->SetParName(2,"bw");
  f1->SetParameter(2,bw);

  TF1 *fs = new TF1("f1", Exp, 0, xmax, 3);
  fs->SetParName(0, "tau");
  fs->SetParameter(0, tau);
  fs->SetParName(1, "norm");
  fs->SetParameter(1, double(ngen));
  fs->SetParName(2,"bw");
  fs->SetParameter(2,bw);

  TRandom3* rand=new TRandom3();
  double r,x;
  for(int i=1;i<=ngen;i++){
    r = (xmax - xtrigger)*rand->Rndm() + xtrigger;
    x = f1->Eval(r);

    h1->Fill(r,x);}
  
  h1->Fit(fs, "L", "",0,xmax);

 printf(" entries %E  h1 int %E f1 int %E  fs int  %E\n", 
    h1->GetEntries(), h1->Integral(1,h1->GetNbinsX()),fs->Integral(0,xmax)/bw,f1->Integral(0,xmax)/bw);
  TCanvas* c=new TCanvas();
  c->SetLogy();
  h1->GetXaxis()->SetRangeUser(0,xmax);
  h1->Draw("");
  //f1->Draw();
  //fs->Draw("Same");
  //c->Draw();
  
}