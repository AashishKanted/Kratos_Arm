#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16MultiArray
from geometry_msgs.msg import Point

class PIDController:
    def __init__(self):
        # Initialize the ROS node
        rospy.init_node('PID')
        
        # Subscribe to the encoder angles and desired angles topics
        rospy.Subscriber('angle_enc', Int16MultiArray, self.callback_current)
        rospy.Subscriber('inv_kin_ang', Point, self.callback_desired)
        
        # Publisher to publish the control efforts
        self.PID_pub = rospy.Publisher('PID_controls', Point, queue_size=10)

        # Initialize variables for PID control
        self.error_integral1 = 0
        self.error_integral2 = 0
        self.prev_error1 = 0
        self.prev_error2 = 0
        self.kp = 0.5  # Proportional gain
        self.ki = 0.01  # Integral gain
        self.kd = 0.1  # Derivative gain

    # Callback function for current encoder angles
    def callback_current(self, msg):
        self.theta1_curr = msg.data[0]
        self.theta2_curr = msg.data[1]

    # Callback function for desired angles
    def callback_desired(self, msg):
        self.theta1_des = msg.x
        self.theta2_des = msg.y

    # PID controller function
    def PID_controller(self):
        # Compute error for angle 1
        error_1 = self.theta1_des - self.theta1_curr
        self.error_integral1 += error_1
        error_derivative1 = error_1 - self.prev_error1
        self.prev_error1 = error_1
        
        # Compute control effort for angle 1 using PID equation
        control_effort_1 = self.kp * error_1 + self.ki * self.error_integral1 + self.kd * error_derivative1

        # Compute error for angle 2
        error_2 = self.theta2_des - self.theta2_curr
        self.error_integral2 += error_2
        error_derivative2 = error_2 - self.prev_error2
        self.prev_error2 = error_2
        
        # Compute control effort for angle 2 using PID equation
        control_effort_2 = self.kp * error_2 + self.ki * self.error_integral2 + self.kd * error_derivative2

        # Create a Point message to publish control efforts
        controls = Point()
        controls.x = control_effort_1
        controls.y = control_effort_2

        return controls

    # Publish control efforts
    def publish_control_effort(self):
        control_set = self.PID_controller()
        self.PID_pub.publish(control_set)


if __name__ == '__main__':
    # Initialize PIDController class
    pid_controller = PIDController()
    
    # Set the rate for publishing control efforts (10 Hz)
    rate = rospy.Rate(10)  # 10 Hz
    
    # Continuous loop to publish control efforts
    while not rospy.is_shutdown():
        pid_controller.publish_control_effort()
        rate.sleep()
