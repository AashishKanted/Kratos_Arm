#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Point
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math

l1 = float(409.149) 
l2 = float(384.811)
angle1 = 0
angle2 = 0

def angles_callback(msg):                               # Get angles in radians from topic
    global angle1, angle2
    angle1 = msg.x
    angle2 = msg.y

def update(frame):                                      # One line takes two inputs- start point and end point. Points are found through Forward Kinematics
    global angle1, angle2
    # Update the lines based on the new angles
    line1.set_xdata([0, l1 * math.cos(angle1)])
    line1.set_ydata([0, l1 * math.sin(angle1)])
    line2.set_xdata([l1 * math.cos(angle1), l1 * math.cos(angle1) + l2 * math.cos(angle1 + angle2 - math.pi)])
    line2.set_ydata([l1 * math.sin(angle1), l1 * math.sin(angle1) + l2 * math.sin(angle1 + angle2 - math.pi)])
    return line1, line2


rospy.init_node('plotting', anonymous=True)
rospy.Subscriber('angles_rad', Point, angles_callback)

fig, ax = plt.subplots()
ax.set_xlim(-250,750)                                     # Sets x and y limits of the plot
ax.set_ylim(-250, 750)
ax.set_aspect('equal')                                    # Sets x and y in equal aspect ratio 

line1, = ax.plot([], [], 'r-')
line2, = ax.plot([], [], 'b-')

ani = FuncAnimation(fig, update, frames=None, blit=True, interval=50)
plt.show()
