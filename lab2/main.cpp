#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <math.h>
#define N 2500
using namespace std;

struct Bench
{
    string OpType;
    string Opt;
};
Bench benchmark;
 
template<typename T>
void Delete_Matrix(T** Matr)
{
    for(int i = 0; i < N; i++)
    {
        delete[] Matr[i];
    }
    delete[] Matr;
}

template<typename T>
void Fill_Matrix(T** Matr, T MaxEl)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
         Matr[i][j] = (T)rand()/(T)(RAND_MAX / MaxEl);
        }
    }
}

template<typename T>
T** Create_Matrix(T tmp)
{
    T** Matr = new T*[N];
    for(int i = 0; i < N; i++)
    {
        Matr[i] = new T[N];
    }
    return Matr;
}

template <typename T>
T** Mul_Matrix(T** Matr1, T** Matr2, T** MRes)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            for(int k = 0; k < N; k++)
            {
                MRes[i][j] += Matr1[i][k] * Matr2[k][j];
            }
        }
    }
    return 0;
}

template <typename T>
double Calculate_Time(T** Matr1, T** Matr2, T** MRes)
{
    clock_t start = clock();
    Mul_Matrix(Matr1, Matr2, MRes);
    clock_t end = clock();
    double res = ((double) end - start) / ((double) CLOCKS_PER_SEC);
    return res;
}

template <typename T>
void Write_Result(T** Matr1, T** Matr2, int Quantity_Test)
{
    T** MRes = Create_Matrix(T(0));
    double *Time = new double[Quantity_Test];
    double *AbsErr = new double[Quantity_Test];
    double *RelErr = new double[Quantity_Test];
    double *AvTime = new double[Quantity_Test];
    double TaskPerf = 0;
    string PModel = "AMD Ryzen 7 1700";
    string Task = "DGEMV";
    string Timer = "time.h";
    int InsCount = N * (N + (N - 1)) + N;

    for(int i = 0; i < Quantity_Test; i++)
    {
        Time[i] = Calculate_Time(Matr1, Matr2, MRes);
        AvTime[i] += Time[i] / Quantity_Test;
        TaskPerf = TaskPerf + (InsCount / Time[i]);
        AbsErr[i] = abs(Time[i] - AvTime[i]);
        RelErr[i] = (AbsErr[i] / AvTime[i]) * 0.1;
    }

    double res = pow((1 / TaskPerf), -1);
    TaskPerf = res;
    fstream Benchmark_Result;
    Benchmark_Result.open("Data/Benchmark_Result.csv", ios_base::app);
    for(int i = 0; i < Quantity_Test; i++)
    {
        Benchmark_Result << PModel << ";" << Task << ";" << benchmark.OpType << ";" << benchmark.Opt << ";" << InsCount << ";"
        << Timer << ";" << Time[i] << ";" << i+1 << ";" << AvTime[i] << ";" << AbsErr[i] << ";" << RelErr[i]  << ";" << res << ";" << endl;
    }
    Benchmark_Result << "\n";
    Delete_Matrix(Matr1);
    Delete_Matrix(Matr2);
    Delete_Matrix(MRes);
    delete[] Time;
}

void Read_Key_Optimisation()
{
    ifstream File("Data/KeyOptimisation.txt");
    string Key;
    getline(File, Key);
    benchmark.Opt = Key;
    File.close();
    system("rm Data/KeyOptimisation.txt");
}

void Benchmark()
{
    int Quantity_Test = 10;
    int IntMaxEl = 10; double DoubleMaxEl = 10.0; float FloatMaxEl = 10.f;
    Read_Key_Optimisation();
    benchmark.OpType = "int";
    int** IM1 = Create_Matrix(int(0)), **IM2 = Create_Matrix(int(0));
    Fill_Matrix(IM1, IntMaxEl);
    Fill_Matrix(IM2, IntMaxEl);
    Write_Result(IM1, IM2, Quantity_Test);
    benchmark.OpType = "double";
    double** DM1 = Create_Matrix(double(0)), **DM2 = Create_Matrix(double(0));
    Fill_Matrix(DM1, DoubleMaxEl);
    Fill_Matrix(DM2, DoubleMaxEl);
    Write_Result(DM1, DM2, Quantity_Test);
    benchmark.OpType = "float";
    float** FM1 = Create_Matrix(float(0)), **FM2 = Create_Matrix(float(0));
    Fill_Matrix(FM1, FloatMaxEl);
    Fill_Matrix(FM2, FloatMaxEl);
    Write_Result(FM1, FM2, Quantity_Test);
}
 
int main()
{
    srand(time(NULL));
    Benchmark();
}