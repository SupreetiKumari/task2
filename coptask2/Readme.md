# COP 290 : Task 1, Subtask 2

This is the readme file for Task 1, Subtask 2: Code performance, learning plotting through scripts as part of COP 290: Design Practices course.<br/>
Contributed by: Arushi Goyal(2020CS50418) and Supreeti Kumari(2020CS10396)

## Aim of the task:

1. Accelerate matrix multiplication speeds using:
* linear algebra libraries: mkl and openblas
* pthreads

2. Measure mean and standard deviations of latencies of the three implementations (mkl, openblas and pthread implementation) over
 different matrix sizes and plot a box plot with error bars using gnuplot.
 
### Note: The architecture of Macbook Air with M1 processor doesn't support The Intel oneAPI. Since both of us use the same laptop, we have been unable to install mkl library for use on our systems. Hence, we request you to kindly redistribute the marks for this assignment. 
<br/>
We have the following files in our folder:<br\>

* Helper function files:
  * filecheck.h: Checks if the inputfile provided exists or not. If not, displays an error:"The inputmatrixfile file unfortunately could not be opened. Please give a valid file".
  * IO.h: Reads inputmatrices from inputfiles and writes the outputmatrix to the outputfile.
  * userfunctions.h: Consists of function "sequential" which is the normal matrix multiplication function. Used for comparing the time taken using linear algenra libraries and pthreads.
* yourcode.cpp: Main function file which executes the suitable implementation for matrix multiplication depending on the input received from command line.
* makefile: Generates the yourcode.o file.

## How to run the file
In the terminal, use the following commands:
<br/>
1. make
2. ./yourcode.o fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt openblas/pthread outputmatrix.txt<br/>

## OpenBlas Implementation:

We have used the cblas_sgemm function from the cblas.h library of openblas to compute matrix multiplication result. The parameters passed to this 





