import numpy as np
from scipy import integrate
from scipy import misc
import time
import matplotlib.pyplot as plt
class PID():
    def __init__(self):
        self.Kp=2
        self.Kd=0
        self.Ki=0
        # self.Ti=0
        # self.Td=0
        self.time_start=time.time()
        self.time_now=0
        self.epsilon=0
        self.t=0
        self.g=-9.8
        self.g1=self.g
        
        pass
    
    def gravity(self):
        #code for the kinematic equations for the calculation of time_now, velocity and position
                
                
                self.time_now=time.time()
                self.t=self.time_now - self.time_start
                self.epsilon = 5000+1/2*(self.g1)*(self.t**2)
                
    def calculation(self):
      
        
  
        self.t=self.time_now-self.time_start
        # self.u= self.Kp*self.epsilon + (self.Ki*integrate.quad(self.epsilon,self.time_start,self.time_now)) + (self.Kd*misc.derivative(self.epsilon,t))
        self.u= self.Kp*self.epsilon
        self.k= -self.u
        self.k1=(self.k/1000000)*(10)
        
        self.g1=self.g+(self.k1)
        self.g2=self.g1-self.g
        print(self.g1)
        

    def main(self):
     while True:
      
      plt.plot(self.t,self.epsilon, 'o')
      plt.xlabel("Time_now(s)")
      plt.ylabel("Position")
      plt.pause(0.0000005)
      self.gravity() 
      self.calculation()   
     

if __name__ == '__main__':
  PID().main()
  