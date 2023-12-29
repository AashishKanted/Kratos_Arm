#!/usr/bin/env python3

'''
Main module for GUI.
'''

import rospy
from std_msgs.msg import Int8
import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import (
     FigureCanvasTkAgg)
import threading
from datetime import datetime

from  gui_stuff.msg import *


# global coordinate varibles
sensor_x = []
co2_y = []
ch4_y = []
co_y = []

spectro_x = []
brad_y = []
chloro_y = []


# callback functions
def sensor_callback(data):
    global co2_y, ch4_y, co_y
    co2_y.append(data.co2)
    ch4_y.append(data.ch4)
    co_y.append(data.co)
    sensor_plot()

def ros_thread():
    # Publishers
    global flag_pub
    flag_pub = rospy.Publisher("/flag_topic", Int8, queue_size=1)
    
    # SUbscribers
    rospy.Subscriber("/sensors", sensor_msg, sensor_callback)
    rospy.spin()

def close_func():
    exit()

def sensor_plot():
    # Clear previous widgets
    for widget in can_frame_sensor.winfo_children():
        widget.destroy()

    # Generates x coordinate
    global sensor_x
    if len(sensor_x)==0:
        x = sensor_x.copy()
        sensor_x.append(0)
        
    elif len(sensor_x)==1:
        global sensor_start 
        sensor_start = datetime.now()
        sensor_x.append(round((datetime.now() - sensor_start).total_seconds()))
        x = sensor_x[1:]
    
    else:
        sensor_x.append(round((datetime.now() - sensor_start).total_seconds()))
        x = sensor_x[1:]
    
    # Clear previous plots
    ax1.cla()
    ax2.cla()
    ax3.cla()
    
    # New plots
    ax1.plot(x, co2_y, 'b^-')
    ax1.set_title('CO2 plot')
    ax1.set_xlabel('time')
    ax1.set_ylabel('ppm')
    
    ax2.plot(x, ch4_y, 'r^-')
    ax2.set_title('CH4 plot')
    ax2.set_xlabel('time')
    ax2.set_ylabel('ppm')
    
    ax3.plot(x, co_y, 'g^-')
    ax3.set_title('CO plot')
    ax3.set_xlabel('time')
    ax3.set_ylabel('ppm')

    plt.tight_layout()

    # Load plots into tkinter window inside canvas widget
    canvas_sensor = FigureCanvasTkAgg(figure=sensor_fig, master=can_frame_sensor)
    canvas_sensor.draw_idle()
    canvas_sensor.get_tk_widget().pack(padx=35, pady=35)
    
def sensor_button_click():
    flag_pub.publish(1)

rospy.init_node("LD_gui", anonymous=True)

# Set daemon as parameter as True
ros_t = threading.Thread(target=ros_thread, daemon=True)
ros_t.start()

# root window definition
main_win = tk.Tk()
main_win.title('Life Detection Window')
# main_win.geometry('1600x900')

main_win.protocol('WM_DELETE_WINDOW', close_func)

# Create different tabs and add titles
notebook = ttk.Notebook(main_win)

sensors = tk.Frame(notebook)
spectro = tk.Frame(notebook)
ml_box = tk.Frame(notebook)
panorama = tk.Frame(notebook)
digi_micro = tk.Frame(notebook)

notebook.add(sensors, text="Sensor readings")
notebook.add(spectro, text="Spectrometer")
notebook.add(ml_box, text="ML box")
notebook.add(panorama, text="Panorama")
notebook.add(digi_micro, text="Digital Microscope")

notebook.pack(expand=True, fill='both')

# sensor window
can_frame_sensor = tk.Frame(sensors)
can_frame_sensor.pack()
sensor_fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(16, 4))

# plots empty graph
sensor_plot()

# trigger for flag var
sensor_button = tk.Button(master=sensors, text='Publish trigger', command=sensor_button_click)
sensor_button.pack(padx=15, pady=25)


main_win.mainloop()
