#! /usr/bin/env python3
# import rospy

import numpy as np
import matplotlib.pyplot as plt
import time

class ball(): 

 def __init__(self):
     self.time_then=0
     self.y=5000
     self.time_start=time.time()
     self.g = -9.8 #gravitational constant N
     pass
 def drop(self):

    """
    This function calculates and creates arrays for the velocity at each time_now interval as well as the position and plots it. Assuming no drag. 
    """
    #Define the constants in the problem
    h_0 = 5000
    #Now need to create arrays to hold the positins, time_now, and velocities
    
 def gravity(self):
        #code for the kinematic equations for the calculation of time_now, velocity and position
            for i in range(1,1000):
                global dt
                time_now=time.time()
                dt=time_now - self.time_start
                self.y = 5000 + 1/2*self.g*(dt**2)
                self.time_then = dt
                if self.y < 0:
        #ensures that the graph will not keep going when the ball hits the ground
                    break


 def main(self):
  while True:
     plt.plot(self.time_then,self.y, 'o')
     plt.xlabel("Time_now(s)")
     plt.ylabel("Position")
     plt.pause(0.0000005)
     self.gravity()
            

if __name__ =="__main__":
    ball().main()