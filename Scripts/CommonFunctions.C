#ifndef COMMONFUNCTIONS__C
#define COMMONFUNCTIONS__C
#include "TH1.h"
#include "TGraphErrors.h"
#include "TMath.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
TFile *GetFile(TString infile) {
  TFile *tf = new TFile(infile,"READ");
  if(!tf) {
    printf("Could not open file %s\n",infile.Data());
    return 0;
  };
  if(tf->IsZombie()) {
    printf("File %s is a zombie\n",tf->GetTitle());
    return 0;
  };
  return tf;
};
TH1 *GetHistFromFile(TFile *tf, TString spName) {
  if(!tf) return 0;
  TH1 *retHist = (TH1*)tf->Get(spName.Data());
  if(!retHist) {printf("Could not get %s from %s\n",spName.Data(),tf->GetName()); return 0;};
  retHist = (TH1D*)retHist->Clone(spName.Data());
  retHist->SetDirectory(0);
  return retHist;
}
TH1 *GetHistFromFile(TString fiName, TString spName) {
  TFile *tf = GetFile(fiName);
  if(!tf) return 0;
  TH1 *retHist = GetHistFromFile(tf,spName);
  tf->Close();
  return retHist;
}
TGraphErrors *GetGraphFromFile(TFile *tf, TString spName) {
  if(!tf) return 0;
  TGraphErrors *retGraph = (TGraphErrors*)tf->Get(spName.Data());
  if(!retGraph) {printf("Could not get %s from %s\n",spName.Data(),tf->GetName()); return 0;};
  return retGraph;
}
TGraphErrors *GetGraphFromFile(TString fiName, TString spName) {
  TFile *tf = GetFile(fiName);
  if(!tf) return 0;
  TGraphErrors *retGraph = GetGraphFromFile(tf,spName);
  tf->Close();
  return retGraph;
}
TGraphAsymmErrors *GetAsymGraphFromFile(TFile *tf, TString spName) {
  if(!tf) return 0;
  TGraphAsymmErrors *retGraph = (TGraphAsymmErrors*)tf->Get(spName.Data());
  if(!retGraph) {printf("Could not get %s from %s\n",spName.Data(),tf->GetName()); return 0;};
  return retGraph;
}
TGraphAsymmErrors *GetAsymGraphFromFile(TString fiName, TString spName) {
  TFile *tf = GetFile(fiName);
  if(!tf) return 0;
  TGraphAsymmErrors *retGraph = GetAsymGraphFromFile(tf,spName);
  tf->Close();
  return retGraph;
}
TGraphErrors *AsymGraphToSym(TGraphAsymmErrors *ingr) {
  TGraphErrors *retGr = new TGraphErrors();
  Double_t *x = ingr->GetX();
  Double_t *y = ingr->GetY();
  Double_t *exl = ingr->GetEXlow();
  Double_t *exh = ingr->GetEXlow();
  Double_t *eyl = ingr->GetEYlow();
  Double_t *eyh = ingr->GetEYhigh();
  for(Int_t i=0;i<ingr->GetN();i++) {
    retGr->SetPoint(i,x[i],y[i]);
    retGr->SetPointError(i,(exl[i]+exh[i])/2, (eyl[i]+eyh[i])/2);
  }
  return retGr;
}
#endif
