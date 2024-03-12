#include <iostream>
#include <cmath>
#include <random>

// Функция для генерации случайного числа из равномерного распределения на интервале [0, 1)
double generateUniformRandom()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
}

// Функция плотности вероятности для первого интервала (-0.5, 0.3)
double density1(double x)
{
    return x + 0.5;
}

// Функция плотности вероятности для второго интервала (0.3, π/2)
double density2(double x)
{
    return -0.3 * sin(2 * x); // Примерно половина периода функции sin(2x) на интервале (0.3, π/2) положительна
}

// Функция распределения для первого интервала (-0.5, 0.3)
double distribute1(double x)
{
    return (x * x / 2.0) + 0.5 * x; // Интеграл от f(x) на интервале (-0.5, x)
}

// Функция распределения для второго интервала (0.3, π/2)
double distribute2(double x)
{
    return 0.75 - 0.375 * cos(2 * x); // Интеграл от f(x) на интервале (0.3, x)
}

// Обратная функция распределения для первого интервала (-0.5, 0.3)
double inverseDistribute1(double y)
{
    return sqrt(2 * y + 0.25) - 0.5; // Функция обратная к distribute1(x)
}

// Обратная функция распределения для второго интервала (0.3, π/2)
double inverseDistribute2(double y)
{
    return acos(1.0 - (4.0 / 3.0) * y) / 2.0; // Функция обратная к distribute2(x)
}

// Функция для генерации случайного числа с заданной плотностью вероятности f(x)
double generateRandomWithDensity()
{
    double xi = generateUniformRandom();
    double sum_integrals = distribute1(0.3) + distribute2(M_PI / 2); // Интегралы на всем интервале
    double choose = xi * sum_integrals;

    if (choose <= distribute1(0.3))
    {
        // Генерируем случайное число на первом интервале (-0.5, 0.3)
        double y = inverseDistribute1(choose);
        return y;
    }
    else
    {
        // Генерируем случайное число на втором интервале (0.3, π/2)
        double y = inverseDistribute2(choose - distribute1(0.3));
        return y;
    }
}

int main()
{
    // Генерируем 10 случайных чисел с заданной плотностью вероятности
    for (int i = 0; i < 10; ++i)
    {
        std::cout << generateRandomWithDensity() << std::endl;
    }

    return 0;
}
