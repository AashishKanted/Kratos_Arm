#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <ros.h>
#include <std_msgs/Int16MultiArray.h>

ros::NodeHandle nh;
std_msgs::Int16MultiArray sensor_data;

ros::Publisher sensor_data_pub("ld_sensor_data", &sensor_data);

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

#define BFS_PIN A2 // CO2
#define MQ7_PIN A0 // CO
#define MQ4_PIN A1 // CH4


// CO Sensor MQ7

	#include "MQ7.h"
	MQ7 mq7(MQ7_PIN,5.0);




//  BFS DEFINATIONS
#define         DC_GAIN                      (8.5)   //define the DC gain of amplifier

/**********************Application Related Macros**********************************/
//These two values differ from sensor to sensor. user should derermine this value.
#define         ZERO_POINT_VOLTAGE           (0.342) //define the output of the sensor in volts when the concentration of CO2 is 400PPM // 0.220
#define         REACTION_VOLTGAE             (0.030) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2


float           CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602-3))};   


int  MGGetPercentage(float volts, float *pcurve)
{
  //  if ((volts/DC_GAIN )>=ZERO_POINT_VOLTAGE) {
  //     return -1;
  //  } else { 
      return pow(10, ((volts/DC_GAIN)-pcurve[1])/pcurve[2]+pcurve[0]);
  //  }
}


/// CH4 stuff


float getMethanePPM(){
  const int R_0 = 945; //Change this to your own R0 measurements

float a1 = analogRead(MQ4_PIN); // get raw reading from sensor
float v_o = a1 * 5 / 1023; // convert reading to volts
float R_S = (5-v_o) * 1000 / v_o; // apply formula for getting RS
float PPM = pow(R_S/R_0,-2.95) * 1000; //apply formula for getting PPM
return PPM; // return PPM value to calling function
}



unsigned long delayTime;

void setup() {
  nh.initNode();
  unsigned status;
    
  // default settings
  status = bme.begin();  
  

  nh.advertise(sensor_data_pub);

  nh.logerror("bme status : ");
  nh.logerror(status);
  delayTime = 1000; // Initial delay for the first publish
}

int sensor_data_raw[6];



void read_data(){
  sensor_data_raw[0] = mq7.getPPM();
  sensor_data_raw[1] = getMethanePPM();
  sensor_data_raw[2] = analogRead(BFS_PIN);

  float buff = analogRead(BFS_PIN);
  float co2_percent = buff*5.0/1024.0;
  if(co2_percent == -1)
    co2_percent = 400;
  sensor_data_raw[2] = MGGetPercentage(co2_percent,CO2Curve);
  
  sensor_data_raw[3] = (int)(bme.readTemperature()*100); // with 2 decimal places = divide by 100 on jetson
  sensor_data_raw[4] = (int)(bme.readHumidity()*100); // same here
  sensor_data_raw[5] = (int)(bme.readPressure() / 10.0F); // will give value in  hPa with 1 decimal places so again divide by 10
  
  
}

void loop() {
  
  read_data();
  // char* to_send = "sensor data: "+sensor_data_raw[4];
  // nh.logerror(to_send);
    sensor_data.data = sensor_data_raw;
    // int test[] = {1,2,3};
    // sensor_data.data = test;
    sensor_data.data_length = 6;
  sensor_data_pub.publish(&sensor_data);

  nh.spinOnce();
  delay(delayTime);
}

