#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16MultiArray, Int8
from sensor_msgs.msg import Joy

r2 = 0 
l2 = 0 

xAxis1 = 0 
yAxis1 = 0 

triangle = 0
cross = 0
#rate = rospy.Rate(10)

def callback(data):
     global r2, l2, xAxis1, yAxis1, triangle, cross

     r2 = data.axes[5] # axes[5] //controls Base
     l2 = data.axes[2] # axes[2]

     xAxis1 = data.axes[3] # axes[3]  //controls Bevel
     yAxis1 = data.axes[4] # axes[4]

     triangle = data.buttons[2] # buttons[2] //controls Stepper (for enabling)
     cross = data.buttons[0] # buttons[0]

rospy.init_node("joy_control", anonymous=True)
pub = rospy.Publisher("/control2", Int16MultiArray, queue_size=1)

gpt_says_hi = 0

def callback_fn_2(data):
     global gpt_says_hi
     gpt_says_hi = 1
     

sub3 = rospy.Subscriber("/arm_gpt_hi", Int8, callback_fn_2)

def gpt_hi_run():
     print("doing shit")
     msg.data = [5, 100] 
     pub.publish(msg)
     rospy.sleep(1)
     msg.data = [6, 100] 
     pub.publish(msg)
     rospy.sleep(1)
     
     

if __name__ == '__main__':
    rospy.Subscriber("/joy", Joy, callback)
    while not rospy.is_shutdown():
       msg = Int16MultiArray()
       
       #BASE
       if r2 < 1:
              var = 1
              vel = int(abs(r2-1)*100/2)
       elif l2 < 1:
              var = 2
              vel = int(abs(l2-1)*100/2)

       #BEVEL
       elif yAxis1 > 0 and abs(yAxis1) > abs(xAxis1):
              var = 3
              vel = int(abs(yAxis1)*100)
       elif yAxis1 < 0 and abs(yAxis1) > abs(xAxis1):
            var = 4
            vel = int(abs(yAxis1)*100)
       elif xAxis1 > 0 and abs(xAxis1) > abs(yAxis1):
            var = 5
            vel = int(abs(xAxis1)*100)
       elif xAxis1 < 0 and abs(xAxis1) > abs(yAxis1):
            var = 6
            vel = int(abs(xAxis1)*100)
       
       #STEPPER
       elif triangle == 1:
            var = 7
            vel = 0
       elif cross == 1:
            var = 8
            vel = 0
       else:
            var = 0
            vel = 0
       
       if (gpt_says_hi == 1):
          gpt_hi_run()
          gpt_says_hi = 0

       msg.data = [var, vel] 
       pub.publish(msg)
