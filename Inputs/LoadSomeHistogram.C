#ifndef LOADSOMEHISTOGRAM__C
#define LOADSOMEHISTOGRAM__C
#include "TString.h"
#include "TH1D.h"
#include "Scripts/CommonFunctions.C"
TString HistFile("InputData/SomeHistograms.root");


void ProduceHistogramTable(TString histName, Bool_t ContinueInFile, Int_t FigureNo, Int_t &gCounter) {
  YAMLTable *tb = new YAMLTable();
  tb->SetDrawTags("XWidth; YStat; YSyst; YUnc");
  TH1D *stat, *syst, *unc;
  stat = (TH1D*)GetHistFromFile(HistFile,histName+"_stat");
  syst = (TH1D*)GetHistFromFile(HistFile,histName+"_syst");
  unc = (TH1D*)GetHistFromFile(HistFile,histName+"_unc");
  if(!stat || !syst || !unc) printf("Could not fetch histograms!\n");
  tb->SetInputHistograms(stat,syst,unc);
  if(ContinueInFile) gCounter--;
  tb->SetNameAndTitles(Form("Table %i",gCounter++),"x-axis title","y-axis title");
  tb->SetLocation(Form("Table from Figure %i",FigureNo));
  tb->AddDescription("Some distribution from histogram");
  tb->AddKeywords("observables","D2N/DPT/DYRAP");
  tb->AddKeywords("cmenergies","13000");
  tb->AddKeywords("reactions","'P P --> $X$'");
  tb->AddQualifier("Mutliplicity","0-100");
  tb->AddQualifier("RE","P P --> $X$");
  tb->AddQualifier("SQRT(S)","13000.0 GEV");
  tb->AddQualifier("YRAP(CM)","\'$-0.5 < y < 0.5$\'");
  tb->PrintTableToFile(ContinueInFile);
  if(!ContinueInFile)
    tb->AddToSubmissions();
  delete tb;
};
#endif
