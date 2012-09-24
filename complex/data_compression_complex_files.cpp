
/*

* title "DATA COMPRESSION" long summer project for first year 
* using complex numbers and files and following Reed Solomon Codes.
* The program needs total points(m) ,max. error points(t)
* and initial points(n) which are defined in the code itself. 

*/


#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iostream>
#include<complex>
#include<math.h>
using namespace std;

#include<NTL/mat_RR.h>
#include<NTL/matrix.h>
NTL_CLIENT
const double pi=3.14159265;
const int m=13;
const int t=2;
const int n=8;
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
//	clrscr();
        ifstream enfile;
        enfile.open("enc1com");

	
	int i,j;
	float r,Co;
	
	complex<double> *d=(complex<double> *)(malloc(m*sizeof(complex<double>)));
	complex<double> *w=(complex<double> *)(malloc(m*sizeof(complex<double>)));

	complex<double> c;
	fill(w,m);
	for(i=0;i<m;i++)
	{
		enfile>>d[i];
	//	cout<<d[i]<<endl;;
	}

	mat_RR X,Y,A,B,C,D,In,IN,F;
	A.SetDims(n+2*t+1,n+2*t+1);
	B.SetDims(n+2*t+1,n+2*t+1);
	C.SetDims(n+2*t+1,1);
	D.SetDims(n+2*t+1,1);
	X.SetDims(n+2*t+1,1);
	Y.SetDims(n+2*t+1,1);
	In.SetDims(2*n+4*t+2,2*n+4*t+2);
	IN.SetDims(2*n+4*t+2,2*n+4*t+2);
	F.SetDims(2*n+4*t+2,1);

	for(i=1;i<=n+2*t+1;i++)
	{
		for(j=1;j<=n+t+1;j++)
		{
			c=w[(i-1)*(j-1)%m];
			A(i,j)=real(c);
			B(i,j)=imag(c);					
		}
		for(j=n+t+2;j<n+2*t+2;j++)
		{
			c=d[i-1]*w[((i-1)*(j-(n+t+2)))%m];
			A(i,j)=-real(c);
			B(i,j)=-imag(c);
		}
		c=d[i-1]*w[(i-1)*t%m];
		C(i,1)=real(c);
		D(i,1)=imag(c);
	}
	for(i=1;i<n+2*t+2;i++)
	{
		for(j=1;j<n+2*t+2;j++)
		{
			In(i,j)=A(i,j);
			In(n+2*t+1+i,n+2*t+1+j)=A(i,j);
			In(i,n+2*t+1+j)=-B(i,j);
			In(i+n+2*t+1,j)=B(i,j);	
		}
	}

	inv(IN,In);

	for(i=1;i<=n+2*t+1;i++)
		F(i,1)=C(i,1);
	for(i=n+2*t+2;i<2*n+4*t+3;i++)
		F(i,1)=D(i-n-2*t-1,1);
	F=IN*F;
//	cout<<"F is as follows\n\n";
	//cout<<F<<"\n\n\n";

//CALCULATING P

	int n1,n2;
	n1=n+t;
	n2=t;

	mat_RR a,b,temp,d1,q;

	a.SetDims(n1+1,2);
	b.SetDims(n2+1,2);
	temp.SetDims(n1+1,2);
	d1.SetDims(n2+1,2);
	q.SetDims(n1-n2+1,2);

	cout<<"DESTINATion REACHED!!!!\n\n";

	for(i=1;i<=n+t+1;i++)	
	{
		temp(n+t+2-i,1)=a(n+t+2-i,1)=F(i,1);
		temp(n+t+2-i,2)=a(n+t+2-i,2)=F(i+n+2*t+1,1);
	}

	 d1(1,1)=b(1,1)=1;
         d1(1,2)=b(1,2)=0;

	//cout<<d1<<endl;

	for(i=0;i<t;i++)
	{
		d1(t+1-i,1)=b(t+1-i,1)=F(i+n+t+2,1);
		d1(t-i+1,2)=b(t-i+1,2)=F(i+2*n+3*t+3,1);	
	}

	//cout<<a<<endl<<endl<<b;

	RR mult1,mult2;
		
	 for(i=0;i<n1-n2+1;i++)
        {

                mult1=(temp(i+1,1)*b(1,1)+temp(i+1,2)*b(1,2)) / (b(1,1)*b(1,1)+b(1,2)*b(1,2));
		mult2=(temp(i+1,2)*b(1,1)+temp(i+1,1)*b(1,2)) / (b(1,1)*b(1,1)+b(1,2)*b(1,2));

                q(i+1,1)=mult1; q(i+1,2)=0;

                for(j=i;j<=n2+i;j++)
                {
                        d1(j-i+1,1)=mult1*b(j-i+1,1)-mult2*b(j-i+1,2);
			d1(j-i+1,2)=mult2*b(j-i+1,1)+mult1*b(j-i+1,2);
			
                        temp(j+1,1)=temp(j+1,1)-d1(j-i+1,1);
			temp(j+1,2)=temp(j+1,2)-d1(j-i+1,2);
                        
                }

        }
	//cout<<"   A  \n"<<a<<endl<<endl<<"       B \n"<<b<<endl;
//	clrscr();
	cout<<q;

	return 0;	
}
