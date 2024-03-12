#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

const double e = 2.71828;

struct props
{
	int bn, n, m, t;
	double lambda, mu;
	props(int a1 = 0, int a2 = 0, double ad1 = 0.0, double ad2 = 0.0, int a3 = 0, int a4 = 0)
	{
		bn = a1;
		n = a2;
		lambda = ad1;
		mu = ad2;
		m = a3;
		t = a4;
	}
};

double delta_x(int x)
{
	if (x >= 0)
		return 1.0;
	else
		return 0.0;
}

/*int factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}*/

double factorial(int n)
{
	unsigned long long int res = 1;
	for (unsigned long long int i = 1; i <= n; i++)
		res = res * i;
	if (n > 55)
		cout << "res = " << res << endl;
	return res;
}

double calc_fact(double a1, double a2)
{
	double r = a1;
	for (double i = 0.0; i < a2; i++)
		r /= i + 1.0;
	return r;
}

double calc_ul(props *pr, int i, int l)
{
	double mu = pr->mu;
	int bn = pr->bn, m = pr->m, t = pr->t;
	double ul = delta_x(bn - i - m);
	ul *= pow(m, l);
	ul *= pow(e, (-1.0) * m * mu * t);
	double ul2 = delta_x(m - bn + i);
	ul2 *= pow(bn - i, l);
	ul2 *= pow(e, (-1.0) * ((bn - i) * mu * t));
	ul += ul2;
	double ulp2 = ul * (1.0 * pow(mu * t, l));
	ul = calc_fact(ulp2, l);
	/*if(ul>1.0){
		cout<<"ul="<<ul<<endl;
		cout<<"i="<<i<<endl;
		cout<<"l="<<l<<endl;
		cout<<"ulp2="<<ulp2<<endl;
	}*/
	return ul;
}

double calc_pr(props *pr, int i, int r, int l)
{
	double lambda = pr->lambda;
	int n = pr->n, t = pr->t;

	double pir = 0.0;
	for (r = 0; r <= i - n + l; r++)
	{
		double pp1 = pow(i * lambda * t, r);
		double pp2 = pow(e, (-1.0) * i * lambda * t);
		double ppt = calc_fact(pp1 * pp2, r);
		pir += ppt;
	}
	return pir;
}

double calc_qi(props *pr, int i)
{
	double eps = 0.01;
	int l = 0;
	int r = 0;
	double mu = pr->mu, lambda = pr->lambda;
	int n = pr->n, bn = pr->bn, m = pr->m, t = pr->t;
	double qs = calc_ul(pr, i, l);
	/*if(qs>1.0)
			cout<<"qs = "<<qs<<endl;*/
	qs *= calc_pr(pr, i, r, l);
	double ql = qs + 10 * eps;
	while (abs(abs(qs) - abs(ql)) > eps)
	{
		if (l > 0)
			qs = ql;
		ql = 0.0;
		l++;
		double qlp1 = calc_ul(pr, i, l);

		double qlp2 = calc_pr(pr, i, r, l);

		ql += qlp1 * qlp2;
	}
	return qs;
}

double calc_pi(props *pr, int i)
{
	int l = 0;
	double mu = pr->mu, lambda = pr->lambda;
	int bn = pr->bn, n = pr->n;
	double pp = 0.0;
	for (l = 0; l <= bn; l++)
	{
		double ppp1 = mu / lambda;
		ppp1 = pow(ppp1, l);
		pp += calc_fact(ppp1, l);
	}
	pp = 1 / pp;
	double p1 = mu / lambda;
	p1 = pow(p1, i);
	pp *= calc_fact(p1, i);
	return pp;
}

double calc_pr_one_time(props *pr, int i, int r)
{
	double lambda = pr->lambda;
	int n = pr->n, bn = pr->bn, t = pr->t;

	double pir1 = pow(i * lambda * t, r);
	double pir2 = pow(e, (-1.0) * i * lambda * t);
	double pir = calc_fact(pir1 * pir2, r);

	return pir;
}

void calc_func(props *prt, int flag)
{
	if ((flag < 1) || (flag > 4))
	{
		cout << "Invalid regime. Exit." << endl;
		exit(0);
	}
	double mu = prt->mu, lambda = prt->lambda;
	int n = prt->n, bn = prt->bn, m = prt->m, t = prt->t;
	if ((n <= 0) || (bn <= 0))
	{
		cout << "Invalid parameter. Exit." << endl;
		exit(0);
	}

	int l = 0, i = 0, r = 0;
	if ((flag == 1) || (flag == 4))
	{

		double rdt = 0.0;
		for (i = n; i <= bn; i++)
		{
			double rtd1 = calc_pi(prt, i);
			double sumpr = 0.0;
			for (r = 0; r <= i - n; r++)
			{
				double rtd2 = 0.0;
				rtd2 = pow(i * lambda * t, r);
				rtd2 *= pow(e, (-1.0) * (i * lambda * t));
				rtd2 = calc_fact(rtd2, r);
				sumpr += rtd2;
			}
			rtd1 = sumpr * rtd1;
			rdt += rtd1;
		}
		cout.precision(12);
		cout << "Ŕ*(t) = " << rdt << endl;
	}

	// Рассчёт U*(t)
	if ((flag == 2) || (flag == 4))
	{
		r = 0;

		double udt = 0.0;
		for (i = 0; i <= n - 1; i++)
		{
			double rtd1 = calc_pi(prt, i);
			double sumul = 0.0;
			for (l = 0; l <= n - i - 1; l++)
				sumul += calc_ul(prt, i, l);
			udt += rtd1 * sumul;
		}
		udt = 1.0 - udt;
		cout.precision(12);
		cout << "Ũ*(t) = " << udt << endl;
	}

	if ((flag == 3) || (flag == 4))
	{
		double st = 0.0;
		if (bn == m)
		{
			st = 1.0 - (pow(lambda, bn - n + 1) * pow(lambda + mu, ((-1.0) * (bn - n + 1))));
		}
		else
		{
			for (int j = 0; j < bn; j++)
			{
				double Pj = pow(mu / lambda, j);
				Pj *= 1 / factorial(j);
				double st1 = 0;
				for (int l = 0; l < bn; l++)
				{
					double st2 = pow(mu / lambda, l);
					st2 *= 1 / factorial(l);
					st1 += st2;
				}
				// st1 = pow(st1, -1);
				Pj *= st1;
				// Pj *= pow(e, -mu / lambda);
				// 	st += Pj;
			}
			// st = 1 - st;
		}
		cout.precision(10);
		cout << "S(t) = " << st << endl;
	}
}