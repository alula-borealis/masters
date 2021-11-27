# libraries
import cmath
import numpy as np
from numpy import random
import scipy.special as spec
import matplotlib.pyplot as plt
from scipy.spatial.distance import cdist
import time

# defining constants
N = 100                # number of scatterers
lambd = 1               # wavelength
k = 2*np.pi/lambd     # wavenumber
a = 4j/k**2             # polarization
        
theta = np.arange(np.pi/2,3*np.pi/2,np.pi/200)
R = 500
plot = 0
M = 100                  # number of realizations

Intensity = []

# counter for number of realisations
for i in range(0,M):
    if i % 5 == 0:
        print(i)
    
    # defining dimensions of the box
    length_x = 20
    length_y = 50
    length_z = 30
    
    # defining positions of scatterers randomly in a Nx3 array
    position = np.random.rand(N, 3)

    position[:, 0] *= length_x
    position[:, 1] *= length_y
    position[:, 2] *= length_z

    x = position[:,0]
    y = position[:,1]
    z = position[:,2]

    def incident(x):
        "calculating the incident field"
        E_0 = 1
        return E_0*np.exp(1j*k*x)
    
    # calculates incident field at each scatterer
    inc_scattered = [incident(i) for i in x]

    def green(r1, r2):
        "calculating the matrix containing the Green's function between two points"
        r = cdist(r1, r2)   # returns distance between scatterers
        return (np.where(r == 0, 1, -1j*(np.exp(1j*k*r))/(4*np.pi*r)))  # evaluates Green's function, giving 1 on main diagonal
    
    excited = np.linalg.solve(green(position, position), inc_scattered)     # the scattered field

    # defining sphere in which to evaluate the field

    phi = np.linspace(np.pi-2, np.pi+2, 150)
    theta = np.linspace(np.pi/2 - 2, np.pi/2 + 2, 150)

    p, t = np.meshgrid(phi, theta)
    
    xyz = np.column_stack(((R*np.cos(p)*np.sin(t)+length_x).reshape(-1,1), (R*np.sin(p)*np.sin(t)+length_y).reshape(-1,1), (R*np.cos(t)+length_z).reshape(-1,1)))

    def intensity(r1, r2):
        "solving the field"
        g = green(r1, r2)
        int = np.sum(g*excited, axis = 1)
        return np.abs(int)**2

    Intensity.append(intensity(xyz, position))

average = np.mean(Intensity, axis=0).reshape(150, 150)
    
# plotting
fig,ax = plt.subplots()
cp = ax.pcolormesh(p, t, average, cmap='binary')
fig.colorbar(cp)

ax.set_title('Intensity')
ax.set_xlabel('phi')
ax.set_ylabel('theta')
plt.show()

fig = plt.figure()
ax = plt.axes(projection='3d')
ax.contour3D(p, t, average, 50, cmap='binary')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')  

plt.savefig('backsacttering_cone2_N=' + str(N)+ '.pdf')
