# BootstrapGenerator Package

## Synopsis

This is an implementation of the bootstrap technique which works in the ATLAS software environment.
It is used to keep track of statistical correlations between overlapping samples, and works for both data and MC simulation.


## Installation

This package is compatible with the ATLAS CMake environment, as well as standalone CMake compilation.
For RootCore and Makefile compilation (deprecated) see below.

### ATLAS environment

If you're running with release 21 and CMake, the CMakeLists.txt file will be picked up and install everything you need in the usual `build/x86_64-slc6-gcc49-opt` directory.
(You only need to call `make`, not `make install` in this setup.)
Don't forget to call the usual
```bash
source build/x86_64-slc6-gcc49-opt/setup.sh
```
in order to pickup the compiled libraries in your environment.
This is needed for `hadd` and an interactive `TBrowser` to work properly.

### Standalone CMake compilation and installation

If you are using a standalone environment with ROOT, CMake, and git, e.g.
```bash
lsetup "root recommended" cmake git
```
If AnalysisBase isn't setup CMake will detect this and default to standalone compilation, allowing for the usual build steps, e.g.
```bash
mkdir build
cd build
cmake ../BootstrapGenerator -DCMAKE_INSTALL_PREFIX=../install
make
make install
```
Once you've compiled everything, you can point your enviroment at the installed libraries and executables:
```bash
cd .. # if you're in the build directory from above
export LD_LIBRARY_PATH=$PWD/install/lib:$LD_LIBRARY_PATH
export PATH=$PWD/install/bin:$PATH
```
If you're compiling against these libraries, the necessary headers are in `install/include`.


## Compiled C++ Examples

An example executable showing how to use the `TH1DBootstrap` class is in the `BootstrapGenerator/test` directory.
After compiling and setting up environment variables, you can run it with the command:
```bash
simpleTest
```


## C++ Macro Examples

An example of how to use the TH1DBootstrap class in a ROOT macro is given in
the scripts directory:
```bash
cd BootstrapGenerator/scripts
root -b -l -q TestBootstrap.C
```
The 'test.C' file compiles the necessary libraries using ROOT's CINT, the runs
the example macro 'TestBootstrap.C'

Another example using it for unfolding is also included:
```bash
cd BootstrapGenerator/scripts
root -b -l -q UnfoldExample.C
```

An example of smoothing systematics with statistical uncertainties is here:
```bash
cd BootstrapGenerator/scripts
root -b -l -q SmoothingExample.C
```
Note: this is an analysis specific example.
Because a dijet mass spectra is smoothed here, there is no bin beyond the last bin.
The last bin also generally has a large uncertainty (due to JES) and little statistical error.
Thus, the actual value is kept instead of the smoothed value.
This can be changed by dropping the final `false` argument in the `smooth::GaussianKernelSmooth()` call, which then defaults to `true` and smooths the last bin.
The rebinning also assumes bins are larger than 1e-4.
If this isn't the case you should tweak this value in `scripts/Smooth.h`.

An example of determining statistical correlations between measurements:
```bash
cd BootstrapGenerator/scripts
root -b -l -q TestCorrelations.C
```


## PyROOT example

You can also play with these classes in Python.
If you compiled in the ATLAS environment, everything should just work.
If you compiled stand alone, start by adding these environment variables:
```bash
> export PYTHONPATH=${PWD}/install/lib:$PYTHONPATH
```
Inside Python, you can now access these classes in the usual way:
```python
> from ROOT import TH1DBootstrap
```

## Athena / AthAnalysisBase tips

The BootstrapGenerator needs to be constructed in the `initialize()` routine:
```cpp
m_bootstrapGenerator = new BootstrapGenerator("BootstrapGenerator", "BootstrapGenerator", 100);
```
The TH\*Bootstraps need to be booked in `initialize()` as well. RootStreamName
needs to be set to the same as the RootStreamName specified in the jobOptions,
and RootDirName can be chosen:
```cpp
ServiceHandle<ITHistSvc> histSvc("THistSvc", name());
m_bootstrapHist = new TH1DBootstrap("MissingEt", "", 1000, 0, 1000, 100, m_bootstrapGenerator);
CHECK( histSvc->regGraph("/RootStreamName/RootDirName/MissingEt",reinterpret_cast<TGraph*>(m_bootstrapHist)) );
```
The `Generate()` function should be called in the beginning of the `execute()` procedure:
```cpp
const xAOD::EventInfo* eventInfo = 0;
CHECK( evtStore()->retrieve( eventInfo, "EventInfo") );
m_bootstrapGenerator->Generate(eventInfo->runNumber(), eventInfo->eventNumber());
```
And in `execute()` the histogram can then be filled as usual:
```cpp
m_bootstrapHist->Fill(met, 1.);
```

