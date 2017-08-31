#include <iostream>

void ChannelPlot_try()
{
  //const int n_points=78;
  float avg = 0;
  float sum = 0;
  int length = 0;
  //TCanvas *c1= new TCanvas("c1","Title",0,0,600,600);
  //c1->SetGrid();
  int j=0;
  TH1F *hist[48]={};
//this data is wrong. just for trial.
  Float_t px1[]= {2,2,2,2,2,2,1,1,1,2,2,2,2,1,2,2,1,1,2,1,1,1,1,1,1,2,2,2,1,1,2,2,1,2,2,2,2,1,2,1,1,1,3,1,2,1,2,2,
		  2,2,2,2,2,2,1,2,2,2,2,3,2,2,2,2,1,1,2,1,2,1,1,1,2,2,2,2,1,2,2,2,1,2,2,2,2,1,2,2,2,1,3,2,2,1,2,2,
		  2,2,2,2,2,2,1,2,2,3,2,3,3,2,2,2,2,1,2,2,2,1,1,2,2,2,2,3,1,2,2,2,1,2,2,2,2,1,2,2,2,2,3,2,2,1,2,2,
		  2,2,2,2,2,2,2,2,2,3,2,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,1,2,2,2,2,2,2,2,2,2,2,2,2,2,3,2,2,2,2,2,
		  2,2,2,2,2,2,2,2,2,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,2,2,2,2,2,3,2,2,2,2,2,2,2,2,3,2,3,2,2,2,
		  2,2,3,2,2,2,3,3,2,3,0,3,3,3,2,3,2,2,3,3,3,2,3,2,2,2,3,3,2,2,3,2,2,3,3,3,2,2,2,2,2,2,3,2,3,2,3,2,
		  2,2,3,3,3,2,3,3,2,3,0,3,3,3,3,3,2,3,3,3,3,2,3,2,3,2,3,3,2,2,3,2,2,3,3,3,2,2,2,3,3,3,3,2,3,2,3,3,
		  2,2,3,3,3,3,3,3,2,3,0,3,0,3,0,3,2,3,3,3,3,2,3,2,3,2,3,3,3,3,3,2,2,3,3,3,2,3,0,3,3,3,3,2,3,2,0,3,
		  2,2,3,3,3,3,3,0,2,3,0,3,0,3,0,0,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,2,3,3,3,3,2,3,0,3,3,3,0,2,3,2,0,3,
		  2,2,3,3,3,3,3,0,2,3,0,3,0,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,2,3,0,3,3,3,0,2,3,3,0,3,
		  2,3,3,3,3,3,0,0,2,3,0,3,0,3,0,0,0,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,0,3,0,3,0,0,3,3,3,0,3,3,0,0,3,
		  2,3,3,3,3,3,0,0,2,3,0,3,0,3,0,0,0,3,3,3,3,0,3,3,3,3,3,3,3,3,0,3,3,0,3,0,3,0,0,3,3,3,0,3,3,0,0,3,
		  3,3,3,3,3,3,0,0,3,3,0,3,0,3,0,0,0,3,3,3,3,0,0,3,3,3,3,3,3,3,0,3,3,0,3,0,3,0,0,3,3,3,0,3,3,0,0,3,
		  3,3,3,0,3,0,0,0,3,3,0,3,0,3,0,0,0,3,3,3,0,0,0,3,4,3,3,3,3,3,0,0,3,0,3,0,3,0,0,3,3,3,0,3,3,0,0,3,
		  0,0,0,0,3,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,3,0,0,0,0,0,0,3,0,3,0,0,3,0,0,0,3,0,0,0,0,
		  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0};

  length = (sizeof(px1)/sizeof(*px1));

  //cout << "The length is " << length <<endl;

  //Scaling array by 0.15
  for (int i=0; i<length; i++) px1[i] *= 0.15;
  //for (int i=0; i<length; i++) sum+=px1[i];
  //avg = sum/length;
  //cout << "The numerical average is " << std::setprecision(3) << avg << endl;
 
  for(int k=0;k<=47; k++){
  //Open a temporary canvas. it is not required. But I took this from Ian's coe and this works. So, why not!!  
 TCanvas *temp_canvOpen = new TCanvas("temp", "temp", 800, 600);
 std:: string thePDFFileName= "Output_";
       thePDFFileName= thePDFFileName + std::to_string(k)+".pdf";


    std::string h_Title="Channel_";
    //Filling Histogram with Array px1[]
    std::string h_Name="Histogram for Channel_";
    h_Title+= std::to_string(k);
    h_Name+= std::to_string(k);
    hist[k]=new TH1F(h_Title.c_str(),h_Name.c_str(), 20,0.05,0.75);
    
    // each time thie pointer hist[k] is creating a new object, and the name of the object has to be different. Root keeps track of the TObjects via names, so two objects can't have a same name. That is whay I need to append the namewith a number every time.
    


    //Formatting Plot
    hist[k]->SetTitle("Counts per Bin Size");
    hist[k]->SetYTitle("Counts");
    hist[k]->SetXTitle("Bin Size with two counts");
    hist[k]->GetYaxis()->SetTitleOffset(1.25);
    hist[k]->GetYaxis()->SetTitleFont(42);
    hist[k]->GetYaxis()->CenterTitle();
    hist[k]->GetXaxis()->SetTitleFont(42);
    hist[k]->GetXaxis()->CenterTitle();
    hist[k]->GetXaxis()->SetTitleOffset(1.25);
    hist[k]->SetLineColor(4);
    hist[k]->SetLineWidth(2);


    hist[k]->Draw();


    // the following stsep takes care of the histogram filling of only 16 elemnts in one histogram (e.g hist[1]).
    for (int i=0; i<=15; i++ )
      {

	hist[k]->Fill(px1[i+j]);
	//	cout<< px1[i+j];
      } 
    j=j+16;
   
       
  temp_canvOpen->SaveAs(thePDFFileName.c_str());  
  //temp_canvOpen->UseCurrentStyle();
temp_canvOpen->Close();

    
// c1->Print(thePDFFileName.c_str()+".pdf");
  }
}	
