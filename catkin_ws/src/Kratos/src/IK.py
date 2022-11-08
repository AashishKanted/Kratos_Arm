#! /usr/bin/env python3


import rospy
import math
from sensor_msgs.msg import Joy
from std_msgs.msg import Float64

class Inv():

    def  __init__(self):
        
        rospy.init_node("Joystick")
        self.sub1=rospy.Subscriber("joy",Joy,self.callback)
        self.pub1= rospy.Publisher("l1",Float64,queue_size=10)
        self.pub2=rospy.Publisher("l2",Float64,queue_size=10)
        self.x=0.0
        self.y=0.0
       
        rospy.spin()

    def callback(self,data):
        self.a6=31
        self.a4=36
        self.h6=1.5
        self.k6=19.5
        self.h4=4
        self.k4=7.5    
        LL6= self.a6+self.h6+self.k4
        LL4=self.a4+self.h4
        print(LL4,LL6)
        self.x+= data.axes[0]*0.1
        self.y+=data.axes[1]*0.1
        self.x=70
        self.y=0
        print(self.x,self.y)
        h=math.radians((math.pi/3))
       
        m1 = (((self.x)**2)+((self.y)**2)-((LL6)**2)-((LL4)**2))/(2*(LL6)*(LL4))
        t2 = -math.acos(m1)
        theta2=math.pi/2+math.radians((t2))
       
        m2=((self.y)/(self.x))
        m3=(int(LL4)*math.sin(theta2))/((LL6)+(LL4)*math.cos(theta2))
        t1= math.atan((m2))+math.atan((m3))
        theta1=math.radians((t1))       
        alpha=math.pi-(theta1)-(h)
        beta=math.pi-(theta1)
        l6=math.sqrt(int(self.k6)*int(self.k6)+(self.a6)*(self.a6)+2*(self.k6)*(self.a6)*math.cos(((alpha))))
        l4=math.sqrt((self.k4)*(self.k4)+(self.a6)*(self.a6)+2*(self.k4)*(self.a6)*math.cos(((beta))))
        #o1 = print(f"l4: {l4} l6: {l6}")
        print(f"q6:{180-math.degrees(theta1)} q4: {math.degrees(-theta2)}")
        # self.pub1.publish(o1)
        
    def main(self):
        pass


if __name__ =="__main__":                
    Inv().main()