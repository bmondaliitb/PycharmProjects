// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__BootstrapGenerator
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

#include "TBuffer.h"
#include "TVirtualObject.h"
#include <vector>
#include "TSchemaHelper.h"


// Header files passed as explicit arguments
#include "BootstrapGenerator/BootstrapGenerator.h"
#include "BootstrapGenerator/TH1Bootstrap.h"
#include "BootstrapGenerator/TH2Bootstrap.h"
#include "BootstrapGenerator/TH3Bootstrap.h"
#include "BootstrapGenerator/BootstrapGenerator.h"
#include "BootstrapGenerator/TH1Bootstrap.h"
#include "BootstrapGenerator/TH2Bootstrap.h"
#include "BootstrapGenerator/TH3Bootstrap.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_BootstrapGenerator(void *p = nullptr);
   static void *newArray_BootstrapGenerator(Long_t size, void *p);
   static void delete_BootstrapGenerator(void *p);
   static void deleteArray_BootstrapGenerator(void *p);
   static void destruct_BootstrapGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BootstrapGenerator*)
   {
      ::BootstrapGenerator *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BootstrapGenerator >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("BootstrapGenerator", ::BootstrapGenerator::Class_Version(), "BootstrapGenerator/BootstrapGenerator.h", 24,
                  typeid(::BootstrapGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BootstrapGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::BootstrapGenerator) );
      instance.SetNew(&new_BootstrapGenerator);
      instance.SetNewArray(&newArray_BootstrapGenerator);
      instance.SetDelete(&delete_BootstrapGenerator);
      instance.SetDeleteArray(&deleteArray_BootstrapGenerator);
      instance.SetDestructor(&destruct_BootstrapGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BootstrapGenerator*)
   {
      return GenerateInitInstanceLocal(static_cast<::BootstrapGenerator*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::BootstrapGenerator*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TH1Bootstrap(void *p);
   static void deleteArray_TH1Bootstrap(void *p);
   static void destruct_TH1Bootstrap(void *p);
   static Long64_t merge_TH1Bootstrap(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Schema evolution read functions
   static void read_TH1Bootstrap_0( char* target, TVirtualObject *oldObj )
   {
      //--- Automatically generated variables ---
      TH1Bootstrap* newObj = (TH1Bootstrap*)target;
      // Supress warning message.
      (void)oldObj;

      (void)newObj;

      //--- User's code ---
      newObj->InitOnFileRead(); 
   }

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH1Bootstrap*)
   {
      ::TH1Bootstrap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH1Bootstrap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH1Bootstrap", ::TH1Bootstrap::Class_Version(), "BootstrapGenerator/TH1Bootstrap.h", 31,
                  typeid(::TH1Bootstrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH1Bootstrap::Dictionary, isa_proxy, 4,
                  sizeof(::TH1Bootstrap) );
      instance.SetDelete(&delete_TH1Bootstrap);
      instance.SetDeleteArray(&deleteArray_TH1Bootstrap);
      instance.SetDestructor(&destruct_TH1Bootstrap);
      instance.SetMerge(&merge_TH1Bootstrap);

      ::ROOT::Internal::TSchemaHelper* rule;

      // the io read rules
      std::vector<::ROOT::Internal::TSchemaHelper> readrules(1);
      rule = &readrules[0];
      rule->fSourceClass = "TH1Bootstrap";
      rule->fTarget      = "";
      rule->fSource      = "";
      rule->fFunctionPtr = (void *)TFunc2void( read_TH1Bootstrap_0);
      rule->fCode        = " newObj->InitOnFileRead(); ";
      rule->fVersion     = "[1-]";
      instance.SetReadRules( readrules );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH1Bootstrap*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH1Bootstrap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH1Bootstrap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH1DBootstrap(void *p = nullptr);
   static void *newArray_TH1DBootstrap(Long_t size, void *p);
   static void delete_TH1DBootstrap(void *p);
   static void deleteArray_TH1DBootstrap(void *p);
   static void destruct_TH1DBootstrap(void *p);
   static Long64_t merge_TH1DBootstrap(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH1DBootstrap*)
   {
      ::TH1DBootstrap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH1DBootstrap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH1DBootstrap", ::TH1DBootstrap::Class_Version(), "BootstrapGenerator/TH1Bootstrap.h", 118,
                  typeid(::TH1DBootstrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH1DBootstrap::Dictionary, isa_proxy, 4,
                  sizeof(::TH1DBootstrap) );
      instance.SetNew(&new_TH1DBootstrap);
      instance.SetNewArray(&newArray_TH1DBootstrap);
      instance.SetDelete(&delete_TH1DBootstrap);
      instance.SetDeleteArray(&deleteArray_TH1DBootstrap);
      instance.SetDestructor(&destruct_TH1DBootstrap);
      instance.SetMerge(&merge_TH1DBootstrap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH1DBootstrap*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH1DBootstrap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH1DBootstrap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH1FBootstrap(void *p = nullptr);
   static void *newArray_TH1FBootstrap(Long_t size, void *p);
   static void delete_TH1FBootstrap(void *p);
   static void deleteArray_TH1FBootstrap(void *p);
   static void destruct_TH1FBootstrap(void *p);
   static Long64_t merge_TH1FBootstrap(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH1FBootstrap*)
   {
      ::TH1FBootstrap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH1FBootstrap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH1FBootstrap", ::TH1FBootstrap::Class_Version(), "BootstrapGenerator/TH1Bootstrap.h", 157,
                  typeid(::TH1FBootstrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH1FBootstrap::Dictionary, isa_proxy, 4,
                  sizeof(::TH1FBootstrap) );
      instance.SetNew(&new_TH1FBootstrap);
      instance.SetNewArray(&newArray_TH1FBootstrap);
      instance.SetDelete(&delete_TH1FBootstrap);
      instance.SetDeleteArray(&deleteArray_TH1FBootstrap);
      instance.SetDestructor(&destruct_TH1FBootstrap);
      instance.SetMerge(&merge_TH1FBootstrap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH1FBootstrap*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH1FBootstrap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH1FBootstrap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static Long64_t merge_TH2Bootstrap(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH2Bootstrap*)
   {
      ::TH2Bootstrap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH2Bootstrap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH2Bootstrap", ::TH2Bootstrap::Class_Version(), "BootstrapGenerator/TH2Bootstrap.h", 22,
                  typeid(::TH2Bootstrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH2Bootstrap::Dictionary, isa_proxy, 4,
                  sizeof(::TH2Bootstrap) );
      instance.SetMerge(&merge_TH2Bootstrap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH2Bootstrap*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH2Bootstrap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH2Bootstrap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH2DBootstrap(void *p = nullptr);
   static void *newArray_TH2DBootstrap(Long_t size, void *p);
   static void delete_TH2DBootstrap(void *p);
   static void deleteArray_TH2DBootstrap(void *p);
   static void destruct_TH2DBootstrap(void *p);
   static Long64_t merge_TH2DBootstrap(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH2DBootstrap*)
   {
      ::TH2DBootstrap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH2DBootstrap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH2DBootstrap", ::TH2DBootstrap::Class_Version(), "BootstrapGenerator/TH2Bootstrap.h", 57,
                  typeid(::TH2DBootstrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH2DBootstrap::Dictionary, isa_proxy, 4,
                  sizeof(::TH2DBootstrap) );
      instance.SetNew(&new_TH2DBootstrap);
      instance.SetNewArray(&newArray_TH2DBootstrap);
      instance.SetDelete(&delete_TH2DBootstrap);
      instance.SetDeleteArray(&deleteArray_TH2DBootstrap);
      instance.SetDestructor(&destruct_TH2DBootstrap);
      instance.SetMerge(&merge_TH2DBootstrap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH2DBootstrap*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH2DBootstrap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH2DBootstrap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH2FBootstrap(void *p = nullptr);
   static void *newArray_TH2FBootstrap(Long_t size, void *p);
   static void delete_TH2FBootstrap(void *p);
   static void deleteArray_TH2FBootstrap(void *p);
   static void destruct_TH2FBootstrap(void *p);
   static Long64_t merge_TH2FBootstrap(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH2FBootstrap*)
   {
      ::TH2FBootstrap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH2FBootstrap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH2FBootstrap", ::TH2FBootstrap::Class_Version(), "BootstrapGenerator/TH2Bootstrap.h", 94,
                  typeid(::TH2FBootstrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH2FBootstrap::Dictionary, isa_proxy, 4,
                  sizeof(::TH2FBootstrap) );
      instance.SetNew(&new_TH2FBootstrap);
      instance.SetNewArray(&newArray_TH2FBootstrap);
      instance.SetDelete(&delete_TH2FBootstrap);
      instance.SetDeleteArray(&deleteArray_TH2FBootstrap);
      instance.SetDestructor(&destruct_TH2FBootstrap);
      instance.SetMerge(&merge_TH2FBootstrap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH2FBootstrap*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH2FBootstrap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH2FBootstrap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static Long64_t merge_TH3Bootstrap(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH3Bootstrap*)
   {
      ::TH3Bootstrap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH3Bootstrap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH3Bootstrap", ::TH3Bootstrap::Class_Version(), "BootstrapGenerator/TH3Bootstrap.h", 25,
                  typeid(::TH3Bootstrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH3Bootstrap::Dictionary, isa_proxy, 4,
                  sizeof(::TH3Bootstrap) );
      instance.SetMerge(&merge_TH3Bootstrap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH3Bootstrap*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH3Bootstrap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH3Bootstrap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH3DBootstrap(void *p = nullptr);
   static void *newArray_TH3DBootstrap(Long_t size, void *p);
   static void delete_TH3DBootstrap(void *p);
   static void deleteArray_TH3DBootstrap(void *p);
   static void destruct_TH3DBootstrap(void *p);
   static Long64_t merge_TH3DBootstrap(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH3DBootstrap*)
   {
      ::TH3DBootstrap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH3DBootstrap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH3DBootstrap", ::TH3DBootstrap::Class_Version(), "BootstrapGenerator/TH3Bootstrap.h", 64,
                  typeid(::TH3DBootstrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH3DBootstrap::Dictionary, isa_proxy, 4,
                  sizeof(::TH3DBootstrap) );
      instance.SetNew(&new_TH3DBootstrap);
      instance.SetNewArray(&newArray_TH3DBootstrap);
      instance.SetDelete(&delete_TH3DBootstrap);
      instance.SetDeleteArray(&deleteArray_TH3DBootstrap);
      instance.SetDestructor(&destruct_TH3DBootstrap);
      instance.SetMerge(&merge_TH3DBootstrap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH3DBootstrap*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH3DBootstrap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH3DBootstrap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr BootstrapGenerator::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *BootstrapGenerator::Class_Name()
{
   return "BootstrapGenerator";
}

//______________________________________________________________________________
const char *BootstrapGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BootstrapGenerator*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int BootstrapGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BootstrapGenerator*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BootstrapGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BootstrapGenerator*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BootstrapGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BootstrapGenerator*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH1Bootstrap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH1Bootstrap::Class_Name()
{
   return "TH1Bootstrap";
}

//______________________________________________________________________________
const char *TH1Bootstrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1Bootstrap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH1Bootstrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1Bootstrap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH1Bootstrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1Bootstrap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH1Bootstrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1Bootstrap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH1DBootstrap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH1DBootstrap::Class_Name()
{
   return "TH1DBootstrap";
}

//______________________________________________________________________________
const char *TH1DBootstrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1DBootstrap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH1DBootstrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1DBootstrap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH1DBootstrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1DBootstrap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH1DBootstrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1DBootstrap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH1FBootstrap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH1FBootstrap::Class_Name()
{
   return "TH1FBootstrap";
}

//______________________________________________________________________________
const char *TH1FBootstrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1FBootstrap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH1FBootstrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1FBootstrap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH1FBootstrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1FBootstrap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH1FBootstrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1FBootstrap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH2Bootstrap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH2Bootstrap::Class_Name()
{
   return "TH2Bootstrap";
}

//______________________________________________________________________________
const char *TH2Bootstrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH2Bootstrap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH2Bootstrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH2Bootstrap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH2Bootstrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH2Bootstrap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH2Bootstrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH2Bootstrap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH2DBootstrap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH2DBootstrap::Class_Name()
{
   return "TH2DBootstrap";
}

//______________________________________________________________________________
const char *TH2DBootstrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH2DBootstrap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH2DBootstrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH2DBootstrap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH2DBootstrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH2DBootstrap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH2DBootstrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH2DBootstrap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH2FBootstrap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH2FBootstrap::Class_Name()
{
   return "TH2FBootstrap";
}

//______________________________________________________________________________
const char *TH2FBootstrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH2FBootstrap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH2FBootstrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH2FBootstrap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH2FBootstrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH2FBootstrap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH2FBootstrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH2FBootstrap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH3Bootstrap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH3Bootstrap::Class_Name()
{
   return "TH3Bootstrap";
}

//______________________________________________________________________________
const char *TH3Bootstrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH3Bootstrap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH3Bootstrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH3Bootstrap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH3Bootstrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH3Bootstrap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH3Bootstrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH3Bootstrap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH3DBootstrap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH3DBootstrap::Class_Name()
{
   return "TH3DBootstrap";
}

//______________________________________________________________________________
const char *TH3DBootstrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH3DBootstrap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH3DBootstrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH3DBootstrap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH3DBootstrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH3DBootstrap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH3DBootstrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH3DBootstrap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void BootstrapGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class BootstrapGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BootstrapGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(BootstrapGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BootstrapGenerator(void *p) {
      return  p ? new(p) ::BootstrapGenerator : new ::BootstrapGenerator;
   }
   static void *newArray_BootstrapGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::BootstrapGenerator[nElements] : new ::BootstrapGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_BootstrapGenerator(void *p) {
      delete (static_cast<::BootstrapGenerator*>(p));
   }
   static void deleteArray_BootstrapGenerator(void *p) {
      delete [] (static_cast<::BootstrapGenerator*>(p));
   }
   static void destruct_BootstrapGenerator(void *p) {
      typedef ::BootstrapGenerator current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::BootstrapGenerator

//______________________________________________________________________________
void TH1Bootstrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH1Bootstrap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH1Bootstrap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH1Bootstrap::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TH1Bootstrap(void *p) {
      delete (static_cast<::TH1Bootstrap*>(p));
   }
   static void deleteArray_TH1Bootstrap(void *p) {
      delete [] (static_cast<::TH1Bootstrap*>(p));
   }
   static void destruct_TH1Bootstrap(void *p) {
      typedef ::TH1Bootstrap current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH1Bootstrap(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH1Bootstrap*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH1Bootstrap

//______________________________________________________________________________
void TH1DBootstrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH1DBootstrap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH1DBootstrap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH1DBootstrap::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH1DBootstrap(void *p) {
      return  p ? new(p) ::TH1DBootstrap : new ::TH1DBootstrap;
   }
   static void *newArray_TH1DBootstrap(Long_t nElements, void *p) {
      return p ? new(p) ::TH1DBootstrap[nElements] : new ::TH1DBootstrap[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH1DBootstrap(void *p) {
      delete (static_cast<::TH1DBootstrap*>(p));
   }
   static void deleteArray_TH1DBootstrap(void *p) {
      delete [] (static_cast<::TH1DBootstrap*>(p));
   }
   static void destruct_TH1DBootstrap(void *p) {
      typedef ::TH1DBootstrap current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH1DBootstrap(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH1DBootstrap*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH1DBootstrap

//______________________________________________________________________________
void TH1FBootstrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH1FBootstrap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH1FBootstrap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH1FBootstrap::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH1FBootstrap(void *p) {
      return  p ? new(p) ::TH1FBootstrap : new ::TH1FBootstrap;
   }
   static void *newArray_TH1FBootstrap(Long_t nElements, void *p) {
      return p ? new(p) ::TH1FBootstrap[nElements] : new ::TH1FBootstrap[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH1FBootstrap(void *p) {
      delete (static_cast<::TH1FBootstrap*>(p));
   }
   static void deleteArray_TH1FBootstrap(void *p) {
      delete [] (static_cast<::TH1FBootstrap*>(p));
   }
   static void destruct_TH1FBootstrap(void *p) {
      typedef ::TH1FBootstrap current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH1FBootstrap(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH1FBootstrap*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH1FBootstrap

//______________________________________________________________________________
void TH2Bootstrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH2Bootstrap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH2Bootstrap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH2Bootstrap::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around the merge function.
   static Long64_t  merge_TH2Bootstrap(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH2Bootstrap*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH2Bootstrap

//______________________________________________________________________________
void TH2DBootstrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH2DBootstrap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH2DBootstrap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH2DBootstrap::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH2DBootstrap(void *p) {
      return  p ? new(p) ::TH2DBootstrap : new ::TH2DBootstrap;
   }
   static void *newArray_TH2DBootstrap(Long_t nElements, void *p) {
      return p ? new(p) ::TH2DBootstrap[nElements] : new ::TH2DBootstrap[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH2DBootstrap(void *p) {
      delete (static_cast<::TH2DBootstrap*>(p));
   }
   static void deleteArray_TH2DBootstrap(void *p) {
      delete [] (static_cast<::TH2DBootstrap*>(p));
   }
   static void destruct_TH2DBootstrap(void *p) {
      typedef ::TH2DBootstrap current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH2DBootstrap(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH2DBootstrap*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH2DBootstrap

//______________________________________________________________________________
void TH2FBootstrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH2FBootstrap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH2FBootstrap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH2FBootstrap::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH2FBootstrap(void *p) {
      return  p ? new(p) ::TH2FBootstrap : new ::TH2FBootstrap;
   }
   static void *newArray_TH2FBootstrap(Long_t nElements, void *p) {
      return p ? new(p) ::TH2FBootstrap[nElements] : new ::TH2FBootstrap[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH2FBootstrap(void *p) {
      delete (static_cast<::TH2FBootstrap*>(p));
   }
   static void deleteArray_TH2FBootstrap(void *p) {
      delete [] (static_cast<::TH2FBootstrap*>(p));
   }
   static void destruct_TH2FBootstrap(void *p) {
      typedef ::TH2FBootstrap current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH2FBootstrap(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH2FBootstrap*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH2FBootstrap

//______________________________________________________________________________
void TH3Bootstrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH3Bootstrap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH3Bootstrap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH3Bootstrap::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around the merge function.
   static Long64_t  merge_TH3Bootstrap(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH3Bootstrap*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH3Bootstrap

//______________________________________________________________________________
void TH3DBootstrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH3DBootstrap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH3DBootstrap::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH3DBootstrap::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH3DBootstrap(void *p) {
      return  p ? new(p) ::TH3DBootstrap : new ::TH3DBootstrap;
   }
   static void *newArray_TH3DBootstrap(Long_t nElements, void *p) {
      return p ? new(p) ::TH3DBootstrap[nElements] : new ::TH3DBootstrap[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH3DBootstrap(void *p) {
      delete (static_cast<::TH3DBootstrap*>(p));
   }
   static void deleteArray_TH3DBootstrap(void *p) {
      delete [] (static_cast<::TH3DBootstrap*>(p));
   }
   static void destruct_TH3DBootstrap(void *p) {
      typedef ::TH3DBootstrap current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH3DBootstrap(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH3DBootstrap*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH3DBootstrap

namespace {
  void TriggerDictionaryInitialization_libBootstrapGenerator_Impl() {
    static const char* headers[] = {
"BootstrapGenerator/BootstrapGenerator.h",
"BootstrapGenerator/TH1Bootstrap.h",
"BootstrapGenerator/TH2Bootstrap.h",
"BootstrapGenerator/TH3Bootstrap.h",
nullptr
    };
    static const char* includePaths[] = {
"/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2",
"/Users/buddha/local_packages/root_install/include",
"/Users/buddha/local_packages/root_install/include/",
"/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/build/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libBootstrapGenerator dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/BootstrapGenerator.h")))  BootstrapGenerator;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/TH1Bootstrap.h")))  TH1Bootstrap;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/TH1Bootstrap.h")))  TH1DBootstrap;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/TH1Bootstrap.h")))  TH1FBootstrap;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/TH2Bootstrap.h")))  TH2Bootstrap;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/TH2Bootstrap.h")))  TH2DBootstrap;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/TH2Bootstrap.h")))  TH2FBootstrap;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/TH3Bootstrap.h")))  TH3Bootstrap;
class __attribute__((annotate("$clingAutoload$BootstrapGenerator/TH3Bootstrap.h")))  TH3DBootstrap;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libBootstrapGenerator dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "BootstrapGenerator/BootstrapGenerator.h"
#include "BootstrapGenerator/TH1Bootstrap.h"
#include "BootstrapGenerator/TH2Bootstrap.h"
#include "BootstrapGenerator/TH3Bootstrap.h"
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

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"BootstrapGenerator", payloadCode, "@",
"TH1Bootstrap", payloadCode, "@",
"TH1DBootstrap", payloadCode, "@",
"TH1FBootstrap", payloadCode, "@",
"TH2Bootstrap", payloadCode, "@",
"TH2DBootstrap", payloadCode, "@",
"TH2FBootstrap", payloadCode, "@",
"TH3Bootstrap", payloadCode, "@",
"TH3DBootstrap", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libBootstrapGenerator",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libBootstrapGenerator_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libBootstrapGenerator_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libBootstrapGenerator() {
  TriggerDictionaryInitialization_libBootstrapGenerator_Impl();
}
