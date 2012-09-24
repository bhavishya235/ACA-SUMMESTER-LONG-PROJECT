//FOR 2^N

#include<fstream>
#include<iostream>

using namespace std;

//#include<NTL/mat_ZZ_p.h>
//#include<NTL/matrix.h>
#include<NTL/ZZ.h>

NTL_CLIENT
ZZ p,q;


int main()
{
	q=1;
	ofstream myfile;
	myfile.open("ino2");
	for(p=0;p<=8;p++) myfile<<3*p<<endl;
	myfile.close();
	return 1;
}
