#include "YAMLTable.cxx"
// #include "../Inputs/LoadSomeHistogram.C"
// #include "../Inputs/LoadSomeGraphErrors.C"
// #include "../Inputs/LoadSomeAsymGraphErrors.C"
#include "../Inputs/LoadPCC.C"
//Yield output
void ProduceTables() {
  Int_t gCounter=1;
  Int_t FigureNo=1;
  // ProduceHistogramTable("h1",kFALSE,FigureNo,gCounter);
  // ProduceHistogramTable("h2",kTRUE,FigureNo,gCounter);
  // FigureNo++;
  ProduceGraphTablePbPb("grpcc2_pbpb",kFALSE,FigureNo,gCounter);
  ProduceGraphTablePbPb("grpcc3_pbpb",kTRUE,FigureNo,gCounter);

  ProduceGraphTableXeXePCC2("grpcc2_xexe",kFALSE,FigureNo,gCounter);
  ProduceGraphTableXeXePCC3("grpcc3_xexe",kFALSE,FigureNo,gCounter);
  FigureNo++;
  ProduceGraphTablePbPbMH("grpcc23_pbpb", kFALSE, FigureNo,gCounter);
  // ProduceAsymGraphTable("gras",kFALSE,FigureNo,gCounter);
};
