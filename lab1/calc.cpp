#include <iostream>
#include <fstream>
#include <iomanip>

void calc_teta(int N, long double lambda, int m, int n, long double mu)
{
    std::ofstream teta_file("TetaGraph.csv", std::ios::app);
    if (!teta_file.is_open())
    {
        std::cout << "Cant write in the file";
    }

    long double teta = 0;
    long double teta_temp = 1;
    long double mul = 0;
    for (int j = n + 1; j <= N; j++)
    {
        teta_temp = 1;
        mul = 0;

        for (int l = n; l <= j - 1; l++)
        {
            if (((N - m) <= l) && (l <= N))
            {
                mul = (N - l) * mu;
            }

            if ((l >= 0) && (l < (N - m)))
            {
                mul = m * mu;
            }

            teta_temp *= mul / (l * lambda);
        }
        teta += teta_temp / (j * lambda);
    }
    teta += 1 / (n * lambda);
    std::cout
        << "Teta = " << teta << std::endl;
    teta_file << n << ';' << mu << ';' << teta << std::endl;
    teta_file.close();
}

void calc_T(int N, long double lambda, int m, int n, long double mu)
{
    std::ofstream T_file("TGraph.csv", std::ios::app);
    if (!T_file.is_open())
    {
        std::cout << "Cant write in the file";
    }
    long double T = 1 / mu;

    long double mul = 0;
    long double T_temp = 1;

    long double mu0 = 0;

    mu0 = m * mu;

    for (int l = 1; l < n - 1; l++)
    {
        mul = 0;
        if (((N - m) <= l) && (l <= N))
        {
            mul = (N - l) * mu;
        }

        if ((l >= 0) && (l < (N - m)))
        {
            mul = m * mu;
        }

        T_temp *= (l * lambda) / mul;
    }

    T = T_temp / mu0;

    for (int j = 1; j <= n - 1; j++)
    {
        T_temp = 1;

        for (int l = j; l <= n - 1; l++)
        {
            mul = 0;
            if (((N - m) <= l) && (l <= N))
            {
                mul = (N - l) * mu;
            }

            if ((l >= 0) && (l < (N - m)))
            {
                mul = m * mu;
            }

            T_temp *= (l * lambda) / mul;
        }

        T += T_temp / (j * lambda);
    }

    std::cout << "T = " << T << std::endl;
    T_file << n << ';' << m << ';' << std::setprecision(10) << T << std::endl;
    T_file.close();
}

int main(int argc, char *argv[])
{
    std::ifstream file("params.txt");
    if (!file.is_open())
    {
        return 1;
    }

    int N, n, m;
    long double lambda, mu;

    while (!file.eof())
    {
        file >> N;
        file >> lambda;
        file >> m;
        file >> n;
        file >> mu;

        // calc_teta(N, lambda, m, n, mu);
        calc_T(N, lambda, m, n, mu);
    }

    std::cout << "FUCK\n";
    return 0;
}
