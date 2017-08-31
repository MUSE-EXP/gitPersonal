#include<Tpad.h>
#include<Tcanvas.h>
#include<plot_figure2.h>

void plotanalysis() {
  c = new TCanvas("c","piM1 beam RF time / pi rejection",000,10,540,540);
  c->SetGrid();
  plot_figure2(gPad);

  gStyle->SetPaperSize(20,26);  //default
  TString fn = "trigpirejm153";
  c->SaveAs(fn+".pdf");
  c->SaveAs(fn+".eps");
  c->SaveAs(fn+".png");
}

