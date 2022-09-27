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
```

## OpenMP Parallel For with Static
```bash
Current Number of Threads = 1
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00850709 
Working on problem size N=2048 
 Elapsed time is : 0.02596457 
Working on problem size N=4096 
 Elapsed time is : 0.088949067 
Working on problem size N=8192 
 Elapsed time is : 0.32174455 
Working on problem size N=16384 
 Elapsed time is : 1.2211346 


Current Number of Threads = 2
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00495418 
Working on problem size N=2048 
 Elapsed time is : 0.013512525 
Working on problem size N=4096 
 Elapsed time is : 0.045650797 
Working on problem size N=8192 
 Elapsed time is : 0.16256014 
Working on problem size N=16384 
 Elapsed time is : 0.61422221 


Current Number of Threads = 4
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00384097 
Working on problem size N=2048 
 Elapsed time is : 0.006868352 
Working on problem size N=4096 
 Elapsed time is : 0.022803064 
Working on problem size N=8192 
 Elapsed time is : 0.082027115 
Working on problem size N=16384 
 Elapsed time is : 0.30760667 


Current Number of Threads = 8
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00366152 
Working on problem size N=2048 
 Elapsed time is : 0.003571915 
Working on problem size N=4096 
 Elapsed time is : 0.011551877 
Working on problem size N=8192 
 Elapsed time is : 0.040978122 
Working on problem size N=16384 
 Elapsed time is : 0.15396409 


Current Number of Threads = 16
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00500869 
Working on problem size N=2048 
 Elapsed time is : 0.001866028 
Working on problem size N=4096 
 Elapsed time is : 0.005919683 
Working on problem size N=8192 
 Elapsed time is : 0.020720626 
Working on problem size N=16384 
 Elapsed time is : 0.077360611 


Current Number of Threads = 32
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00891946 
Working on problem size N=2048 
 Elapsed time is : 0.004400975 
Working on problem size N=4096 
 Elapsed time is : 0.003168057 
Working on problem size N=8192 
 Elapsed time is : 0.010668288 
Working on problem size N=16384 
 Elapsed time is : 0.039814734 


Current Number of Threads = 64
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.0160421 
Working on problem size N=2048 
 Elapsed time is : 0.005701633 
Working on problem size N=4096 
 Elapsed time is : 0.011540827 
Working on problem size N=8192 
 Elapsed time is : 0.021452706 
Working on problem size N=16384 
 Elapsed time is : 0.020396036
```

## OpenMP Parallel For with Dynamic

```bash
Current Number of Threads = 1
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00840492 
Working on problem size N=2048 
 Elapsed time is : 0.02622124 
Working on problem size N=4096 
 Elapsed time is : 0.088689517 
Working on problem size N=8192 
 Elapsed time is : 0.32142011 
Working on problem size N=16384 
 Elapsed time is : 1.2196458 


Current Number of Threads = 2
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00495439 
Working on problem size N=2048 
 Elapsed time is : 0.013624934 
Working on problem size N=4096 
 Elapsed time is : 0.045297698 
Working on problem size N=8192 
 Elapsed time is : 0.16257208 
Working on problem size N=16384 
 Elapsed time is : 0.61363755 


Current Number of Threads = 4
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00380979 
Working on problem size N=2048 
 Elapsed time is : 0.006883402 
Working on problem size N=4096 
 Elapsed time is : 0.022882443 
Working on problem size N=8192 
 Elapsed time is : 0.081507246 
Working on problem size N=16384 
 Elapsed time is : 0.3082689 


Current Number of Threads = 8
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00366184 
Working on problem size N=2048 
 Elapsed time is : 0.003529096 
Working on problem size N=4096 
 Elapsed time is : 0.011574187 
Working on problem size N=8192 
 Elapsed time is : 0.040953913 
Working on problem size N=16384 
 Elapsed time is : 0.15419928 


Current Number of Threads = 16
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00490546 
Working on problem size N=2048 
 Elapsed time is : 0.001892977 
Working on problem size N=4096 
 Elapsed time is : 0.005943994 
Working on problem size N=8192 
 Elapsed time is : 0.020665056 
Working on problem size N=16384 
 Elapsed time is : 0.07765838 


Current Number of Threads = 32
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.00815563 
Working on problem size N=2048 
 Elapsed time is : 0.004548525 
Working on problem size N=4096 
 Elapsed time is : 0.003332076 
Working on problem size N=8192 
 Elapsed time is : 0.010676178 
Working on problem size N=16384 
 Elapsed time is : 0.039773894 


Current Number of Threads = 64
Description:	OpenMP dgemv.

Working on problem size N=1024 
 Elapsed time is : 0.0155547 
Working on problem size N=2048 
 Elapsed time is : 0.005866544 
Working on problem size N=4096 
 Elapsed time is : 0.011806366 
Working on problem size N=8192 
 Elapsed time is : 0.022682514 
Working on problem size N=16384 
 Elapsed time is : 0.020273007 
```


## CBLAS

```bash
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
