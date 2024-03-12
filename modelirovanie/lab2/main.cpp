#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>
#include <utility>
#include <functional>

// Функция для генерации случайных чисел в диапазоне [0, 1)
double generateRandomNumber()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    return std::generate_canonical<double, sizeof(double) * 8>(gen);
}

class Generator
{
public:
    using density = std::function<double(double)>;
    using distribute = std::function<double(double)>;
    using inverse_distribution = std::function<double(double)>;
    using range = std::pair<double, double>;
    std::vector<std::tuple<density, distribute, inverse_distribution, range>> functions;
    Generator(std::vector<std::tuple<density, distribute, inverse_distribution, range>> _functions) : functions(_functions)
    {
    }
    double gen()
    {
        double xi = generateRandomNumber();
        double sum_integrals = 0.0;
        std::vector<double> weights;
        for (const auto &[f, F, F_inv, range] : functions)
        {
            auto [a, b] = range;
            double integral = F(b) - F(a);
            sum_integrals += integral;
            weights.push_back(sum_integrals);
        }
        double choose = xi * sum_integrals;
        int chosen_function = 0;
        for (int i = 0; i < functions.size(); ++i)
        {
            if (choose <= weights[i])
            {
                chosen_function = i;
                break;
            }
        }
        const auto &[f, F, F_inv, range] = functions[chosen_function];

        auto [a, b] = range;
        double A = 0.0;
        for (int i = 0; i < chosen_function; ++i)
        {
            const auto &[f, F, F_inv, range] = functions[i];
            auto [a, b] = range;
            A += F(b) - F(a);
        }
        double result = F_inv(xi * sum_integrals - A);
        return result;
    }
};

int main()
{
    double a = -0.3;
    double b = 1.5;
    double k = -0.8;
    auto f = [&](double x)
    {
        double tmp = (x + 0.2);
        return x + 0.5;
    };
    auto f2 = [&](double x)
    {
        return 1.5 * sin(2 * x); // Примерно половина периода функции sin(2x) на интервале (0.3, π/2) положительна
    };
    auto F = [&](double x)
    {
        double tmp = (x + 0.2);
        return (x * x / 2.0) + 0.5 * x; // Интеграл от f(x) на интервале (-0.5, x)
    };
    auto F2 = [&](double x)
    {
        return 0.75 - 0.375 * cos(2 * x); // Интеграл от f(x) на интервале (0.3, x)
    };
    auto F_inv = [&](double y)
    {
        return sqrt(2 * y + 0.25) - 0.5; // Функция обратная к distribute1(x)
    };
    auto F_inv2 = [&](double y)
    {
        return acos(1.0 - (4.0 / 3.0) * y) / 2.0; // Функция обратная к distribute2(x)
    };
    Generator generator({{f, F, F_inv, {a, 0.3}}, {f2, F2, F_inv2, {0.3, b}}});
    int numbers_count = 10000000;
    int intervals_count = 10000;
    double interval = (b - a) / (double)intervals_count;
    // double S = F(1.0) - F(-0.2) + F2(2.5) - F2(1.0);

    std::vector<int> intervals(intervals_count, 0);
    for (int i = 0; i < numbers_count; ++i)
    {
        double res_num = generator.gen();
        double interval_num = (res_num - a);
        int interval_index = (int)(interval_num / interval);
        intervals[interval_index] += 1;
    }
    std::ofstream out("data.csv");
    for (int i = 0; i < intervals.size(); ++i)
    {
        out << ((double)i * interval + a) << ' ' << (double)intervals[i] / intervals_count << '\n';
    }
    return 0;
}