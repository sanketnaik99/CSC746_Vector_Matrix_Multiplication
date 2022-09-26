# vmmul instructional test harness

This directory contains a benchmark harness for testing different implementations of
vector-matrix multiply (VMM) for varying problem sizes.

The main code is benchmark.cpp, which sets up the problem, iterates over problem
sizes, sets up the vector and matrix, executes the vmmul call, and tests the
result for accuracy by comparing your result against a reference implementation (CBLAS).

Note that cmake needs to be able to find the CBLAS package. For CSC 746 Fall 2022,
this condition is true on Cori@NERSC and on the class VM. It is also true for some
other platforms, but you are on your own if using a platform other than Cori@NERSC
or the class VM.

# Build instructions - general

After downloading, cd into the main source directly, then:

% mkdir build  
% cd build  
% cmake ../  

Before these commands actually work, you may need to make some adjustments to your environment.
Below is information for Cori@NERSC, and for MacOS systems.

# Build peculiarities on Cori@NERSC

When building on Cori, make sure you are on a KNL node when doing the compilation. The
Cori login nodes are *not* KNL nodes, the Cori login nodes have Intel Xeon E5-2698
processors, not the Intel Xeon Phi 7250 (KNL) processors.  The simplest way to do this is
grab an interactive KNL node:  
salloc --nodes 1 --qos interactive --time 01:00:00 --constraint knl --account m3930

Also on Cori:

- cmake version: you need to use cmake/3.14 or higher. By default, Cori's cmake is cmake/3.10.2. 
Please type "module load cmake" from the command line, and the modules infrastructure will make
available to you cmake/3.14.4.

- Programming environment. You need to use the Cray-Gnu compilers for this assignment. To access
them, please type "module swap PrgEnv-intel PrgEnv-gnu" on the command line.

# Build peculiarities for MacOSX platforms:

On Prof. Bethel's laptop, which is an intel-based Macbook Pro running Big Sur, and
with Xcode installed, cmake (version 3.20.1) can find the BLAS package, but then the build fails with
an error about not being able to find cblas.h.

The workaround is to tell cmake where cblas.h lives by using an environment variable:
export CXXFLAGS="-I /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/Headers/"
then clean your build directory (rm -rf * inside build) and run cmake again. 

Note you will need to "locate cblas.h" on your machine and replace the path to cblas.h
in the CXXFLAGS line above with the path on your specific machine.

# Adding your code

For timing:

You will need to modify the benchmark.cpp code to add timing instrumentation, to 
report FLOPs executed, and so forth.


For vector-matrix multiplication:

There are stub routines inside dgemv-basic.cpp and dgemv-openmp.cpp where you can
add your code for doing basic and OpenMP-parallel vector-matrix multiply, respectively.

For the OpenMP parallel code, note that you specify concurrency at runtime using
the OMP_NUM_THREADS environment variable. While it is possible to set the number of
concurrent OpenMP threads at compile time, it is generally considered better practice to
specify the number of OpenMP threads via the OMP_NUM_THREADS environment variable.


# Running the codes

Some sample job scripts are provided as part of the harness. In principle, you should be able to use
them to launch batch jobs that run your code. You will probably need to make some adjustments
to these scripts for your particular testing workflow.

These sample job scripts have some reference values and tips for managing OpenMP-related
environment variables that are relevant to HW3 and Cori@NERSC.


# Results

## Basic

