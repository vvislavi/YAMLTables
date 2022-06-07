#include "YAMLTable.cxx"
#include "TString.h"
// #include "../Inputs/LoadSomeHistogram.C"
#include "../Inputs/FigureX.C"
// #include "../Inputs/LoadSomeGraphErrors.C"
// #include "../Inputs/LoadSomeAsymGraphErrors.C"
//Yield output
TString fig1Desc("The flow angle fluctuation $A_{\\rm 2}^{\\rm f}$ as a function of $p_{\\rm T}^{\\rm a}$ in different centrality classes");
TString fig2Desc("The flow magnitude fluctuation $M_{\\rm 2}^{\\rm f}$ as a function of $p_{\\rm T}^{\\rm a}$ in different centrality classes");
TString fig3Desc("Lower (upper) limit of flow angle (magnitude) fluctuations and flow vector fluctuations as a function of centrality for 3.0 < $p_{\\rm T}^{\\rm a}$ < 4.0 GeV/$c$");
TString fig3bDesc("Ratio of lower (upper) flow angle (magnitude) fluctuation limits to total flow vector fluctuations as a function of centrality for 3.0 < $p_{\\rm T}^{\\rm a}$ < 4.0 GeV/$c$");

TString pta("$p_{\\rm T}^{a}$");
TString A2f("$A_{2}^{\\rm f}$");
TString M2f("$M_{2}^{\\rm f}$");
TString angleFile("InputData/flowAngleData.root");
TString magnitudeFile("InputData/flowMagData.root");
TString limitFile("InputData/flowLimitData.root");
//TString angP("'$\\langle\\cos 2 (\\Psi_{2}(p_{\\rm T}^{\\rm a} - \\Psi_{2})\\rangle_{\\rm min}$'");
TString angP("$\\langle \\cos 2 (\\Psi_{2}(p_{\\rm T}^{\\rm a})-\\Psi_{2})\\rangle_{\\rm min}$");
TString magP("$\\langle v_{2}(p_{\\rm T}^{\\rm a})v_{2}\\rangle/(\\langle v_{2}^{2}(p_{\\rm T}^{\\rm a})\\rangle\\langle v_{2}^{2}\\rangle)^{1/2}_{\\rm max}$");
TString vecP("$v_{2}\\{2\\}/v_{2}[2]$");
TString angR("$\\frac{\\langle \\cos 2 (\\Psi_{2}(p_{\\rm T}^{\\rm a})-\\Psi_{2})\\rangle_{\\rm min}}{v_{2}\\{2\\}/v_{2}[2]}$");
TString magR("$\\frac{\\langle v_{2}(p_{\\rm T}^{\\rm a})v_{2}\\rangle/(\\langle v_{2}^{2}(p_{\\rm T}^{\\rm a})\\rangle\\langle v_{2}^{2}\\rangle)^{1/2}_{\\rm max}}{v_{2}\\{2\\}/v_{2}[2]}$");
void ProduceTables() {
  Int_t gCounter=1;
  Int_t FigureNo=1;
  ProduceATable(angleFile, "A2f%s_05", kFALSE, FigureNo, gCounter,
                pta, "0-5%", fig1Desc, {A2f},0,4);
  ProduceATable(angleFile, "A2f%s_1020", kTRUE, FigureNo, gCounter,
                pta, "10-20%", fig1Desc, {A2f},0,4);
  ProduceATable(angleFile, "A2f%s_3040", kTRUE, FigureNo, gCounter,
                pta, "30-40%", fig1Desc, {A2f},0,4);
  FigureNo++;
  ProduceATable(magnitudeFile, "M2f%s_05", kFALSE, FigureNo, gCounter,
                pta, "0-5%", fig2Desc, {M2f},0,4);
  ProduceATable(magnitudeFile, "M2f%s_1020", kTRUE, FigureNo, gCounter,
                pta, "10-20%", fig2Desc, {M2f},0,4);
  ProduceATable(magnitudeFile, "M2f%s_3040", kTRUE, FigureNo, gCounter,
                pta, "30-40%", fig2Desc, {M2f},0,4);
  FigureNo++;

  ProduceATable(limitFile, "angleLimit%s", kFALSE, FigureNo, gCounter,
                "centrality", angP, fig3Desc, {"$(A_{2}^{\\rm f})_{\\rm min}$","$(M_{2}^{\\rm f})_{\\rm max}$",vecP}, 0, 40, {make_pair("PT","'$3.0 < p_{\\rm T}^{\\rm a} < 4.0{\\rm\\ GeV}/c$'")});
  ProduceATable(limitFile, "magLimit%s", kTRUE, FigureNo, gCounter,
                "centrality", magP, fig3Desc, {"$(A_{2}^{\\rm f})_{\\rm min}$","$(M_{2}^{\\rm f})_{\\rm max}$",vecP}, 0, 40, {make_pair("PT","'$3.0 < p_{\\rm T}^{\\rm a} < 4.0{\\rm\\ GeV}/c$'")});
  ProduceATable(limitFile, "flowvec%s", kTRUE, FigureNo, gCounter,
                "centrality", vecP, fig3Desc, {"$(A_{2}^{\\rm f})_{\\rm min}$","$(M_{2}^{\\rm f})_{\\rm max}$",vecP}, 0, 40, {make_pair("PT","'$3.0 < p_{\\rm T}^{\\rm a} < 4.0{\\rm\\ GeV}/c$'")});
  // FigureNo++;

  ProduceATable(limitFile, "angleRel%s", kFALSE, FigureNo, gCounter,
                "centrality", angR, fig3bDesc, {"$\\frac{(A_{2}^{\\rm f})_{\\rm min}}{v_{2}\\{2\\}/v_{2}[2]}$","$\\frac{(M_{2}^{\\rm f})_{\\rm max}}{v_{2}\\{2\\}/v_{2}[2]}$"}, 0, 40, {make_pair("PT","'$3.0 < p_{\\rm T}^{\\rm a} < 4.0{\\rm\\ GeV}/c$'")});

  ProduceATable(limitFile, "magRel%s", kTRUE, FigureNo, gCounter,
                "centrality", magR, fig3bDesc, {"$\\frac{(A_{2}^{\\rm f})_{\\rm min}}{v_{2}\\{2\\}/v_{2}[2]}$","$\\frac{(M_{2}^{\\rm f})_{\\rm max}}{v_{2}\\{2\\}/v_{2}[2]}$"}, 0, 40, {make_pair("PT","'$3.0 < p_{\\rm T}^{\\rm a} < 4.0{\\rm\\ GeV}/c$'")});
  // ProduceATable(limitFile, "magRel%s", kTRUE, FigureNo, gCounter,
  //               "centrality", magR, fig3Desc, {"$\frac{(A_{2}^{\\rm f})_{\\rm min}}{v_{2}\\{2\\}/v_{2}[2]}$","$\\frac{(M_{2}^{\\rm f})_{\\rm max}}{v_{2}\\{2\\}/v_{2}[2]}$"}, 0, 40, {make_pair("PT","'$3.0 < p_{\\rm T}^{\\rm a} < 4.0{\\rm\\ GeV}/c$'")});
  FigureNo++;



  // ProduceAngleTable("A2f%s_05",kFALSE,FigureNo,gCounter,"0-5%");
  // ProduceAngleTable("A2f%s_1020",kTRUE,FigureNo,gCounter,"10-20%");
  // ProduceAngleTable("A2f%s_3040",kTRUE,FigureNo,gCounter,"30-40%");
  // FigureNo++;
  // ProduceMagnitudeTable("M2f%s_05",kFALSE,FigureNo,gCounter,"0-5%");
  // ProduceMagnitudeTable("M2f%s_1020",kTRUE,FigureNo,gCounter,"10-20%");
  // ProduceMagnitudeTable("M2f%s_3040",kTRUE,FigureNo,gCounter,"30-40%");
  // FigureNo++;

  // ProduceHistogramTable("h2",kTRUE,FigureNo,gCounter);
  // FigureNo++;
  // ProduceGraphTable("gr",kFALSE,FigureNo,gCounter);
  // FigureNo++;
  // ProduceAsymGraphTable("gras",kFALSE,FigureNo,gCounter);
};
