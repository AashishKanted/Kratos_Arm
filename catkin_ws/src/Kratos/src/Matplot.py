#! /usr/bin/env python3


from time import time
import rospy
from sensor_msgs.msg import Joy
import matplotlib.pyplot as plt



class Joystick():
    def __init__(self):
        rospy.init_node('Joystick')
        self.sub1 = rospy.Subscriber("joy",Joy,self.callback)
        self.x=0
        self.y=0
        while not rospy.is_shutdown():
            self.time()
        
    
    def callback(self,data):
        
        print(self.x,self.y)
        
        if (data.axes[0] > 0.8 ):
         self.x =self.x-1
        if (data.axes[0]<-0.8):
         self.x =self.x+1
        else:
            self.x =self.x
        

         
        
        if (data.axes[1] > 0.8 ):
           self.y =self.y+1 
        elif(data.axes[1]<-0.8): 
           self.y =self.y-1
        else:
            self.y =self.y
        

    def time(self):
        plt.plot(self.x,self.y,'o')
        print("Plotting")
        plt.pause(0.00005)
          
          

if __name__ == "__main__":
  Joystick().time()
  
    