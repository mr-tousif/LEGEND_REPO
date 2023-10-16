void read_root()
{
    TFile* fr=new TFile("summary-type-1-dir-caenData_4_11-4_19-2023-05-31-12-34.root","READ");
    TH1D* h1;
    fr->GetObject("RunHitWaveFile208Chan2",h1);
    h1->Draw();
}