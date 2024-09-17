// Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

{
#ifdef __CLING__
  cout << "This should only be used with ROOT 5, aborting." << std::endl;
#endif

#ifdef __CINT__
  gSystem->AddIncludePath(" -I../");
  gSystem->AddIncludePath(" -I../BootstrapGenerator/");
  gROOT->LoadMacro("../Root/BootstrapGenerator.cxx+");
  gROOT->LoadMacro("../Root/TH1Bootstrap.cxx+");

  gROOT->LoadMacro("TestBootstrap.C+");
  TestBootstrap();
#endif
}

