import matplotlib.pyplot as plt
import numpy as np


def grafik():
    with open('err.txt', 'r') as errFile:
        lines = [i for i in errFile.read().split('\n')]
        line1 = [float(i) for i in lines[0].split()]
        line2 = [float(i) for i in lines[1].split()]
        line3 = [float(i) for i in lines[2].split()]

        h = []
        h.append(1.)
        for i in range(15):
            h.append(h[-1] * 0.1)
    h = np.array(h, dtype=float)
    line1 = np.array(line1, dtype=float)
    line2 = np.array(line2, dtype=float)
    line3 = np.array(line3, dtype=float)

    plt.figure(figsize=(12, 7))
    plt.minorticks_on()
    plt.grid(
        which='major'
    )
    plt.grid(
        which='minor',
        linestyle='--'
    )

    plt.plot(abs(np.log10(h)), np.log10(line1), linestyle='dashed', marker='o', markerfacecolor='green',
             label=f'N = 3, {abs(np.log10(line1[4]) - np.log10(line1[3])) / (abs(np.log10(h[4])) - abs(np.log10(h[3])))}')
    plt.plot(abs(np.log10(h)), np.log10(line2), linestyle='dashed', marker='o', markerfacecolor='blue',
             label=f'N = 4, {abs(np.log10(line2[1]) - np.log10(line2[0])) / (abs(np.log10(h[1])) - abs(np.log10(h[0])))}')
    plt.plot(abs(np.log10(h)), np.log10(line3), linestyle='dashed', marker='o', markerfacecolor='red',
             label=f'N = 5, {abs(np.log10(line3[1]) - np.log10(line3[0])) / abs(np.log10(h[1]) - np.log10(h[0]))}')

    plt.xlabel("|log(step)|")
    plt.ylabel(r"log(err)")

    plt.legend()
    plt.savefig("basic.png")
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
            h.append(h[-1] * 0.1)
    h = np.array(h, dtype=float)
    line1 = np.array(line1, dtype=float)
    line2 = np.array(line2, dtype=float)
    line3 = np.array(line3, dtype=float)

    plt.figure(figsize=(12, 7))
    plt.minorticks_on()
    plt.grid(
        which='major'
    )
    plt.grid(
        which='minor',
        linestyle='--'
    )

    plt.plot(abs(np.log10(h)), np.log10(line1), linestyle='dashed', marker='o', markerfacecolor='green',
             label=f'N = 3, {abs(np.log10(line1[4]) - np.log10(line1[3])) / (abs(np.log10(h[4])) - abs(np.log10(h[3])))}')
    plt.plot(abs(np.log10(h)), np.log10(line2), linestyle='dashed', marker='o', markerfacecolor='blue',
             label=f'N = 4, {abs(np.log10(line2[4]) - np.log10(line2[3])) / (abs(np.log10(h[4])) - abs(np.log10(h[3])))}')
    plt.plot(abs(np.log10(h)), np.log10(line3), linestyle='dashed', marker='o', markerfacecolor='red',
             label=f'N = 5, {abs(np.log10(line3[4]) - np.log10(line3[3])) / abs(np.log10(h[4]) - np.log10(h[3]))}')

    plt.xlabel("|log(step)|")
    plt.ylabel(r"log(err)")

    plt.legend()
    plt.savefig("advanced.png")
    plt.show()


if __name__ == '__main__':
    grafik()
