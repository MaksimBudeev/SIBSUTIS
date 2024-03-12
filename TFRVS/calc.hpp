#pragma once
#include <iostream>

using namespace std;

void calc_teta_and_t(int bn, long double lambda, int m, int n, long double mu, int flag)
{
	if((flag<1)||(flag>3))
	{
		cout<<"Invalid regime. Exit."<<endl;
		exit(0);
	}
	if((n<=0)||(bn<=0))
	{
		cout<<"Invalid parameter. Exit."<<endl;
		exit(0);
	}
	long double bt=0, teta=0, tetap1=1;
	int j,l;
	long double muarr[bn];
	
	// расчет µ
	for(l=0;l<=bn-1;l++)
	{
		if(((bn-m)<=l)&&(l<=bn))
			muarr[l]=(bn-l)*mu;
		if((l>=0)&&(l<(bn-m)))
			muarr[l]=m*mu;
	}
	
	// расчет Ɵ(n)
	if((flag==1)||(flag==3))
	{
		for(j=n+1;j<=bn;j++)
		{
			tetap1=1;
			for(l=n;l<=j-1;l++)
			{
				tetap1*=muarr[l]/(l*lambda);
			}
			teta+=tetap1/(j*lambda);
		}
		teta+=1/(n*lambda);
		
		cout<<"Ɵ(n) = "<<teta<<endl;
	}
	// расчёт T(n)
	if((flag==2)||(flag==3))
	{
		if(n>1)
		{
			long double btp1=1, btp2=1;
			for(l=1;l<=n-1;l++)
			{
				btp1*=(l*lambda)/muarr[l];
			}
			bt=btp1/muarr[0];
			
			for(j=1;j<=n-1;j++)
			{
				btp2=1;
				for(l=j;l<=n-1;l++)
				{
					btp2*=(l*lambda)/muarr[l];
				}
				bt+=btp2/(j*lambda);
			}
		} else {
			bt=1/muarr[0];
		}
		cout<<"T(n) = "<<bt<<endl;
	}
}