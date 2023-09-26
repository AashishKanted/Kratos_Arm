#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int8, Int64
from sensor_msgs.msg import Joy


# publishes for actuators
def actuator(act_1, act_2):
    act_1 = int(act_1*255)
    act_2 = int(act_2*255)
    
    if act_1>0.25 or act_1<-0.25:
        pub_act.publish(act_1) # l up
        
    if act_2>0.25:
        pub_act.publish(act_2+255) # r up
    elif act_2<-0.25:
        pub_act.publish(act_2-255) # r down

# publishes for bevel motors
def bevel(x, cir, tri, sq):
    if x==1:
        pub_bevel.publish(1) # both one dir
    elif cir==1:
        pub_bevel.publish(2) # both opp dir
    elif tri==1:
        pub_bevel.publish(3) # opp dir
    elif sq==1:
        pub_bevel.publish(4) # alternate opp dir

def stepper(step_l, step_r):
    if step_l == step_r:
        pub_step.publish(0)
    elif step_l == 1:
        pub_step.publish(1) # one direction
    else:
        pub_step.publish(2) # opp direction

def callbackfunc(data):
    x = data.buttons[0]
    cir = data.buttons[1]
    tri = data.buttons[2]
    sq = data.buttons[3]
    
    act_1 = data.axes[1] # top and bottom contraint
    act_2 = data.axes[4] # left and right contraint
    
    step_l = data.buttons[4]
    step_r = data.buttons[5]
    
    # checks for non-zero value of buttons
    if any(data.buttons[0:4]):
        bevel(x, cir, tri, sq)
    else:
        pub_bevel.publish(0)

    if act_1!=0.0 or act_2!=0.0:
        actuator(act_1, act_2)
    else:
        pub_act.publish(0)

    if step_l==1 or step_r==1:
        stepper(step_l, step_r)
    else:
        pub_step.publish(0)

rospy.init_node('arm_control' , anonymous = True)
pub_bevel = rospy.Publisher('controls_bevel', Int8, queue_size=1)
pub_act = rospy.Publisher('controls_act', Int64, queue_size=1)
pub_step = rospy.Publisher('controls_stepper', Int8, queue_size=1)
rate = rospy.Rate(10)

rospy.Subscriber('/joy', Joy, callback=callbackfunc)
rospy.spin()
