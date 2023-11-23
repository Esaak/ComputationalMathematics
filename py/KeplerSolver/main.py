import matplotlib.pyplot as plt
import numpy as np



def grafikBase(x, y, filename):

    plt.figure(figsize=(12, 7))
    plt.minorticks_on()
    plt.grid(
        which='major'
    )
    plt.grid(
        which='minor',
        linestyle='--'
    )

    coef1 = np.polyfit(x[0], np.log10(y[0]), 1)
    coef2 = np.polyfit(x[1], np.log10(y[1]), 1)
    coef3 = np.polyfit(x[2], np.log10(y[2]), 1)
    coef4 = np.polyfit(x[3], np.log10(y[3]), 1)

    plt.plot(x[0], np.log10(y[0]), linestyle='dashed', marker='o', markerfacecolor='green', color = "green",
             label=f'ecc = 0.1, k = {np.round(coef1[0][0], 1)}')
    plt.plot(x[1], np.log10(y[1]), linestyle='dashed', marker='o', markerfacecolor='blue', color = "blue",
             label=f'ecc = 0.2, k = {np.round(coef2[0][0], 1)}')

    plt.plot(x[2],np.log10(y[2]), linestyle='dashed', marker='o', markerfacecolor='red', color = "red",
             label=f'ecc = 0.5, k = {np.round(coef3[0][0], 1)}')
    plt.plot(x[3], np.log10(y[3]), linestyle='dashed', marker='o', markerfacecolor='black', color="black",
             label=f'ecc = 0.8, k = {np.round(coef4[0][0], 1)}')
    plt.plot(x[0], x[0]*coef1[0] + coef1[1],color = "green", label ="polyfit ecc = 0.1")
    plt.plot(x[1], x[1]*coef2[0] + coef2[1],color = "blue", label ="polyfit ecc = 0.1")
    plt.plot(x[2], x[2]*coef3[0] + coef3[1],color = "red", label ="polyfit ecc = 0.1")
    plt.plot(x[3], x[3]*coef4[0] + coef4[1],color = "black", label ="polyfit ecc = 0.1")

    # plt.xlim([0,2])
    # plt.ylim([0,1])
    plt.xlabel(r"$i$")
    plt.ylabel(r"$\lg(err)$")
    plt.title("Лабораторная работа: 'Нелинейные уравнения'. уравнение Кеплера")
    plt.legend()
    plt.savefig(f"{filename.split('.')[0]}.png")
    plt.show()


def readData(filename):
    with open(filename, 'r') as errFile:
        data = [i.strip().split() for i in errFile.readlines()]
    return data


if __name__ == '__main__':
    filename1 = 'errBase_0_1.txt'
    filename2 = 'errBase_0_2.txt'
    filename3 = 'errBase_0_5.txt'
    filename4 = 'errBase_0_8.txt'

    err_1 = np.array(readData(filename1), dtype=float)
    err_2 = np.array(readData(filename2), dtype=float)
    err_3 = np.array(readData(filename3), dtype=float)
    err_4 = np.array(readData(filename4), dtype=float)

    x_1 = np.arange(1, len(err_1) + 1)
    x_2 = np.arange(1, len(err_2) + 1)
    x_3 = np.arange(1, len(err_3) + 1)
    x_4 = np.arange(1, len(err_4) + 1)
    err = [err_1, err_2, err_3, err_4]
    x = [x_1, x_2, x_3, x_4]
    grafikBase(x, err, 'err_plot.png')