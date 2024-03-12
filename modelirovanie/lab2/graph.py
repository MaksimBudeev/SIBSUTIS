import numpy as np
import matplotlib.pyplot as plt

# Функция плотности вероятности для первого интервала (-0.5, 0.3)
def density1(x):
    return x + 0.5

# Функция плотности вероятности для второго интервала (0.3, π/2)
def density2(x):
    return 1.5 * np.sin(2 * x)

# Задаем значения x для построения графика
x1 = np.linspace(-0.5, 0.3, 10000)
x2 = np.linspace(0.3, np.pi / 2, 10000)

# Вычисляем значения функции плотности вероятности для заданных интервалов
y1 = density1(x1)
y2 = density2(x2)

# Строим графики
plt.figure(figsize=(10, 6))
plt.plot(x1, y1, label='f(x) на интервале (-0.5, 0.3)', color='blue')
plt.plot(x2, y2, label='f(x) на интервале (0.3, π/2)', color='green')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('График функции плотности вероятности')
plt.legend()
plt.grid(True)
plt.savefig('dsfjls.png')