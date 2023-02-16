# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'publish_buttons.ui'
#
# Created by: PyQt5 UI code generator 5.14.1
#
# WARNING! All changes made in this file will be lost!

import rospy
from std_msgs.msg import Float32
from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        
        rospy.init_node("button_publisher")

        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(795, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.splitter_5 = QtWidgets.QSplitter(self.centralwidget)
        self.splitter_5.setGeometry(QtCore.QRect(0, 0, 791, 551))
        self.splitter_5.setOrientation(QtCore.Qt.Vertical)
        self.splitter_5.setObjectName("splitter_5")
        self.splitter_4 = QtWidgets.QSplitter(self.splitter_5)
        self.splitter_4.setOrientation(QtCore.Qt.Horizontal)
        self.splitter_4.setObjectName("splitter_4")
        self.splitter_3 = QtWidgets.QSplitter(self.splitter_4)
        self.splitter_3.setOrientation(QtCore.Qt.Vertical)
        self.splitter_3.setObjectName("splitter_3")
        self.splitter_2 = QtWidgets.QSplitter(self.splitter_3)
        self.splitter_2.setOrientation(QtCore.Qt.Horizontal)
        self.splitter_2.setObjectName("splitter_2")
        self.pushButton = QtWidgets.QPushButton(self.splitter_2)
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(self.splitter_2)
        self.pushButton_2.setObjectName("pushButton_2")
        self.splitter = QtWidgets.QSplitter(self.splitter_3)
        self.splitter.setOrientation(QtCore.Qt.Horizontal)
        self.splitter.setObjectName("splitter")
        self.pushButton_3 = QtWidgets.QPushButton(self.splitter)
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_4 = QtWidgets.QPushButton(self.splitter)
        self.pushButton_4.setObjectName("pushButton_4")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 795, 22))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.msg = Float32()
        self.msg.data = 1.698

        self.pub = None
       
        self.pushButton.clicked.connect(self.b1)
        self.pushButton_2.clicked.connect(self.b2)
        self.pushButton_3.clicked.connect(self.b3)
        self.pushButton_4.clicked.connect(self.b4)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pushButton.setText(_translate("MainWindow", "1"))
        self.pushButton_2.setText(_translate("MainWindow", "2"))
        self.pushButton_3.setText(_translate("MainWindow", "3"))
        self.pushButton_4.setText(_translate("MainWindow", "4"))
    
    def b1(self):
        self.pub = rospy.Publisher("topic1",Float32,queue_size=10)
        self.pub.publish(self.msg)
    
    def b2(self):
        self.pub = rospy.Publisher("topic2",Float32,queue_size=10)
        self.pub.publish(self.msg)

    def b3(self):
        self.pub = rospy.Publisher("topic3",Float32,queue_size=10)
        self.pub.publish(self.msg)

    def b4(self):
        self.pub = rospy.Publisher("topic4",Float32,queue_size=10)
        self.pub.publish(self.msg)





if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
