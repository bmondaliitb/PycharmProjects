# Install script for directory: /Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/build/libBootstrapGenerator.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBootstrapGenerator.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBootstrapGenerator.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "libBootstrapGenerator.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBootstrapGenerator.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/buddha/local_packages/root_install/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBootstrapGenerator.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBootstrapGenerator.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/build/libBootstrapGenerator_rdict.pcm"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/build/libBootstrapGenerator.rootmap"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/build/simpleTest")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/simpleTest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/simpleTest")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/build/libBootstrapGenerator.dylib" "libBootstrapGenerator.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/simpleTest")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/buddha/local_packages/root_install/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/simpleTest")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/simpleTest")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/BootstrapGenerator" TYPE FILE FILES
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/BootstrapGenerator.h"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/TH1Bootstrap.h"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/TH2Bootstrap.h"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/TH3Bootstrap.h"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/TH1DBootstrap.h"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/TH2DBootstrap.h"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/TH3DBootstrap.h"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/TH1FBootstrap.h"
    "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/BootstrapGenerator/TH2FBootstrap.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/build/BootstrapGeneratorConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/buddha/PycharmProjects/HEP/BootStrapping/BootstrapGenerator-v1.11.2/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
