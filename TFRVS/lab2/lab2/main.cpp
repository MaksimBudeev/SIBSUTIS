#include <iostream>
#include <fstream>
#include "calc.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	int flag=0;
	cout<<"Input regime (1 - calculate only R*(t), 2 - calculate only U*(t), 3 - calculate only S, 4 - calculate all: "<<endl;
	cin>>flag;
	if((flag<1)||(flag>4))
	{
		cout<<"Invalid regime. Exit."<<endl;
		exit(0);
	}

	if(argv[1]==0)
	{
		cout<<"argv[1] = 0x0. Reading from the console."<<endl;
		cout<<"Input params N, n, λ, µ, m, t: "<<endl;
		int bn, n, m, t;
		double lambda, mu;
		cin>>bn;
		cin>>n;
		cin>>lambda;
		cin>>mu;
		cin>>m;
		cin>>t;
		props pr(bn, n, lambda, mu, m, t);
		calc_func(&pr, flag);
	} else {
		ifstream fr(argv[1]);
		if(!fr.is_open())
		{
			cout<<"File opening error."<<endl;
			return 0;
		}
		cout<<"argv[1] = "<<argv[1]<<". Reading from a file."<<endl;
		int bn, n, m, t;
		double lambda, mu;
		while(true)
		{
			fr>>bn;
			fr>>n;
			fr>>lambda;
			fr>>mu;
			fr>>m;
			fr>>t;
			props pr(bn, n, lambda, mu, m, t);
			calc_func(&pr, flag);
			//cout<<endl<<"**********"<<endl;
			if(fr.eof()) break;
		}
		fr.close();
	}
	return 0;
}