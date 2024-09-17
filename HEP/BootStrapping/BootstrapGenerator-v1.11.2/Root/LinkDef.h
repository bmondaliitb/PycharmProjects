#include "BootstrapGenerator/BootstrapGenerator.h"
#include "BootstrapGenerator/TH1Bootstrap.h"
#include "BootstrapGenerator/TH2Bootstrap.h"
#include "BootstrapGenerator/TH3Bootstrap.h"

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;

#pragma link C++ class BootstrapGenerator+;

#pragma link C++ class TH1Bootstrap+;
#pragma link C++ class TH1DBootstrap+;
#pragma link C++ class TH1FBootstrap+;

#pragma link C++ class TH2Bootstrap+;
#pragma link C++ class TH2DBootstrap+;
#pragma link C++ class TH2FBootstrap+;

#pragma link C++ class TH3Bootstrap+;
#pragma link C++ class TH3DBootstrap+;

#pragma read \
   sourceClass="TH1Bootstrap" \
   version="[1-]" \
   source="" \
   targetClass="TH1Bootstrap" \
   target="" \
   code="{ newObj->InitOnFileRead(); }"

#endif
