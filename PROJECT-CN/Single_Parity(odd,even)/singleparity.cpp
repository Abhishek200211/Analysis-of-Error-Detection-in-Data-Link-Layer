#include<iostream>
#include<stdlib.h>
#include <windows.h>
#include<fstream>
#define maxlength 10
#define maxmessages 10
using namespace std;
fstream file("paritycheck_output.txt",ios::in | ios::out | ios::app);
int crr[50];
void initialize(int arr[10],int m)
{
file<<"DATA you inserted : ";
for(int i=0;i<m;i++)
{
cin>>arr[i];
file<<arr[i];
arr[i] = arr[i]%2;
}


}
void print(int arr[10],int m)
{
for(int i =0;i<m;i++)
{

file<<arr[i]<<" ";
}
cout<<endl;
file<<endl;
}

// Even Parity
void addparbiteven(int arr[10],int m)  
{
int count=0;
for(int i=0;i<m;i++)
{
if(arr[i] == 1)
count++;
}
if(count%2 == 0)
arr[m] = 0;
else
arr[m] = 1;

for(int i=0;i<m;i++)
{
	crr[i]=arr[i];
}

print(arr,m+1);
}
//Odd parity
void oddpairtyy(int arr[10],int m)
{
int count=0;
for(int i=0;i<m;i++)
{
if(arr[i] == 1)
count++;
}
if(count%2 == 0)
arr[m] = 1;
else
arr[m] = 0;

for(int i=0;i<m;i++)
{
	crr[i]=arr[i];
}
print(arr,m+1);

}
//parity checker
void checkerror(int arr[10],int crr[50],int m) 
{
int count=0;

for(int i=0;i<m;i++)
{
    if(crr[i]!=arr[i])
	{
   
    file<<"Error Detected at :"<<i<<endl;
	}
	else
	{

	file<<"NO ERROR AT :"<<i<<endl;
    }

}
}
int main()
{   
    	 file<<("\t\t\n************< Welcome to PARITY BIT ERROR DETECTION > ************\n");
int m,arr[maxlength],data[50];
int ctr;
 system("Color 0A");
	char ch='y';
	 cout<<("\t*****< Welcome to PARITY BIT ERROR DETECTION > *****\n");
	file<<"\n ------OPTIONS------ \n1.ENTER DATA \n2.ADD PARITY EVEN \n3.ADD PARITY ODD \n4.ERROR CHECKER\n5.EXIT \n";
	do
	{
		cout<<"\n ------OPTIONS------ \n1.ENTER DATA \n2.ADD PARITY EVEN \n3.ADD PARITY ODD \n4.ERROR CHECKER\n5.EXIT ";
	
		cout<<"\nENTER YOUR CHOICE : ";
		cin>>ctr;
		file<<"\n YOUR CHOICE : ";
		file<<ctr<<endl;
		
		switch(ctr)
		{
	   case 1 : cout<<"Enter length of the message :";
                     cin>>m;
                     cout<<"Enter the message line by line"<<endl;
                     initialize(arr,m);
			   break;
         case 2 : cout<<"\nEven parity bit ADDED"<<endl;
                 file<<"\nAfter adding even parity bit the message is:"<<endl;
                     addparbiteven(arr,m);
					 break;
         case 3 : cout<<"\nOdd parity bit ADDED:"<<endl;
                  file<<"\nAfter adding odd parity bit the message is:"<<endl;
	              oddpairtyy(arr ,m);
	     break;
          case 4 : cout<<"\nchecking error....."<<endl;
		            checkerror(arr,crr,m+1);
                
	      break;		 
        case 5  : exit(0);
        default : cout<<"\n WRONG CHOICE " ;
                  file<<"\n WRONG CHOICE " ;
        
                     }
        cout<<"\n WANT TO CONTINUE? (Y/N) : ";
        file<<"\n WANT TO CONTINUE? (Y/N) : ";
         cin>>ch;
         file<<ch;
	}while(ch=='y'||ch=='Y');
	
    
		return 0;
}

