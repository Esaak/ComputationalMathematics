import matplotlib.pyplot as plt
import numpy as np


def grafik():
    with open('errSecondBaseN3.txt', 'r') as errFile:
        line1 = [i for i in errFile.read().split()]
    with open('errSecondBaseN4.txt', 'r') as errFile:
        line2 = [i for i in errFile.read().split()]
    with open('errSecondBaseN5.txt', 'r') as errFile:
        line3 = [i for i in errFile.read().split()]
        h = []
        h.append(2.)
        for i in range(5):
            h.append(h[-1] * 0.5)
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

    plt.plot(h, line1, linestyle='dashed', marker='o', markerfacecolor='green',
             label=f'N = 3')
    plt.plot(h, line2, linestyle='dashed', marker='o', markerfacecolor='blue',
             label=f'N = 4')
    plt.plot(h,line3, linestyle='dashed', marker='o', markerfacecolor='red',
             label=f'N = 5')

    plt.xlabel("length")
    plt.ylabel(r"err")
    plt.title('Равномерные узлы')
    plt.legend()
    plt.savefig("basic.png")
    plt.show()

def grafik2():
    with open('errChebBaseN3.txt', 'r') as errFile:
        line1 = [i for i in errFile.read().split()]
    with open('errChebBaseN4.txt', 'r') as errFile:
        line2 = [i for i in errFile.read().split()]
    with open('errChebBaseN5.txt', 'r') as errFile:
        line3 = [i for i in errFile.read().split()]
        h = []
        h.append(2.)
        for i in range(5):
            h.append(h[-1] * 0.5)
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

    plt.plot(h, line1, linestyle='dashed', marker='o', markerfacecolor='green',
             label=f'N = 3')
    plt.plot(h, line2, linestyle='dashed', marker='o', markerfacecolor='blue',
             label=f'N = 4')
    plt.plot(h,line3, linestyle='dashed', marker='o', markerfacecolor='red',
             label=f'N = 5')

    plt.xlabel("length")
    plt.ylabel(r"err")
    plt.title('Чебышевские узлы')
    plt.legend()
    plt.savefig("basicCheb.png")
    plt.show()
if __name__ == '__main__':
    grafik2()
