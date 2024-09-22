#include<iostream>
#include<string.h>
#include <windows.h>
#include<fstream>
using namespace std;
fstream file("CRC_OUTPUT.txt",ios::in | ios::out | ios::app);//file for retreive its output!!

class CRC {
	

	string input,divisor,divident,result;
	
	int len_divident, len_gen, len_inp;// variables

public:
	string fun_xor(string a,string b)  // this fuction will xor the temp_divident,temp_div
	{
		string result="";
		if(a[0]=='0')
		return a.substr(1); // drop 0
		else
		{
			for(int i=0;i<len_gen;i++)
			{
				result=result+(a[i]==b[i]?'0':'1');
			}
			
			return result.substr(1);
		}
	}
	void  modulo_div()// this function will divide the divident with divisor and store the result in variable along with input and crc bit
	{
		
		string temp_div=divisor;
		string temp_divident=divident.substr(0,len_gen);
		int j=len_gen;
		while(j<len_divident)
		{
			temp_divident=fun_xor(temp_divident,temp_div);
			temp_divident=temp_divident+divident[j];//shifting
			j++;
		}
		result=input+fun_xor(temp_divident, temp_div);
	
		
	}
	void getdata()// GET INPUT FROM THE SENDER 
	{
		
		cout<<"\nEnter Input: ";
		cin>>input;
		cout<<"\nEnter coefficients of generator polynomial: ";
		cin>>divisor;
		
		len_gen=divisor.length();// TAKING LENGTH OF OF DIVSISOR
		len_inp=input.length();
		divident=input;
		int r=len_gen-1;//this will store divsior_length -1 
		for(int i=0;i<r;i++)
		{
			divident=divident+'0';	// append r number of '0' bit into the divident	
		}
		len_divident=divident.length();// updating the length of divident 
		
		modulo_div(); // calling modulo_div() function
		
		
		
	}
	void sender_side()   // SENDING DATA 
	{

    	cout<<"Data to send: "<<result<<"\n";
			file<<"Input: "<<input<<"\n";
		    file<<"Polynomial: "<<divisor<<"\n";
		    file<<"Divident: "<<divident<<"\n";
		    file<<"Data to send: "<<result<<"\n";
		
	}
	void receiver_side()
	{
		string data_rec;
		cout<<"\nEnter Data Received: ";
		   file<<"\nReceived Data: ";
		   cin>>data_rec;
		   file<<data_rec;

		string temp_div=divisor;// storing divisor into the temp value because it can't effect the original data.
		string temp_divident=data_rec.substr(0,len_gen);//  it will extract the data which is received by the Receiver and store into temp  
		int j=len_gen;
		while(j<data_rec.length())// while loop will run  from length of generator to received length of data.
		{
			temp_divident=fun_xor(temp_divident,temp_div);
			temp_divident=temp_divident+data_rec[j];
			j++;
		}
		string error=fun_xor(temp_divident, temp_div);
	
		file<<"\nreminder is: "<<error;

		bool flag=0;
		for(int i=0;i<len_gen-1;i++)
		{
			if(error[i]=='1')
			{
				flag=1;
				break;
			}
		}
		if(flag==0)// If The Reminder is zero  the no error in data bit
		{
			   
		       file<<"\nCorrect Data Received Without Any Error";
			
		}
		
		else  //  If The Reminder is  not equa  to zero  the error in data bit so it will be rejected !!
		{
			
	        	file<<"\nData Received Contain Some  Error";
		}
	
	}

};
 int main() {
    	file<<("\t\n**< Welcome to CYCLIC REDUNDANCY CHECK (CRC) ERROR DETECTION > **\n\n");
	system("Color 0B");

    cout<<("\t**< Welcome to CYCLIC REDUNDANCY CHECK (CRC) ERROR DETECTION > **\n");
	 CRC crc;// creating object for CRC class
	 crc.getdata(); 
	system("Color 0A");
	 crc.sender_side();
	 crc.receiver_side();
	 return 0;
}