#!/usr/bin/env python3

"""//////////////////////////////////////////////

CLEAN THE CODE

////////////////////////////////////////////////////"""
import rospy
from std_msgs.msg import Int32
from sensor_msgs.msg import Joy
import math


class ik():

    def __init__(self):
        self.x = 0
        self.y = 0
        self.theta1=0
        self.theta2 = 0
      
        rospy.init_node('ik', anonymous=True)
        self.pulse= 0
        self.sub1 =rospy.Subscriber("/joy", Joy, self.callback)
        self.pub1 = rospy.Publisher("link1",Int32,queue_size = 10)
        self.pub2= rospy.Publisher("link2",Int32,queue_size = 10)

    def callback(self,data):
        
        if data.axes[0] > 0.8 :
            self.x += 0.005

        elif data.axes[0] < -0.8 :
            self.x -= -0.005  

        if data.axes[1] > 0.8 :
            self.y += 0.005

        elif data.axes[1] < -0.8 :
            self.y -= -0.005 

        else:
            self.x +=0
            self.y +=0  
        rospy.loginfo(self.x)
        rospy.loginfo(self.y)
        self.a2 = 1
        self.a1 = 1 
      
        self.theta1 = -1*(math.acos(((self.x**2) + (self.y**2) - (self.a2**2) - (self.a1**2))/(2*self.a2*self.a1)))*(180/math.pi)
        print(self.theta1*180/math.pi)
        
        self.theta2 = (math.atan(self.y/self.x) + math.atan((self.a1*math.sin(self.theta1))/(self.a6+(self.a1*math.cos(self.theta1)))))*180/math.pi
        
        """"""""""
        publishing pulse count
        """"""""""
        self.pub1.publish(int(self.theta1*2352/360)) 
        self.pub2.publish(int(self.theta2*2352/360))    
        print("theta2 = ",self.theta2)
        print("theta1 = ",self.theta1)
        
    def listener(self):
        self.sub1
        rate = rospy.Rate(10)
        while not rospy.is_shutdown():
            rate.sleep()

if __name__ == '__main__':
    ik().listener()
    

