# + polarisation
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from IPython.display import clear_output
from matplotlib import animation
import scipy as sp
import mpl_toolkits.mplot3d.axes3d as p3


figure = plt.figure(figsize=(9,9))
axis = p3.Axes3D(figure)
plot = list()

def init():
    return plot
framecount = 300
# called for each frame

def animate(i):
    clear_output(wait=True)
    print("Rendering frame " + str(i+1) + " of " + str(framecount))
    theta = np.linspace(0, 256*(np.pi),5000)
    c = 3e8
    k=1
    #z=1
    z = np.linspace(0, 25, 5000)
    r = np.sqrt(1 - 0.5*np.cos(k*(z - c*i))*np.cos(2*theta))
    x = r*np.cos(theta)
    y = r*np.sin(theta)
    padding = 1.1 # Padding between edge of data and the axis
    axis.clear()
    axis.set_xlim3d(left=-5,right=25)
    axis.set_ylim3d(bottom=-3,top=3)
    axis.set_zlim3d(bottom=-3,top=3)
    axis.set_xlabel('X')
    axis.set_ylabel('Y')
    axis.set_zlabel('Z')
    axis.set_yticklabels([])
    axis.set_xticklabels([])
    axis.set_zticklabels([])
    plot = axis.plot(z, x, y, linewidth=1, antialiased=True)
    return plot,
anim = animation.FuncAnimation(figure, animate, init_func=init, frames=framecount, interval=33, blit=False)

anim.save("plus_polarisation.gif", writer="imagemagick")
print("Done!")
