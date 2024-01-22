#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16MultiArray
from sensor_msgs.msg import Joy

class JoystickControl:
    def __init__(self):
        self.auger = 0
        self.mixer = 0
        self.pump = 0
        self.msg = Int16MultiArray()
        
        self.sub = rospy.Subscriber("/joy", Joy, self.callback)
        self.pub = rospy.Publisher("/lduno_topic", Int16MultiArray, queue_size=1)

    def callback(self, data):
        xAxis1 = data.axes[0] 
        yAxis1 = data.axes[1]
        square = data.buttons[3]
        circle = data.buttons[1]
        self.auger = 0
        self.mixer = 0
        self.pump = 0
        
        if xAxis1 > 0 and abs(xAxis1) > abs(yAxis1):
            self.auger = 1
        if xAxis1 < 0 and abs(xAxis1) > abs(yAxis1):
            self.auger = -1
        if yAxis1 > 0 and abs(xAxis1) < abs(yAxis1):
            self.mixer = 1
        if yAxis1 < 0 and abs(xAxis1) < abs(yAxis1):
            self.mixer = -1

        if square == 1:
            self.pump = 1

        self.msg.data = [self.auger, self.mixer, self.pump]
        self.pub.publish(self.msg)

if __name__ == '__main__':
    rospy.init_node("joy_control", anonymous=True)
    joystick_control = JoystickControl()
    rospy.spin()