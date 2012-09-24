//PROJECT USING INTEGERS WITHOUT FILE


#include<stdio.h>
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

int main()
{
	int m,t,n,i,j;
	cout<<"enter mod :";cin>>p;
	cout<<"Enter the number of points to be given:";
	cin>>m;
	cout<<"Enter the number of error points:";
	cin>>t;
	cout<<"Enter the degree of polynomial:";
	cin>>n;
	if(m-n-2*t-1<0)
	{
		cout<<"Insufficient INFO\n";
		exit(0);
	}
	cout<<"Please enter points for field\n";
	
	ZZ_p::init(p);

	mat_ZZ_p d,w;

	d.SetDims(m,1);
	w.SetDims(m,1);

	for(i=1;i<=m;i++) w(i,1)=pow(3,i-1);
	for(i=1;i<=m;i++) cin>>d(i,1);
//	cout<<w;
//	cout<<d;

	mat_ZZ_p A,C,D,Ainv;
	A.SetDims(m,m);
	Ainv.SetDims(m,m);
	C.SetDims(m,1);
	D.SetDims(m,1);

	for(i=1;i<=m;i++)
	{
		
		for(j=1;j<=n+t+1;j++) A(i,j)=w( ( (i-1)*(j-1) %m)+1 , 1 );
		for(j=n+t+2;j<=m;j++) A(i,j) =-1*d(i,1) * w( ( ( (i-1)*(j-(n+t+2)) ) %m ) +1,1);

		C(i,1)=d(i,1) * w( ( (i-1) *t %m) +1,1 );
	}
//	cout<<A<<endl;
//	cout<<C<<endl;
	
	inv(Ainv,A);

	C=Ainv * C;

	cout<<"C is as follows\n\n";
	cout<<C<<"\n\n\n";

//CALCULATE P

	int n1,n2;
	n1=n+t;
	n2=t;

	mat_ZZ_p a,b,temp,d1,q;			//a=b*q

	a.SetDims(n1+1,1);
	b.SetDims(n2+1,1);
	temp.SetDims(n1+1,1);
	d1.SetDims(n2+1,1);
	q.SetDims(n1-n2+1,1);

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
//	cout<<"   A  \n"<<a<<endl<<endl<<"       B \n"<<b<<endl;
	cout<<q;
	return 0;
}	
