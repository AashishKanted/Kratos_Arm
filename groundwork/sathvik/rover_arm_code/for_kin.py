#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist, Point
from math import sin, cos, radians

len1 = float(input("Enter length of base attached arm: "))
len2 = float(input("Enter length of next arm: "))

#assertion values for angles
THETA_1_MAX = 90
THETA_2_MAX = 180

def callbackfunc(data):
    # angle wrt base: 0 to 90
    theta1 = data.angular.x
    #angle wrt first arm: 0 to 180
    theta2 = data.angular.y

    # angle wrt plane parallel to base
    theta2 = theta1+theta2-180

    # checks absolute values of angles
    if (abs(theta1)>0 and abs(theta1)<THETA_1_MAX) and (abs(theta2)>0 and abs(theta2)<THETA_2_MAX):
        theta1 = radians(theta1)
        theta2 = radians(theta2)
        
        coords = Point()
        coords.x = len1*cos(theta1) + len2*cos(theta2)
        coords.y = len1*sin(theta1) + len2*sin(theta2)
        coords.z = 0.0
        
        print(f"Coordinates (x, y): ({coords.x}, {coords.y})")
        while not rospy.is_shutdown():
            pub_coords.publish(coords)

rospy.init_node('forward_kin' , anonymous = True)

pub_coords = rospy.Publisher('coordinates', Point, queue_size=1)
rate = rospy.Rate(10)

rospy.Subscriber('parameters', Twist, callback=callbackfunc)
rospy.spin()
