/*
* This project is being made as "The Semester Project" in first year.
* Title"DATA COMPRESSION" the aim of this project is to correct errors 
* in data during transmission or storage.
* One has to enter m: total no. of points, t: maximum error points, n:initial points


* Library used: NTL

*/

#include<stdio.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<iostream>
#include<math.h>
using namespace std;

#include<NTL/mat_ZZ_p.h>
#include<NTL/matrix.h>
#include<NTL/ZZ_p.h>

NTL_CLIENT
ZZ p;

const int m=15,n=8;
//const 
int t=3;

int main()
{
	p=151;
	int i,j;

	if(m-n-2*t-1<0)
	{
		cout<<"Insufficient INFO\n";
		exit(0);
	}
	
	ZZ_p::init(p);

	mat_ZZ_p d,w;

	d.SetDims(m,1);
	w.SetDims(m,1);

	fstream fin;
	fin.open("enc2");

	for(i=1;i<=m;i++) w(i,1)=pow(2,i-1);
	for(i=1;i<=m;i++) fin>>d(i,1);
//	cout<<w;
//	cout<<d;

	mat_ZZ_p A,C,D,Ainv;
	A.SetDims(n+2*t+1,n+2*t+1);
	Ainv.SetDims(n+2*t+1,n+2*t+1);
	C.SetDims(n+2*t+1,1);
	D.SetDims(n+2*t+1,1);

	for(i=1;i<=(n+2*t+1);i++)
	{
		
		for(j=1;j<=n+t+1;j++) A(i,j)=w( ( (i-1)*(j-1) %m)+1 , 1 );
		for(j=n+t+2;j<=(n+2*t+1);j++) A(i,j) =-1*d(i,1) * w( ( ( (i-1)*(j-(n+t+2)) ) %m ) +1,1);

		C(i,1)=d(i,1) * w( ( (i-1) *t %m) +1,1 );
	}
//	cout<<A<<endl;
//	cout<<C<<endl;
	ZZ_p det;
	do
	{
		determinant(det,A);
		if(det==0)
		{
			t--;
			mat_ZZ_p At;
			At.SetDims(n+2*t+1,n+2*t+1);
			C.SetDims(n+2*t+1,1);
			for(i=1;i<=n+2*t+1;i++)
        		{
                		for(j=1;j<=n+t+1;j++) At(i,j)=A(i,j);
                		for(j=n+t+2;j<=n+2*t+1;j++) At(i,j) =A(i,j+1);
                		C(i,1)=d(i,1) * w( ( (i-1) *t %m) +1,1 );
        		}
			swap(A,At);
		}
		else break;
	}while(t>0);

//	cout<<det;
	

	inv(Ainv,A);

	C=Ainv * C;

//	cout<<"C is as follows\n\n";
//	cout<<C<<"\n\n\n";

//CALCULATE P

	int n1,n2;
	n1=n+t;
	n2=t;

	mat_ZZ_p a,b,temp,d1,q,q0;			//a=b*q

	a.SetDims(n1+1,1);
	b.SetDims(n2+1,1);
	temp.SetDims(n1+1,1);
	d1.SetDims(n2+1,1);
	q.SetDims(n1-n2+1,1);
	q0.SetDims(n1-n2+1,1);

	cout<<"DESTINATion REACHED!!!!\n\n";

	for(i=1;i<=n+t+1;i++)	
	{
		temp(n+t+2-i,1)=a(n+t+2-i,1)=C(i,1);
	}

	 d1(1,1)=b(1,1)=1;

	//cout<<d1<<endl;

	for(i=0;i<t;i++)
	{
		d1(t+1-i,1)=b(t+1-i,1)=C(i+n+t+2,1);
	}

	//cout<<a<<endl<<endl<<b;

	ZZ_p mult1;

	ofstream fout;
	fout.open("rec");

	for(i=0;i<n1-n2+1;i++)
        {


                mult1= temp(i+1,1) / b(1,1);

                q(i+1,1)=mult1;

                for(j=i;j<=n2+i;j++)
                {
                        d1(j-i+1,1)=mult1*b(j-i+1,1);

                        temp(j+1,1)=temp(j+1,1)-d1(j-i+1,1);
                }

        }

	for(i=0;i<n1-n2+1;i++) q0(i+1,1)=q(n1-n2+1-i,1);

	fout<<q0<<endl;
	return 0;
}