```bash
snaik@nid02391:~/CSC_746/CSC746_Vector_Matrix_Multiplication/build> chmod +x ./job-basic
snaik@nid02391:~/CSC_746/CSC746_Vector_Matrix_Multiplication/build> ./job-basic
Description:	Basic implementation of matrix-vector multiply.

Working on problem size N=1024 
 Elapsed time is : 0.00450678 
Working on problem size N=2048 
 Elapsed time is : 0.018008524 
Working on problem size N=4096 
 Elapsed time is : 0.071882576 
Working on problem size N=8192 
 Elapsed time is : 0.28734153 
Working on problem size N=16384 
 Elapsed time is : 1.1541844 
Description:	Basic implementation of matrix-vector multiply.

Working on problem size N=1024 
 Elapsed time is : 0.00449734 
Working on problem size N=2048 
 Elapsed time is : 0.017965604 
Working on problem size N=4096 
 Elapsed time is : 0.071887466 
Working on problem size N=8192 
 Elapsed time is : 0.28749719 
Working on problem size N=16384 
 Elapsed time is : 1.1540181 
Description:	Basic implementation of matrix-vector multiply.

Working on problem size N=1024 
 Elapsed time is : 0.00450837 
Working on problem size N=2048 
 Elapsed time is : 0.018039394 
Working on problem size N=4096 
 Elapsed time is : 0.072002706 
Working on problem size N=8192 
 Elapsed time is : 0.28753452 
Working on problem size N=16384 
 Elapsed time is : 1.1544154 
```

## OpenMP Parallel For in Inner Loop

```bash
snaik@nid02391:~/CSC_746/CSC746_Vector_Matrix_Multiplication/build> ./job-openmp 
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00710305 
Working on problem size N=2048 
 Elapsed time is : 0.023301589 
Working on problem size N=4096 
 Elapsed time is : 0.083488145 
Working on problem size N=8192 
 Elapsed time is : 0.31128662 
Working on problem size N=16384 
 Elapsed time is : 1.2069041 
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00718356 
Working on problem size N=2048 
 Elapsed time is : 0.018307533 
Working on problem size N=4096 
 Elapsed time is : 0.054725612 
Working on problem size N=8192 
 Elapsed time is : 0.18841288 
Working on problem size N=16384 
 Elapsed time is : 0.65553428 
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00723779 
Working on problem size N=2048 
 Elapsed time is : 0.015278916 
Working on problem size N=4096 
 Elapsed time is : 0.039629925 
Working on problem size N=8192 
 Elapsed time is : 0.1162557 
Working on problem size N=16384 
 Elapsed time is : 0.36770469 
```

## OpenMP Parallel For in Both Loops

```bash
snaik@nid02391:~/CSC_746/CSC746_Vector_Matrix_Multiplication/build> ./job-openmp 
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00842517 
Working on problem size N=2048 
 Elapsed time is : 0.029700134 
Working on problem size N=4096 
 Elapsed time is : 0.088982221 
Working on problem size N=8192 
 Elapsed time is : 0.32214719 
Working on problem size N=16384 
 Elapsed time is : 1.2353732 

Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00496619 
Working on problem size N=2048 
 Elapsed time is : 0.013495818 
Working on problem size N=4096 
 Elapsed time is : 0.04531799 
Working on problem size N=8192 
 Elapsed time is : 0.16263744 
Working on problem size N=16384 
 Elapsed time is : 0.61625256 

Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.0038625 
Working on problem size N=2048 
 Elapsed time is : 0.006847094 
Working on problem size N=4096 
 Elapsed time is : 0.02291375 
Working on problem size N=8192 
 Elapsed time is : 0.081596707 
Working on problem size N=16384 
 Elapsed time is : 0.30744932 
```


## CBLAS

```bash
snaik@nid02391:~/CSC_746/CSC746_Vector_Matrix_Multiplication/build> ./job-blas
Description:	Reference dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.0644224 
Working on problem size N=2048 
 Elapsed time is : 0.003327037 
Working on problem size N=4096 
 Elapsed time is : 0.013381408 
Working on problem size N=8192 
 Elapsed time is : 0.054469422 
Working on problem size N=16384 
 Elapsed time is : 0.21716591 
Description:	Reference dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00511087 
Working on problem size N=2048 
 Elapsed time is : 0.003319397 
Working on problem size N=4096 
 Elapsed time is : 0.013312508 
Working on problem size N=8192 
 Elapsed time is : 0.054558742 
Working on problem size N=16384 
 Elapsed time is : 0.21725939 
Description:	Reference dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00525184 
Working on problem size N=2048 
 Elapsed time is : 0.003295108 
Working on problem size N=4096 
 Elapsed time is : 0.013411328 
Working on problem size N=8192 
 Elapsed time is : 0.054892711 
Working on problem size N=16384 
 Elapsed time is : 0.21989115 
```