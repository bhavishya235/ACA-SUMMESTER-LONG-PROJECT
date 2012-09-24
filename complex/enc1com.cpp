//ENCODING DATA FOR COMPLEX CASE

#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<math.h>
#include<complex>

using namespace std;

const int N=13;
const int n=8;
const double pi=3.14159265;

void fill(complex<double> *w,int m)
{
        double angle;
        int i;
        angle=2*pi/m; //stores angle for the second root of unity
        for(i=0;i<m;i++)
                w[i]=polar(1.0,i*angle);
}


int main()
{
	int i=0,j=0,a;

	ifstream myfile;
	ofstream enfile;

	myfile.open("inocom");
	enfile.open("enc1com");

	complex<double>*X=(complex<double> *)(malloc(N*sizeof(complex<double>)));
        complex<double>*w=(complex<double> *)(malloc(N*sizeof(complex<double>)));
	complex<double>*x=(complex<double> *)(malloc((n+1)*sizeof(complex<double>)));

	
	fill(w,N);
	i=0;
	cout<<w[i]<<endl;
	while(i<=n)
	{
//		cout<<i<<endl;
		myfile>>x[i++];
	}
	
//	cout<<"hell\n";;

	for(i=0;i<N;i++)
	{
		for(j=0;j<=n;j++)
		{	
			X[i]=X[i]+x[j]*pow(w[i],j);
		}
		enfile<<X[i]<<endl;
	//	cout<<X[i]<<endl;
	}
	cout<<"done\n";
		
	myfile.close();
	enfile.close();
	return 1;
}
