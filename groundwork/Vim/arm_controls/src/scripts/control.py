#!/usr/bin/env python

import rospy
from std_msgs.msg import Int8

from sensor_msgs.msg import Joy

# UP = both forward = 2
# DOWN = both backward = 4
# LEFT = L FOR / R BACK = 8
# RIGHT = R FOR / L BACK = 16
# STOP = 32


rospy.init_node('motor_control', anonymous=True)
publisher1 = rospy.Publisher('/control_motor', Int8, queue_size=10)

useful_data = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]

def callback_fn(data):
    global useful_data
    useful_data = data.axes
    # print(useful_data)


rospy.Subscriber("/joy", Joy, callback_fn)

data = 0
rate = rospy.Rate(10)  #update once every second

while not rospy.is_shutdown():   
    # data = int(input("Enter input: "))  
    
    # global useful_data
    # publisher1.publish(data)
    
    # print(useful_data)
    condition_1 = useful_data[7]
    condition_2 = useful_data[6]
    
    if(condition_1 == 1.0):
        motor_control = 2
    elif(condition_1 == -1.0):
        motor_control = 4
    elif(condition_2 == 1.0):
        motor_control = 8
    elif(condition_2 == -1.0):
        motor_control = 16
    else :
        motor_control = 32
    
    publisher1.publish(motor_control)
    print(motor_control)


    rate.sleep()



# data = float(input("Enter input"))  # take input from user for radius
# # default value is 5 meters
# bot = Control_motor()
# bot.user_input = data
# bot.blink_led()