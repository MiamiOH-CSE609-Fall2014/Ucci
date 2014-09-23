#include<iostream>
#include <vector>

using namespace std;

//create variables to read the matrix sizes as determined by the user
int matrixArows, matrixAcolumns, matrixBrows, matrixBcolumns;
int main()
{
  cout << "Please enter the number of rows for matrix A: " <<endl;
  cin >> matrixArows;
  cout << "Please enter the number of columns for matrix A: " << endl;
  cin >> matrixAcolumns;
  cout << "Please enter the number of rows for matrix B: " << endl;
  cin >> matrixBrows;
  cout << "Please enter the number of columns for matrix B: " << endl;
  cin >> matrixBcolumns;
  // check to make sure matrix dimensions match
  if (matrixAcolumns != matrixBrows)
    {	cout << "Invalid input\n" << endl;
  return 1;
    }
  // initialize the all the matrices
  int MatrixA [matrixArows][matrixAcolumns];
  int MatrixB [matrixBrows][matrixBcolumns];
  int MatrixC [matrixArows][matrixBcolumns];
  for (int b=0; b < matrixBcolumns; b++)
    {
      for (int c=0; c < matrixArows; c++)
	{ MatrixC[b][c] = 0;
	}
    }
  // read in values for matrix A
  for (int d=0; d < matrixArows; d++)
    {
      for(int e=0; e<matrixAcolumns; e++)
	{
	  cin >> MatrixA[d][e];
	}
    }
 // read in values for  matrix B
  for (int f=0; f < matrixBrows; f++)
    {
      for(int g=0; g < matrixBcolumns; g++)
	{
	  cin >> MatrixB[f][g];
	}
    }

  // calculate matrixC
  for (int h=0; h < matrixArows; h++)
    {
      for (int i=0; i < matrixAcolumns; i++)
	{
	  for (int j=0; j < matrixBcolumns; j++)
	    {
	      MatrixC[h][j] += MatrixA[h][i] * MatrixB[i][j]; 
	    }
	}
    }
    
  // output matrixA 
  for (int b=0; b < matrixArows; b++)
    {
      for (int c=0; c < matrixAcolumns; c++)
	{
	  cout << MatrixA[b][c];
	  cout << " ";
	}
      cout << "\n";
    }

  // output matrixB
  for (int d=0; d < matrixBrows; d++)
    {
      for (int e=0; e < matrixBcolumns; e++)
	{
	  cout << MatrixB[d][e];
	  cout << " ";
	}
      cout << "\n";
    }

  // output matrixC

  for (int f=0; f < matrixArows; f++)
    {
      for ( int g=0; g < matrixBcolumns; g++)
	{
	  cout << MatrixC[g][f];
	  cout << " ";
	}
      cout << "\n";
    }
  return 0;
}
