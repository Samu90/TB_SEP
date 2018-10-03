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

void MIPFind(){
  

}


int main(int argc, char **argv){

  TFile*  file= TFile::Open(argv[1]);
  TTree* digiTree = (TTree*)file->Get("digi");

  Float_t amp_max[15],MIPVal;

  MIPFind(digiTree,&MIPVal);
}
