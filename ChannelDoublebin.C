#include <iostream>

void ChannelDoublebin()
{
const int n_points=78;
float avg = 0;
float sum = 0;
int length = 0;
TCanvas *c1= new TCanvas("c1","Title",0,0,400,400);
c1->SetGrid();

Float_t px1[]= {2,
2,
2,
2,
2,
3,
3,
3,
3,
3,
3,
3,
3,
3
};

length = (sizeof(px1)/sizeof(*px1));

cout << "The length is " << length <<endl;

//Scaling array by 0.15
for (int i=0; i<length; i++) px1[i] *= 0.15;
for (int i=0; i<length; i++) sum+=px1[i];
avg = sum/length;
cout << "The numerical average is " << std::setprecision(3) << avg << endl;

//Filling Histogram with Array px1[]
TH1F *hist= new TH1F("histt", "my first macro histogram", 10,0,0.65);

//Formatting Plot
hist->SetTitle("Counts per Bin Size");
hist->SetYTitle("Counts");
hist->SetXTitle("Bin Size");
hist->GetYaxis()->SetTitleOffset(1.25);
hist->GetYaxis()->SetTitleFont(42);
hist->GetYaxis()->CenterTitle();
hist->GetXaxis()->SetTitleFont(42);
hist->GetXaxis()->CenterTitle();
hist->GetXaxis()->SetTitleOffset(1.25);
hist->SetLineColor(4);
hist->SetLineWidth(2);

hist->Draw();
for (int i=0; i<length; i++ )
{
hist->Fill(px1[i]);
}

//hist->Update();
//delete hist();

} 	
