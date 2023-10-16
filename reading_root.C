void reading_root(){
Tfile*f=Tfile::open("summary-type-1-dir-caenData_4_11-4_19-2023-05-31-12-34.root")
TH1D *sumPeakWave8= (TH1D*) f->Get("sumPeakWave8");
sumPeakWave8>GetEntries();
sumPeakWave8>Draw();
}
