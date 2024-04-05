#!/usr/bin/env python3
import rospy
import math
from std_msgs.msg import Int16MultiArray
from geometry_msgs.msg import Point

l1 = float(384.811)
l2 = float(409.149)

def callback(msg):
    global angle_1,angle_2
    angle_1 = msg.data[0]
    angle_2 = msg.data[1]
    
    theta_1 = math.radians(theta_1)
    theta_2 = math.radians(angle_2-180+angle_1)
    
    coords = Point()
    coords.x = l1*math.cos(theta_1) + l2*math.cos(theta_2)
    coords.y = l1*math.sin(theta_1) + l2*math.sin(theta_2)
    coords.z = 0
    coords_pub.publish(coords)
    

rospy.init_node('forward_kin',anonymous=True)
rospy.Subscriber('/angle_enc',Int16MultiArray ,callback=callback)
coords_pub = rospy.Publisher('forward_kin', Point, queue_size=1)
rospy.spin()
