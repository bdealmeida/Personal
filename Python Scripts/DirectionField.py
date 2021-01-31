import numpy as np
import matplotlib.pyplot as plt

X, Y = np.meshgrid(np.arange(-1, 2, .2), np.arange(-.5, 2, .15))
dYdX = -3*(1 - Y)*(1 - 2*Y)
U = 4/(1 + dYdX**2)**0.5*np.ones(X.shape)
V = 4/(1 + dYdX**2)**0.5*dYdX
plt.figure()
plt.title('Direction Field for dydx = -3*(1 - Y)*(1 - 2*Y)')
Q = plt.quiver(X, Y, U, V)
plt.quiver(X, Y, U, V)
plt.savefig('/mnt/c/Users/bdeal/Documents/fig.png')