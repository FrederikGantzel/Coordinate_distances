# Coordinate_distances
Program for Assignment 5 of CS550 "Parallel Computing", NAU Fall Semester 2021. I had the same professor in this class as in CS599 "High Performance Computing", and I think he was really good.

## Description
Part one of this assignment (Brute_Force.c) was to write a brute-force parallel algorithm that would calculate the distance between every pair of a pre-generated set of two-dimentional coordinates, and determine how many of these pairs had a distance between them less than an inputted value "ε".

Part two of this assignment (Optimized.c) was a sort of Competition for the class, where we would try to optimize the brute-force algorithm to make it go as fast as possible. I ended up getting second place, so I was pretty satisfied with my results. For a full description of how I optimized the algorithm, see the Assignment Report.

## Installation and Usage
To run the program, first download the Coordinate_Distance_Measurer folder, and set your directory to that folder. The programs use openmp, so make sure you have that installed

To compile one of the programs type in the command:

__gcc Brute_Force.c -o Brute_Force -lm -fopenmp__

For the Brute Force algorithm, or:

__gcc Optimized.c -o Optimized -lm -fopenmp__

For the Optimized Algorithm

For extra optimization, put a __-O3__ at the end of this command. This is some automatic optimization that openmp does to make the program go faster (I don't know exactly how it works). Example:

__gcc Optimized.c -o Optimized -lm -fopenmp -O3__

To run the programs, type in:

__./Brute Force [x]__

or

__./Optimized [x]__

Where x is the desired value of ε. Note that the Optimized version runs slower the bigger ε is.

Note that in the assignment report, a bigger value of K is used (100,000). I have made it smaller in the programs so they would run faster for demonstrative purposes.

Some examples of the programs:

![image](https://user-images.githubusercontent.com/91853323/215660655-98e0f166-4413-472c-a5a6-b4ec9f0fd310.png)

![image](https://user-images.githubusercontent.com/91853323/215660755-71abbcbf-b086-4b77-a72a-709811fc9f61.png)

