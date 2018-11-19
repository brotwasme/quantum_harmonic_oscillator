
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import gaussian_kde

def flucuations(fs, mean_f):
    return (np.sum((fs - mean_f)**2)**(0.5))/np.abs(mean_f)

def jack(os, B):
    N = len(os)
    NB = int(N/B)
    Eo = np.mean(os)
    tol = np.zeros(NB)
    for i in range(1, NB):
        ok = np.sum(os[(i-1)*(B):i*B])/B
        tol[i] = (np.sum(np.subtract(os, B*ok)))/(N-B)
    iner = np.subtract(tol, Eo)
    err = (NB -1)*np.sum(np.power(iner, 2))/NB
    return np.sqrt(err)

def error(x, Ex):
    s2 = np.sum(np.power(x-Ex, 2))/(len(x)-1)
    return np.sqrt(s2/len(x))

def corralation_mct(fs, gs):
    N = len(gs)
    Gdt = np.zeros(N)
    Egi = np.mean(gs)
    Efit = np.mean(fs)
    Gdt[0] = np.mean(np.multiply(np.subtract(gs,Egi),np.subtract(fs, Efit)))/(N-1)
    for i in range(1,len(gs)-1):
        Egi = np.mean(gs[:(N-i+1)])
        Efit = np.mean(fs[(N-i):])
        Gdt[i] = np.mean(np.multiply(np.subtract(gs,Egi)[:-i],np.subtract(fs, Efit)[i:]))/(N-i-1)
    return Gdt

def int_corralation_mct(fs, gs): #not needed
    N = len(gs)
    Gdt = np.zeros(N)
    Egi = np.mean(gs)
    Efj = np.mean(fs)
    Gdt += np.mean(np.multiply(np.subtract(gs,Egi),np.subtract(fs, Egj)))/(N-1)
    for i in range(1,N):
        for j in range(1,N):
            Gdt += np.mean(np.multiply(np.subtract(gs,Egi)[:-i],np.subtract(fs, Efj)[j:]))/(N-i-1)
    return Gdt

def interg(acr):
    N = len(acr)
    int_acr = np.zeros(N)
    sum = 0.5
    int_acr[0] = 0.5
    for i in range(1, N):
        sum += (N-i)*acr[i]/(N*acr[0])
        int_acr[i] = sum
    return int_acr


def corralation_tau(fs, gs):
    B = 5
    Gdt = np.zeros(len(gs[0]))
    err = np.zeros(len(gs[0]))
    gf = np.multiply(gs,fs).flatten()
    Gdt[0] = np.mean(gf);
    err[0] = jack(gf, B)
    for i in range(1, len(gs[0])):
        fs = np.roll(fs, 1, 1)
        gf = np.multiply(gs,fs).flatten()
        Gdt[i] = np.mean(gf);
        err[i] = jack(gf, B)
    print(len(Gdt))
    print(len(err))
    return Gdt[:10], err[:10]


def eff_mass(gdt):
    gdtn = np.roll(gdt, 1)
    gdtp = np.roll(gdt, -1)
    return 0.5*np.log(gdtn/gdtp)

def av(xs, mean_x2):
    avr = np.divide(xs, mean_x2)
    return avr

def data_in(file, N_var):
    a = np.array([])
    data = np.loadtxt(file)
    print(len(data))
    vars = data[0:N_var]
    data = data[N_var:]
    return vars, data

def get_xns(data, vars):
    data = np.reshape(data, (int(vars[1]), int(vars[4])))
    xs = data[:, 0]
    x2s = data[:,1]
    x3s = data[:,2]
    x4s = data[:,3]
    return xs, x2s, x3s, x4s

def get_xs(data, vars):
    data = np.reshape(data, (int(vars[1]), int(vars[0])))
    return data

def xns_means(xs, x2s, x3s, x4s, vars):
    mean_x = np.mean(xs)
    er_x = error(xs, mean_x)
    
    mean_x2 = np.mean(x2s)
    er_x2 = error(x2s, mean_x2)
    
    mean_x3 = np.mean(x3s)
    er_x3 = error(x3s, mean_x3)

    mean_x4 = np.mean(x4s)
    er_x4 = error(x4s, mean_x4)

    fluctuation_x = flucuations(xs, mean_x)
    
    print("mean of x: ", mean_x, "error: ", er_x)
    print("mean of x^2: ", mean_x2, "error: ", er_x2)
    print("mean of x^3: ", mean_x3, "error: ", er_x3)
    print("mean of x^4: ", mean_x4, "error: ", er_x4)
    print("size of path: ", vars[1], "fluctuations in x:" , fluctuation_x)
    print( "percentage diffrence between len and fluc^-2", (vars[1] - np.power(fluctuation_x,-2))/vars[1])
    return mean_x, mean_x2, mean_x3, mean_x4

def prob_dens_plot(data):
    #if (not len(data[0]) == 1):
    #    data1d = data.flatten()
    #else:
    data1d = data
    binwidth = 0.1
    density = gaussian_kde(data1d)
    xs_all = np.linspace(-10, 10, 1000)
    plt.plot(xs_all, density(xs_all))

