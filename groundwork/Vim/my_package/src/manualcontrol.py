#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16MultiArray
from sensor_msgs.msg import Joy

xAxis1 = 0
yAxis1 = 0
triangle = 0
cross = 0
square = 0
circle = 0


def callback(data):
    global xAxis1, yAxis1, triangle, cross, square, circle

    xAxis1 = data.axes[0] # axes[0]  //controls Linear Actuators
    yAxis1 = data.axes[1] # axes[1]

    triangle = data.buttons[2] #buttons[2] //controls Stepper (for enabling)
    cross = data.buttons[0] # buttons[0]
    square = data.buttons[3]
    circle = data.buttons[1]


rospy.init_node("joy_control", anonymous=True)
pub = rospy.Publisher("/control1", Int16MultiArray, queue_size=1)

if __name__ == '__main__':
    rospy.Subscriber("/joy", Joy, callback)
    while not rospy.is_shutdown():
        msg = Int16MultiArray()  # Create a message instance
        if xAxis1 > 0 and abs(xAxis1) > abs(yAxis1):
            var = 1
            vel = int(abs(xAxis1) * 255)
        elif xAxis1 < 0 and abs(xAxis1) > abs(yAxis1):
            var = 2
            vel = int(abs(xAxis1) * 255)
        elif yAxis1 > 0 and abs(yAxis1) > abs(xAxis1):
            var = 3
            vel = int(abs(yAxis1) * 255)
        elif yAxis1 < 0 and abs(yAxis1) > abs(xAxis1):
            var = 4
            vel = int(abs(yAxis1) * 255)
        elif square == 1:
            var = 5
            vel = 0
        elif circle == 1:
            var = 6
            vel = 0
        else:
            var = 0
            vel = 0

        msg.data = [var, vel] 
        pub.publish(msg)
