//Author: Yonah Elorza
//This program subscribes to the mbed pub and shows its messages on the screen

//This header defines the standard ROS classes.
#include <ros/ros.h>
#include <telebot/Mobility.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "SimpleSerial.h"

void dataMessageRecieved(const telebot::Mobility msg) {
     
	std::ostringstream yax;
	std::ostringstream xax;	
	std::ostringstream b1;
	std::ostringstream b2;
	std::ostringstream b3;
	
	double nxax = (roundf(100.0* (static_cast <double>((static_cast <double>(msg.xax)-512.00)*static_cast <double>((1.00/512.00))))))/100.0;
        double nyax = (roundf(100.0*(static_cast <double>((static_cast <double>(msg.yax)-512.00)*static_cast <double>((1.00/512.00))))))/100.0;

	xax << static_cast<float>(nxax);
	yax << static_cast<float>(nyax);
	b1 << static_cast<int>(msg.b1);
	b2 << static_cast<int>(msg.b2);
	b3 << static_cast<int>(msg.b3);
	
	std::string data = std::string() + yax.str() + ' ' + xax.str() + ' ' + b1.str() + ' ' + b2.str() + ' ' + b3.str();	
	ROS_INFO_STREAM(data);
        //SimpleSerial serial("/dev/mbed",57600);

        //serial.writeString(data);
	yax.str("");
	xax.str("");
	b1.str("");
	b2.str("");
        b3.str("");

	yax.clear();
	xax.clear();
	b1.clear();
	b2.clear();
	b3.clear();
	
	
}

int main(int argc, char **argv) {
     //Initialize the ROS system and become a node
     ros::init(argc, argv, "mobility_sub");
     ros::NodeHandle nh;

     //Create a subscriber object
     ros::Subscriber sub = nh.subscribe("mobility_sys", 1000, &dataMessageRecieved);

     //Let ROS take over
     ros::spin();
     
}
