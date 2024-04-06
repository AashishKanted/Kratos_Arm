#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16MultiArray
from geometry_msgs.msg import Point

error_integral1 = 0
error_integral2 = 0
prev_error1 = 0
prev_error2 = 0
kp = 0.5
ki = 0.01
kd = 0.1
    
    
def callback_current(msg):
    global theta1_curr,theta2_curr
    theta1_curr = msg.data[0]
    theta2_curr = msg.data[1]
    
def callback_desired(msg):
    global theta1_des,theta2_des
    theta1_des = msg.x
    theta2_des = msg.y
    
def PID_controller(des1,des2,curr1,curr2):
    global error_integral1,error_integral2,prev_error1,prev_error2,kp,ki,kd    
        
    ###################################################################  
    # Angle 1
    error_1 = des1 - curr1
    error_integral1 = error_integral1 + error_1
    error_derivative1 = error_1 - prev_error1
    prev_error1 = error_1
           # Control effort using PID equation
    control_effort_1 = kp*error_1 + ki*error_integral1 + kd*error_derivative1
    
    ###################################################################   
    # Angle 2
    error_2 = des2 - curr2
    error_integral2 = error_integral2 + error_2
    error_derivative2 = error_2 - prev_error2
    prev_error2 = error_2
            # Control effort using PID equation
    control_effort_2 = kp*error_2 + ki*error_integral2 + kd*error_derivative2
    
    ###################################################################    
    controls = Point()
    controls.x = control_effort_1
    controls.y = control_effort_2
    
    return controls

if __name__ == '__main__':
    rospy.init_node('PID')
    rospy.Subscriber('angle_enc',Int16MultiArray,callback_current)
    rospy.Subscriber('inv_kin_ang',Point,callback_desired)  
    
    PID_pub = rospy.Publisher('PID_controls',Point,queue_size=10)
    control_set = PID_controller(theta1_des,theta2_des,theta1_curr,theta2_curr)
    
    PID_controller.publish(control_set)
    
    
