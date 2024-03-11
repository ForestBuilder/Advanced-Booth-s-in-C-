#include <iostream>
#include <bits/stdc++.h>

using namespace std;


void addBits(int AC[], int x[], int length, int &carry);//add bits

void twosComp(int a[], int n_len);//2's comp 

void rightShift(int AC[], int qr[], int& eB, int length,int carry=0, int ADD = 0);//shift right

void modifiedBooth(int B[], int Q[], int length);//simulates modified booth's algo

void boothsAlgo(int B[], int Q[], int length, int iteration); //simulates booths algo

void display(int AC[], int Q[], int length, int eB);// display the array

int main()
{

  for(int i = 0; i< 17; i++)
  {
    int length = 0;
  
    //ask for the size
    cout<<"What is the size of the numbers you want to multiply?  ";
    cin>>length;
    
    int B[length];//multiplicant
    int Q[length];//multiplier
    cout<<"Input the multiplier: ";
    for(int i=0; i<length; i++)
      {
        cin>>Q[i];
      }
    cout<<"Input the multiplicand: ";
    for(int i=0; i<length; i++)
      {
        cin>>B[i];
      }

  
    //make temp variables
    int tempB[length];
    int tempQ[length];
    for(int i=0; i<length; i++)
      {
        tempB[i] = B[i];
      }
    for(int i=0; i<length; i++)
    {
      tempQ[i] = Q[i];
    }
      
    boothsAlgo(B, Q, length, length);
    
    modifiedBooth(tempB,tempQ,length);
  }
}

//this function takes the twos comp of the multiplier
void twosComp(int a[], int n_len)
{
  int i;
  int *x = new int[n_len]; //x holds the value of 1 
  for(int k = 0; k < n_len; k++) //x is initialized to 0
    {
      x[k]=0;
    }
  x[n_len-1] = 1; //x holds the value 1
  
  for (i = 0; i < n_len; i++) //toggle the bits of the mulitplier
    a[i] = (a[i] + 1) % 2;

  int carry = 0;
  addBits(a,x,n_len, carry); //Add x (which is 1) to the toggled multiplier
}  

void modifiedBooth(int B[], int Q[], int length)
{
  int eB = 0; //extended bit
  int *AC = new int[length]; //Accumulator
  int *Bcomp = new int[length]; //2's complement of B
  int carry = 0; //at the start the carry is
  int iteration = length/2;
  int addSubCount = 0;// count the number of Addition and Subtraction
  
  for (int i = length-1; i>=0;i--) //copy the contents of B (multiplicand) to Bcomp variable
    Bcomp[i]=B[i];

  twosComp(Bcomp, length); //take the 2's complement of Bcomp

  for(int i = length; i < length; i++)// Make the AC all zeros
    AC[i] = 0;

  int count = 1; //start the counter to keep track of iterations

  //output the starting values
  cout<<"\nSTART Mod Booth's" << count << ": ";
  display(AC, Q, length, eB);

  //going through the literaions
  while (iteration != 0)
  {

    if ((Q[length-2] == 0) && (Q[length-1] ==0) && (eB == 0))//000
    {
      // no action right shift twice
      cout<<"Iteration: " << count <<endl;
      rightShift(AC, Q, eB, length);
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";

      display(AC, Q, length, eB);
    }
    else if ((Q[length-2] == 0) && (Q[length-1] ==0) && (eB == 1))//001
    {
      //add multiplicand shift right shift twice
      cout<<"Iteration: " << count <<endl;
      
      //add B to AC
      addBits(AC, B, length, carry);
      cout<<"Add: ";
      display(AC, Q, length, eB);
      
      //right shift twice
      rightShift(AC, Q, eB, length);
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";
      display(AC, Q, length, eB);

      addSubCount++;
    }
    else if ((Q[length-2] == 0) && (Q[length-1] ==1) && (eB == 0))//010
    {
      //add multiplicand shift right shift twice
      cout<<"Iteration: " << count <<endl;

      //add B to AC
      addBits(AC, B, length, carry);
      cout<<"Add: ";
      display(AC, Q, length, eB);

      //right shift twice
      rightShift(AC, Q, eB, length);
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";
      display(AC, Q, length, eB);
      
      addSubCount++;
    }
    else if ((Q[length-2] == 0) && (Q[length-1] ==1) && (eB == 1))//011
    {
      //add 2*multiplicand shift right shift twice
      cout<<"Iteration: " << count <<endl;
      
      //add B to AC twice
      addBits(AC, B, length, carry);
      addBits(AC, B, length, carry);
      cout<<"Add: ";
      display(AC, Q, length, eB);

      //right shift wtice
      rightShift(AC, Q, eB, length);
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";
      display(AC, Q, length, eB);
      
      addSubCount++;
    }
    else if ((Q[length-2] == 1) && (Q[length-1] ==0) && (eB == 0))//100
    {
      //sub 2*multiplicand shift right shift twice
      cout<<"Iteration: " << count << " \n";

      //subtract bits twice
      addBits(AC,Bcomp,length, carry);
      addBits(AC,Bcomp,length, carry);
      cout<<"Subtract: ";
      display(AC, Q, length, eB);

      //shift right twice
      rightShift(AC, Q, eB, length);
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";
      display(AC, Q, length, eB);
      
      addSubCount++;
    }
    else if ((Q[length-2] == 1) && (Q[length-1] ==0) && (eB == 1))//101
    {
      //sub multiplicand shift right shift twice  
      cout<<"Iteration: " << count << " \n";
      addBits(AC,Bcomp,length, carry);
      cout<<"Subtract: ";
      display(AC, Q, length, eB);

      //shift right twice
      cout<<"Iteration: " << count <<endl;
      rightShift(AC, Q, eB, length);
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";
      display(AC, Q, length, eB);

      addSubCount++;
    }
    else if ((Q[length-2] == 1) && (Q[length-1] ==1) && (eB == 0))//110
    {
      //sub multiplicand shift right shift twice  
      cout<<"Iteration: " << count << " \n";

      //Sub Bits
      addBits(AC,Bcomp,length, carry);
      cout<<"Subtract: ";
      display(AC, Q, length, eB);

      //shift right twice
      cout<<"Iteration: " << count <<endl;
      rightShift(AC, Q, eB, length);
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";
      display(AC, Q, length, eB);

      addSubCount++;
    }
    else if ((Q[length-2] == 1) && (Q[length-1] ==1) && (eB == 1))//111
    {
      //no action shift right twice
      cout<<"Iteration: " << count <<endl;
      rightShift(AC, Q, eB, length);
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";
      display(AC, Q, length, eB);
    }
    else
      cout<<"\nError: Out of range \n";    

    count++;
    iteration--;
  }

  cout<<"\nThe number of Addition and Subtraction is: "<< addSubCount <<endl<<endl;
}

