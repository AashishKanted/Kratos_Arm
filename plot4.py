# importing various libraries
import sys
from PyQt5.QtWidgets import QDialog, QApplication, QPushButton, QVBoxLayout
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
import matplotlib.pyplot as plt
import random
import pandas as pd


class Window(QDialog):
# constructor
    def __init__(self, parent=None):
        super(Window, self).__init__(parent)

        # a figure instance to plot on
        self.figure = plt.figure()

        # this is the Canvas Widget that
        # displays the 'figure'it takes the
        # 'figure' instance as a parameter to __init__
        self.canvas = FigureCanvas(self.figure)

        # this is the Navigation widget
        # it takes the Canvas widget and a parent
        self.toolbar = NavigationToolbar(self.canvas, self)

        # Just some button connected to 'plot' method
        self.button = QPushButton('Plot')
        
        # adding action to the button
        self.button.clicked.connect(self.plot)

        # creating a Vertical Box layout
        layout = QVBoxLayout()
        
        # adding tool bar to the layout
        layout.addWidget(self.toolbar)
        
        # adding canvas to the layout
        layout.addWidget(self.canvas)
        
        # adding push button to the layout
        layout.addWidget(self.button)
        
        # setting layout to the main window
        self.setLayout(layout)

    def plot(self):
        df1 = pd.read_csv('uno-data.csv',sep=',')
        print(df1[' Visible'])
        
        self.figure.clear()
        ax = self.figure.add_subplot(221)
        ax2 = self.figure.add_subplot(222)
        ax3 = self.figure.add_subplot(223)
        ax4 = self.figure.add_subplot(224)

        ax.plot(df1[' Visible'], df1[' UV'])
        ax2.plot(df1[' Visible'], df1[' IR'])
        ax3.plot(df1[' IR'], df1[' UV'])
        ax4.plot(df1[' IR'], df1[' Visible'])
        self.canvas.draw()
    
# driver code
if __name__ == '__main__':
	
	# creating apyqt5 application
	app = QApplication(sys.argv)

	# creating a window object
	main = Window()
	
	# showing the window
	main.show()

	# loop
	sys.exit(app.exec_())
