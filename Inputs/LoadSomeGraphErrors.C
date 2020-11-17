#ifndef LOADSOMEGRAPHERRORS__C
#define LOADSOMEGRAPHERRORS__C
#include "TString.h"
#include "TGraphErrors.h"
#include "Scripts/CommonFunctions.C"
#include "Scripts/YAMLTable.cxx"

TString GraphErrorsFile("InputData/SomeGraph.root");
void ProduceGraphTable(TString grname, Bool_t ContinueInFile, Int_t FigureNo, Int_t &gCounter) {
  YAMLTable *tb = new YAMLTable();
  tb->SetDrawTags("YStat; YSyst");
  TGraphErrors *stat, *syst;
  stat = GetGraphFromFile(GraphErrorsFile,grname+"_stat");
  syst = GetGraphFromFile(GraphErrorsFile,grname+"_syst");
  tb->SetInputGraphs(stat,syst);
  if(ContinueInFile) gCounter--;
  tb->SetNameAndTitles(Form("Table %i",gCounter++),
                       "x-axis",
                       "y-axis");
  tb->AddKeywords("reactions","'P P --> $X$'");
  tb->AddQualifier("RE","P P --> $X$");
  tb->AddKeywords("observables","'2*i+rn->Rndm()'");
  tb->AddKeywords("cmenergies","13000");
  tb->AddQualifier("SQRT(S)","13000.0 GEV");
  tb->AddQualifier("YRAP(CM)","\'$-0.5 < y < 0.5$\'");
  tb->SetLocation(Form("Table from Figure %i",FigureNo));
  tb->AddDescription("Values from a random graph");
  tb->PrintTableToFile(ContinueInFile);
  if(!ContinueInFile)
    tb->AddToSubmissions();
  delete tb;
};

#endif
