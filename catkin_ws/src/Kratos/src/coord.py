#!/usr/bin/env python3  
from pickle import FALSE
import rospy
import tf2_ros
import gazebo_msgs.msg
import geometry_msgs.msg
import time
from std_msgs.msg import Float32
from std_msgs.msg import Time



if __name__ == '__main__':
    
    rospy.init_node('gazebo_tf_broadcaster')

    use_sim_time:True

    broadcaster = tf2_ros.StaticTransformBroadcaster()

    publish_frequency = rospy.get_param("publish_frequency", 1000)

    last_published = None

    pub = rospy.Publisher('ball',Float32,queue_size=10)
    #pub1 = rospy.Publisher('gshock',Time,queue_size=10)


    sent_value=0

    def ypub():
        ##self.pub = rospy.Publisher('chatter',Int8,queue_size=10)    
        pub.publish(sent_value)

    def callback(data):
        global last_published
        global sent_value
        if last_published and publish_frequency > 0.0 and time.time() - last_published <= 1.0 / publish_frequency:
            return
        transforms = []
        for i in range(len(data.name)):
            print(data.name[i])
            transform = geometry_msgs.msg.TransformStamped()
            transform.header.stamp = rospy.Time.now()
            transform.header.frame_id = "world"
            transform.child_frame_id = data.name[i]
            transform.transform.translation.x = data.pose[i].position.x
            print(data.pose[i].position.x)
            transform.transform.translation.y = data.pose[i].position.y
            print(data.pose[i].position.y)
            transform.transform.translation.z = data.pose[i].position.z
            print(data.pose[i].position.z)
            transform.transform.rotation.w = data.pose[i].orientation.w
            print(data.pose[i].orientation.w)
            transform.transform.rotation.x = data.pose[i].orientation.x
            print(data.pose[i].orientation.x)
            transform.transform.rotation.y = data.pose[i].orientation.y
            print(data.pose[i].orientation.y)
            transform.transform.rotation.z = data.pose[i].orientation.z
            print(data.pose[i].orientation.z)
            transforms.append(transform)
        broadcaster.sendTransform(transforms)
        last_published = time.time()
        sent_value=data.pose[i].position.y
        ypub()

    #def pubtime():
        #gazebo_clock = 
    
    rospy.Subscriber("/gazebo/model_states", gazebo_msgs.msg.ModelStates, callback)


    rospy.spin()