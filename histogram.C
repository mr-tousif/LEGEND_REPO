:ivoid histogram(){
	TH1D*h1=new TH1D("h1","test",50,0,100);
	/*
	h1->Fill(26);
	h1->Fill(20);
	h1->Fill(50,4);
	h1->Draw("hist");
	*/
	TRandom3*r=new TRandom3();
	for(int ij=0;ij<100000;ij++){
		h1->Fill(r->Gaus(30,10));}
	h1->Fit("gaus");
	h1->Draw();
}
