#include <iostream>
int a = 10;
class chugubandar {
    private:
        int a;
    public:
        chugubandar() {
            this->a = 0;
            std::cout << "chugubandar default constructor" << std::endl;
        }
        void setter(int);
        int getter();
        
};

void chugubandar::setter(int a) {
    a = a;
}

int chugubandar::getter() {
    return this->a;
}

int main() {
    chugubandar* obj = new chugubandar();
    obj->setter(69);
    std::cout << obj->getter() << std::endl;
    return 0;
}




























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

// We have to check the following functions- 
// copy constructor
// grow() function
// scalar multiplication

// Function left to do: 
// matrix multiplication

// Tasks left:
// Writing test cases
// Uploading files on gradescope
// Editing comments + documentation
