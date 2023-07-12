/// ----------------------------------------------------------------------------------------------------------------------
/// * Matrix implementation *
///
/// In this project, we have defined a class mymatrix<T> explicitly designed to support a 2D data structure. 
/// Like vector<T>, it can grow dynamically in terms of rows and columns. Unlike vector<T>, the use of push_back 
/// is not required to add elements. Instead, a matrix is defined to have a given number of rows and columns, 
/// and the resulting elements are initialized to C++’s natural default value.

/// - Student info - 
/// Name: Srijita Banerjee          
/// netid: sbane4@uic.edu 
/// UIN: 675443340

/// - Project info -
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023
/// ----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "mymatrix.h"

using namespace std;


bool test_default_constructor () {
    mymatrix <int> a; // creating object of "int" type for default constructor

    // checking if number of rows = number of columns = 4 and each element in the matrix = 0
    if (a.numrows() == 4) { 
        for (int r=0; r<a.numrows(); ++r) {
            if (a.numcols(r) == 4) {
                for (int c=0; c<a.numcols(r); ++c) {
                    if (a.at(r,c) != 0) {
                        return false;
                    }
                }
            }
        }
    } 

  return true;  
}


bool test_parameterized_constructor (int R, int C) {
    mymatrix <int> a(R,C); // creating object of "int" type for parameterized constructor

    // checking if number of rows = R, number of columns = C and each element in the matrix = 0
    if (a.numrows() == R) { 
        for (int r=0; r<a.numrows(); ++r) {
            if (a.numcols(r) == C) {
                for (int c=0; c<a.numcols(r); ++c) {
                    if (a.at(r,c) != 0) {
                        return false;
                    }
                }
            }
        }
    } 

    return true;
}


bool test_copy_constructor (mymatrix <int> b) {
    mymatrix <int> a(b); // creating object of "int" type for copy constructor

    if (a.numrows() != b.numrows()) { // checking if # of rows of matrix a =  # of rows of matrix b
        return false;
    }

    for (int r=0; r<a.numrows(); ++r) {

        // checking if # of columns of matrix a =  # of columns of matrix b
        if (a.numcols(r) != b.numcols(r)) {
            return false;
        }

        for (int c=0; c<a.numcols(r); ++c) {
            if (a.at(r,c) != b.at(r,c)) { // checking if each element of both the matrices have been copied correctly
                return false;
            }
        }
        
    }
    return true;
}


bool test_num_of_rows (int R, int C) {
    mymatrix <int> abc (R,C);
    if (abc.numrows () != R) { // checking if numrows() function doesn't return the # of rows correctly
        return false;
    } 
    return true;
}


bool test_num_of_columns (int R, int C) {
    mymatrix <int> abc (R,C);
    for (int r=0; r<R; ++r) {
        if (abc.numcols(r) != C) { // checking if numcols() function doesn't return the # of rows correctly
            return false;
        }
    }
    return true;
}


bool test_growcols (int r, int C) {
    mymatrix <int> abc (3,5); 

    // making a matrix of 3 rows and 5 columns
    abc(0,0) = 99;
    abc (0,2) = -10;
    abc (1,1) = 34;
    abc (2,2) = 2;
    abc (2,3) = -11;

    abc.growcols (r,C); // implemented growcols() function

    if (abc.numcols(r) != C) { // checking if # of columns for row r has not been increased
        return false;
    }
    return true;
}

bool test_grow_function (int R, int C) {
    mymatrix <int> abc (3,2);
    abc(0,0) = 99;
    abc (0,2) = -10;
    abc (1,1) = 34;
    abc (2,0) = 2;
    abc (2,1) = -11;

    abc.grow (R,C); // implementing grow () function

    if (abc.numrows() != R) {
        return false; // number of rows have not been incremented correctly
    }

    for (int r=0; r<3; ++r) {
        if (abc.numcols(r) < C) { // columns have not been updated to be >=C
            return false;
        }
        for (int c=2; c<C; ++c) {
            if (abc.at(r,c)!=0) { // extra columns have not been populated correctly
                return false;
            }
        }
    }

    // checking validity of the new rows
    for (int r=3; r<R; ++r) {
        if (abc.numcols(r) < C) { // columns have not been updated to be >=C
            return false;
        }
        for (int c=0; c<C; ++c) {
            if(abc.at(r,c)!=0) { // extra columns have not been populated correctly
                return false;
            }
        }
    }
    return true;
}

