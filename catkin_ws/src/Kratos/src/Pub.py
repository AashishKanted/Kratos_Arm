#! /usr/bin/env python3

import rospy
##from geometry_msgs.msg import Twist
from std_msgs.msg import String, Int32







def puby():
     rospy.init_node('Sub')
     pub= rospy.Publisher("Sub",Int32,queue_size=10)
    #  sub = rospy.Subscriber("Pub",String,callback)
     while not rospy.is_shutdown():
        pub.publish(5)
        
        continue  

# def callback(data):
#     rospy.loginfo(data.data)
   
    
    
if __name__ == "__main__" :
      
   puby()

    
   
    
    