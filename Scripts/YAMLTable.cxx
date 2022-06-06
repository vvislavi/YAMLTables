#ifndef YAMLTABLE__CXX
#define YAMLTABLE__CXX
#include "YAMLTable.h"

YAMLTable::YAMLTable():
  fAsymmetric(kFALSE),
  fTableName(new TString("output")),
  fXTitle(new TString("x")),
  fYTitle(new TString("y")),
  fDrawTags(new TString("XWidth; YStat; YSyst; YUnc")),
  fInHist(0),
  fInHistSyst(0),
  fInHistUnc(0),
  fInGra(0),
  fInGraSyst(0),
  fInGraUnc(0),
  fInAsGra(0),
  fInAsGraSyst(0),
  fInAsGraUnc(0),
  fXMin(0),
  fXMax(-1),
  fXArray(0),
  fYArray(0),
  fLocation(0),
  fDescription(new TString("no description")),
  fKeywords(0),
  fQualifiers(0),
  fExtScale(1),
  fExtXLabels(0),
  fFileName(new TString("mytable.yaml"))
{
};
YAMLTable::~YAMLTable() {
  delete fTableName;
  delete fXTitle;
  delete fYTitle;
  delete fXArray;
  delete fYArray;
  delete fFileName;
  delete fLocation;
  delete fKeywords;
  delete fQualifiers;
};
void YAMLTable::BuildXArray() {
  if(fXArray) fXArray->Clear();
  else {
    fXArray = new TObjArray();
    fXArray->SetOwner(kTRUE);
  };
  AddXValue(Form("- header: {name: \'%s\'}",fXTitle->Data()),"");
  AddXValue("  values:","");
  Int_t startind=fXMax>fXMin?FindXMin(fXMin+1e-6):FindXMin(-1e6);
  Int_t stopind=fXMax>fXMin?FindXMax(fXMax-1e-6):FindXMax(1e6);
  if(startind>stopind) {
    Int_t tempind = startind;
    startind=stopind;
    stopind=tempind;
  };
  for(Int_t i=startind;i<=stopind;i++) {
    if(fExtXLabels)
      AddXValue(Form("  - value: %s",fExtXLabels[i]));
    else {
      if(GetYValue(i)==0) continue;
      if(fDrawTags->Contains("XWidth"))
	     AddXValue(Form("  - {low: %f, high: %f}",GetXLower(i),GetXHigher(i)));
      else
	     AddXValue(Form("  - value: %e",GetXCenter(i)));
    };
  };
};
void YAMLTable::BuildYArray() {
  if(fYArray) fYArray->Clear();
  else {
    fYArray = new TObjArray();
    fYArray->SetOwner(kTRUE);
  };
  AddYValue(Form("- header: {name: \'%s\'}",fYTitle->Data()),"");
  if(fQualifiers) {
    if(fQualifiers->GetEntries()>0) {
      AddYValue("  qualifiers:","");
      for(Int_t i=0;i<fQualifiers->GetEntries();i++) {
	       AddYValue(Form("  - {name: %s, value: %s}",fQualifiers->At(i)->GetName(), fQualifiers->At(i)->GetTitle()),"");
      };
    };
  };

  AddYValue("  values:","");
  Int_t startind=fXMax>fXMin?FindXMin(fXMin+1e-6):FindXMin(-1e6);
  Int_t stopind=fXMax>fXMin?FindXMax(fXMax-1e-6):FindXMax(1e6);
  for(Int_t i=startind;i<=stopind;i++) {
    if(GetYValue(i)==0) continue;
    AddYValue("  - errors:");
    if(fAsymmetric) {
      if(fDrawTags->Contains("YStat")) {
        Double_t *err = GetYAsStat(i);
        AddYValue(Form("    - {asymerror: {plus: %e, minus: -%e}, label: stat}",err[0],err[1]));
        //delete [] err; //Uncomment
      };
      if(fDrawTags->Contains("YSyst")) {
        Double_t *err = GetYAsSyst(i);
        AddYValue(Form("    - {asymerror: {plus: %e, minus: -%e}, label: \'full syst.\'}",err[0],err[1]));
        //delete [] err; //Uncomment
      };
      if(fDrawTags->Contains("YUnc")) {
        Double_t *err = GetYAsSyst(i);
        AddYValue(Form("    - {asymerror: {plus: %e, minus: -%e}, label: \'unc. syst.\'}",err[0],err[1]));
        //delete [] err; //Uncomment
      };

    } else {
      if(fDrawTags->Contains("YStat"))
        AddYValue(Form("    - {symerror: %e, label: stat}",GetYStat(i)));
      if(fDrawTags->Contains("YSyst"))
        AddYValue(Form("    - {symerror: %e, label: \'full syst.\'}",GetYSyst(i)));
      if(fDrawTags->Contains("YUnc"))
        AddYValue(Form("    - {symerror: %e, label: \'unc. syst.\'}",GetYUnc(i)));
    };
    AddYValue(Form("    value: %e",GetYValue(i)));
  };
};
void YAMLTable::SetInputHistograms(TH1 *inhstat, TH1 *inhsys, TH1 *inhunc) {
  if(inhstat)
    fInHist=inhstat;
  if(inhsys)
    fInHistSyst=inhsys;
  if(inhunc)
    fInHistUnc=inhunc;
};
void YAMLTable::SetInputGraphs(TGraphErrors *gr1, TGraphErrors *gr2, TGraphErrors *gr3) {
  if(gr1)
    fInGra=gr1;
  if(gr2)
    fInGraSyst=gr2;
  if(gr3)
    fInGraUnc=gr3;
};
void YAMLTable::SetInputAsGraphs(TGraphAsymmErrors *gr1, TGraphAsymmErrors *gr2, TGraphAsymmErrors *gr3) {
  if(gr1)
    fInAsGra=gr1;
  if(gr2)
    fInAsGraSyst=gr2;
  if(gr3)
    fInAsGraUnc=gr3;
  fAsymmetric=kTRUE;
}

