#include <iostream>
#include <fstream>
#include "calc.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	int flag=0;
	cout<<"Input regime (1 - calculate only Ɵ(n), 2 - calculate only T(n), 3 - calculate teta(n) and T(n)): "<<endl;
	cin>>flag;
	if((flag<1)||(flag>3))
	{
		cout<<"Invalid regime. Exit."<<endl;
		exit(0);
	}

	if(argv[1]==0)
	{
		cout<<"argv[1] = 0x0. Reading from the console."<<endl;
		cout<<"Input params N, λ, m, n, µ: "<<endl;
		int bn, n, m;
		long double lambda, mu;
		cin>>bn;
		cin>>lambda;
		cin>>m;
		cin>>n;
		cin>>mu;
		calc_teta_and_t(bn, lambda, m, n, mu, flag);
	} else {
		ifstream fr(argv[1]);
		if(!fr.is_open())
		{
			cout<<"File opening error."<<endl;
			return 0;
		}
		cout<<"argv[1] = "<<argv[1]<<". Reading from a file."<<endl;
		int bn, n, m;
		long double lambda, mu;
		while(true)
		{
			fr>>bn;
			fr>>lambda;
			fr>>m;
			fr>>n;
			fr>>mu;
			calc_teta_and_t(bn, lambda, m, n, mu, flag);
			//cout<<endl<<"**********"<<endl;
			if(fr.eof()) break;
		}
		fr.close();
	}
	return 0;
}