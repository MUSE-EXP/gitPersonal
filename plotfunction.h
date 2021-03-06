
void plot_figure2(TPad *thePad,bool saxis=false,float ymin=0.,float ymax=10000.0,bool with_d=false) {
  //void plot_figure(TPad *thePad,bool saxis=false,float ymin=0.,float ymax=1.0,bool with_d=false) {
  //cout<<"wit"<<with_d<<endl;
  
  gStyle->SetOptFit();
  gStyle->SetPadTickY(1);
  //gStyle->SetLogY();
  
  gStyle->SetLineStyleString(11,"40 20");
  float xmin=0.,xmax=20.;
  //float xmin=0.,xmax=16.;
  
  //thePad->cd();
  //thePad->SetLogy();
  //thePad->SetGrid();
  
  /*****************************************************
 Colors
  *****************************************************/
  int HRMcol=kRed+2;
  int RNAcol=kMagenta;
  int QGScol=kGreen+1;
  
  Double_t x,y;
  /*****************************************************
 Format the pad
  *****************************************************/
  
  thePad->SetTopMargin(0.15);
  TH1F *hr = thePad->DrawFrame(xmin,ymin,xmax,ymax);
  hr->SetYTitle("events");
  hr->SetXTitle("RF time (ns)");
  //hr->SetYTitle("event fraction");
  //hr->SetXTitle("RF time bin");
  hr->GetYaxis()->SetTitleOffset(1.5);
  hr->GetYaxis()->SetTitleSize(.06);
  hr->GetYaxis()->SetTitleFont(42);
  hr->GetYaxis()->CenterTitle();
  hr->GetXaxis()->SetTitleSize(.06);
  hr->GetXaxis()->SetTitleFont(42);
  /*****************************************************
  Draw legend
  *****************************************************/
  
  //TLegend *dummylegend=new TLegend();
  //TLegend *legend=new TLegend(0.15,0.17,0.75,0.27);
  //legend->SetMargin(0.2);
  //legend->SetTextFont(72);
  //legend->SetTextSize(0.035);
  //legend->SetFillStyle(0);
  //legend->SetBorderSize(0);
  //legend->Draw();
  
  TLegend *thlegend=new TLegend(0.27,0.59,0.47,0.79);
  thlegend->SetMargin(0.2);
  thlegend->SetTextFont(72);
  thlegend->SetTextSize(0.035);
  thlegend->SetFillStyle(0);
  thlegend->SetBorderSize(0);
  thlegend->Draw();
  
  thePad->SetLeftMargin(0.19);
  /*****************************************************
    Make Title
  *****************************************************/
  float titlex1=0.47, titley1=0.85,titlex2=0.56,titley2=0.95;
  TPaveLabel *label = new TPaveLabel(titlex1,titley1,titlex2,titley2,"Target RF time, z=23.0 m","NDC");
  label->SetTextSize(0.6);
  label->SetFillStyle(0);
  label->SetTextFont(42);
  label->SetBorderSize(0);
  label->Draw();
  TPaveLabel *label2 = new TPaveLabel(titlex1-15,titley1-0.09,titlex2-15,titley2-0.09,"210 MeV/c","NDC");
  label2->SetTextSize(0.5);
  label2->SetFillStyle(0);
  label2->SetTextFont(42);
  label2->SetBorderSize(0);
  label2->Draw();
  /*--------------------------------------------------------------------------------------
    Constants?
    ---------------------------------------------------------------------------------------*/
  //Float_t pchan = 210.;
  Float_t pchan = 115.;
  //Float_t pchan = 153.;
  Int_t nmu = 59000, ne = 231000, npi = 210000;
  //Int_t nmu = 39000, ne = 54000, npi = 407000;
  //Float_t pchan = 153.;
  //Int_t nmu = 20000, ne = 80000, npi = 80000;
  //Float_t pchan = 115.;
  //Int_t nmu = 20000, ne = 60000, npi = 6000;
  Float_t dist = 23.0;
  //Float_t dist = 12.2;
  Float_t toff = 0.0;
  Float_t sigmat = 0.35;
  // choose number of channels for 20 ns RF time width
  const Int_t npts = 800;
  const Int_t ntbins = 32;
  TRandom3 r;
  Float_t Time[npts], efrac[npts], mufrac[npts], pifrac[npts], allfrac[npts];
  Float_t Times[ntbins], frace[ntbins], fracmu[ntbins], fracpi[ntbins], fracall[ntbins];
  for (Int_t j=0; j<npts; j++) {
    Time[j] = 20.*j/npts;
    efrac[j] = 0.;
    mufrac[j] = 0.;
    pifrac[j] = 0.;
    allfrac[j] = 0.;
  }
  //Double_t th25[npts] = {67.0,     58.0,     51.0,     44.0,     39.0,     35.5};
  //masses
  Float_t xmpi=139.57, xme=0.511, xmmu=105.658366;
  Int_t i;
  Float_t cee = 0.3;
  Float_t bite = 0.03*5./79.2;
  Float_t p = pchan;
  Int_t bince, bincmu, bincpi;
  

  //Float_t p = pchan;  This line is an error
  Float_t Emu =TMath::Power(TMath::Power(p,2.0) + TMath::Power(xmmu,2.0),0.5);
  Float_t bmu = p/Emu;
  Float_t Tim_mu = toff+dist/(cee*bmu);
  while (Tim_mu>20.){Tim_mu = Tim_mu - 20.;}
  bincmu = 0.8*Tim_mu;
  for (Int_t j=0; j<nmu; j++) {
    p = pchan * (1.+bite*(gRandom->Rndm()-0.5));
    Emu =TMath::Power(TMath::Power(p,2.0) + TMath::Power(xmmu,2.0),0.5);
    bmu = p/Emu;
    Tim_mu = toff+dist/(cee*bmu);
    while (Tim_mu>20.){Tim_mu = Tim_mu - 20.;}
    //printf(" Tim_mu = %f bin %d\n",Tim_mu,bincmu);
    //Int_t ntimmu = 0.8*Tim_mu;
    //mufrac[ntimmu] = 1.;
    x = Tim_mu;
    Double_t x = r.Gaus(x,sigmat);
    Int_t ntimmu = npts*x/20.;
    if (ntimmu > npts-1) {ntimmu = ntimmu - npts;}
    if (ntimmu < 0) {ntimmu = ntimmu + npts;}
    //printf(" x = %f nTim_mu = %d\n",x,ntimmu);
    mufrac[ntimmu] = mufrac[ntimmu]+1.;
  }
  

  p = pchan;
  Float_t Ee = TMath::Power(TMath::Power(p,2.0) + TMath::Power(xme,2.0),0.5);
  Float_t be = p/Ee;
  Float_t Tim_e = toff+dist/(cee*be);
  while (Tim_e>20.){Tim_e = Tim_e - 20.;}
  bince = 0.8*Tim_e;
  for (Int_t j=0; j<ne; j++) {
    p = pchan * (1.+bite*(gRandom->Rndm()-0.5));
    Ee = TMath::Power(TMath::Power(p,2.0) + TMath::Power(xme,2.0),0.5);
    be = p/Ee;
    Tim_e = toff+dist/(cee*be);
    while (Tim_e>20.){Tim_e = Tim_e - 20.;}
    //printf(" Tim_e = %f bin %d\n",Tim_e,bince);
    //Int_t ntime = 0.8*Tim_e;
    //efrac[ntime] = 1.;
    x = Tim_e;
    x = r.Gaus(x,sigmat);
    Int_t ntime = npts*x/20.;
    if (ntime > npts-1) {ntime = ntime - npts;}
    if (ntime < 0) {ntime = ntime + npts;}
    //printf(" x = %f nTim_e = %d\n",x,ntime);
    efrac[ntime] = efrac[ntime]+1.;
  }
  

  Float_t ntime(0), ntimmu(0), ntimpi(0); //Declarations
  p = pchan;
  Float_t Epi = TMath::Power(TMath::Power(p,2.0) + TMath::Power(xmpi,2.0),0.5);
  Float_t bpi = p/Epi;
  Float_t Tim_pi = toff+dist/(cee*bpi);
  while (Tim_pi>20.){Tim_pi = Tim_pi - 20.;}
  bincpi = 0.8*Tim_pi;
  for (Int_t j=0; j<npi; j++) {
    p = pchan * (1.+bite*(gRandom->Rndm()-0.5));
    Epi = TMath::Power(TMath::Power(p,2.0) + TMath::Power(xmpi,2.0),0.5);
    bpi = p/Epi;
    Tim_pi = toff+dist/(cee*bpi);
    while (Tim_pi>20.){Tim_pi = Tim_pi - 20.;}
    //printf(" Tim_pi = %f bin %d\n",Tim_pi,bincpi);
    //Int_t ntimpi = 0.8*Tim_pi;
    //pifrac[ntimpi] = 1.;
    x = Tim_pi;
    x = r.Gaus(x,sigmat);
    Int_t ntimpi = npts*x/20.;
    if (ntimpi > npts-1) {ntimpi = ntimpi - npts;}
    if (ntimpi < 0) {ntimpi = ntimpi + npts;}
    //printf(" x = %f nTim_pi = %d\n",x,ntimpi);
    pifrac[ntimpi]= pifrac[ntimpi]+1.;
  }
  
  for (Int_t j=0; j<npts; j++) {
    allfrac[j] = efrac[j] + mufrac[j] + pifrac[j];
  }
  printf(" t_e,mu,pi = %f %f %f, nt_e,mu,pi = %f %f %f\n",Tim_e,Tim_mu,Tim_pi, ntime,ntimmu,ntimpi);
  
  Float_t allne = 0., allnmu=0., allnpi = 0.;
  for (Int_t k=0; k<ntbins; k++) {
    frace[k] = 0.;
    fracmu[k] = 0.;
    fracpi[k] = 0.;
    fracall[k] = 0.;
    Times[k] = k+0.5;
    for (Int_t j = 0; j<25; j++) {
      frace[k] = frace[k] + efrac[25*k+j];
      fracmu[k] = fracmu[k] + mufrac[25*k+j];
      fracpi[k] = fracpi[k] + pifrac[25*k+j];
      fracall[k] = fracall[k] + allfrac[25*k+j];
    }
    allne = allne + frace[k];
    allnmu = allnmu + fracmu[k];
    allnpi = allnpi + fracpi[k];
    printf(" bin %d cts e mu pi = %f %f %f\n",k,frace[k],fracmu[k],fracpi[k]);
  }

  Int_t imine = bince - 2, iminmu = bincmu - 2, iminpi = bincpi - 2;
  if(imine < 0){imine = imine+ntbins;}
  if(iminmu < 0){iminmu = iminmu+ntbins;}
  if(iminpi < 0){iminpi = iminpi+ntbins;}
  Int_t neine=0, neinmu=0, neinpi=0, nmuine=0, nmuinmu=0, nmuinpi=0, npiine=0, npiinmu=0, npiinpi=0;
  for (int k=0; k<5; k++) {
    neine = neine + frace[imine];
    nmuine = nmuine + fracmu[imine];
    npiine = npiine + fracpi[imine];
    neinmu = neinmu + frace[iminmu];
    nmuinmu = nmuinmu + fracmu[iminmu];
    npiinmu = npiinmu + fracpi[iminmu];
    neinpi = neinpi + frace[iminpi];
    nmuinpi = nmuinpi + fracmu[iminpi];
    npiinpi = npiinpi + fracpi[iminpi];
    imine++;
    iminmu++;
    iminpi++;
    if(imine>ntbins-1){imine=imine-ntbins;}
    if(iminmu>ntbins-1){iminmu=iminmu-ntbins;}
    if(iminpi>ntbins-1){iminpi=iminpi-ntbins;}
  }
  printf(" frac of e in e mu pi cuts: %f %f %f\n",neine/allne,neinmu/allne,neinpi/allne);
  printf(" frac of mu in e mu pi cuts: %f %f %f\n",nmuine/allnmu,nmuinmu/allnmu,nmuinpi/allnmu);
  printf(" frac of pi in e mu pi cuts: %f %f %f\n",npiine/allnpi,npiinmu/allnpi,npiinpi/allnpi);

  for (Int_t k=0; k<ntbins; k++) {
    frace[k] = frace[k]/fracall[k];
    fracmu[k] = fracmu[k]/fracall[k];
    fracpi[k] = fracpi[k]/fracall[k];
  }
  
  Int_t iplot = 0;
  if (iplot==0) {
    //TGraph* gRNA=new TGraph(npts,Time,allfrac);
    //gRNA->SetLineColor(1);
    //gRNA->SetMarkerColor(2);
    //gRNA->SetMarkerStyle(2);
    //gRNA->SetMarkerSize(0.6);
    //gRNA->SetLineStyle(2);
    //gRNA->SetLineWidth(3);
    //gRNA->Draw("C");
    //thlegend->AddEntry(gRNA,"e+#mu+#pi","L");
    TGraph* gRNA0=new TGraph(npts,Time,efrac);
    gRNA0->SetLineColor(3);
    gRNA0->SetLineStyle(3);
    gRNA0->SetLineWidth(4);
    gRNA0->Draw("C");
    thlegend->AddEntry(gRNA0,"e","L");
    Float_t ycut[2], xcut[2];
    ycut[0] = 0.;
    ycut[1] = 750.;
    xcut[0] = imine*5./4.;
    xcut[1] = xcut[0];
    TGraph* gRNA1=new TGraph(2,xcut,ycut);
    gRNA1->SetLineColor(3);
    gRNA1->SetLineStyle(1);
    gRNA1->SetLineWidth(4);
    gRNA1->Draw("C");
    xcut[0] = (imine-5)*5./4.;
    if(xcut[0]<0.){xcut[0] = xcut[0]+20.;}
    xcut[1] = xcut[0];
    TGraph* gRNA2=new TGraph(2,xcut,ycut);
    gRNA2->SetLineColor(3);
    gRNA2->SetLineStyle(1);
    gRNA2->SetLineWidth(4);
    gRNA2->Draw("C");

    TGraph* gRNA3=new TGraph(npts,Time,mufrac);
    gRNA3->SetLineColor(4);
    gRNA3->SetLineStyle(4);
    gRNA3->SetLineWidth(4);
    gRNA3->Draw("C");
    thlegend->AddEntry(gRNA3,"#mu","L");
    xcut[0] = iminmu*5./4.;
    xcut[1] = xcut[0];
    TGraph* gRNA4=new TGraph(2,xcut,ycut);
    gRNA4->SetLineColor(4);
    gRNA4->SetLineStyle(1);
    gRNA4->SetLineWidth(4);
    gRNA4->Draw("C");
    xcut[0] = (iminmu-5)*5./4.;
    if(xcut[0]<0.){xcut[0] = xcut[0]+20.;}
    xcut[1] = xcut[0];
    TGraph* gRNA5=new TGraph(2,xcut,ycut);
    gRNA5->SetLineColor(4);
    gRNA5->SetLineStyle(1);
    gRNA5->SetLineWidth(4);
    gRNA5->Draw("C");

    TGraph* gRNA6=new TGraph(npts,Time,pifrac);
    gRNA6->SetLineColor(6);
    gRNA6->SetLineStyle(6);
    gRNA6->SetLineWidth(4);
    gRNA6->Draw("C");
    thlegend->AddEntry(gRNA6,"#pi","L");
    xcut[0] = iminpi*5./4.;
    xcut[1] = xcut[0];
    TGraph* gRNA7=new TGraph(2,xcut,ycut);
    gRNA7->SetLineColor(6);
    gRNA7->SetLineStyle(1);
    gRNA7->SetLineWidth(4);
    gRNA7->Draw("C");
    xcut[0] = (iminpi-5)*5./4.;
    if(xcut[0]<0.){xcut[0] = xcut[0]+20.;}
    xcut[1] = xcut[0];
    TGraph* gRNA8=new TGraph(2,xcut,ycut);
    gRNA8->SetLineColor(6);
    gRNA8->SetLineStyle(1);
    gRNA8->SetLineWidth(4);
    gRNA8->Draw("C");
  } 
  if (iplot==1) {
    TGraph* gRNA9=new TGraph(ntbins,Times,frace);
    gRNA9->SetLineColor(3);
    gRNA9->SetLineStyle(3);
    gRNA9->SetLineWidth(4);
    gRNA9->Draw("C");
    thlegend->AddEntry(gRNA9,"e","L");
    TGraph* gRNAa=new TGraph(ntbins,Times,fracmu);
    gRNAa->SetLineColor(4);
    gRNAa->SetLineStyle(4);
    gRNAa->SetLineWidth(4);
    gRNAa->Draw("C");
    thlegend->AddEntry(gRNAa,"#mu","L");
    TGraph* gRNAb=new TGraph(ntbins,Times,fracpi);
    gRNAb->SetLineColor(6);
    gRNAb->SetLineStyle(6);
    gRNAb->SetLineWidth(4);
    gRNAb->Draw("C");
    thlegend->AddEntry(gRNAb,"#pi","L");
  }
}
