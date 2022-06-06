#ifndef LOADSOMEGRAPHERRORS__C
#define LOADSOMEGRAPHERRORS__C
#include "TString.h"
#include "TGraphErrors.h"
#include "Scripts/CommonFunctions.C"
#include "Scripts/YAMLTable.cxx"

TString InputFile("InputData/hepdata.root");
void ProduceGraphTablePbPb(TString grname, Bool_t ContinueInFile, Int_t FigureNo, Int_t &gCounter) {
  YAMLTable *tb = new YAMLTable();
  tb->SetDrawTags("YStat; YSyst");
  TGraphErrors *stat, *syst;
  stat = GetGraphFromFile(InputFile,grname+"_stat");
  syst = GetGraphFromFile(InputFile,grname+"_sys");
  tb->SetInputGraphs(stat,syst);
  if(ContinueInFile && gCounter>1) gCounter--;
  TString yTitle = Form("$\\rho\\left(v_{%i}^{2}, [p_{\\rm T}] \\right)$",ContinueInFile?3:2);
  tb->SetNameAndTitles(Form("Table %i",gCounter++),
                       "Centrality",
                       yTitle.Data());
  tb->AddKeywords("reactions","'Pb Pb --> $h^{\\pm}$'");
  tb->AddQualifier("RE","'Pb Pb --> $h^{\\pm}$'");
  // tb->AddKeywords("$\\rho\\left(v_{2}^{2}, p_{\\rm T} \\right)$","'2*i+rn->Rndm()'");
  tb->AddKeywords("cmenergies","5020");
  tb->AddQualifier("SQRT(S)","5020.0 GEV");
  tb->AddQualifier("ABS(ETA)","'$< 0.8$'");
  tb->AddQualifier("PT","'$0.2 - 3.0$ GeV/$c$'");
  tb->SetLocation(Form("Table from Figure %i",FigureNo));
  tb->AddDescription("'Centrality dependence of $\\rho\\left(v_{2}^{2}, [p_{\\rm T}] \\right)$  and $\\rho\\left(v_{3}^{2}, [p_{\\rm T}] \\right)$ in Pb--Pb collisions at $\\sqrt{s_{\\rm NN}}$ = 5.02 TeV'");
  tb->PrintTableToFile(ContinueInFile);
  if(!ContinueInFile)
    tb->AddToSubmissions();
  delete tb;
};
void ProduceGraphTableXeXePCC2(TString grname, Bool_t ContinueInFile, Int_t FigureNo, Int_t &gCounter) {
  YAMLTable *tb = new YAMLTable();
  tb->SetDrawTags("YStat; YSyst");
  TGraphErrors *stat, *syst;
  stat = GetGraphFromFile(InputFile,grname+"_stat");
  syst = GetGraphFromFile(InputFile,grname+"_sys");
  tb->SetInputGraphs(stat,syst);
  if(ContinueInFile && gCounter>1) gCounter--;
  TString yTitle = Form("$\\rho\\left(v_{%i}^{2}, [p_{\\rm T}] \\right)$",2);
  tb->SetNameAndTitles(Form("Table %i",gCounter++),
                       "Centrality",
                       yTitle.Data());
  tb->AddKeywords("reactions","'Xe Xe --> $h^{\\pm}$'");
  tb->AddQualifier("RE","'Xe Xe --> $h^{\\pm}$'");
  // tb->AddKeywords("$\\rho\\left(v_{2}^{2}, p_{\\rm T} \\right)$","'2*i+rn->Rndm()'");
  tb->AddKeywords("cmenergies","5440");
  tb->AddQualifier("SQRT(S)","5440.0 GEV");
  tb->AddQualifier("ABS(ETA)","'$< 0.8$'");
  tb->AddQualifier("PT","'$0.2 - 3.0$ GeV/$c$'");
  tb->SetLocation(Form("Table from Figure %i",FigureNo));
  tb->AddDescription("'Centrality dependence of $\\rho\\left(v_{2}^{2}, [p_{\\rm T}] \\right)$ in Xe--Xe collisions at $\\sqrt{s_{\\rm NN}}$ = 5.44 TeV'");
  tb->PrintTableToFile(ContinueInFile);
  if(!ContinueInFile)
    tb->AddToSubmissions();
  delete tb;
};
void ProduceGraphTableXeXePCC3(TString grname, Bool_t ContinueInFile, Int_t FigureNo, Int_t &gCounter) {
  YAMLTable *tb = new YAMLTable();
  tb->SetDrawTags("YStat; YSyst");
  TGraphErrors *stat, *syst;
  stat = GetGraphFromFile(InputFile,grname+"_stat");
  syst = GetGraphFromFile(InputFile,grname+"_sys");
  tb->SetInputGraphs(stat,syst);
  tb->LimitXRange(0,45);
  if(ContinueInFile && gCounter>1) gCounter--;
  TString yTitle = Form("$\\rho\\left(v_{%i}^{2}, [p_{\\rm T}] \\right)$",3);
  tb->SetNameAndTitles(Form("Table %i",gCounter++),
                       "Centrality",
                       yTitle.Data());
  tb->AddKeywords("reactions","'Xe Xe --> $h^{\\pm}$'");
  tb->AddQualifier("RE","'Xe Xe --> $h^{\\pm}$'");
  // tb->AddKeywords("$\\rho\\left(v_{2}^{2}, p_{\\rm T} \\right)$","'2*i+rn->Rndm()'");
  tb->AddKeywords("cmenergies","5440");
  tb->AddQualifier("SQRT(S)","5440.0 GEV");
  tb->AddQualifier("ABS(ETA)","'$< 0.8$'");
  tb->AddQualifier("PT","'$0.2 - 3.0$ GeV/$c$'");
  tb->SetLocation(Form("Table from Figure %i",FigureNo));
  tb->AddDescription("'Centrality dependence of $\\rho\\left(v_{3}^{2}, [p_{\\rm T}] \\right)$ in Xe--Xe collisions at $\\sqrt{s_{\\rm NN}}$ = 5.44 TeV'");
  tb->PrintTableToFile(ContinueInFile);
  if(!ContinueInFile)
    tb->AddToSubmissions();
  delete tb;
};
void ProduceGraphTablePbPbMH(TString grname, Bool_t ContinueInFile, Int_t FigureNo, Int_t &gCounter) {
  YAMLTable *tb = new YAMLTable();
  tb->SetDrawTags("YStat; YSyst");
  TGraphErrors *stat, *syst;
  stat = GetGraphFromFile(InputFile,grname+"_stat");
  syst = GetGraphFromFile(InputFile,grname+"_sys");
  tb->SetInputGraphs(stat,syst);
  tb->LimitXRange(0,45);
  if(ContinueInFile && gCounter>1) gCounter--;
  TString yTitle = "$\\rho\\left(v_{2}^{2}, v_{3}^{2}, [p_{\\rm T}] \\right)$";
  tb->SetNameAndTitles(Form("Table %i",gCounter++),
                       "Centrality",
                       yTitle.Data());
  tb->AddKeywords("reactions","'Pb Pb --> $h^{\\pm}$'");
  tb->AddQualifier("RE","'Pb Pb --> $h^{\\pm}$'");
  // tb->AddKeywords("$\\rho\\left(v_{2}^{2}, p_{\\rm T} \\right)$","'2*i+rn->Rndm()'");
  tb->AddKeywords("cmenergies","5020");
  tb->AddQualifier("SQRT(S)","5020.0 GEV");
  tb->AddQualifier("ABS(ETA)","'$< 0.8$'");
  tb->AddQualifier("PT","'$0.2 - 3.0$ GeV/$c$'");
  tb->SetLocation(Form("Table from Figure %i",FigureNo));
  tb->AddDescription("'Centrality dependence of $\\rho\\left(v_{2}^{2}, v_{3}^{2}, [p_{\\rm T}] \\right)$ in Pb--Pb collisions at $\\sqrt{s_{\\rm NN}}$ = 5.02 TeV'");
  tb->PrintTableToFile(ContinueInFile);
  if(!ContinueInFile)
    tb->AddToSubmissions();
  delete tb;
};

#endif
