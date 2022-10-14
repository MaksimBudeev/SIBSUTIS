import matplotlib.pyplot as plt
import numpy as np

index = np.arange(4)
values1 = [1.57728,	2.54596, 1.10266, 1.10591]
values2 = [1.60251,	2.07568, 8.12552, 7.87289]
values3 = [1.66384, 2.15523, 8.10505, 8.24819]
bw = 0.3
plt.axis([0,4,0,10])
plt.title('A Multiseries Bar Chart', fontsize=20)
plt.bar(index, values1, bw, color='b')
plt.bar(index+bw, values2, bw, color='g')
plt.bar(index+2*bw, values3, bw, color='r')
plt.xticks(index+1.5*bw, ['None', '-O1', '-O2', '-O3'])
plt.title("Efficiency")
plt.xlabel("Key Optimisation")
plt.ylabel("Task Perf")
plt.legend(["int", "double", "float"])
plt.savefig('Data/chart.png')