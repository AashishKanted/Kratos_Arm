#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16, Int16MultiArray
import time

class EncoderCalibration:
    def __init__(self):
        # Initialize ROS node
        rospy.init_node('enc_calibration', anonymous=True)
        
        # Subscribe to encoder topics
        rospy.Subscriber("Orange_enc", Int16, self.callback_1)
        rospy.Subscriber("Orange_enc_2", Int16, self.callback_2)
        
        # Publisher for velocity command
        self.vel_pub = rospy.Publisher('/control1', Int16MultiArray, queue_size=1)
        
        # Publisher for encoder feedback
        self.feed_pub = rospy.Publisher('/feedback_topic', Int16MultiArray, queue_size=1)
        
        # Publisher for publishing calibrated angles
        self.angle_pub = rospy.Publisher('/angle_enc', Int16MultiArray, queue_size=1)
        
        # Rate object for controlling loop rate
        self.rate = rospy.Rate(10)
        
        # Calibration status
        self.status = 1
        
        # Initialize variables for encoder readings
        self.prev_enc_1 = 0
        self.prev_enc_2 = 0
        self.enc_1 = 0
        self.enc_2 = 0
        
        # Angle factor for conversion from encoder readings to angles
        self.angle_factor = 360 / 800
        
        # Encoders' fully retracted angles
        self.enc_ret_1 = 0
        self.enc_ret_2 = 0
        
        # Constant fully retracted angles
        self.ang_1_ret = 0
        self.ang_2_ret = 0

    # Callback function for the first encoder
    def callback_1(self, data):
        self.prev_enc_1 = self.enc_1
        self.enc_1 = data.data

    # Callback function for the second encoder
    def callback_2(self, data):
        self.prev_enc_2 = self.enc_2
        self.enc_2 = data.data

    # Calibration routine
    def calibrate_encoders(self):
        while self.status:
            start_t = time.time()
            
            # Publish velocity command for 5 seconds
            while (time.time() - start_t) < 5:
                array = Int16MultiArray()
                array.data = [255, 255]
                self.vel_pub.publish(array)
                self.rate.sleep()
            
            # Calibration completed
            else:
                self.status = 0
                
                # Store encoder readings at fully retracted position
                self.enc_ret_1 = self.enc_1
                self.enc_ret_2 = self.enc_2
                
                # Publish encoder feedback
                enc_arr = Int16MultiArray()
                enc_arr.data = [self.enc_1, 0]
                start_t = time.time()
                while (time.time() - start_t) < 2:
                    self.feed_pub.publish(enc_arr)
                    self.rate.sleep()

    # Publish calibrated angles
    def publish_calibrated_angles(self):
        while not rospy.is_shutdown():
            # Compute angles based on calibration
            angle_1 = self.ang_1_ret + (self.enc_1 - self.enc_ret_1) * self.angle_factor
            angle_2 = self.ang_2_ret + (self.enc_2 - self.enc_ret_2) * self.angle_factor
            
            # Publish calibrated angles
            self.angle_pub.publish(Int16MultiArray(data=[angle_1, angle_2]))
            self.rate.sleep()

if __name__ == '__main__':
    encoder_calibrator = EncoderCalibration()
    encoder_calibrator.calibrate_encoders()
    encoder_calibrator.publish_calibrated_angles()
