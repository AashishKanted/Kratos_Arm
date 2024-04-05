#!/usr/bin/env python3
import rospy
from std_msgs.msg import Float32MultiArray

rospy.init_node('tester',anonymous=True)
pub_tester = rospy.Publisher('inv_kin_point',Float32MultiArray,queue_size=1)
rate = rospy.Rate(10)
testing = Float32MultiArray()
x = 0


while not rospy.is_shutdown():
    testing.data = [x,x]
    x = x + 1
    pub_tester.publish(testing)
    rospy.sleep(0.2)

rospy.spin()