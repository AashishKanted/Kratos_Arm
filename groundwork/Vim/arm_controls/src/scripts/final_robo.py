#!/usr/bin/env python

import rospy
from std_msgs.msg import Int8, Int16

from sensor_msgs.msg import Joy

# UP = both forward = 2
# DOWN = both backward = 4
# LEFT = L FOR / R BACK = 8
# RIGHT = R FOR / L BACK = 16
# STOP = 32


# iindex = 1 - left axis
# index = 4 - right axis`
# 
# `



rospy.init_node('motor_control', anonymous=True)
publisher_motors_bevel = rospy.Publisher('/control_motors', Int8, queue_size=10)

publisher_motors_act_1 = rospy.Publisher('/control_motors_act1', Int16, queue_size=10)
publisher_motors_act_2 = rospy.Publisher('/control_motors_act2', Int16, queue_size=10)


publisher_stepper = rospy.Publisher('/control_stepper', Int8, queue_size=10)
## buttons - 2 
# buttons - 0


useful_data = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
useful_data_2 = [0,0,0,0,0,0,0,0]

def callback_fn(data):
    global useful_data
    global useful_data_2
    useful_data = data.axes    
    useful_data_2 = data.buttons

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
    
    publisher_motors_bevel.publish(motor_control)
    # print(motor_control)
    
    condition_act_1 = useful_data[1]
    condition_act_2 = useful_data[4]
    temp_val_1 = 0
    temp_val_2 = 0
    
    stepper_cond_1 = useful_data_2[0]
    stepper_cond_2 = useful_data_2[2]
    
    if(stepper_cond_1 == 1):
        publisher_stepper.publish(5)
    elif(stepper_cond_2 == 1):
        publisher_stepper.publish(10)
    
    if(condition_act_1 >= 0):
        temp_val_1 = int(condition_act_1 * 255)
    elif(condition_act_1 < 0):
        temp_val_1 = int(condition_act_1 * 255)
        
    if(condition_act_2 >= 0):
        temp_val_2 = int(condition_act_2 * 255)
    elif(condition_act_2 < 0):
        temp_val_2 = int(condition_act_2 * 255)
    
    
    
    publisher_motors_act_1.publish(temp_val_1)
    publisher_motors_act_2.publish(temp_val_2)
    
    
    
    


    rate.sleep()



# data = float(input("Enter input"))  # take input from user for radius
# # default value is 5 meters
# bot = Control_motor()
# bot.user_input = data
# bot.blink_led()