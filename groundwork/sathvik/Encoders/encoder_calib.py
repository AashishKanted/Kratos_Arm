#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16, Int16MultiArray, Float32MultiArray
import time

# status = 1

prev_enc_1 = 0
prev_enc_2 = 0

stat_1 = 0
stat_2 = 0

enc_1 = 0
enc_2 = 0

angle_factor = 360/800

# fully dextended angles; constant
ang_1_ret = 0
ang_2_ret = 0

def callback_1(data):
    global prev_enc_1, enc_1, stat_1
    if not stat_1:
        stat_1 = 1
        prev_enc_1 = data.data
    enc_1 = data.data    

def callback_2(data):
    global prev_enc_2, enc_2, stat_2
    if not stat_2:
        stat_2 = 1
        prev_enc_2 = data.data
    enc_2 = data.data

rospy.init_node('enc_calibration', anonymous=True)
rospy.Subscriber("Orange_enc_1", Int16, callback_1)
rospy.Subscriber("Orange_enc_2", Int16, callback_2)

angle_pub = rospy.Publisher('/angle_enc', Float32MultiArray, queue_size=1)
rate = rospy.Rate(10)


while not rospy.is_shutdown():
    print(enc_1, prev_enc_1)
    print(enc_2, prev_enc_2)
    print('#####\n')
    angle_1 = ang_1_ret + (enc_1 - prev_enc_1)*angle_factor
    angle_2 = ang_2_ret + (enc_2 - prev_enc_2)*angle_factor
    arr = Float32MultiArray()
    arr.data = [angle_1, angle_2]
    angle_pub.publish(arr)
    rate.sleep()

rospy.spin()
