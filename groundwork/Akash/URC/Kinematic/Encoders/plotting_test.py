#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Point
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math
import numpy as np

class ArmVisualizer:
    def __init__(self):
        # Initialize ROS node
        rospy.init_node('arm_visualizer', anonymous=True)
        
        # Subscribe to the inverse kinematics angles topic
        rospy.Subscriber('inv_kin_ang', Point, self.angles_callback)
        
        # Lengths of the two segments of the arm
        self.l1 = float(384.811)
        self.l2 = float(409.149)
        
        # Initialize angles of the two segments
        self.angle1 = 0
        self.angle2 = 0
        
        # Create figure and axis for the plot
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlim(-300, 800)
        self.ax.set_ylim(-200, 800)
        self.ax.set_aspect('equal')
        
        # Initialize lines for the plot
        self.line1, = self.ax.plot([], [], 'r-')
        self.line2, = self.ax.plot([], [], 'b-')
        
        # Create animation
        self.ani = FuncAnimation(self.fig, self.update, frames=None, blit=True, interval=50)
        
        # Show the plot
        plt.show()

    # Callback function for updating angles
    def angles_callback(self, msg):
        self.angle1 = np.radians(msg.x)
        self.angle2 = np.radians(msg.y) - np.pi

    # Update function for the animation
    def update(self, frame):
        # Update the lines based on the new angles
        self.line1.set_xdata([0, self.l1 * math.cos(self.angle1)])
        self.line1.set_ydata([0, self.l1 * math.sin(self.angle1)])
        self.line2.set_xdata([self.l1 * math.cos(self.angle1), self.l1 * math.cos(self.angle1) + self.l2 * math.cos(self.angle1 + self.angle2)])
        self.line2.set_ydata([self.l1 * math.sin(self.angle1), self.l1 * math.sin(self.angle1) + self.l2 * math.sin(self.angle1 + self.angle2)])
        return self.line1, self.line2

if __name__ == '__main__':
    arm_visualizer = ArmVisualizer()
