#include <iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include <sstream>

using namespace std;

int main()
{
ifstream infile;
fstream outfile;
string value;
stringstream ss;
string token;
outfile.open("newfile.txt", ios::out);

//int j =0;

infile.open("channel28.csv");

while(!infile.eof())
{
getline(infile, value);

//if (value!="28")
//{
ss<<value<<'\n';





}
while(std::getline(ss, token, ',')) {
    std::cout << token << '\n';
    outfile<<token<<" ";
    }
    
    
    cout<<ss.str();
}






