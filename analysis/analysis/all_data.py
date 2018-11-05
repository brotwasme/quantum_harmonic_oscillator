
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import gaussian_kde

def flucuations(fs, mean_f):
    return (np.sum((fs - mean_f)**2)**(0.5))/np.abs(mean_f)

def corralation1(f_0s, fs):
    f_0s = np.repeat(f_0s.reshape(len(f_0s),1), len(fs[0]), axis = 1)
    f_0sfs = np.multiply(f_0s,fs)
    mean_ = np.mean(f_0sfs, 0)
    return mean_

def corralation2(fs, gs):
    Gdt = np.zeros(len(gs[0,:]))
    for i in range(len(gs[0,:])-1):
        #print(gs)
        gs = np.roll(gs, 1, 1)
        #print(gs)
        gsfs = np.multiply(gs,fs)
        #print(gsfs)
        Gdt[i] = np.mean(gsfs)
    #mean_ = np.mean(f_0sfs, 0)
    return Gdt

def eff_mass(gdt):
    gdtn = np.roll(gdt, 1)
    gdtp = np.roll(gdt, -1)
    return 0.5*np.log(gdtn/gdtp)

if True:

    file = "xn.txt"
    a = np.array([])
    data = np.loadtxt(file)
    print(len(data))
    vars = data[0:5]
    data = data[5:]
    print(len(data))
    print(vars)
    m = vars[3]
    data = np.reshape(data, (int(vars[1]), int(vars[4])))
    #print(vars)
    #print(data)
    xs = data[:, 0]
    x2s = data[:,1]
    x3s = data[:,2]
    x4s = data[:,3]
    mean_x = np.sum(xs)/len(xs)
    print("mean of x: ", mean_x)
    mean_x2 = np.sum(x2s)/len(x2s)
    print("mean of x^2: ", mean_x2)
    fluctuation_x = flucuations(xs, mean_x)
    print("size of path: ", vars[1],"fluctuations in x: ",
          fluctuation_x, "percentage diffrence between len and fluc^-2",
          (vars[1] - fluctuation_x**(-2))/vars[1] )
    #print(xs)
    #print(x2s)
    plt.figure(1)
    plt.subplot(411)
    plt.plot(xs)
    plt.subplot(412)
    plt.plot(x2s)
    plt.subplot(413)
    plt.plot(x3s)
    plt.subplot(414)
    plt.plot(x4s)
    plt.figure(2)
    plt.subplot(411)
    plt.acorr(xs)
    plt.subplot(412)
    plt.acorr(x2s)
    plt.subplot(413)
    plt.acorr(x3s)
    plt.subplot(414)
    plt.acorr(x4s)
elif True:
    file = "data.txt"
    a = np.array([])
    data = np.loadtxt(file)
    print(len(data))
    vars = data[0:4]
    data = data[4:]
    print(len(data))
    print(vars)
    m = vars[3]
    data = np.reshape(data, (int(vars[1]), int(vars[0])))
    #print(vars)
    #print(data)
    data = data
    corrl = corralation2(data, data)
    tau = np.multiply(m,np.linspace(0, len(corrl), len(corrl)))
    plt.figure(1)
    plt.semilogy(tau, corrl)
    efm = eff_mass(corrl)
    plt.figure(2)
    plt.plot(tau, efm)
    plt.figure(3)
    data1d = data.flatten()
    binwidth = 0.1
    density = gaussian_kde(data1d)
    xs_all = np.linspace(-4, 4, 1000)
    plt.plot(xs_all, density(xs_all))

else:
    arr = np.linspace(1, 50, 50)
    #print(arr)
    arr = arr.reshape(10, 5)
    #print(arr)
    #print(arr[:,0])
    #print(arr[:,-1])
    #print(arr[0,:])
    full = np.repeat(arr[:,0].reshape((10,1)), 5, axis = 1)
    #print(full)
    new = np.multiply(full, arr)
    #print(new)
    mean_ = np.mean(new, 0)
    #cor = corralation1(arr, arr)
    corr = corralation2(arr, arr)
    print(corr)
    #print(mean_)
    #print(cor)
plt.show()
