import matplotlib.pyplot as plt
import scipy as sp
import scipy.special as spc
import matplotlib.pyplot as plt
import numpy as np
from numpy import random

N = 10

x_coords = random.randint(1, 10, size = N)
y_coords = random.randint(1, 10, size = N)

# greens function
def green(x_j, y_j, x_k, y_k):
    r = np.sqrt((x_j - x_k)**2 + (y_j - y_k)**2)
    k_0 = 2*sp.pi
    
    return (1j/4)*spc.hankel1(0, k_0*r)

# defining matrix to calculate exciting field on each scatterer
matrix = []
for i in range(len(x_coords)):
    row = []
    for j in range(len(y_coords)):
        if i==j:
            row.append(1)
        else:
            row.append(-4*1j*green(x_coords[i], y_coords[i], x_coords[j], y_coords[j]))
    matrix.append(row)

# defining incident field on scatterers (complex)    
def inc_field(i):
    E_0 = 1
    k_0 = 2*sp.pi
    
    return E_0*np.exp(k_0*i*1j)

scatterer = [inc_field(i) for i in matrix[i]]
ext_field = sp.linalg.solve(green(x_coords[0], y_coords[0], x_coords[1], y_coords[1]), scatterer) # solving for E_j

# function to calculate the total field
def tot_field(x,y):
    E_tot = inc_field(x)
    for i in range(len(ext_field)):
        E_tot += 4*1j*green(x,y,x_coords[i],y_coords[i])*ext_field[i]
    return np.real(E_tot)

def tot_field_mod(x,y):
    E_tot = inc_field(x)
    for i in range(len(ext_field)):
        E_tot += 4*1j*green(x,y,x_coords[i],y_coords[i])*ext_field[i]
    return np.real(abs(E_tot)**2)

# figures for contour map
fig1 = plt.figure()
ax1 = fig1.subplots()

fig2 = plt.figure()
ax2 = fig2.subplots()


# coordinate range for contour map
d1 = np.arange(0, 10, 0.01)
d2 = np.arange(0, 10, 0.01)

X, Y = np.meshgrid(d1, d2)
Z = tot_field(X, Y)
Z_mod = tot_field_mod(X, Y)

cf = ax1.pcolormesh(X, Y, Z, cmap="Blues")
cf_mod = ax2.pcolormesh(X, Y, Z_mod, cmap="Blues")
ax1.scatter(x_coords,y_coords,c='black')
fig1.colorbar(cf)
ax2.scatter(x_coords,y_coords,c='black')
fig2.colorbar(cf_mod)
ax1.set_ylabel('y')
ax1.set_xlabel('x')
ax2.set_ylabel('y')
ax2.set_xlabel('x')


plt.show()
plt.savefig("scat_2")
plt.savefig("scat_2_mod")
