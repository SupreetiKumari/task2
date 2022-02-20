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

We have used the cblas_sgemm function from the cblas.h library of openblas to compute matrix multiplication result. The parameters passed to this are:<br/>
Given input matrices A and B, outputmatrix C, and constants p and q, it performs the following operation:<br/>
C = (pxAxB) + qxC
1. Matrix format: CblasColMajor(Column major format)
2. Transpose the inputmatrix(A) or not: CblasNoTrans
3. Transpose the weightmatrix(B) or not: CblasNoTrans
4. No. of rows in outputmatrix(C): row1
5. No. of columns in outputmatrix(C): co2
6. No. of columms in inputmatrix(A) or equivalently no. of rows in weightmatrix(B): co1
7. Multiplication constant(p):1.0
8. Inputmatrix(A)
9. No. of rows in inputmatrix(A): row1
10. Weightmatrix(B)
11. No. of rows in weightmatrix(B): co1
12. Multiplication constant(q):0.0
13. Outputmatrix(C)
14. No. of rows in outputmatrix(C): row1<br/>

cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, row1, co2, co1, 1.0, inputmatrix1, row1, weightmatrix1, co1, 0.0, outputmatrix1, row1);<br/>
To this outputmatrix, biasmatrix is added to obtain the final result.

## Pthread Implementation
 Library imported: pthread.h
 
* Created an array of 4 threads using function pthread_t.
* Used function pthread_create to create threads which perform matrix multiplication by dividing the computation among them. This function take 4 parameters as input: address of threadid, default NULL value, function for multiplication, argument to be passed to multiplication function).<br/>
pthread_create(&threadid[i],NULL,multiply,(void*)i);
* multiply function: Initializes start and end row index for each thread and thus divides the multiplication operation among all threads. Post this, it performs regular matrix multiplication.
* After creating threads, we join all the 4 threads using function pthread_join and thus obtain the final outputmatrix.

## Timing analysis of different implementations


## Boxplots using gnuplot