void YAMLTable::PrintTableToFile(Bool_t ContinueInSameFile) {
  if((!fInHist)&&(!fInGra)&&(!fInAsGra)) {
    printf("Nothing to write, make sure the input histogram is set!\n");
    return;
  };
  BuildXArray();
  BuildYArray();
  const char *writeType = ContinueInSameFile?"a":"w";
  FILE *fout = fopen(Form("OutputFiles/%s",fFileName->Data()),writeType);
  if(!ContinueInSameFile) {
    // fprintf(fout,"name: %s\n",fFileName->Data());
    fprintf(fout,"independent_variables:\n");
    for(Int_t i=0;i<fXArray->GetEntries();i++)
      fprintf(fout,"%s\n",fXArray->At(i)->GetTitle());
    fprintf(fout,"dependent_variables:\n");
  };
  for(Int_t i=0;i<fYArray->GetEntries();i++)
    fprintf(fout,"%s\n",fYArray->At(i)->GetTitle());
  fclose(fout);
};
void YAMLTable::SetNameAndTitles(const char *lName, const char *lxTitle, const char *lyTitle) {
  if(fTableName) delete fTableName;
  if(fXTitle) delete fXTitle;
  if(fYTitle) delete fYTitle;
  if(fFileName) delete fFileName;
  fTableName=new TString(lName);
  fXTitle=new TString(lxTitle);
  fYTitle=new TString(lyTitle);
  fFileName=new TString("");
  TObjArray *loba = fTableName->Tokenize(" ");
  for(Int_t i=0;i<loba->GetEntries();i++)
    fFileName->Append(Form("%s%s",i?"_":"",loba->At(i)->GetName()));
  fFileName->Append(".yaml");
};
void YAMLTable::AddToSubmissions() {
  FILE *fout = fopen("OutputFiles/submission.yaml","a");
  fprintf(fout,"---\n");
  fprintf(fout,"data_file: %s\n",fFileName->Data());
  if(fLocation) fprintf(fout,"location: %s\n",fLocation->Data());
  fprintf(fout,"description: %s\n",fDescription->Data());
  if(fKeywords) {
    fprintf(fout,"keywords:\n");
    for(Int_t i=0;i<fKeywords->GetEntries();i++)
      fprintf(fout,"  - {name: %s, values: [%s]}\n",fKeywords->At(i)->GetName(),fKeywords->At(i)->GetTitle());
    };
  fprintf(fout,"name: %s\n",fTableName->Data());
  fclose(fout);
};
void YAMLTable::SetLocation(const char *newval) {
  if(!fLocation) fLocation = new TString("");
  ClearLocation();
  fLocation->Append(newval);
};
void YAMLTable::AddKeywords(const char *lname, const char *lvalue) {
  if(!fKeywords) fKeywords = new TObjArray();
  fKeywords->Add(new TNamed(lname, lvalue));
};
void YAMLTable::AddQualifier(const char *lname, const char *lvalue) {
  if(!fQualifiers) fQualifiers = new TObjArray();
  fQualifiers->Add(new TNamed(lname, lvalue));
};
Int_t YAMLTable::FindXMin(Double_t lXMin) {
  if(!fInHist && !fInGra && !fInAsGra) {printf("No input set!\n"); return 1; };
  if(fInHist) {
    Int_t rbin = fInHist->FindBin(lXMin);
    if(rbin<1) rbin=1;
    return rbin;
  };
  Double_t x,y;
  if(fInGra) {
    for(Int_t i=0;i<fInGra->GetN();i++) {
      fInGra->GetPoint(i,x,y);
      if(x>lXMin) {
        if(i>0) return i-1;
        return 0;
      };
    };
  };
  for(Int_t i=0;i<fInAsGra->GetN();i++) {
    fInAsGra->GetPoint(i,x,y);
    if(x>lXMin) {
      if(i>0) return i-1;
      return 0;
    };
  };
  return 0;
};
Int_t YAMLTable::FindXMax(Double_t lXMax) {
  if(!fInGra && !fInHist && !fInAsGra) {
    printf("Neither hist. nor graph is set up!\n");
    return 1;
  };
  if(fInHist) { //histogram case
    Int_t rbin = fInHist->FindBin(lXMax);
    if(rbin>fInHist->GetNbinsX())
      rbin=fInHist->GetNbinsX();
    return rbin;
  };
  Double_t x,y;
  if(fInGra) { //TGraphErrors case
    for(Int_t i=0;i<fInGra->GetN();i++) {
      fInGra->GetPoint(i,x,y);
      if(x>lXMax) {
        if(i>=fInGra->GetN()) return i-1;
        return i;
      };
    };
    return fInGra->GetN()-1;
  };
  for(Int_t i=0;i<fInAsGra->GetN();i++) { //TGraphAsymmErrors case
    fInAsGra->GetPoint(i,x,y);
    if(x>lXMax) {
      if(i>=fInAsGra->GetN()) return i-1;
      return i;
    };
  };
  return fInAsGra->GetN()-1;
};
Double_t YAMLTable::GetXLower(Int_t bin) {
  if(fInHist) return fInHist->GetBinLowEdge(bin);
  if(fInGraSyst) return fInGraSyst->GetX()[bin] - fInGraSyst->GetEX()[bin];
  return fInAsGraSyst->GetX()[bin] - fInAsGraSyst->GetEXlow()[bin];
};
Double_t YAMLTable::GetXHigher(Int_t bin) {
  if(fInHist) return fInHist->GetBinLowEdge(bin)+fInHist->GetBinWidth(bin);
  if(fInGraSyst) return fInGraSyst->GetX()[bin] + fInGraSyst->GetEX()[bin];
  return fInAsGraSyst->GetX()[bin] + fInAsGraSyst->GetEXhigh()[bin];
};
Double_t YAMLTable::GetXCenter(Int_t bin) {
  if(fInHist) return fInHist->GetBinCenter(bin);
  if(fInGra) return fInGra->GetX()[bin];
  return fInAsGra->GetX()[bin];
};
Double_t YAMLTable::GetYValue(Int_t bin) {
  if(fInHist) return fInHist->GetBinContent(bin)*fExtScale;
  if(fInGra) return fInGra->GetY()[bin]*fExtScale;
  return fInAsGra->GetY()[bin]*fExtScale;
};
Double_t *YAMLTable::GetYAsStat(Int_t bin) {
  if(!fInAsGra) return 0;
  Double_t *retval = new Double_t[2];
  retval[0] = fInAsGra->GetEYlow()[bin]*fExtScale;
  retval[1] = fInAsGra->GetEYhigh()[bin]*fExtScale;
  return retval;
};
Double_t *YAMLTable::GetYAsSyst(Int_t bin) {
  if(!fInAsGraSyst) return 0;
  Double_t *retval = new Double_t[2];
  retval[0] = fInAsGraSyst->GetEYlow()[bin]*fExtScale;
  retval[1] = fInAsGraSyst->GetEYhigh()[bin]*fExtScale;
  return retval;
};
Double_t *YAMLTable::GetYAsUnc(Int_t bin) {
  if(!fInAsGraUnc) return 0;
  Double_t *retval = new Double_t[2];
  retval[0] = fInAsGraUnc->GetEYlow()[bin]*fExtScale;
  retval[1] = fInAsGraUnc->GetEYhigh()[bin]*fExtScale;
  return retval;
};

#endif
