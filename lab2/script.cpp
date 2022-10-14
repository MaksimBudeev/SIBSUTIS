#include <iostream>
#include <fstream>
using namespace std;

void Create_Table_Header()
{
    ofstream Benchmark_Result;
    Benchmark_Result.open("Data/Benchmark_Result.csv");
    Benchmark_Result << "PModel;" << "Task;" << "OpType;" << "Opt;" << "InsCount;" << "Timer;" 
    << "Time;" << "LNum;" << "AvTime;" << "AbsErr;" << "RelErr;" << "TaskPerf;" << endl;
    Benchmark_Result.close();
}

void Write_Optimisation(string Opt)
{
    ofstream KeyOptimistioan;
    KeyOptimistioan.open("Data/KeyOptimisation.txt");
    KeyOptimistioan << Opt << endl;
    KeyOptimistioan.close();
}

void Auto_Test()
{
    string Opt;

    Opt = "none";
    Write_Optimisation(Opt);
    system("g++ -O0 -o Benchmark main.cpp");
    system("./Benchmark");

    Opt = "O1";
    Write_Optimisation(Opt);
    system("g++ -O1 -o Benchmark main.cpp");
    system("./Benchmark");

    Opt = "O2";
    Write_Optimisation(Opt);
    system("g++ -O2 -o Benchmark main.cpp");
    system("./Benchmark");

    Opt = "O3";
    Write_Optimisation(Opt);
    system("g++ -O3 -o Benchmark main.cpp");
    system("./Benchmark");
   
}

int main()
{
    Create_Table_Header();
    Auto_Test();
}