void boothsAlgo(int B[], int Q[], int length, int iteration)
{
  int eB = 0; //extended bit
  int *AC = new int[length]; //Accumulator
  int *Bcomp = new int[length];//2's complement of B
  int carry=0;// at the start the carry is 
  int addSubCount = 0;//count the number of addition and subtraction
  
  for (int i = length-1; i>=0;i--) //copy the contents of B (multiplicand) to Bcomp variable
    Bcomp[i]=B[i];
  
  twosComp(Bcomp,length); //take the 2's complemtn of Bcomp&

  for(int i = length; i < length; i++)// Make the AC all zeros
    AC[i] = 0;

  int count = 1;// start the counter to keep track of iterations

  //output the starting values
  cout<<"\nSTART Booth's algo" << count << ": ";
  display(AC, Q, length, eB);

  //going through the literaions
  while (iteration != 0)
  {
    
    if ((eB == 0) && (Q[length-1] == 0))
    {
      //do nothing and shift right
      cout<<"Iteration: " << count <<endl;
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift: ";
      
      display(AC, Q, length, eB);
    }
    else if ((eB == 1) && (Q[length-1] == 0))
    {
      //Add bits
      cout<<"Iteration: " << count<<endl;
      addBits(AC, B, length, carry);
      cout<<"Add: ";
      display(AC, Q, length, eB);
      
      rightShift(AC, Q, eB, length, carry);
      cout<<"Right Sifht: ";
      display(AC, Q, length, eB);

      addSubCount++;
    }
    else if ((eB == 0) && (Q[length-1] == 1))
    {
      //Sub Bits
      cout<<"Iteration: " << count << " \n";
      addBits(AC,Bcomp,length, carry);
      cout<<"Subtract: ";
      display(AC, Q, length, eB);
      
      rightShift(AC, Q, eB, length, carry);
      cout<<"Right Shift: ";
      display(AC, Q, length, eB);

      addSubCount++;
    }
    else if ((eB == 1) && (Q[length-1] == 1))
    {
      //do nothing and shift right
      cout<<"Iteration: " << count <<endl;
      rightShift(AC, Q, eB, length);
      cout<<"Right Shift:";
      
      display(AC, Q, length, eB);
    } 
    else
      cout<<"\nError: Out of range \n";
    
    count++;
    iteration--;
  }

   cout<<"\nThe number of Addition and Subtraction is: "<< addSubCount <<endl<<endl;
}


void addBits(int AC[], int x[], int length, int &carry)
{
  int c = 0; //initialize c as 0

  
  for(int i=length-1; i>=0;i--) // add going the opposite direction to simulate binary addition
    {
      //A = A + B
      AC[i] = AC[i]+x[i]+c; //Add each bit together and store in AC

      //Carry bit
      if(AC[i]>1) //if the total bits is greater than 1
      {
        AC[i] = AC[i] %2; //modulus by 2 to get the binary digit 
        c = 1; //carry is set at 1
      }
      else //if the total bits is not greater than 1
        c = 0; //carry is set at 0
    }
  carry = c; //keep track of carry
}

void rightShift(int AC[], int qr[], int& eB, int length, int carry, int ADD)
{
  int temp, i; //create some temp variables
  temp = AC[length-1]; //set temp as the last digit in the AC
  int temp2 = AC[0]; //set temp2 as the first digit in the AC
  eB = qr[length-1]; //set eb (extended bit) to the last digit in the mulitplier

  for(i = length-1; i>0; i--) //shift the digits right by 1 bit
    {
      AC[i] = AC[i-1];
      qr[i] = qr[i-1];
    }
    AC[0] = temp2; //set the first digit in the AC to temp2 (EXTEND THE BIT- 2's comp)
  
  qr[0] = temp; //set the first digit in the multiplier to temp 
}

void display(int AC[],int Q[], int length, int eB)// displays the array
{
  for(int i = 0; i < length; i++) //display the AC
    cout<<AC[i];
  cout<<" ";
  for(int i = 0; i < length; i++)//diplay the Q
    cout<<Q[i];
  cout<<" "<<eB<<endl;
}

