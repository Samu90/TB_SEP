//LibAnalysis.h

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TROOT.h"
#include "stdio.h"
#include "string.h"

Float_t MIPFind(Float_t* amp_L,Float_t* amp_R,Float_t* MIP_L,Float_t* MIP_R,Int_t nentries){
  TH1F* AmpDistribHisto[2];
  Int_t i;
  Int_t nbin=300;

  AmpDistribHisto[0] = new TH1F("DistribAmpL","DistribAmpL",nbin,0,1);
  AmpDistribHisto[1] = new TH1F("DistribAmpR","DistribAmpR",nbin,0,1);
  
  for(i=0;i<nentries;i++){
    AmpDistribHisto[0]->Fill(amp_L[i]);
    AmpDistribHisto[1]->Fill(amp_R[i]);
  }
  
  TF1* FitLandau[2];
  FitLandau[0]= new TF1("FLand_L","landau",0.2,0.5);
  FitLandau[1]= new TF1("FLand_R","landau",0.2,0.5);
  AmpDistribHisto[0]->Fit("FLand_L","R0");  
  AmpDistribHisto[1]->Fit("FLand_R","R0");

  TLegend* legenda[2];

  legenda[0] = new TLegend();
  legenda[1] = new TLegend();

  TCanvas* CanvasHisto = new TCanvas("CanvasDistribAmp","",1200,800);
  CanvasHisto->Divide(2,1);
  
  CanvasHisto->cd(1)->SetLogy();
  AmpDistribHisto[0]->GetXaxis()->SetTitle("amp_max[mv]");
  AmpDistribHisto[0]->GetYaxis()->SetTitle("counts");
  AmpDistribHisto[0]->Draw("HISTO");
  FitLandau[0]->DrawF1(0.0,1.0,"SAME");
  legenda[0]->AddEntry(FitLandau[0],("MIP="+std::to_string(FitLandau[0]->GetParameter(1))).c_str());
  legenda[0]->Draw();

  CanvasHisto->cd(2)->SetLogy();
  AmpDistribHisto[0]->GetXaxis()->SetTitle("amp_max[mv]");
  AmpDistribHisto[0]->GetYaxis()->SetTitle("counts");
  AmpDistribHisto[1]->Draw("HISTO");
  FitLandau[1]->DrawF1(0.0,1.0,"SAME");
  legenda[1]->AddEntry(FitLandau[1],("MIP="+std::to_string(FitLandau[1]->GetParameter(1))).c_str());
  legenda[1]->Draw();
 
  *MIP_L=FitLandau[0]->GetParameter(1);
  *MIP_R=FitLandau[1]->GetParameter(1);
  
  
  CanvasHisto->SaveAs("Plots/PlotFitLandau.pdf");
  
 
}


