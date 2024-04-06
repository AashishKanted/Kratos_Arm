#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16MultiArray
from sensor_msgs.msg import Joy

class JoystickControl:
    def __init__(self):
        self.pump2 = 0 # variable to control peristalic pump 2
        self.pump3 = 0 # variable to control peristalic pump 3
        self.auger_spin = 0
        self.msg = Int16MultiArray()
        
        
        self.sub = rospy.Subscriber("/joy", Joy, self.callback)
        self.pub = rospy.Publisher("/ldmega_topic", Int16MultiArray, queue_size=1)

    def callback(self, data):
        xAxis = data.axes[3] 
        yAxis = data.axes[4]
        square = data.buttons[3]
        circle = data.buttons[1]
        self.auger_spin = 0
        self.mixer = 0
        self.pump2 = 0
        self.pump3 = 0
        
        if xAxis > 0 and abs(xAxis) > abs(yAxis):
            self.auger_spin = 1 
        if xAxis < 0 and abs(xAxis) > abs(yAxis):
            self.auger_spin = -1

        if square == 1:
            self.pump2 = 1
        if circle == 1:
            self.pump3 = 1

        self.msg.data = [self.auger_spin, self.pump2, self.pump3]
        self.pub.publish(self.msg)

if __name__ == '__main__':
    rospy.init_node("joy_control", anonymous=True)
    joystick_control = JoystickControl()
    rospy.spin()