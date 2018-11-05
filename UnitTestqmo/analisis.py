
import matplotlib.pyplot as plt
import numpy as np

a = np.fromfile("data.txt")
path_len = a[0]
a = a.reshape(path_len)
print(a)