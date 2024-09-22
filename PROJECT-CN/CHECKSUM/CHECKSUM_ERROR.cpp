#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<stdio.h>
#include<stdbool.h>
#include <windows.h>
using  namespace std;
fstream file("checksum_output.txt",ios::in | ios::out | ios::app);// file handling for saving the output and displayed on GUI
int* decToBin(int dec,int n) // change decimal value in binary format
{
    int * bin=(int *)calloc(n,sizeof(int));
    
    for(int i=n-1;i>=0;i--)
    {
        bin[i]=dec%2;
        dec/=2;
    }
    return bin;
}
 
void checksumGen(int **data,int n,int k) // Sender side
{
    int carrynum=0;
    for(int j=k-1;j>=0;j--)
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=data[i][j];
        }
        sum+=carrynum;
        data[n][j]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0; // this will check the sum is 0 or 1 then it stored into the carrysum 
    }
    int *carry=decToBin(carrynum,k);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            cout<<(data[i][j]);
            file<<(data[i][j]);
        }
        
        file<<"<-Segment ["<<i+1<<"]\n";
      
    }
    file<<("-----------------\n");
    for(int j=0;j<k;j++)
     file<<(data[n][j]);
     file<<("<-Sum1\n");
    carrynum=0;
    for(int i=k-1;i>=0;i--)
    {
        int sum=carrynum+carry[i]+data[n][i];
        data[n][i]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    for(int i=0;i<k;i++)
        file<<(carry[i]);
        file<<("<-Carry\n");
        file<<("-----------------\n");
    for(int i=0;i<k;i++)
    {   
         file<<(data[n][i]);
        data[n][i]= data[n][i]==0 ? 1 : 0;
    }
        file<<("<-Sum2\n");
       file<<("-----------------\n");
       cout<<"\n\n";
    for(int i=0;i<k;i++)
    {
         file<<(data[n][i]);
         cout<<(data[n][i]);
    }
         cout<<("<-CHECKSUM SENDER SIDE\n");
         file<<("<-CHECKSUM SENDER SIDE\n");
}

void checksumChk(int **data,int n,int k)  // Receiver side
{
    int *chkBucket=(int *)calloc(k,sizeof(int));
    int carrynum=0;
    for(int j=k-1;j>=0;j--)
    {
        int sum=0;
        for(int i=0;i<=n;i++)
        {
            sum+=data[i][j];
        }
        sum+=carrynum;
        chkBucket[j]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    int *carry=decToBin(carrynum,k);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            file<<(data[i][j]);
        }
        file<<"<-Segment ["<<i+1<<"]\n";
    }
    for(int i=0;i<k;i++)
    {
        file<<(data[n][i]);
    }
      file<<("<-CHECKSUM (Receiver)\n");
     file<<("-----------------\n");
    for(int j=0;j<k;j++)
         file<<(chkBucket[j]);
         file<<("<-Sum1\n");
    carrynum=0;
    for(int i=k-1;i>=0;i--)
    {
        int sum=carrynum+carry[i]+chkBucket[i];
        chkBucket[i]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    for(int i=0;i<k;i++)
          file<<(carry[i]);
         file<<("<-Carry\n");
        file<<("-----------------\n");
    for(int i=0;i<k;i++)
    {
        file<<(chkBucket[i]);
        chkBucket[i]=chkBucket[i]==0 ? 1 : 0;
    }
         file<<("<-Sum2\n");
         file<<("-----------------\n");
    bool accept=true;
    for(int i=0;i<k;i++)
    {
        file<<(chkBucket[i]);
        if(chkBucket[i]!=0)
            accept=false;
    }
      file<<("<-CHECKSUM\n");
      file<<("%s",(accept ? "Accepted!" : "Rejected!"));// ternary operator is used 
      file<<("\n");
}

int main()
{
	file<<("\t\n*******< Welcome to CHECKSUM ERROR DETECTION > *******\n");
	system("Color 09");
    cout<<("\t\t*******< Welcome to CHECKSUM ERROR DETECTION > *******\n");
    int n,k;
    cout<<("\nEnter no of Segmets: ");
    cin>>(n);
    cout<<("Enter bit lenght of each segmet: ");
    cin>>(k);
    int len=(n+1)*sizeof(int *)+ (n+1)*(k)*sizeof(int);
    int **data=(int **)malloc(len);//dynamically create a space in heap
    int * ptr=(int *)(data+n+1);
    for(int i=0;i<n+1;i++)
        data[i]=(ptr+k*i);
    for(int i=0;i<n;i++)
    {
    	cout<<"Enter Segment ["<<i+1<<"](space separated): ";
        
        for(int j=0;j<k;j++)
        {
            cin>>(data[i][j]);
        }
    }
    checksumGen(data,n,k);
     cout<<("\nNow sender is sending the segments with checksum ... \n\n");
     file<<("\nNow sender is sending the segments with checksum ... \n\n");
     file<<("------------------------------------------\n");
     cout<<("Hello Transmission channel do you want to alter message (y/n): ");
     file<<("Hello Transmission channel do you want to alter message (y/n): ");
    char choice;scanf(" %c",&choice);
    file<<choice<<"\n";
    switch(choice)
    {
        case 'y':
            cout<<"You are supposed to enter "<<n<<" segments of "<<k<<" length!\n";
            for(int i=0;i<n;i++)
            {
                cout<<"Enter Segment ["<<i+1<<"](space separated): ";
                for(int j=0;j<k;j++)
                {
                    cin>>(data[i][j]);
                }
            }
            cout<<"Enter the checksum (space separated): ";
            for(int j=0;j<k;j++)
                cin>>(data[n][j]);
            break;
        case 'n':
             file<<"Transmission successfull without error!\n";
            break;
    }
    checksumChk(data,n,k);
}