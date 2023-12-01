import matplotlib.pyplot as plt
import numpy as np


def grafikBase(x, y, filename):
    plt.figure(figsize=(12, 12))
    # plt.minorticks_on()
    # plt.grid(
    #     which='major'
    # )
    # plt.grid(
    #     which='minor',
    #     linestyle='--'
    # )
    plt.plot(np.array(x, dtype=float), np.array(y, dtype=float))
    max_x = np.max(np.abs(np.array(x, dtype=float)))
    max_y = np.max(np.abs(np.array(y, dtype=float)))
    x_ticks = np.linspace(-max_x, max_x, 10)
    print(max_x)
    print(max_y)
    y_ticks = np.linspace(-max_y, max_y, 10)
    plt.xticks(x_ticks)
    plt.yticks(y_ticks)
    plt.xlabel(r"$x$")
    plt.ylabel(r"$y$")
    plt.title("Лабораторная работа: 'DPRK4'. Advanced")
    # plt.legend()
    plt.savefig(f"{filename.split('.')[0]}.png")
    print(1)
    plt.show()


def readData(filename):
    with open(filename, 'r') as errFile:
        data = [i.strip().split() for i in errFile.readlines()]
        data_x = [i[0] for i in data]
        data_y = [i[1] for i in data]
    return data_x, data_y


if __name__ == '__main__':
    filename1 = 'errDP.txt'
    # with open(filename1, 'r') as errFile:
    #     for i in errFile.readlines():
    #         x, y = i.strip().split()
    #         plt.plot(float(x), float(y))
    #         plt.show()
    x, y = readData(filename1)

    grafikBase(x, y, 'orbit.png')
