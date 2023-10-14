import matplotlib.pyplot as plt
import numpy as np


def grafik(x, y, k, filename, title):
    # i = 0
    # for j in range(3, len(x)):
    #     coef1 = np.polyfit(np.log(x[0:j]), np.log(y[0:j]), 1)
    #     coef2 = np.polyfit(np.log(x[0:3]), np.log(y[0:3]), 1)
    #
    #     if np.abs(coef1[0] - coef2[0])/np.abs(coef1[0]) >0.04:
    #         i = j
    #         break

    coef1 = np.polyfit(np.log(x[0:k]), np.log(y[0:k]), 1)
    plt.figure(figsize=(12, 7))
    plt.minorticks_on()
    plt.grid(
        which='major'
    )
    plt.grid(
        which='minor',
        linestyle='--'
    )
    plt.plot(np.log(x[0:k]), coef1[0] * np.log(x[0:k]) +coef1[1],lw = 4, color = 'green', label = "polyfit")
    plt.plot(np.log(x), np.log(y), linestyle='dashed', marker='o', markerfacecolor='green', color = 'green',
             label=f'Коэффициент наклона = {coef1[0]}')

    # plt.loglog(h, line1, linestyle='dashed', marker='o', markerfacecolor='green',
    #          label=f'N = 3, Коэффициент наклона = {coef1[0]}')
    # plt.loglog(h, line2, linestyle='dashed', marker='o', markerfacecolor='green',
    #          label=f'N = 4, Коэффициент наклона = {coef2[0]}')
    # plt.loglog(h, line3, linestyle='dashed', marker='o', markerfacecolor='green',
    #          label=f'N = 5, Коэффициент наклона = {coef3[0]}')
    # plt.xlim([-4, 2])
    # plt.ylim([0, 1])
    plt.xlabel("log(step)")
    plt.ylabel(r"log(err)")
    plt.title(title)
    plt.legend()
    plt.savefig(f"{filename.split('.')[0]}.png")
    plt.show()


def readData(filename):
    with open(filename, 'r') as errFile:
        data = [i.split() for i in errFile.readlines()]
    return data


if __name__ == '__main__':
    filename1 = "errN3.txt"
    filename2 = "errN5.txt"
    title1 = "Лабораторная работа: 'Интегрирование'. Квадратура Гаусса с 3 узлами"
    title2 = "Лабораторная работа: 'Интегрирование'. Квадратура Гаусса с 5 узлами"
    data1 = readData(filename1)
    data2 = readData(filename2)
    h = []
    h.append(16.)
    for i in range(len(data1) - 1):
        h.append(h[-1] * 0.5)
    grafik(h, np.array(data1, dtype=float), 9,  filename1, title1)
    grafik(h, np.array(data2, dtype=float), 5, filename2, title2)
