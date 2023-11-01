#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int8
from sensor_msgs.msg import Joy


# publishes for actuators
def actuator(act_1, act_2):
    if act_1>0.5:
        pub_act.publish(1) # l up
    elif act_1<-0.5:
        pub_act.publish(2) # l down
        
    if act_2>0.5:
        pub_act.publish(3) # r up
    elif act_2<-0.5:
        pub_act.publish(4) # r down


# publishes for bevel motors
def bevel(x, cir, tri, sq):
    if x==1:
        pub_bevel.publish(1)
    elif cir==1:
        pub_bevel.publish(2)
    elif tri==1:
        pub_bevel.publish(3)
    elif sq==1:
        pub_bevel.publish(4)

def callbackfunc(data):
    x = data.buttons[0]
    cir = data.buttons[1]
    tri = data.buttons[2]
    sq = data.buttons[3]
    
    act_1 = data.axes[1] # top and bottom contraint
    act_2 = data.axes[4] # left and right contraint
    
    # checks for non-zero value of buttons
    if any(data.buttons[0:4]):
        bevel(x, cir, tri, sq)
    else:
        pub_bevel.publish(0)

    # checks for non-zero value of buttons
    if act_1!=0.0 or act_2!=0.0:
        actuator(act_1, act_2)
    else:
        pub_act.publish(0)

rospy.init_node('arm_control' , anonymous = True)
pub_bevel = rospy.Publisher('controls_bevel', Int8, queue_size=1)
pub_act = rospy.Publisher('controls_act', Int8, queue_size=1)
rate = rospy.Rate(10)

rospy.Subscriber('/joy', Joy, callback=callbackfunc)
rospy.spin()
