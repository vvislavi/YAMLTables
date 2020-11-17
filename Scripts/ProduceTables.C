#include "YAMLTable.cxx"
#include "../Inputs/LoadSomeHistogram.C"
#include "../Inputs/LoadSomeGraphErrors.C"
#include "../Inputs/LoadSomeAsymGraphErrors.C"
//Yield output
void ProduceTables() {
  Int_t gCounter=1;
  Int_t FigureNo=1;
  ProduceHistogramTable("h1",kFALSE,FigureNo,gCounter);
  ProduceHistogramTable("h2",kTRUE,FigureNo,gCounter);
  FigureNo++;
  ProduceGraphTable("gr",kFALSE,FigureNo,gCounter);
  FigureNo++;
  ProduceAsymGraphTable("gras",kFALSE,FigureNo,gCounter);
};
