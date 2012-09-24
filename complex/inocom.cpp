//DATA POINTS FOR COMPLEX CASE

#include<fstream>
#include<iostream>

using namespace std;

int main()
{
	ofstream myfile;
	myfile.open("inocom");
	for(int i=0;i<=8;i++) myfile<<i<<endl;
	myfile.close();
	return 1;
}
