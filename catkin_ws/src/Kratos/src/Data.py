#! /usr/bin/env python3
import rospy
from  sensor_msgs.msg import Joy

class Joystick():
    def __init__(self):
        rospy.init_node('Joystick')
        self.sub1 = rospy.Subscriber("joy",Joy,self.callback)
        rospy.spin()
        pass
    
    def callback(self,data):
        rospy.loginfo(data.axes)
        rospy.loginfo(data.buttons)      

if __name__ == "__main__":
   Joystick()
   