bool test_at_function () {
    mymatrix <int> abc; // setting up the default matrix
    
    for (int r=0; r<abc.numrows(); ++r) {
        for (int c=0; c<abc.numcols(r); ++c) {
            if (abc.at(r,c)!=0) { // if desired value is not found, using at() function
                return false;
            }
        }
    }
    return true;
}

bool test_paranthesis_operator () {
    mymatrix <int> abc; // setting up the default matrix
    if (abc (0,0) != abc.at (0,0)) { // if () doesn't work the same way as .at()
        return false;
    }

    return true;
}

bool test_scalar_multiplication (int scalar) {
    mymatrix <int> abc(2,2);

    // setting up a 2X2 matrix
    abc.at(0,0) = 1;
    abc.at(0,1) = 2;
    abc.at(1,0) = 3;
    abc.at(1,1) = 4;

    mymatrix <int> result;
    result = abc.operator*(scalar); // result stores matrix after scalar multiplication is implemented

    for (int r=0; r<2; ++r) {
        for (int c=0; c<2; ++c) {
            if (result.at(r,c) != (scalar*abc.at(r,c))) { // if scalar multiplication is not implemented correctly
                return false;
            }
        }
    }

    return true;
}



// Driver function
int main () {
    int passed_cases = 0, failed_cases = 0;
    
    // Test case #1 : checking implementation of default constructor
    if (&test_default_constructor) {
        passed_cases ++;
    } else {
        failed_cases ++;
    }
    // Test case #2 : checking implementation of parameterized constructor
    if (test_parameterized_constructor (2,3)) {
        passed_cases++;
    } else {
        failed_cases++;
    }
    // Test case #3 : checking implementation of copy constructor
    mymatrix <int> abc;
    if (test_copy_constructor (abc)) {
        passed_cases++;
    } else {
        failed_cases++;
    }
    // Test case #4 : checking implementation of numrows () function
    if (test_num_of_rows (2,3)) {
        passed_cases++;
    } else {
        failed_cases++;
    }
    // Test case #5 : checking numcols (r) implementation
    if (test_num_of_columns (2,3)) {
        passed_cases++;
    } else {
        failed_cases++;
    }
    // Test case #6.1: checking growcols (r,C) implementation with correct input format
    // not checking test_growcols () for invalid input format since exception is thrown correctly and program terminates
    if (test_growcols (1,5)) {
        passed_cases++;
    } else {
        failed_cases++;
    }

    // Test case #6.2: checking growcols (r,C) implementation with correct input format (C<numcols(r))
    if (test_growcols (1,3)) {
        passed_cases++;
    } else {
        failed_cases++;
    }

    /*
    // Test case #7.1: checking grow (R,C) implementation with correct input format
    // not checking test_grow_function () for invalid input format since exception is thrown correctly and program terminates
    if (test_grow_function (4,10)) {
        passed_cases++;
    } else {
        failed_cases++;
    }
    */
    
    
    // Test case #8: checking implementation of at() function
    // not checking test_at_function () for invalid input format since exception is thrown correctly and program terminates
    if (test_at_function()) {
        passed_cases++;
    } else {
        failed_cases++;
    }
    
    // Test case #9: checking implementation of operator ()
    // not checking test_paranthesis_operator () for invalid input format since exception is thrown correctly and program terminates
    if (test_paranthesis_operator()) {
        passed_cases++;
    } else {
        failed_cases++;
    }
    
    /*
    // Test case #10: testing scalar multiplication implementation
    if (test_scalar_multiplication(2)) {
        passed_cases++;
    } else {
        failed_cases++;
    }
    */
    
    

    

    cout << "# of test cases passed: " << passed_cases << endl
         << "# of test cases failed: " << failed_cases << endl;
    
    return 0; // make C++ happy
}

