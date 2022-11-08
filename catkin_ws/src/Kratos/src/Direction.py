#! /usr/bin/env python3
import rospy
from sensor_msgs.msg import Joy
from std_msgs.msg import Int8


class  Motor():
    
    
    
    
    def __init__(self):
        
        rospy.init_node('')
        self.sub1 = rospy.Subscriber("joy",Joy,self.callback)
        self.pub1= rospy.Publisher("Directions",Int8,queue_size=10)
        
        self.x=0
        self.y=0
        while not rospy.is_shutdown():
            rospy.spin()
          
    
    def callback(self,data):
        rospy.loginfo(data.axes)
        rospy.loginfo(data.buttons)   
        print(self.x,self.y)
        if (data.axes[0] > 0.8 ):
            self.pub1.publish(2)
        elif(data.axes[0]<-0.8):
            self.pub1.publish(3) 
        
        
        elif (data.axes[1] > 0.8):
            self.pub1.publish(4) 
        elif(data.axes[1]<-0.8):
           self.pub1.publish(5) 
        
        
        elif (data.axes[3] > 0.8):
            self.pub1.publish(6) 
        elif(data.axes[3]<-0.8):
           self.pub1.publish(7) 
        
        elif (data.axes[4] > 0.8):
            self.pub1.publish(8) 
        elif(data.axes[4]<-0.8):
           self.pub1.publish(9) 
        
    
        else:
            self.pub1.publish(0) 


if __name__ == "__main__" :
    Motor()


