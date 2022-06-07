#ifndef LOADHISTOGRAM__C
#define LOADHISTOGRAM__C
#include "TString.h"
#include "TH1D.h"
#include "Scripts/CommonFunctions.C"
#include "TNamed.h"


void ProduceATable(TString HistFile, TString histName, Bool_t ContinueInFile, Int_t FigureNo, Int_t &gCounter, TString l_xLabel, TString l_yLabel, TString l_Description, vector<TString> l_observables, Double_t xMin, Double_t xMax, vector< pair<TString, TString> > extraQs = {}) {
  YAMLTable *tb = new YAMLTable();
  tb->SetDrawTags("XWidth; YStat; YSyst");
  TH1D *stat, *syst, *unc;
  stat = (TH1D*)GetHistFromFile(HistFile,Form(histName.Data(),""));
  syst = (TH1D*)GetHistFromFile(HistFile,Form(histName.Data(),"sys"));
  if(!stat || !syst) printf("Could not fetch histograms!\n");
  tb->SetInputHistograms(stat,syst);
  tb->LimitXRange(xMin,xMax);
  if(ContinueInFile) gCounter--;
  tb->SetNameAndTitles(Form("Table %i",gCounter++),l_xLabel,l_yLabel);
  tb->SetLocation(Form("Table from Figure %i",FigureNo));
  // tb->AddDescription("The flow angle fluctuation $A_{\\rm 2}^{\\rm f}$ as a function of $p_{\\rm T}^{\\rm a}$ in different centrality classes");
  // tb->AddKeywords("observables","'$A_{2}^{\\rm f}$'");
  tb->AddDescription(l_Description);
  for(Int_t i=0;i<l_observables.size();i++) tb->AddKeywords("observables","'"+l_observables.at(i)+"'");
  tb->AddKeywords("cmenergies","5020");
  tb->AddKeywords("reactions","'Pb Pb --> $X$'");
  // tb->AddQualifier("Centrality","0-5");
  tb->AddQualifier("RE","Pb Pb --> $X$");
  tb->AddQualifier("SQRT(S)","5020.0 GEV");
  tb->AddQualifier("ETARAP(CM)","\'$|\\eta| < 0.8$\'");
  for(Int_t i=0; i<extraQs.size(); i++) tb->AddQualifier(extraQs.at(i).first, extraQs.at(i).second);
  tb->PrintTableToFile(ContinueInFile);
  if(!ContinueInFile)
    tb->AddToSubmissions();
  delete tb;
};
#endif
