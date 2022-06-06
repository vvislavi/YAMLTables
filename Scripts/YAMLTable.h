#ifndef YAMLTable__H
#define YAMLTable__H
#include "TString.h"
#include "TH1.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TNamed.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

class YAMLTable {
 public:
  YAMLTable();
  ~YAMLTable();
  Bool_t fAsymmetric;
  TString *fTableName;
  TString *fXTitle;
  TString *fYTitle;
  TString *fDrawTags;
  TH1 *fInHist; //Input histogram
  TH1 *fInHistSyst; //Input histogram
  TH1 *fInHistUnc; //Input histogram
  TGraphErrors *fInGra; //Input graph
  TGraphErrors *fInGraSyst; //Input graph syst;
  TGraphErrors *fInGraUnc; //Input graph unc.
  TGraphAsymmErrors *fInAsGra; //Input graph
  TGraphAsymmErrors *fInAsGraSyst; //Input graph syst;
  TGraphAsymmErrors *fInAsGraUnc; //Input graph unc.
  Double_t fXMin, fXMax;
  TObjArray *fXArray;
  TObjArray *fYArray;
  TString *fDescription;
  TString *fLocation;
  TObjArray *fKeywords;
  TObjArray *fQualifiers;
  Double_t fExtScale;
  const char **fExtXLabels;
  void SetXLabels(const char **nlbs) { fExtXLabels = nlbs; };
  void BuildXArray();
  void BuildYArray();
  void AddXValue(const char *lentry, const char *lname="") { fXArray->Add(new TNamed(lname,lentry)); };
  void AddYValue(const char *lentry, const char *lname="") { fYArray->Add(new TNamed(lname,lentry)); };
  void SetInputHistograms(TH1 *inh_stat, TH1 *inh_sys=0, TH1 *inh_unc=0);
  void SetInputGraphs(TGraphErrors *gr_stat, TGraphErrors *gr_syst=0, TGraphErrors *gr_unc=0);
  void SetInputAsGraphs(TGraphAsymmErrors *gr_stat, TGraphAsymmErrors *gr_syst=0, TGraphAsymmErrors *gr_unc=0);
  void SetNameAndTitles(const char *lName, const char *lxTitle, const char *lyTitle);
  void AddKeywords(const char *lname, const char *lvalue);
  void AddDescription(const char *ldescription) { ClearDescription(); fDescription->Append(ldescription); };
  void AddQualifier(const char *lname, const char *lvalue);
  void ClearKeywords() { fKeywords->Clear(); };
  void ClearDescription() { fDescription->Clear(); };
  void ClearQualifiers() { fQualifiers->Clear(); };
  void SetLocation(const char *newval);
  void ClearLocation() { if(fLocation) fLocation->Clear(); };
  void LimitXRange(Double_t lxmin, Double_t lxmax) { fXMin=lxmin; fXMax=lxmax; };
  void PrintTableToFile(Bool_t ContinueInSameFile=kFALSE);
  void AddToSubmissions();
  void SetDrawTags(const char *newtags) { fDrawTags->Clear(); fDrawTags->Append(newtags);};
  void SetExtScale(Double_t newval) { fExtScale=newval; };
  Int_t FindXMin(Double_t lXMin);
  Int_t FindXMax(Double_t lXMax);
  Double_t GetXLower(Int_t bin);
  Double_t GetXHigher(Int_t bin);
  Double_t GetXCenter(Int_t bin);
  Double_t GetYValue(Int_t bin);
  Double_t GetYStat(Int_t bin) { return (fInHist?fInHist->GetBinError(bin):fInGra->GetErrorY(bin))*fExtScale; };
  Double_t GetYSyst(Int_t bin) { return (fInHistSyst?fInHistSyst->GetBinError(bin):fInGraSyst->GetErrorY(bin))*fExtScale;};
  Double_t GetYUnc(Int_t bin) { return (fInHistUnc?fInHistUnc->GetBinError(bin):fInGraUnc->GetErrorY(bin))*fExtScale;};
  Double_t *GetYAsStat(Int_t bin);
  Double_t *GetYAsSyst(Int_t bin);
  Double_t *GetYAsUnc(Int_t bin);
 private:
  TString *fFileName;
};


#endif
