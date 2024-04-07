#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16MultiArray
from sensor_msgs.msg import Joy

class JoystickControl:
    def __init__(self):
        self.vel_la1 = 0 # velocity of linear actuator 1 
        self.vel_la2 = 0 # velocity of linear actuator 2
        #self.var_st1 = 0 # variable to enabel/disable gripper
        self.var_bev = 0 # variable to control bevel motors
        self.vel_bev = 0 # velocity of bevel motors
        self.var_base = 0 # variable to control base
        self.vel_base = 0 # velocity of base
        self.var_gripper = 0 # variable to control gripper        
        self.msg = Int16MultiArray()
        
        self.sub = rospy.Subscriber("/joy", Joy, self.callback)
        self.pub = rospy.Publisher("/control", Int16MultiArray, queue_size=1)

    def callback(self, data):
        xAxis1 = data.axes[0] # axes[0] controls linear actuators
        yAxis1 = data.axes[1] # axes[1]
        xAxis2 = data.axes[3] # axes[3]  //controls Bevel
        yAxis2 = data.axes[4] # axes[4]

        r2 = data.axes[5] # axes[5] //controls Base
        l2 = data.axes[2] # axes[2]

        triangle = data.buttons[2] # buttons[2] //controls Stepper (for enabling)
        cross = data.buttons[0] # buttons[0]
        square = data.buttons[3] # buttons[3] enables stepper
        circle = data.buttons[1] # buttons[1] disables stepper

        self.vel_la1 = 0 
        self.vel_la2 = 0
        self.var_bev = 0
        self.vel_bev = 0
        self.var_base = 0
        self.vel_base = 0
        self.var_gripper = 0

        # this part of if block, will tell base motor to run at a certain speed

        if r2 < 1:
            self.var_base = 1
            self.vel_base = int(abs(r2-1)*255/2)
        elif l2 < 1:
            self.var_base = 2
            self.vel_base = int(abs(l2-1)*255/2)

        # this part of if block, will tell which linear actuators to run and in which combo
        # For eg: Both extending, one extending and other retracting, etc.
        
        if xAxis1 > 0:
            self.vel_la1 = int((xAxis1)*255) # velocity of linear actuator 1 is proportional to how much you move the joystick (analog)
        if xAxis1 < 0:
            self.vel_la1 = int((xAxis1)*255)
        if yAxis1 < 0:
            self.vel_la2 = int((yAxis1)*255) # velocity of linear actuator 2 is proportional to how much you move the joystick (analog)
        if yAxis1 > 0:
            self.vel_la2 = int((yAxis1)*255)

        # this part of if block, will tell the gripper to perform roll or pitch motion, in which direction and what velocity
            
        if yAxis2 > 0 and abs(yAxis2) > abs(xAxis2):
            self.var_bev = 1
            self.vel_bev = int(abs(yAxis2)*255)
        elif yAxis2 < 0 and abs(yAxis2) > abs(xAxis2):
            self.var_bev = 2
            self.vel_bev = int(abs(yAxis2)*255)
        elif xAxis2 > 0 and abs(xAxis2) > abs(yAxis2):
            self.var_bev = 3
            self.vel_bev = int(abs(xAxis2)*255)
        elif xAxis2 < 0 and abs(xAxis2) > abs(yAxis2):
            self.var_bev = 4
            self.vel_bev = int(abs(xAxis2)*255)

        # this part will tell if stepper should be enabled or disabled

        #if square == 1:
        #    self.var_st1 = 1
        #elif circle == 1:
        #    self.var_st1 = 2
        #else:
        #    self.var_st1 = 0

        #this part of the if block will tell the gripper to open or close
            
        if triangle == 1:
            self.var_gripper = 1
        elif cross == 1:
            self.var_gripper = 2
        else:
            self.var_gripper = 0

        self.msg.data = [self.vel_la1, self.vel_la2, self.var_base, self.vel_base, self.var_bev, self.vel_bev, self.var_gripper]
        self.pub.publish(self.msg)

if __name__ == '__main__':
    rospy.init_node("joy_control", anonymous=True)
    joystick_control = JoystickControl()
    rospy.spin()