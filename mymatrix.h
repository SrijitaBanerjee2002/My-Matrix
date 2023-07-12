/*mymatrix.h*/

// 
// TODO
//
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023


//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    
    Rows = new ROW [R]; // an array with R row structs
    NumRows = R;

    // initialising each row to have C columns
    for (int i=0; i<NumRows; ++i) {
      Rows[i].Cols = new T[C]; // dynamic array of column elements for R rows
      Rows[i].NumCols = C; // number of columns for each row

      // intialising each element of the matrix 
      for (int j=0; j<Rows[i].NumCols; ++j) {
        Rows[i].Cols[j] = T{}; // default value of T
      }
    }
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
    //
    // TODO - DONE
    //
    // Getting number of rows in "other" matrix
    NumRows = other.NumRows;
    // Dynamically allocating NumRows rows into the matrix
    Rows = new ROW[NumRows];

    // intialising each row to have as many columns as there are in "other" matrix
    for (int r=0; r<NumRows; ++r) {
      Rows[r].Cols = new T[other.numcols(r)]; // dynamic array of column elements for each row as there are in "other" matrix
      Rows[r].NumCols = other.numcols(r); // number of columns for each row as there are in "other" matrix

      // initialising each element of the matrix to the element as in "other" matrix
      for (int c=0; c<Rows[r].NumCols; ++c) {
        Rows[r].Cols[c] = other.at(r,c); 
      }
    }
  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    return NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    
    return Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    
    if (numcols(r) < C) {
      // dynamically allocate new no of columns
      ROW obj;
      obj.Cols = new T[C];
      obj.NumCols = C;
      
      // populate with default data type of T
      for (int i=0; i<C; ++i) {
        if (i<numcols(r)) { // retaining all existing values of the array till the index numcols(r)-1
          obj.Cols[i] = at(r,i); 
        } else {
          obj.Cols[i] = T{}; // default value for T
        }
      }
      // update new number of columns (with default values) in row r
      Rows[r] = obj;
    } else {
      // * no action required here *
    }
    

  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");

    if (R <= numrows ()) { // 
      for (int r=0; r<numrows(); ++r) {
        // when a row has < C columns, columns are added for that particular row
        // using growcols () function
        growcols (r,C);
      }
    } else if (R > numrows()) {
      ROW* new_array = new ROW[R];
      
      // making a copy of the original matrix
      for (int r=0; r<numrows(); ++r) {
        new_array[r].Cols = new T [numcols(r)];
        new_array[r].NumCols = numcols(r);

        for (int c=0; c<new_array[r].NumCols; ++c) {
          new_array[r].Cols[c] = Rows[r].Cols[c];
        }
      }

      for (int r=numrows(); r<R; ++r) {
        new_array[r].Cols = new T[C];
        new_array[r].NumCols = C;
        growcols (r,C);
      }
      Rows = new_array;
      
      NumRows = R;
      growcols (R,C);
    }
    
  }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
    int total = 0;

    for (int r=0; r<numrows(); ++r) {
      total = total + numcols(r); // total = accumulating number of columns for each row
    }

    return total;
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    
    T& temp = Rows[r].Cols[c]; // accessing reference of element in r-th row and c-th column
    return temp;
    
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

    

    T& temp = Rows[r].Cols[c]; // accessing reference of element in r-th row and c-th column
    return temp;
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result;

    for (int r=0; r<result.numrows(); ++r) {
      for (int c=0; c<result.numcols(r); ++c) {
        result.at(r,c) = scalar * (Rows[r].Cols[c]);
      }
    }

    return result;
  }


  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    mymatrix<T> result;

    //
    // both matrices must be rectangular for this to work:
    //

    // if (this matrix is not rectangular)
    
    // check whether the number of columns is same for each row
    int first_row_this = numcols(0); // storing the number of columns for first row
    int count_this = 0;

    for (int r=0; r<numrows(); ++r) {
      if (numcols(r) != first_row_this) { // if we find out that "this" matrix is jagged
        count_this++;
      }
    }
    if (count_this != 0) {
      // throwing error here....?
      throw runtime_error("mymatrix::*: this not rectangular");
    } else {
      // now we know that "this" matrix is rectangular
    }

    // if (other matrix is not rectangular)
    
    int first_row_other = other.numcols (0); // storing the number of columns of "other" matrix
    int count_other = 0;

    for (int r=0; r<other.numrows(); ++r) {
      if (other.numcols(r) != first_row_other) { // we found that "other" matrix is jagged
      count_other++;
      }
    }
    if (count_other != 0) {
      // throwing runtime error.....?
      throw runtime_error("mymatrix::*: other not rectangular");
    } else {
      // now we know that "other" matrix is also rectangular
    }
    

    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //

    int this_column = first_row_this; 
    int other_row = other.numrows();
    if (this_column != other_row) { // if # of columns != # of rows 
      // throw runtime error ....?
      throw runtime_error("mymatrix::*: size mismatch");
    } else {
      // we know that both matrices can be multiplied
    }
    

    //
    // Okay, we can multiply:
    //
    
    // dynamically allocate rows for "result" matrix
    int result_rows = numrows ();
    int result_columns = other.numcols(0);

    result.Rows = new ROW[result_rows]; // dynamically allocating rows for "result" array
    result.NumRows = result_rows; // allocating number of rows for "result" array

    for (int r=0; r<result.NumRows; ++r) {
      result.Rows[r].Cols = new T[first_row_other]; // dynamically array for column elements
      result.Rows[r].NumCols = first_row_other; // number of columns for each row

      for (int c=0; c<result.Rows[r].NumCols; ++c) {
        result.Rows[r].Cols[c] = Rows[r].Cols[c] * other.Rows[c].Cols[r];
      }
    }

    return result;
  }


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};