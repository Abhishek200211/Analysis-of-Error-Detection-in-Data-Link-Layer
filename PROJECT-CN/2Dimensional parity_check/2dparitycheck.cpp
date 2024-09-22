#include<iostream>
#include<stdlib.h>
#include <windows.h>
#include<string>
#include<fstream>
using namespace std;
#define maxlength 10
#define maxmessages 10

fstream file("2D_OUTPUT.txt",ios::in | ios::out | ios::app);//It is used to store the  output of this code and display on GUI

void initialize(int arr[][10], int m, int n) {// random function is used here it will automatic generate [mxn] matrix in 0 and 1 
  for (int i = 0; i < m; i++)

    for (int j = 0; j < n; j++)

  {

    arr[i][j] = rand() % 2;

  }

}

void print(int arr[][10], int m, int n)// Displaying 2D matrix

{
 
  for (int i = 0; i < m; i++)

  {
    for (int j = 0; j < n; j++)

    {

      file<< arr[i][j] << " ";

    }

    file <<endl;

  }
  file<<endl;

}

//this Function will add parity bit it  and count the number of ones if count is odd then add 1 in parity to make it even
void addparbit(int arr[][10], int m, int n) // Even Parity

{

  for (int i = 0; i < m; i++)

  {

    int count = 0;

    for (int j = 0; j < n; j++)

    {

      if (arr[i][j] == 1)

        count++;

    }

    if (count % 2 == 0)

      arr[i][n] = 0;

    else

      arr[i][n] = 1;

  }

}

void induceerror(int arr[][10], int m, int n)// it will induce the error in line

{

  int k1, k2;
  k1 = rand() % m;
  k2 = rand() % n;
  if (arr[k1][k2] == 0)

    arr[k1][k2] = 1;

  else

    arr[k1][k2] = 0;

  file << "\nInducing error at line : " << k1 << endl;

}

void checkerror(int arr[][10], int m, int n)// This function will check in which line error will occur

{

  for (int i = 0; i < m; i++)

  {

    int count = 0;

    for (int j = 0; j < n; j++)

    {

      if (arr[i][j] == 1)

        count++;

    }

    if (count % 2 == 0 && arr[i][n] != 0)

    {

      file << "Error here at line :" << i<<endl;

    } else if (count % 2 == 1 && arr[i][n] != 1)

    {

      file << "\nError here at line : " << i<<endl;

    }

  }

}

int main()

{
	   file<<"\t**< Welcome to TWO DIMENSIONAL ERROR DETECTION > **\n";
	   system("Color 03");
	  cout<<("\t**< Welcome to TWO DIMENSIONAL ERROR DETECTION > **\n");
  int m, n, arr[maxmessages][maxlength];
  cout << "\nEnter total number of messages: ";
  cin >> m;

  cout << "Enter length of each message: ";
  cin >> n;
  
  cout<<"\n BY using RANDOM FUNCTION "<<m<<"x"<<n<<" MATRIX IS GENERATED !!";

  initialize(arr, m, n);
  print(arr, m, n);
  addparbit(arr, m, n);
  print(arr, m, n + 1);
  induceerror(arr, m, n);
  print(arr, m, n + 1);
  checkerror(arr, m, n);
  return 0;
}