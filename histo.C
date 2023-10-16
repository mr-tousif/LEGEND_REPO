
void histo() 
{
   auto c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);

   fstream file;
   file.open("np2.txt", ios::in);
   while(1){
   double n=1131
   double x,y,yerr;
   file>>x>>y>>yerr;
   }
   auto gr = new TGraphErrors(n,x,y,yerr);
   gr->SetTitle("TGraphErrors Example");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->Draw("ALP");
}
