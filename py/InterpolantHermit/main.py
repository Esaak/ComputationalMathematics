import matplotlib.pyplot as plt
import numpy as np



def grafikBase(filename):
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
    coef1 = np.polyfit(np.log10(h[:8]), np.log10(line1[:8]), 1)
    coef2 = np.polyfit(np.log10(h[:5]), np.log10(line2[:5]), 1)
    coef3 = np.polyfit(np.log10(h[:3]), np.log10(line3[:3]), 1)
    plt.plot(np.log10(h), np.log10(line1), linestyle='dashed', marker='o', markerfacecolor='green', color = "green",
             label=f'N = 3,  Коэффициент наклона = {coef1[0]}')
    plt.plot(np.log10(h), np.log10(line2), linestyle='dashed', marker='o', markerfacecolor='blue', color = "blue",
             label=f'N = 4, Коэффициент наклона = {coef2[0]}')

    plt.plot(np.log10(h),np.log10(line3), linestyle='dashed', marker='o', markerfacecolor='red', color = "red",
             label=f'N = 5, Коэффициент наклона = {coef3[0]}')
    plt.plot(np.log10(h[:8]), np.log10(h[:8])*coef1[0] + coef1[1],color = "green", label ="polyfit N = 3")
    plt.plot(np.log10(h[:5]), np.log10(h[:5])*coef2[0] + coef2[1],color = "blue", label ="polyfit N = 4")
    plt.plot(np.log10(h[:3]), np.log10(h[:3])*coef3[0] + coef3[1],color = "red", label ="polyfit N = 5")

    # plt.xlim([0,2])
    # plt.ylim([0,1])
    plt.xlabel(r"$\log(length)$")
    plt.ylabel(r"$\log(err)$")
    plt.title("Лабораторная работа: 'Интерполяция Эрмита'. Равномерные узлы")
    plt.legend()
    plt.savefig(f"{filename.split('.')[0]}.png")
    plt.show()




if __name__ == '__main__':
    filename = 'errBaseN3.txt'
    grafikBase(filename)