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

    coef1 = np.polyfit(np.log10(x[0][4:]), np.log10(y[0][4:]), 1)
    coef2 = np.polyfit(np.log10(x[1][4:]), np.log10(y[1][4:]), 1)

    plt.plot(np.log10(x[0]), np.log10(y[0]), linestyle='dashed', marker='o', markerfacecolor='green', color = "green",
             label=f"$y' = t^3,$ \n $y(0) = 0 $, \n k = {np.round(coef1[0][0], 2)} \n")
    plt.plot(np.log10(x[1]), np.log10(y[1]), linestyle='dashed', marker='o', markerfacecolor='blue', color = "blue",
             label=f"$y'' = -y,$\n$ y'(0) = 1, y(0) = 0 $,\n k = {np.round(coef2[0][0], 2)} \n")
    plt.plot(np.log10(x[0]), np.log10(x[0])*coef1[0] + coef1[1],color = "green", label =f"polyfit \t$y' = t^3$")
    plt.plot(np.log10(x[1]), np.log10(x[1])*coef2[0] + coef2[1],color = "blue", label =f"polyfit \t$y'' = -y$")


    plt.xlabel(r"$\lg(step)$")
    plt.ylabel(r"$\lg(err)$")
    plt.title("Лабораторная работа: 'BDF4'. База")
    plt.legend()
    plt.savefig(f"{filename.split('.')[0]}.png")
    plt.show()


def readData(filename):
    with open(filename, 'r') as errFile:
        data = [i.strip().split() for i in errFile.readlines()]
    return data


if __name__ == '__main__':
    filename1 = 'err.txt'
    filename2 = 'err2.txt'

    err_1 = np.array(readData(filename1), dtype=float)
    err_2 = np.array(readData(filename2), dtype=float)


    x_1 = [1e-3]
    for i in range(len(err_1) - 1):
        x_1.append(x_1[-1] + 1e-3)
    x_2 = [0.001]
    for i in range(len(err_2) - 1):
        x_2.append(x_2[-1] + 0.001)
    #print(x_1)
    #print(err_2)
    err = [err_1, err_2]
    x = [x_1, x_2]
    grafikBase(x, err, 'err_plot.png')