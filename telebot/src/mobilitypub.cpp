//Author: Yonah Elorza
//This program publishes motor coordinates to the mbed, which updates the mobility motors

#include <ros/ros.h>
#include <telebot/Mobility.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "SimpleSerial.h"
#include <string>

using namespace std;

int main(int argc, char **argv) {
     ros::init(argc, argv, "mobility_pub");	

     ros::NodeHandle nh;

     ros::Publisher pub = nh.advertise<telebot::Mobility>("mobility_sys", 1000);

     telebot::Mobility msg;	
     
     ros::Rate loop_rate(10);

     SimpleSerial serial("/dev/ttyUSB0",57600);

     while(ros::ok()){

     std:string motor = serial.readLine();

     int temp1 = 0;
     int temp2 = 0;
     int temp3 = 0;
     int temp4 = 0;
	 
     std::string b1 = "";
     std::string yax = "";
     std::string xax = "";
     std::string b3 = "";
     std::string b2 = "";

     for(int i=0; i < motor.length(); i++){
           if(temp3 != 0) {
                if (motor[i] == ' '){
                     temp4 = i;
                }
           }

           if(temp2 != 0) {
                if (motor[i] == ' '){
                     temp3 = i;
                }
           }

           else if(temp1 != 0){
                if (motor[i] == ' '){
                     temp2 = i;
                }
           }

	   else{
                if (motor[i] == ' '){
                     temp1 = i;
                }
           }
     }

     for(int i = 0; i < temp1; i++){
          yax+=motor[i];
     } 

     for(int i = temp1 + 1; i < temp2; i++){
          xax+=motor[i];
     }

     for(int i = temp2 + 1; i < temp3; i++){
          b1+=motor[i];
     }  

     for(int i = temp3 + 1; i < temp4; i++){
          b2+=motor[i];
     } 

     for(int i = temp4 + 1; i < motor.length(); i++){
          b3+=motor[i];
     }

     msg.b1 = atoi(b1.c_str());
     msg.yax = atoi(yax.c_str());
     msg.xax = atoi(xax.c_str());
     msg.b3 = atoi(b3.c_str());
     msg.b2 = atoi(b2.c_str());


     ROS_INFO_STREAM(yax + " " + xax + " " + b1 + " " + b2 + " " + b3);

     pub.publish(msg);

     ros::spinOnce();

     loop_rate.sleep();

     }
}
