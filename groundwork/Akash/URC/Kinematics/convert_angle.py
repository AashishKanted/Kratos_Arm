#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import  Point
import math

rospy.init_node('forward_kinematics' , anonymous = True)

l1 = float(409.149)     # Link 1 length
l2 = float(384.811)     # Link 2 length

link_1_low = 20              #Minimum and Max extension angles, minimum refers to when the linear actuator is fully retracted and max refers to when
link_1_high = 110            #the linear actuator is extended to its maximum(for base it cannot be extended to max so something needs to be figrued out)
link_2_low = 50              # INPUT IN DEGREES
link_2_high = 120

pot1_low = 200              # Again low value refers to when actuator is fully retracted
pot1_high = 600             # THE LOW VALUE CAN BE MORE THAN THE HIGH VALUE
pot2_low = 200
pot2_high = 600


def mapping(ang_low,ang_high,pot_low,pot_high):
    ang_range = ang_high - ang_low
    pot_range = pot_high - pot_low
    
    return float(ang_range/pot_range)

clicks_1 = mapping(link_1_low,link_1_high,pot1_low,pot1_high)
clicks_2 = mapping(link_2_low,link_2_high,pot2_low,pot2_high)

# Publishes angles in radians/degrees and coordinates to topics
def callbackfunc(data):   
    pot1 = data.x
    pot2 = data.y

    ang_deg = Point()                                           # Calculates angles in degrees from how many 'clicks' they are from base potentiometer reading 
    ang_deg.x = link_1_low + clicks_1*(pot1 - pot1_low)
    ang_deg.y = link_2_low + clicks_2*(pot2- pot2_low)
    ang_deg.z = 0
    
    ang_rad = Point()                                           # Converts angles in radians 
    ang_rad.x = math.radians(ang_deg.x)
    ang_rad.y = math.radians(ang_deg.y)
    ang_rad.z = 0
    
    coords = Point()                                            # Forward kinematics to calculate coordinates
    coords.x = l1 * math.cos(ang_rad.x) + l2 * math.cos(ang_rad.x + ang_rad.y - math.pi)
    coords.y = l1 * math.sin(ang_rad.x) + l2 * math.sin(ang_rad.x + ang_rad.y - math.pi)
    coords.z = 0
    
    pub_coords.publish(coords)
    pub_ang_rad.publish(ang_rad)
    pub_ang_deg.publish(ang_deg)


pub_coords = rospy.Publisher('coordinates', Point, queue_size=1)
pub_ang_deg = rospy.Publisher('angles_deg', Point, queue_size=1)
pub_ang_rad = rospy.Publisher('angles_rad', Point, queue_size=1)
rate = rospy.Rate(10)

rospy.Subscriber('Potentiometer_values', Point, callback=callbackfunc)
rospy.spin() 
