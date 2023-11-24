#!/usr/bin/env python3

import rospy
from std_msgs.msg import  Int16, Float32MultiArray, Float32, String


flag = 1

rospy.init_node("fox_test", anonymous=True)

# CO2 publishers
co2_y = rospy.Publisher("/co2_y", Float32MultiArray, queue_size=1)
co2_x = rospy.Publisher("/co2_x", Float32MultiArray, queue_size=1)

# Methane publishers
ch4_y = rospy.Publisher("/ch4_y", Float32MultiArray, queue_size=1)
ch4_x = rospy.Publisher("/ch4_x", Float32MultiArray, queue_size=1)

# Carbon monoxide publishers
co_y = rospy.Publisher("/co_y", Float32MultiArray, queue_size=1)
co_x = rospy.Publisher("/co_x", Float32MultiArray, queue_size=1)

# Bradford assay publishers
brad_y = rospy.Publisher("/brad_y", Float32MultiArray, queue_size=1)
brad_x = rospy.Publisher("/brad_x", Float32MultiArray, queue_size=1)

# Chlorophyll publishers
chloro_y = rospy.Publisher("/chloro_y", Float32MultiArray, queue_size=1)
chloro_x = rospy.Publisher("/chloro_x", Float32MultiArray, queue_size=1)

ml_pub = rospy.Publisher("/ml", String, queue_size=1)


y_val = Float32MultiArray()
x_val = Float32MultiArray()


co2_sensor = {
    0: 600,
    5: 570,
    10: 580,
    15: 610,
    20: 660,
    25: 690,
    30: 680
}


ch4_sensor = {
    0: 1.88,
    5: 1.87,
    10: 1.89,
    15: 1.87,
    20: 1.86,
    25: 1.87,
    30: 1.88
}


co_sensor = {
    0: 5.1,
    5: 5.3,
    10: 5.1,
    15: 5.2,
    20: 5.1,
    25: 5.4,
    30: 5.3
}


bradford_assay = {
    410: 0.08,
    435: 0.04,
    460: 0.005,
    485: 0.008,
    510: 0.015,
    535: 0.03,
    560: 0.08,
    585: 0.15,
    610: 0.241,
    635: 0.19,
    680: 0.11,
    705: 0.07
}


chlorophyll = {
    410: 0.3,
    435: 0.25,
    460: 0.2,
    485: 0.18,
    510: 0.15,
    535: 0.12,
    560: 0.14,
    585: 0.16,
    610: 0.3,
    635: 0.4,
    680: 0.2,
    705: 0.1
}


'''
x_val.data = [1,2,3,4,5]
y_val.data = [1,3,4,2,0]
'''

str_inp = """Running on GPU...

Total number of images for site 1 = 50
Total breakdown for site 1:
Basalt: 0.211579004590509
Conglomerate: 0.154108799183155
Coprolite: 0.064276531761994
Dolomite: 0.016016354133365
Fossil: 0.053301881200145
Granite: 0.131860339753656
Limestone: 0.965734889819681
Obsidian: 0.189001124311103
Sandstone: 0.071260748078191
Shale: 0.044254417612316

Final Prediction: Limestone"""

while not rospy.is_shutdown():
    if (flag):
        try:
            for i in range(15):
                # CO2 publishers
                co2_y.publish(Float32MultiArray(data=list(co2_sensor.values())[:i]))
                co2_x.publish(Float32MultiArray(data=list(co2_sensor.keys())[:i]))

                # Methane publishers
                ch4_y.publish(Float32MultiArray(data=list(ch4_sensor.values())[:i]))
                ch4_x.publish(Float32MultiArray(data=list(ch4_sensor.keys())[:i]))

                # Carbon monoxide publishers
                co_y.publish(Float32MultiArray(data=list(co_sensor.values())[:i]))
                co_x.publish(Float32MultiArray(data=list(co_sensor.keys())[:i]))

                # Bradford assay publishers
                brad_y.publish(Float32MultiArray(data=list(bradford_assay.values())[:i]))
                brad_x.publish(Float32MultiArray(data=list(bradford_assay.keys())[:i]))

                # Chlorophyll publishers
                chloro_y.publish(Float32MultiArray(data=list(chlorophyll.values())[:i]))
                chloro_x.publish(Float32MultiArray(data=list(chlorophyll.keys())[:i]))
                
                rospy.sleep(1)
            
            if (i==14):
                flag = 0
                break
        except:
            pass
    
    # ml_pub.publish(str_inp)
    
rospy.spin()
