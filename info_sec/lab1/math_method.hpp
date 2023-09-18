#pragma once 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <map>
#include <vector>

#define RANGE 100000

using namespace std;

long long powmod(long long a, long long x, long long p);
vector <long long> gcd_Evclid(int a, int b);

bool is_prime(long long p);
long long random_prime_number(long long lower_limit, long long upper_limit);
void getGP (long long *p, long long *g);
void diff_helf();
void Shanks(long long a, long long y, long long p, long long m, long long k);
