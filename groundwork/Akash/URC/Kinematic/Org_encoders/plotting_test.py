#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Point
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math
import numpy as np

l1 = float(384.811) 
l2 = float(409.149)
angle1 = 0
angle2 = 0

def angles_callback(msg):
    global angle1, angle2
    angle1 = np.radians(msg.x)
    angle2 = np.radians(msg.y) - np.pi

def update(frame):
    global angle1, angle2
    # Update the lines based on the new angles
    line1.set_xdata([0, l1 * math.cos(angle1)])
    line1.set_ydata([0, l1 * math.sin(angle1)])
    line2.set_xdata([l1 * math.cos(angle1), l1 * math.cos(angle1) + l2 * math.cos(angle1 + angle2 )])
    line2.set_ydata([l1 * math.sin(angle1), l1 * math.sin(angle1) + l2 * math.sin(angle1 + angle2)])
    return line1, line2


rospy.init_node('arm_visualizer', anonymous=True)
rospy.Subscriber('inv_kin_ang', Point, angles_callback)

fig, ax = plt.subplots()
ax.set_xlim(-300,800)
ax.set_ylim(-200,800)
ax.set_aspect('equal')

line1, = ax.plot([], [], 'r-')
line2, = ax.plot([], [], 'b-')

ani = FuncAnimation(fig, update, frames=None, blit=True, interval=50)
plt.show()