## Motivation

The statistical correlations in a measurement, as well as between different measurements, can be determined using the Bootstrap method.
This method uses a set of replicas of the nominal spectrum, derived by fluctuating each event in the sample by a Poisson distribution with average one, to produce the covariance/correlation matrix in the usual way.
The seed of the Poisson generator is determined uniquely based on the event and run number, as well as channel ID when MC is used.
In this way the combination of measurements, with full knowledge of the statistical correlations due to the synchronized replicas, can be performed after they are individually published.
The Bootstrap method can also be used to determine the statistical error on systematic uncertainties, which can be useful for determining their significance or when applying a smoothing algorithm. 

Useful references:  
[Slides introducing the Bootstrap method](https://indico.cern.ch/getFile.py/access?contribId=6&resId=0&materialId=slides&confId=237710)  
[Slides introducing the how to use the BootstrapGenerator package](https://indico.cern.ch/getFile.py/access?contribId=2&resId=0&materialId=slides&confId=217082)  


## Deprecated

### Installation

This package is also RootCore compatible, which was the recommended
method for compiling Run-1 analyses. In order to use hadd on files containing THBootstrap
classes, a library map must also be generated. This automatically done, but
means you must have the RootCore libraries in your path (read: RootCore must be
setup) if you'd like to hadd files containing TH\*Bootstrap objects.
```bash
cd ${ROOTCOREDIR}
RootCore/scripts/compile.sh
```
However, if you are using RootCore-00-01-38 (rev531835) or earlier, you will need
to manually generate the library map used by hadd:
```bash
cd ${ROOTCOREDIR}/RootCore/lib
rlibmap -f -o libBootstrapGenerator.rootmap -l libBootstrapGenerator.so -c ../../BootstrapGenerator/Root/LinkDef.h
```
If your setup does not use RootCore there is also a Standalone Makefile
provided:
```bash
mkdir BootstrapGenerator/StandAlone
cd BootstrapGenerator/cmt
make -f Makefile.Standalone
```
All libraries will be outputted to the newly created 'StandAlone' directory.
This package also compiles within an Athena project, although the rlibmap
portion has not yet been tested as working (provide feedback if you have any!):
```bash
cd BootstrapGenerator/cmt
cmt config
source setup
make
cd ../StandAlone
rlibmap -f -o libBootstrapGenerator.rootmap -l libBootstrapGenerator.so -c ../LinkDef.h
```


### C++ Examples

An example of how to use the TH1DBootstrap class in a ROOT macro is given in
the scripts directory:
```bash
cd scripts/
root -b -l -q test.C
```
The 'test.C' file compiles the necessary libraries using ROOT's CINT, the runs
the example macro 'TestBootstrap.C'

Another example using it for unfolding is also included:
```bash
cd scripts/
root -b -l -q unfold.C
```
An example of smoothing systematics with statistical uncertainties is here:
```bash
cd scripts/
root -b -l -q SmoothingExample.C
```
An example of determining statistical correlations between measurements:
```bash
cd scripts/
root -b -l -q TestCorrelations.C
```


### PyROOT example

You can also play with these classes in Python. If you compiled using RootCore,
everything should just work. If you compiled StandAlone, start by adding these
environment variables:
```bash
> export PYTHONPATH=${PWD}/BootstrapGenerator/StandAlone:$PYTHONPATH
> export LD_LIBRARY_PATH=${PWD}/BootstrapGenerator/StandAlone:$LD_LIBRARY_PATH
```
Inside Python, you can now access these classes in the usual way:
```python
> from ROOT import TH1DBootstrap
```

