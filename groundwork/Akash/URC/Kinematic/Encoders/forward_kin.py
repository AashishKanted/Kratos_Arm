#!/usr/bin/env python3

import rospy
import math
from std_msgs.msg import Int16MultiArray
from geometry_msgs.msg import Point

class ForwardKinematicsSolver:
    def __init__(self):
        # Initialize ROS node
        rospy.init_node('forward_kin', anonymous=True)
        
        # Subscribe to the encoder angles topic
        rospy.Subscriber('/angle_enc', Int16MultiArray, callback=self.callback)
        
        # Publisher to publish the forward kinematics results
        self.coords_pub = rospy.Publisher('forward_kin', Point, queue_size=1)

        # Lengths of the links
        self.l1 = float(384.811)
        self.l2 = float(409.149)

        rospy.spin()

    # Callback function to compute forward kinematics
    def callback(self, msg):
        angle_1 = msg.data[0]
        angle_2 = msg.data[1]
        
        # Convert angles to radians
        theta_1 = math.radians(angle_1)
        theta_2 = math.radians(angle_2 - 180 + angle_1)
        
        # Compute forward kinematics
        coords = Point()
        coords.x = self.l1 * math.cos(theta_1) + self.l2 * math.cos(theta_2)
        coords.y = self.l1 * math.sin(theta_1) + self.l2 * math.sin(theta_2)
        coords.z = 0
        
        # Publish forward kinematics results
        self.coords_pub.publish(coords)

if __name__ == '__main__':
    forward_kinematics_solver = ForwardKinematicsSolver()
