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
    r = np.max(np.sqrt((np.array(x[0], dtype=float) - np.array(x[1], dtype=float))**2 + (np.array(y[0], dtype=float) - np.array(y[1], dtype=float))**2))
    print(r)
    plt.plot(np.array(x[0], dtype=float),np.array(y[0], dtype=float), label = '$\it{Простейший~ случай, ~когда ~Земля ~круглая. ~Метод ~RK4}$')
    plt.plot(np.array(x[1], dtype=float),np.array(y[1], dtype=float), label = '$\it{Cлучай, ~когда ~Земля ~не~круглая. ~Метод ~RK4}$ \n'f' маскимальное отлонение орбит r = {r}')
    plt.xlabel(r"$X, м$")
    plt.ylabel(r"$Y, м$")
    plt.title(r"Лабораторная работа: 'Многошаговые методы'. не База ")
    plt.legend()
    plt.savefig(f"{filename.split('.')[0]}.png")
    plt.show()

def grafik3d(x,y,z, filename):
    fig = plt.figure(figsize=(12, 12))
    ax = fig.add_subplot(111, projection='3d')


    x = np.array(x, dtype=float)
    y = np.array(y, dtype=float)
    z = np.array(z, dtype=float)
    q_len = np.max([np.max(np.abs(x)),np.max(np.abs(y)), np.max(np.abs(z))])
    # Plot the x axis
    ax.quiver(0, 0, 0, q_len, 0, 0, color='r', label = "x")
    # Plot the y axis
    ax.quiver(0, 0, 0, 0, q_len, 0, color='g', label = "y")
    # Plot the z axis
    ax.quiver(0, 0, 0, 0, 0, q_len, color='b', label = "z")
    ax.plot(x[0], y[0], z[0], color = 'b')
    ax.plot(x[1], y[1], z[1], color = 'orange')
    plt.savefig(f"{filename.split('.')[0]}.png")
    plt.legend()
    plt.show()


def readData(filename):
    with open(filename, 'r') as errFile:
        data = [i.strip().split() for i in errFile.readlines()]
    return data


if __name__ == '__main__':
    filename1 = 'coordsSuperTask.txt'
    filename2 = 'coordsSuperTask1.txt'
    filename3 = 'coordsSuperTaskI30.txt'
    filename4 = 'coordsSuperTaskI30NotCirc.txt'

    err_1 = np.array(readData(filename1), dtype=float)
    err_2 = np.array(readData(filename2), dtype=float)
    err_3 = np.array(readData(filename3), dtype=float)
    err_4 = np.array(readData(filename4), dtype=float)



    x_1 = []
    y_1 = []
    z_1 = []
    for i in err_1:
        x_1.append(i[0])
        y_1.append(i[1])
        z_1.append(i[2])
    x_2 = []
    y_2 = []
    z_2 = []
    for i in err_2:
        x_2.append(i[0])
        y_2.append(i[1])
        z_2.append(i[2])

    x = [x_1, x_2]
    y = [y_1, y_2]
    xx_1 = []
    yy_1 = []
    zz_1 = []
    for i in err_3:
        xx_1.append(i[0])
        yy_1.append(i[1])
        zz_1.append(i[2])
    xx_2 = []
    yy_2 = []
    zz_2 = []
    for i in err_4:
        xx_2.append(i[0])
        yy_2.append(i[1])
        zz_2.append(i[2])
        
    xx = [xx_1, xx_2]
    yy = [yy_1, yy_2]
    zz = [zz_1, zz_2]
    #grafikBase(x, y, 'superTaskPlotAll.png')
    grafik3d(xx, yy, zz, "coordsSuperTaskI30All3.png")