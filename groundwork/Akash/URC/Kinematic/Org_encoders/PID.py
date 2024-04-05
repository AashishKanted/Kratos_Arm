#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16MultiArray
from geometry_msgs.msg import Point

def callback_current(msg):
    global theta1_curr,theta2_curr
    theta1_curr = msg.data[0]
    theta2_curr = msg.data[1]
    
def callback_desired(msg):
    global theta1_des,theta2_des
    theta1_des = msg.x
    theta2_des = msg.y