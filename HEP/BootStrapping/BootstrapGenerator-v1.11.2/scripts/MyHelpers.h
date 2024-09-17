#ifndef __MYHELPERS_H__
#define __MYHELPERS_H__

#include "TString.h"
#include <string>
#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}

void DrawLabel(TString,double,double,double t=0.040);
void DrawBoxLabel(TString,double,double,int=1,int=1,int=1,double t=0.040);
void DrawMarkerLabel(TString,double,double,int=20,int=1,double=1.0,double t=0.040,bool noLine=false, bool yline=false);
void DrawLineLabel(TString,double,double,int=1,int=1,int=2,double t=0.040, bool two=false);
Int_t SetColorPalette();


#endif //__MYHELPERS_H__
