import matplotlib.pyplot as plt
import numpy as np


def grafik():
    with open('errSecondBaseN3.txt', 'r') as errFile:
        pairLine= [i.split() for i in errFile.readlines()]
        line1x = [i[1] for i in pairLine]
        line1y = [i[0] for i in pairLine]
        line1z = [i[2] for i in pairLine]
    with open('errSecondBaseN4.txt', 'r') as errFile:
        pairLine = [i.split() for i in errFile.readlines()]
        line2x = [i[1] for i in pairLine]
        line2y = [i[0] for i in pairLine]
        line2z = [i[2] for i in pairLine]
    with open('errSecondBaseN5.txt', 'r') as errFile:
        pairLine = [i.split() for i in errFile.readlines()]
        line3x = [i[1] for i in pairLine]
        line3y = [i[0] for i in pairLine]
        line3z = [i[2] for i in pairLine]
        h = []
        h.append(2.)
        for i in range(5):
            h.append(h[-1] * 0.5)
    h = np.array(h, dtype=float)
    line1x = np.array(line1x, dtype=float)
    line1y = np.array(line1y, dtype=float)
    line1z = np.array(line1z, dtype=float)
    line2x = np.array(line2x, dtype=float)
    line2y = np.array(line2y, dtype=float)
    line2z = np.array(line2z, dtype=float)
    line3x = np.array(line3x, dtype=float)
    line3y = np.array(line3y, dtype=float)
    line3z = np.array(line3z, dtype=float)
    coef1 = np.polyfit(np.log(line1x), np.log(line1y), 1)
    coef2 = np.polyfit(np.log(line2x), np.log(line2y), 1)
    coef3 = np.polyfit(np.log(line3x), np.log(line3y), 1)
    coef1z = 3 + np.log(line1z)/np.log(line1x) - np.log(3)/np.log(line1x)
    print(coef1z)
    coef2z = 4 + np.log(line2z)/np.log(line2x) - np.log(4)/np.log(line3x)
    coef3z = 5 + np.log(line3z)/np.log(line3x) - np.log(5)/np.log(line3x)
    plt.figure(figsize=(12, 7))
    plt.minorticks_on()
    plt.grid(
        which='major'
    )
    plt.grid(
        which='minor',
        linestyle='--'
    )

    plt.plot(np.log(line1x), np.log(line1y), linestyle='dashed', marker='o', markerfacecolor='green',
             label=f'N = 3, Коэффициент наклона = {coef1[0]}, {np.min(coef1z)}')
    plt.plot(np.log(line2x), np.log(line2y), linestyle='dashed', marker='o', markerfacecolor='blue',
             label=f'N = 4, Коэффициент наклона = {coef2[0]}, {np.min(coef2z)}')
    plt.plot(np.log(line3x), np.log(line3y), linestyle='dashed', marker='o', markerfacecolor='red',
             label=f'N = 5, Коэффициент наклона = {coef3[0]}, {np.min(coef3z)}')
    # plt.loglog(h, line1, linestyle='dashed', marker='o', markerfacecolor='green',
    #          label=f'N = 3, Коэффициент наклона = {coef1[0]}')
    # plt.loglog(h, line2, linestyle='dashed', marker='o', markerfacecolor='green',
    #          label=f'N = 4, Коэффициент наклона = {coef2[0]}')
    # plt.loglog(h, line3, linestyle='dashed', marker='o', markerfacecolor='green',
    #          label=f'N = 5, Коэффициент наклона = {coef3[0]}')
    #plt.xlim([-4, 2])
    #plt.ylim([0, 1])
    plt.xlabel("step")
    plt.ylabel(r"err")
    plt.title('Равномерные узлы')
    plt.legend()
    plt.savefig("basicLogLog.png")
    plt.show()

def grafikCheb():
    with open('errChebBaseN3.txt', 'r') as errFile:
        line1 = [i for i in errFile.read().split()]
    with open('errChebBaseN4.txt', 'r') as errFile:
        line2 = [i for i in errFile.read().split()]
    with open('errChebBaseN5.txt', 'r') as errFile:
        line3 = [i for i in errFile.read().split()]
        h = []
        h.append(2.)
        for i in range(19):
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
    coef1 = np.polyfit(np.log(h), np.log(line1), 1)
    coef2 = np.polyfit(np.log(h), np.log(line2), 1)
    coef3 = np.polyfit(np.log(h), np.log(line3), 1)
    plt.plot(np.log(h), np.log(line1), linestyle='dashed', marker='o', markerfacecolor='green',
             label=f'N = 3,  Коэффициент наклона = {coef1[0]}')
    plt.plot(np.log(h), np.log(line2), linestyle='dashed', marker='o', markerfacecolor='blue',
             label=f'N = 4, Коэффициент наклона = {coef2[0]}')
    plt.plot(np.log(h),np.log(line3), linestyle='dashed', marker='o', markerfacecolor='red',
             label=f'N = 5, Коэффициент наклона = {coef3[0]}')
    # plt.xlim([0,2])
    # plt.ylim([0,1])
    plt.xlabel("length")
    plt.ylabel(r"err")
    plt.title('Чебышевские узлы')
    plt.legend()
    plt.savefig("basicChebLogLog.png")
    plt.show()

def grafikBase():
    with open('errBaseN3.txt', 'r') as errFile:
        line1 = [i for i in errFile.read().split()]
    with open('errBaseN4.txt', 'r') as errFile:
        line2 = [i for i in errFile.read().split()]
    with open('errBaseN5.txt', 'r') as errFile:
        line3 = [i for i in errFile.read().split()]
        h = []
        h.append(2.)
        for i in range(19):
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
    coef1 = np.polyfit(np.log10(h), np.log10(line1), 1)
    coef2 = np.polyfit(np.log10(h), np.log10(line2), 1)
    coef3 = np.polyfit(np.log10(h), np.log10(line3), 1)
    plt.plot(np.log10(h), np.log10(line1), linestyle='dashed', marker='o', markerfacecolor='green',
             label=f'N = 3,  Коэффициент наклона = {coef1[0]}')
    plt.plot(np.log10(h), np.log10(line2), linestyle='dashed', marker='o', markerfacecolor='blue',
             label=f'N = 4, Коэффициент наклона = {coef2[0]}')
    plt.plot(np.log10(h),np.log10(line3), linestyle='dashed', marker='o', markerfacecolor='red',
             label=f'N = 5, Коэффициент наклона = {coef3[0]}')
    # plt.xlim([0,2])
    # plt.ylim([0,1])
    plt.xlabel("length")
    plt.ylabel(r"err")
    plt.title('Равномерные узлы')
    plt.legend()
    plt.savefig("basicLogLog.png")
    plt.show()




if __name__ == '__main__':

