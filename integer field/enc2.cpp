//ENCODED DATA WITH GENERATOR 2^n

#include<fstream>
#include<iostream>
#include<math.h>

using namespace std;

#include<NTL/mat_ZZ_p.h>
#include<NTL/matrix.h>
#include<NTL/ZZ_p.h>

NTL_CLIENT
ZZ p;


const int N=15;
const int n=8;

int main()
{
	p=151;
	ZZ_p::init(p);

	int i=1,j=1,k;
	mat_ZZ_p X,w,x;
	ZZ_p temp,a,temp2;

	ifstream myfile;
	ofstream enfile;

	myfile.open("ino2");
	enfile.open("enc2");

	X.SetDims(N,1);
	x.SetDims(n+1,1);
	w.SetDims(N,1);

	for(i=1;i<=N;i++) 
	{
		w(i,1)=pow(2,i-1);
	}

	//cout<<w;

	i=0;
	while(i<=n)
	{
		myfile>>a;
		x(i+1,1)=a;
		i=i+1;
	}
	
	//cout<<x;

	for(i=0;i<N;i++)
	{
		for(j=0;j<=n;j++)
		{
			temp2=1;
			for(k=0;k<j;k++) temp2*=w(i+1,1);
			temp=x(j+1,1)*temp2;
	//		cout<<temp<<endl;
			X(i+1,1)=X(i+1,1)+temp;
		}
		enfile<<X(i+1,1)<<endl;
	//	cout<<X(i+1,1)<<endl;
	}
	cout<<"done\n";
		
	myfile.close();
	enfile.close();
	return 1;
}