def ploter(data, title, lables, type, N_previous=0, x=[], yerr = []):
    N = 1
    if not (len(data[0]) == 1):
        N = len(data)
    plt.figure(1+N_previous)
    for i in range(N):
        plt.suptitle(title)
        plt.subplot(N,1,i+1)
        plt.title(lables[i][0])
        plt.xlabel(lables[i][1])
        plt.ylabel(lables[i][2])
        plt.grid(True)
        #print(data[i])
        if type[i] == 1:
            plt.plot(data[i])
        elif type[i] == 2:
            plt.acorr(data[i])
        elif type[i] == 3:
            plt.semilogy(data[i])
        elif type[i] == 4:
            plt.errorbar(x, data[i], yerr)
    return 1+N_previous

def acorr_ploter(data, title, lables, N_previous=0):
    N = len(data)
    plt.figure(1+N_previous)
    for i in range(N):
        plt.suptitle(title)
        plt.subplot(N,1,i+1)
        plt.title(lables[i][0])
        plt.xlabel(lables[i][1])
        plt.ylabel(lables[i][2])
        plt.acorr(data[i])
    return 1+N_previous

def xn_func(file=False):
    if file:
        file = "xn.txt"
    vars, data = data_in(file, 5)
    xs, x2s, x3s, x4s = get_xns(data, vars)
    print(vars)
    mean_x, mean_x2, mean_x3, mean_x4 = xns_means(xs, x2s, x3s, x4s, vars)
    #corrl = corralation(data, data)
    m = vars[3]
    title1 = [["1", "2"], ["3", "4"]]
    print(title1)
    print(title1[0][1]) #2
    print(title1[1][1]) #4
    labels = [["x^"+str(i+1), "markov time", "x^"+str(i+1)] for i in range(4)] #title, xlabel, ylabel
    suptitle = "configurations of <x^n> vs monte carlo time"
    print(labels)
    data = [xs,x2s,x3s,x4s]
    n = ploter(data, suptitle, labels, [1,1,1,1])

    suptitle = "autocorralation of x^n, np output"
    labels = [["autocorralation of x^"+str(i+1), "d(markov time)", "corralation of x^"+str(i+1)] for i in range(4)] #title, xlabel, ylabel
    n = acorr_ploter(data, suptitle, labels, n)

    cor1 = corralation_mct(xs,xs)[:100]
    cor2 = av(cor1, cor1[0])
    cor3 = np.correlate(xs,xs,mode='full')[len(xs)-1:len(xs)-1+100]
    cor4 = np.divide(cor3, cor3[0])
    suptitle = "autocorralation of x^n non np output"
    labs = [" not "," ", " not ", " "]
    labels = [["autocorralation of x,"+l+"normalised",
              "d(markov time)",
             "autocorralation of x,"+l+"normalised"]
             for l in labs] #title, xlabel, ylabel
    n = ploter([cor1, cor2, cor3, cor4], suptitle, labels, [1, 1, 1, 1], n)
    int_cor = interg(cor1)
    n = ploter([int_cor], "intergrated coralation",[["intergrated coralation", "monte carlo time", "intergrated corralation"]], [1], n )


def data_func(file=False):
    if file:
        file = "data_.txt"
    vars, data1d = data_in(file, 4)
    m = vars[3]
    #data = get_xs(data, vars)
    true = False;
    n = 0
    if true:
        plt.figure(1)
        prob_dens_plot(data1d)
        n=1
    elif not true:
        data = np.reshape(data1d, (int(vars[1]), int(vars[0])))
        print(data)
        print(len(data))
        print(len(data[0]))
        print(len(data[0,:]))
        print(data[0][0])
        print(data[0][1])
        print(vars)
        cor, err = corralation_tau(data[:100], data[:100])
        print(len(cor))
        suptitle = "corralation vs imagenary time"
        labels = [["corralation vs d imagenary time",
                  "d imagenary time", "coralation"],
                  ["corralation vs d imagenary time",
                  "imagenary time", "coralation+abs(min(corralation))"],
                  ["corralation vs d imagenary time",
                  "d imagenary time", "ln( coralation+abs(min(corralation)) )"],
                  ["effective mass from coralation+abs(min(corralation)) vs imagenary time",
                  "d imagenary time", "effective mass from coralation+abs(min(corralation))"],
                  ["effective mass from coralation2 vs d imagenary time",
                  "d imagenary time", "effective mass from coralation+abs(min(corralation))"]] #title, xlabel, ylabel
        min = 0 #np.abs(np.min(cor))
        #print(min)

        cor1 = np.add(cor, min+min/10000)
        cor2 = np.mean([ np.correlate(data_l, data_l, mode='full')[len(data_l)-1:]
                       for data_l in data], 0)
        cor2 = cor2/ cor2[0]
        print(len(cor2))
        mass = eff_mass(cor1)
        n = ploter([cor, cor1, cor1, mass, cor2], suptitle, labels, [1,1,3,1,1])
        pass


def play():
    arr = np.linspace(1, 50, 50)
    print(arr)
    arr = arr.reshape(10, 5)
    print(arr)
    print(arr[:,0])
    print(arr[:,-1])
    print(arr[0,:])
    arr = np.roll(arr, 1, 1)
    mean = np.mean(arr)
    print(arr)
    print(mean)


def testing():
    file = "xn.txt"
    a = np.array([])
    data = np.loadtxt(file)
    print(len(data))
    vars = data[0:4]
    data = data[4:]
    print(len(data))
    print(vars)
    print(data[:6])
    data = np.reshape(data, (int(vars[1]), 4))
    print(data)

def main():
    #xn_func("xn_1.txt")
    data_func("data_1.txt")
    #play()
    plt.show()

main()