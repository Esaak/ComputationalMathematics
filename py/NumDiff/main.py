import matplotlib.pyplot as plt
import numpy as np


def grafik():
    with open('errSecond.txt', 'r') as errFile:
        lines = [i for i in errFile.read().split('\n')]
        line1 = [float(i) for i in lines[0].split()]
        line2 = [float(i) for i in lines[1].split()]
        line3 = [float(i) for i in lines[2].split()]

        h = []
        h.append(1.)
        for i in range(15):
            h.append(h[-1] * 0.5)
    h = np.array(h, dtype=float)
    line1 = np.array(line1, dtype=float)
    line2 = np.array(line2, dtype=float)
    line3 = np.array(line3, dtype=float)
    coef1 = np.polyfit(np.log10(h[:-4]), np.log10(line1[:-4]), 1)
    coef2 = np.polyfit(np.log10(h[:-6]), np.log10(line2[:-6]), 1)
    coef3 = np.polyfit(np.log10(h[:-8]), np.log10(line3[:-8]), 1)
    plt.figure(figsize=(12, 7))
    plt.minorticks_on()
    plt.grid(
        which='major'
    )
    plt.grid(
        which='minor',
        linestyle='--'
    )

    plt.plot(np.log10(h), np.log10(line1), linestyle='dashed', marker='o', markerfacecolor='green',
             label=f'N = 3, Коэффициент наклона = {coef1[0]}')
    plt.plot(np.log10(h), np.log10(line2), linestyle='dashed', marker='o', markerfacecolor='blue',
             label=f'N = 4, Коэффициент наклона = {coef2[0]}')
    plt.plot(np.log10(h), np.log10(line3), linestyle='dashed', marker='o', markerfacecolor='red',
             label=f'N = 5, Коэффициент наклона = {coef3[0]}')

    plt.xlabel("log(step)")
    plt.ylabel(r"log(err)")
    plt.title("Base")
    plt.legend()
    plt.savefig("basicSecond.png")
    plt.show()


def grafik2():
    with open('errAdvanced.txt', 'r') as errFile:
        lines = [i for i in errFile.read().split('\n')]
        line1 = [float(i) for i in lines[0].split()]
        line2 = [float(i) for i in lines[1].split()]
        line3 = [float(i) for i in lines[2].split()]
        print(line1)
        h = []
        h.append(1.)
        for i in range(15):
            h.append(h[-1] * 0.5)
    h = np.array(h, dtype=float)
    line1 = np.array(line1, dtype=float)
    line2 = np.array(line2, dtype=float)
    line3 = np.array(line3, dtype=float)
    coef1 = np.polyfit(np.log10(h[:-4]), np.log10(line1[:-4]), 1)
    coef2 = np.polyfit(np.log10(h[:-6]), np.log10(line2[:-6]), 1)
    coef3 = np.polyfit(np.log10(h[:-8]), np.log10(line3[:-8]), 1)
    plt.figure(figsize=(12, 7))
    plt.minorticks_on()
    plt.grid(
        which='major'
    )
    plt.grid(
        which='minor',
        linestyle='--'
    )

    plt.plot((np.log10(h)), np.log10(line1), linestyle='dashed', marker='o', markerfacecolor='green',
             color = 'green', label=f'N = 3, Коэффициент наклона = {coef1[0]}')
    plt.plot(np.log10(h), np.log10(line2), linestyle='dashed', marker='o', markerfacecolor='blue',
             color = 'blue', label=f'N = 4, Коэффициент наклона = {coef2[0]}')
    plt.plot(np.log10(h), np.log10(line3), linestyle='dashed', marker='o', markerfacecolor='red',
             color = 'red', label=f'N = 5, Коэффициент наклона = {coef3[0]}')
    plt.plot(np.log10(h[:-4]), coef1[0] * np.log10(h[:-4])+ coef1[1], label = 'polyfit N = 3', color = 'green')
    plt.plot(np.log10(h[:-6]), coef2[0] * np.log10(h[:-6]) + coef2[1], label = 'polyfit N = 4', color = 'blue')
    plt.plot(np.log10(h[:-8]), coef3[0] * np.log10(h[:-8]) + coef3[1], label = 'polyfit N = 5', color = 'red')
    plt.xlabel("log(step)")
    plt.ylabel(r"log(err)")
    plt.title("Advanced")
    plt.legend()
    plt.savefig("advanced.png")
    plt.show()

def multiiplyMatrix():
    a = np.array([[1.2, 4.4, 2, 6],
         [4, 11, 0, 87],
         [3, 10, 9, 5.6],
         [2.1, 1.1, 3, 1.3]])
    b = np.array([1.2, 2.1, 1, 5.6])
    print(np.dot(np.linalg.inv(a), b))
    a1 = np.array([[1, 1, 1, 1],
                   [0, 1, 2, 3],
                   [0, 0.5, 2, 4.5],
                   [0, 1/6., 4/3., 4.5]])
    b1 = np.array([0, 1., 0, 0.])
    print(np.dot(np.linalg.inv(a1), b1))

if __name__ == '__main__':
    grafik2()
