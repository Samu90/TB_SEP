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
#include "LibAnalysis.h"

//per compilare g++ -o leak1 Analisi.cpp LibAnalysis.h $WITHROOT

int main(int argc, char **argv){

  TFile*  file= TFile::Open(argv[1]);
  TTree* digiTree = (TTree*)file->Get("digi");

  Int_t LAmp=15; //Lunghezza tempo
  Int_t LTime=239; //Lunghezza ampiezze
  Int_t i;
  Int_t max=4096; //Qual'è il massimo??

  Float_t amp_max[LAmp],time[LTime];
  Int_t LED300;
  Int_t AMP1,AMP2;
  
  Float_t MIP_L,MIP_R;

  digiTree->SetBranchAddress("amp_max",&amp_max);
  digiTree->SetBranchAddress("time",&time);
  digiTree->SetBranchAddress("LED300",&LED300);
  digiTree->SetBranchAddress("AMP1",&AMP1);
  digiTree->SetBranchAddress("AMP2",&AMP2);

  gSystem->Exec("rm -r -f Plots");
  gSystem->Exec("mkdir Plots");

  
  Int_t nentries=digiTree->GetEntries();
  Float_t amp_L[nentries], amp_R[nentries];
  
  for(i=0;i<nentries;i++){
    digiTree->GetEntry(i);
    amp_L[i]=amp_max[AMP1]/max;
    amp_R[i]=amp_max[AMP2]/max;
    
    if(i%10000==0) std::cout << i <<" / "<< nentries <<"   "<<amp_L[i]<<std::endl;
  }// chiudo for i-nentries

  MIPFind(amp_L,amp_R,&MIP_L,&MIP_R,nentries);
  
  
}//chiudo main
