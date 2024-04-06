#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import Point
import numpy as np


class InverseKinematicsSolver:
    def __init__(self):
        rospy.init_node('inverse_kinematics_node')

        # Subscribe to the inv_kin_point topic
        rospy.Subscriber('inv_kin_point', Float32MultiArray, self.inverse_kinematics_callback)

        # Publish joint angles in degrees to inv_kin_ang topic
        self.inv_kin_ang_pub = rospy.Publisher('inv_kin_ang', Point, queue_size=10)

        rospy.spin()

    def inverse_kinematics_callback(self, msg):
        x = msg.data[0]
        y = msg.data[1]
        l1 = float(384.811)  # Length of the first arm segment
        l2 = float(409.149)  # Length of the second arm segment

        # Compute inverse kinematics
        theta1, theta2 = self.inverse_kinematics(x, y, l1, l2)

        # Max and min angles of arm for each link
        min_theta1 = np.radians(-360)
        min_theta2 = np.radians(-360)
        max_theta1 = np.radians(360)
        max_theta2 = np.radians(360)
        if self.check_angle_ranges(theta1, theta2, min_theta1, max_theta1, min_theta2, max_theta2):
            # Publish joint angles in degrees
            self.inv_kin_ang_pub.publish(Point(np.degrees(theta1), np.degrees(theta2), 0))
        else:
            # Publish 0 if angles are not within ranges
            self.inv_kin_ang_pub.publish(Point(0, 0, 0))

    def inverse_kinematics(self, x, y, l1, l2):
        # Compute theta2 using the law of cosines
        cos_theta2 = (x ** 2 + y ** 2 - l1 ** 2 - l2 ** 2) / (2 * l1 * l2)
        sin_theta2 = np.sqrt(1 - cos_theta2 ** 2)
        theta2 = -np.arctan2(sin_theta2, cos_theta2)

        # Compute theta1 using trigonometry
        alpha = np.arctan2(y, x)
        beta = np.arctan2(l2 * np.sin(theta2), l1 + l2 * np.cos(theta2))
        theta1 = alpha - beta

        theta2 = np.pi - theta2  # Makes it easier to visualize

        return theta1, theta2

    def check_angle_ranges(self, theta1, theta2, min_theta1, max_theta1, min_theta2, max_theta2):
        # Checks if angles are within accepted arm limits
        return min_theta1 <= theta1 <= max_theta1 and min_theta2 <= theta2 <= max_theta2


if __name__ == '__main__':
    ik_solver = InverseKinematicsSolver()
