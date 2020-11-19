################################################################################
Converting ROOT objects (TH1, TGraphErrors, TGraphAsymmErrors) to yaml
files ( = for HEPData).
Written by Vytautas Vislavicius (vytautas.vislavicius@cern.ch)
In development stage, but I hope someone will find it useful :)
################################################################################
1. How does it work?
-- The program consists of a steering macro (Scripts/ProduceTables.C) and loading macros (Inputs/Load... .C). The steering macro loads loading macros and executes them.
Loading macros are where the user builds YAML tables. In practice, since each table requires different description, one will likely have a different loading macro for each table (of course, one is free to write a long spaghetti code into ProduceTables.C, but I would strongly recommend against that).
I have currently added three example loading macros (one for TH1D, one for TGraphErrors and one for TGraphAsymmErrors), see the code for examples.

Essentially, for each table, there are few requirements:
- Each table must have input data. At the very least, it's a single TH1/TGraphErrors/TGraphAsymmErrors. These are set using:
 -- YAMLTable::SetInputHistograms(TH1* stat, TH1* syst=0, TH1* systUnc=0) for histograms
 -- YAMLTable::SetInputGraphs(TGraphErrors* stat, TGraphErrors* syst=0, TGraphErrors* systUnc=0) for TGraphErrors
 -- YAMLTable::SetInputAsGraphs(TGraphAsymmErrors* stat, TGraphAsymmErrors* syst=0, TGraphAsymmErrors* systUnc=0) for TGraphAsymmErrors

- Each table must have draw tags (YAMLTable::SetDrawTags(const char*)). These can be:
 -- "XWidth" -> x-value is represented by bin. In graph case, the bin width is from -Xerror(low) to +Xerror(high). If this is not set, the bin center (for histogram) or x-value (for graphs) are used. Since the x-error is always represented by a bin width, it is not possible to have two different bin widths for a single point in a single table (e.g. one cannot have stat. and syst. uncertainty on x-value)
 -- "YStat" -> statistical uncertainties for a given point
 -- "YSyst" -> full systematic uncertainties for a given point
 -- "YUnc"  -> uncorrelated uncertainties for a given point
 Note that the "central" y-value is always taken from the "statistical" graph.

- Each table must have name and titles (YAMLTable::SetNameAndTitles(const char* name, const char* x-title, const char* y-title)).
 -- The name of the figure should be "Table X", with incrementing X. If you'd like to have a table with multiple columns (e.g. pT-spectra in dif. multiplicity bins, but pT-binning remains the same), then table number should remain the same.
 -- x-title and y-title are self explanatory.

- Each table must have a location (which figure it came from). This is set by YAMLTable::SetLocation(const char* loc)
- Each table should have keywords (YAMLTable::AddKeywords(const char* keyword, const char* value)) and qualifiers (YAMLTable::AddQualifier(const char* qualifier, const char* value)). Note that for latex formatting one should use "''" (single quotes inside double-quotes), see implementation. Sometimes, the single-quotes also have to be escaped to be printed properly.


Once all the above are set, call YAMLTable::PrintTableToFile(Int_t tableNo). This will create a OutputFiles/Table_X.yaml file. Note that among other Table_X.yaml files, there also has to be a sumbission.yaml file, which contains information on all the tables. If you are not planning to write any more to this particular table, then also call YAMLTable::AddToSubmissions(). This will add the current table to the submission.yaml files.

2. What is this submission.yaml file?
- This is a header file that contains abstract and a list of all the tables to be included. In the root directory, you can find a file YAMLHeader, which is a "clean" version of the submissions.yaml. Also, your abstract goes here (just replace the dummy "Some abstract goes here") in it and don't worry about the rest -- tables will be added to it, when they are generated!

3. How to add my own histograms/graphs?
- Ideally, one can copy one of the existing templates (to load TH1/TGraphErrors/TGraphAsymmErrors) and modify it to add whatever input you have. Then, this loading macro has to be called and executed in Scripts/ProduceTables.C macro. Also, note for recurrent graphs (e.g. pT spectra of dif. particles in dif. multi bins, but same pT-binning), one can write a single loading macro and just dynamically set the input + keywords/qualifiers.

4. How do I run it?
- To run it, go to the main directory (YAMLTables/) and do
source MakeTables.sh
This will:
-- Clean the OutputFiles/ directory
-- Create the OutputFiles/submission.yaml
-- Compile the necessary scripts, execute them, produce tables and add them to the submission.yaml
-- Create a tarball to be uploaded to the HEPData sandbox (https://www.hepdata.net/record/sandbox)

Final notes:
-- I started writing it while using root5. When I moved to root6, I noticed that root6 treats the anchor point of relative paths different. In particular, in root6, the anchor point is the directory from which root is called, while in root5 it was the directory where the file is located. Thus, if you are running root5, you will most likely have to edit the include paths in the Inputs/* files to make sure they find what they are looking for (most likely, just add ../ to the relevant includes).
