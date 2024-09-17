# Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration

################################################################################
# Project: BootstrapGenerator
################################################################################

cmake_minimum_required(VERSION 2.8)

project(BootstrapGenerator)

find_package( ROOT COMPONENTS Matrix Hist RIO MathCore Physics)

find_package(AnalysisBase QUIET)
find_package(AthAnalysis QUIET)

if (${AnalysisBase_FOUND} OR ${AthAnalysis_FOUND})
  message ("Configuring for build within analysis release")
  set (foundAnalysisRelease  1)
else() 
  set (foundAnalysisRelease  0)
endif()

set(BootstrapGenerator_HEADERS 
    BootstrapGenerator/BootstrapGenerator.h
    BootstrapGenerator/TH1Bootstrap.h
    BootstrapGenerator/TH2Bootstrap.h
    BootstrapGenerator/TH3Bootstrap.h)
set(BootstrapGenerator_LINKDEF 
  Root/LinkDef.h)
file(GLOB BootstrapGenerator_SOURCES Root/*.cxx)

if(${foundAnalysisRelease})
  atlas_subdir( BootstrapGenerator )
  
  atlas_add_root_dictionary( BootstrapGeneratorLib _dictSource
    ROOT_HEADERS
    ${BootstrapGenerator_HEADERS}
    ${BootstrapGenerator_LINKDEF}
    )
  
  atlas_add_library( BootstrapGeneratorLib
    BootstrapGenerator/*.h Root/*.cxx ${_dictSource}
    PUBLIC_HEADERS BootstrapGenerator
    PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
    PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES} )
  
  atlas_add_test( BootstrapGeneratorTest
    SOURCES test/simpleTest.cxx
    INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
    LINK_LIBRARIES BootstrapGeneratorLib ${ROOT_LIBRARIES} )
else()
  # register all the files and directories
  include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
  include_directories ("${ROOT_INCLUDE_DIRS}")

  set(SETUP ${CMAKE_CURRENT_BINARY_DIR}/setup.sh)
  file(WRITE ${SETUP} "#!/bin/bash\n")
  file(APPEND ${SETUP} "# this is an auto-generated setup script\n" )
  file(APPEND ${SETUP} "export PATH=\${PATH}:${CMAKE_CURRENT_BINARY_DIR}\n")
  file(APPEND ${SETUP} "export PYTHONPATH=\${PYTHONPATH}:${CMAKE_CURRENT_BINARY_DIR}\n")
  file(APPEND ${SETUP} "export LD_LIBRARY_PATH=\${LD_LIBRARY_PATH}:${CMAKE_CURRENT_BINARY_DIR}\n")

  # generate the dictionary source code
  include(${ROOT_USE_FILE})
  ROOT_GENERATE_DICTIONARY(G__BootstrapGenerator ${BootstrapGenerator_HEADERS} LINKDEF ${BootstrapGenerator_LINKDEF})

  # register the shared object to include both sources and dictionaries
  add_library( BootstrapGenerator SHARED ${BootstrapGenerator_SOURCES} G__BootstrapGenerator.cxx)

  # link everything together at the end
  target_link_libraries( BootstrapGenerator ${ROOT_LIBRARIES} )

  # Add all targets to the build-tree export set
  export(TARGETS BootstrapGenerator FILE "${PROJECT_BINARY_DIR}/BootstrapGeneratorTargets.cmake")
  
  # Export the package for use from the build-tree
  # (this registers the build-tree with a global CMake-registry)
  export(PACKAGE BootstrapGenerator)
  
  set(CONF_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
  set(CONF_LIBRARY_DIRS "${PROJECT_BINARY_DIR}")
  set(CONF_LIBRARIES    BootstrapGenerator)
  configure_file(BootstrapGeneratorConfig.cmake.in
    "${PROJECT_BINARY_DIR}/BootstrapGeneratorConfig.cmake" @ONLY)

  add_executable(simpleTest test/simpleTest.cxx)
  target_link_libraries(simpleTest BootstrapGenerator)
  
  install(TARGETS BootstrapGenerator DESTINATION lib)
  install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libBootstrapGenerator_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libBootstrapGenerator.rootmap
    DESTINATION lib)
  install(TARGETS simpleTest DESTINATION bin)
  install(
    FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/BootstrapGenerator.h"        
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/TH1Bootstrap.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/TH2Bootstrap.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/TH3Bootstrap.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/TH1DBootstrap.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/TH2DBootstrap.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/TH3DBootstrap.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/TH1FBootstrap.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BootstrapGenerator/TH2FBootstrap.h"
    DESTINATION include/BootstrapGenerator)
    
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/BootstrapGeneratorConfig.cmake"
    DESTINATION . COMPONENT dev)
endif()

