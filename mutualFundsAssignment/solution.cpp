/* Mohammed Mogasbe
 Xcode on a Mac
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;
const int rows = 500; //constant amount of rows
const int cols = 2; // constant amount of columns
const string inFileName= "VTSMX.csv";
const string inFileModified= "VTSMXmodified.csv";
void checkFile(ifstream&, fstream& ); // check for file errors
void checkinFile2( fstream& ); // check for file errors after changing the modified file from an If to an Of stream
void readFileinFile(ifstream&, fstream&); // read contents of original file and weed out the dashes and commas
void printOldest(int [500][2], int, int ); // print 5 eldest records
string dateParse(int ); // parsing for proper date output
float centsTamper(float ); // parsing for proper close output
void yearToDate(int [][cols], int ); // calculating the percent gain of the Year to Date
int  lastClose(int [][cols], int ); // finding the last close of 2017 this returns the index of that row
void currentDate(int); // finds the current date
void currentClose(int); //finds the close
void printLatest(int [500][2], int );// find the latest five records
void sortArray(int  [][cols], int , int); // sorts an array by highest closes if optionSort1 but if optionSort2 sort by date
void print(int [500][2],int ,int ); // print for personal checking purposes of all arrays that were changed or read to
void printHighest(int [500][2], int ); // prints highest closes after sorted
void movingAverage50And200(int [][cols], int); // moving average 50 days
void percentGain200(int [][cols], int); // percent gain and recomendations given at the end based off of it.
int main()
{
    
    //day = (dates%10000)%100 //Personal Calculations
    //month= (dates% 10000) / 100 //Personal Calculations
    //year = (20161910/ 10000) % 100; //Personal Calculations
    int a[rows][cols]; // main array for whole assignment
    string garbage; // stores garbage data
    int dates; //stores dates
    float close; // stores closes
    int close1; // holds final closes
    int i= 0; // integer I for moving through arrays
    int optionSort1 =1;
    int optionSort2 = 2;
    ifstream inFile; //initial file
    ofstream InFile2; // create modified file
    fstream inFile2; // modifed file
    inFile.open(inFileName);
    InFile2.open(inFileModified);
    if(InFile2.fail())
    {
        cout<<"Failure to create File: "<<inFileModified<<endl;
    }
    InFile2.close();
    inFile2.open(inFileModified);
    checkFile(inFile, inFile2);
    readFileinFile(inFile, inFile2);
    checkinFile2( inFile2) ;
    inFile2.open(inFileModified);
    
    while(inFile2>>dates>>garbage>>garbage>>garbage>>close>>garbage>>garbage) //assigning variables to the modified file columns
    {
        
        int closeFinal = static_cast<int>(round(close*100)); //rounding the closes
        close1 = closeFinal;
        a[i][0]= dates;
        a[i][1]= close1;
        
        
        //cout<<setw(11)<<fixed<<left<<a[i][0]<<a[i][1]<<endl;
        i++;
        
    }
    currentDate(a[499][0]);
    currentClose(a[499][1]);
    printLatest(a,rows);
    printOldest(a,rows,cols);
    sortArray(a,cols,optionSort1);
    printHighest( a,rows);
    sortArray(a,cols,optionSort2);
    //print(a,rows,cols);
    yearToDate( a,cols);
    movingAverage50And200( a,cols);
    
    percentGain200( a,cols);
}
void checkFile(ifstream& inFile,fstream& inFile2 )
{
    
    
    if(inFile.fail()|| inFile2.fail())
    {
        if(inFile.fail())
        {
            cout<<"Can not open file named "<<inFileName<<endl;
            
        }
        if(inFile2.fail())
        {
            cout<<"Can not open file named "<<inFileModified<<endl;
            
        }
        
        exit(0);
    }
}
void checkinFile2( fstream& inFile2 )
{
    if(inFile2.fail())
    {
        cout<<"Can not open file named "<<inFileModified<<endl;
        exit(0);
    }
    
    
}

void readFileinFile(ifstream& inFile, fstream& inFile2)
{
    string numbers;
    string xtraLine;
    getline(inFile,xtraLine);
    
    while(!inFile.eof())
    {
        numbers = inFile.get();
        
        if(numbers != "-")
        {
            if(numbers ==",")
            {
                inFile2<< " ";
                
            }
            else
            {
                if(inFile.eof())
                {
                    inFile2<<flush;
                }
                
                else
                {
                    inFile2<<numbers;
                    
                }}}}
    inFile.close();
    inFile2.close();
    
}
void printOldest(int a[500][2], int oldRows, int oldColumns )
{
    cout<<"The oldest five closes are:"<<endl;
    oldRows = 5;
    oldColumns= 2;
    for(int i=0; i<oldRows; i++)
    {
        cout<<setw(11)<<left<<dateParse(a[i][0])<<fixed<<setprecision(2)<<"$"<<centsTamper(a[i][1])<<endl;
    }
    cout<<endl;
}
string dateParse(int date)
{
    int month = (date % 10000) / 100;
    int day = date % 100;
    int year = (date / 10000) % 100;
    
    stringstream dateStream;
    dateStream<<setfill ('0') <<setw (2)<<month<<"/"<<setfill ('0') <<setw (2)<<day<<"/"<<year<<flush;
    
    return dateStream.str();
}



float centsTamper(float numbers)
{
    float price = numbers/100;
    
    return price;
}
void currentDate(int element)
{
    cout<<"Current Date: "<<dateParse(element)<<endl;
    
}
void printLatest(int a[500][2], int newRows)
{
    cout<<"The latest five closes are:"<<endl;
    newRows = 499;
    
    for(int i=newRows; i>newRows-5; i--)
    {
        cout<<setw(11)<<left<<dateParse(a[i][0])<<fixed<<setprecision(2)<<"$"<<centsTamper(a[i][1])<<endl;
        
    }
    
    cout<<endl;
}


void sortArray(int a[][cols], int cols,int optionSort)
{
    if(optionSort==1)
    {
        for(int i=0;i<500;i++){
            for(int j=0;j<(500-i)-1;j++)
            {
                if(a[j][1]>a[j+1][1])
                    
                {
                    int k=a[j][0];
                    a[j][0]=a[j+1][0];
                    a[j+1][0]=k;
                    
                    k=a[j][1];
                    a[j][1]=a[j+1][1];
                    a[j+1][1]=k;
                    
                    
                }
            }
        }
    }
    if(optionSort==2)
    {
        for(int i=0;i<500;i++){
            for(int j=0;j<500-1;j++)
            {
                if(a[j][0]<a[j+1][0])
                    
                {
                    int k=a[j][0];
                    a[j][0]=a[j+1][0];
                    a[j+1][0]=k;
                    
                    k=a[j][1];
                    a[j][1]=a[j+1][1];
                    a[j+1][1]=k;
                    
                    
                }
            }
        }
    }
    
}



void print(int a[500][2],int rows,int cols)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            cout<<setw(3)<<a[i][j]<<" ";
        cout<<"\n";
    }
}
void printHighest(int a[500][2], int newRows)
{
    cout<<"The highest five closes are:"<<endl;
    newRows = 499;
    
    for(int i=newRows; i>newRows-5; i--)
    {
        cout<<setw(11)<<left<<dateParse(a[i][0])<<fixed<<setprecision(2)<<"$"<<centsTamper(a[i][1])<<endl;
        
    }
    cout<<endl;
    
}

int  lastClose(int a[][cols], int cols)
{
    for(int i= 0; i<rows; i++)
    {
        if((a[0][0]/10000)-1 == a[i][0]/10000)
        {
            return i;
        }
    }
    return 0;
}
void yearToDate(int a[][cols], int cols)
{
    double YTD=(a[0][1]-a[lastClose(a,cols)][1]);
    double YTDF= YTD/a[lastClose(a,cols)][1];
    cout<<"Percent gain YTD:"<<YTDF*100<<"%"<<endl;
    cout<<endl;
}
void movingAverage50And200(int a[][cols], int cols)
{
    for(int g=0;g<2;g++)
    {
        if (g==0)
        {
            cout<<"50 Day Moving Average:"<<flush;
            double total= 0;
            for(int i=0; i<50; i++)
            {
                total +=a[i][1];
                
            }
            cout<<"$"<<(total/50)/100<<endl;
        }
        if(g==1)
        {
            cout<<"200 Day Moving Average:"<<flush;
            int total= 0;
            for(int i=0; i<200; i++)
            {
                total +=a[i][1];
            }
            cout<<"$"<<round(total/200)/100<<endl;
        }
    }
    
}
void percentGain200(int a[][cols], int cols)
{
    cout<<"Percent gain over 200 Day Moving Average:"<<flush;
    int total= 0;
    for(int i=0; i<200; i++)
    {
        total +=a[i][1];
    }
    
    double finalFinal = a[0][1]-(round(total/200));
    double finalFinalFinale= (finalFinal/round(total/200))*100;
    cout<<finalFinalFinale<<"%"<<endl;
    if(finalFinalFinale>5)
    {
        cout<<"Recommendation: Sell"<<endl;
    }
    else if(finalFinalFinale<-5)
    {
        cout<<"Recommendation: Buy"<<endl;
    }
    else
    {
        cout<<"Recommendation: Hold"<<endl;
        
    }
    
}
void currentClose( int element)
{
    cout<<"Current Close: "<<fixed<<setprecision(2)<<"$"<<centsTamper(element)<<endl;
    cout<<endl;
}

