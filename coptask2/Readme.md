# COP 290 : Task 1 Subtask 2

This is the readme file for Task 1 Subtask 2: Code performance, learning plotting through scripts as part of COP 290: Design Practices course.<br/>
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
  * userfunctions.h: Consists of function "sequential" which is the normal matrix multiplication function. Used for comparing the time taken using linear algebra libraries and pthreads against sequentail implementation.
* yourcode.cpp: Main function file which executes the suitable implementation for matrix multiplication depending on the input received from command line.
* makefile: Generates the yourcode.out file.
* Readme.md
* mean_sd.cpp: Used to calculate mean and standard deviation of time taken by different implementations for matrix multiplication.
* .dat files: Contains matrix sizes and the correspong time taken for different implementations
  * pthread.dat
  * openblas.dat
  * sequential.dat
* gnuscriptfiles:
  * openblas-plot.png - picture of plot of matrix size vs running time
  * openblas-plot.eps- eps file of open blas plot
  * pthread-plot.png - picture of plot of matrix size vs running time
  * pthread-plot.eps- eps file of pthread plot
  * sequential-plot.png - picture of plot of matrix size vs running time
  * sequential-plot.eps- eps file of sequential plot
  * script-comparison - contains the script for comparison between different implementations
  * script-plot - contains the script for plotting matrix size vs running time
  * comparison-mean.png - picture of plot of comaprison on the basis of mean
  * comparison-mean.eps - eps file of comparion-mean
  * comparison-sd.png - picture of plot of comaprison on the basis of sd
  * comparison-sd.eps - eps file of comparion-sd

## How to run the file
In the terminal, use the following commands:
<br/>
1. ``` make ```<br/>
An executable named ``` yourcode.out ``` will be generated.
3. ``` ./yourcode.out ``` fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt openblas/pthread outputmatrix.txt<br/>
4. You can also run ```make clean``` to clean the .o files generated.

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
* multiply function: Initializes begin and end row index for each thread and thus divides the multiplication operation among all threads. Post this, it performs regular matrix multiplication.
* After creating threads, we join all the 4 threads using function pthread_join and thus obtain the final outputmatrix.

## Timing analysis of different implementations

Range of matrix sizes considered: 100 to 1000<br/>
The mean and standard deviations of time taken by the 3 implementations are as follows:<br/>

#### 1. Pthread

Mean: 0.42385 s<br/>
Std. deviation: 0.500127 s<br/>

#### 2. OpenBlas

Mean: 0.00464799 s<br/>
Std. deviation: 0.0049685 s<br/>

#### 3. Sequential

Mean: 0.867278 s<br/>
Std. deviation: 1.01302 s <br/><br/>
<img src="comparison-mean.png" alt="Mean" width="600"/><br/>
<img src="comparison-sd.png" alt="Standard dev" width="600"/>



## Boxplots using gnuplot

We have 2 different type of plots. One is comparison based and second based on timing vs matrix size.

1. Comparison Based-
 It shows the comparison beteen the openblas, sequential and pthread on the basis of two prameters- mean and standard devaition. The script of this is contained in the file called script-comparison. It plots the implementation on the x axis and mean/standard deviation on the y axis. The reults are in files called comparion-mean.png,comparison-mean.eps,comparison-sd.png and comparison-sd.eps.
2. Matrix size based- 
The script is contained in the file called script-plot. It plots matrix size on x-axis and running time on the y-axis. It is in this way implementated on the data obtained from the 3 implementations-openblas, pthread and sequential implementation. The result obtained fron openblas is in the file called openblas-plot.png and openblas-plot.eps. Similarly for the other two implementations

## Result of the task-

After running the matrix multiplication operation in three different ways on matrices of variuos sizes we can conclude these points-

1. For small sized matrices(1x1 to 10x10) the running time follows the order- pthread > openblas > sequential
2. For medium and large sized matrices ( 50X50 onwards) the running time follows the order- sequential > pthread > openblas 
3. On observing carefully we can conclude that the mean running time for large matrices follows the pattern-
running time for sequential=2 X (running time for pthreads). The openblas implementation takes very less time in comparison to other implementations.

