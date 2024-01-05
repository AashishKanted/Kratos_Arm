#!/usr/bin/env python3

'''
Main module for GUI.
'''

import rospy
from std_msgs.msg import Int8
import tkinter as tk
from tkinter import (
    ttk, filedialog, messagebox)
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import (
     FigureCanvasTkAgg)
from matplotlib import style
import threading
from datetime import datetime
import csv

from  gui_stuff.msg import *

# global coordinate varibles
sensor_x = []
co2_y = []
ch4_y = []
co_y = []

spectro_x = []
brad_y = []
chloro_y = []


# backend functions
def sensor_callback(data):
    global co2_y, ch4_y, co_y
    co2_y.append(data.co2)
    ch4_y.append(data.ch4)
    co_y.append(data.co)
    sensor_plot()

def spectro_callback(data):
    global brad_y, chloro_y
    brad_y.append(data.brad)
    chloro_y.append(data.chloro)
    spectro_plot()

def ros_thread():
    # Publishers
    global flag_pub
    flag_pub = rospy.Publisher("/flag_topic", Int8, queue_size=1)
    
    # Subscribers
    rospy.Subscriber("/sensors", sensor_msg, sensor_callback)
    rospy.Subscriber("/spectrometer", spectro_msg, spectro_callback)
    rospy.spin()

def close_func():
    exit()


# frontend functions
def sensor_rec_plot():
    ax1.clear()
    ax2.clear()
    ax3.clear()
    
    ax1.plot(sensor_x, co2_y, 'b^-')
    ax1.set_title('CO2 plot')
    ax1.set_xlabel('time')
    ax1.set_ylabel('ppm')

    ax2.plot(sensor_x, ch4_y, 'r^-')
    ax2.set_title('CH4 plot')
    ax2.set_xlabel('time')
    ax2.set_ylabel('ppm')

    ax3.plot(sensor_x, co_y, 'g^-')
    ax3.set_title('CO plot')
    ax3.set_xlabel('time')
    ax3.set_ylabel('ppm')

def sensor_plot():
    global sensor_start
    if len(sensor_x)==0:
        sensor_start = datetime.now()
        sensor_x.append(0)
    else:
        # sensor_x.append(round((datetime.now() - sensor_start).total_seconds()))
        sensor_x.append(((datetime.now() - sensor_start).total_seconds()))
    
    sensor_rec_plot()
    
    canvas_sensor.draw_idle()
    
def spectro_rec_plot():
    ax4.clear()
    ax5.clear()
    
    ax4.plot(spectro_x, brad_y, 'b^-')
    ax4.set_title('Bradford assay')
    ax4.set_xlabel('wavelength')
    ax4.set_ylabel('absorbance')

    ax5.plot(spectro_x, chloro_y, 'r^-')
    ax5.set_title('Chlorophyll')
    ax5.set_xlabel('wavelength')
    ax5.set_ylabel('absorbance')

def spectro_plot():
    global spectro_start
    if len(spectro_x)==0:
        spectro_start = datetime.now()
        spectro_x.append(0)
    else:
        spectro_x.append((datetime.now() - spectro_start).total_seconds())
    
    spectro_rec_plot()
    
    canvas_spectro.draw_idle()

# button click functions
def sensor_button_click():
    flag_pub.publish(1)

def spectro_button_click():
    flag_pub.publish(2)
    
def sensor_save():
    file_path = filedialog.asksaveasfilename()
    if file_path:
        with open(file_path, mode='w', newline='') as csv_file:
            writer = csv.writer(csv_file)
            writer.writerow(sensor_x)
            writer.writerow(co2_y)
            writer.writerow(ch4_y)
            writer.writerow(co_y)
            
    sensor_x.clear()
    co2_y.clear()
    ch4_y.clear()
    co_y.clear()
    
    sensor_rec_plot()
    canvas_sensor.draw_idle()

    messagebox.showinfo(f"Save info", "Your file has been saved")

def spectro_save():
    file_path = filedialog.asksaveasfilename()
    if file_path:
        with open(file_path, mode='w', newline='') as csv_file:
            data = [brad_y, chloro_y]
            
            writer = csv.writer(csv_file)
            writer.writerow(spectro_x)
            writer.writerow(brad_y)
            writer.writerow(chloro_y)
            
    spectro_x.clear()
    brad_y.clear()
    chloro_y.clear()
    
    spectro_rec_plot()
    canvas_spectro.draw_idle()

    messagebox.showinfo(f"Save info", "Your file has been saved")

rospy.init_node("LD_gui", anonymous=True)

# Set daemon as parameter as True
ros_t = threading.Thread(target=ros_thread, daemon=True)
ros_t.start()

# root window definition
main_win = tk.Tk()
main_win.title('Life Detection Window')
# main_win.geometry('1600x900')

style.use("ggplot")

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

sensor_fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(16, 4))

sensor_rec_plot()

canvas_sensor = FigureCanvasTkAgg(figure=sensor_fig, master=sensors)
canvas_sensor.draw_idle()
canvas_sensor.get_tk_widget().pack(padx=35, pady=35)

sensor_button = tk.Button(master=sensors, text='Publish trigger', command=sensor_button_click)
sensor_button.pack(padx=15, pady=25)

save_sensor = tk.Button(master=sensors, text="Save values", command=sensor_save)
save_sensor.pack(padx=15, pady=25)

# spectro window
spectro_fig, (ax4, ax5) = plt.subplots(1, 2, figsize=(16, 4))

spectro_rec_plot()

canvas_spectro = FigureCanvasTkAgg(figure=spectro_fig, master=spectro)
canvas_spectro.draw_idle()
canvas_spectro.get_tk_widget().pack(padx=35, pady=35)

spectro_button = tk.Button(master=spectro, text='Publish trigger', command=spectro_button_click)
spectro_button.pack(padx=15, pady=25)

save_spectro = tk.Button(master=spectro, text="Save values", command=spectro_save)
save_spectro.pack(padx=15, pady=25)

plt.tight_layout()


main_win.mainloop()
