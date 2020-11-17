void MakeTables() {
  gROOT->ProcessLine(".L Scripts/YAMLTable.cxx+");
  gROOT->ProcessLine(".x Scripts/ProduceTables.C+");
  gROOT->ProcessLine(".q");
};
