#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
using namespace std;
#define d 0.5
#define r 0.10 // the radius in m 

//name of node= "twist"
//takes left and right side velocities (from encoder) in vel_msg by subscribing to topic "in_data"
//gives linear and angular velocity of the bot in out_msg by publishing to topic "out_data"
// define D as width of bot

/********CHECK IF ANGULAR VELOCITY IS NEGATIVE**************/

 float vr, vl;
 float v, omega;
 geometry_msgs::Twist vel_msg;
 geometry_msgs::Twist out_msg;

void callback (geometry_msgs::Twist vel_msg)
{
 v = vel_msg.linear.x;
 omega = vel_msg.angular.z;

 vl = (2*v - d*omega)/2;
 vr = (2*v + d*omega)/2;

 out_msg.linear.y = vr*1000*60/(2*3.1415*175*r);
 out_msg.linear.x = vl*1000*60/(2*3.1415*175*r);
}

int main (int argc, char **argv)
{
 ros::init(argc, argv, "convert");
 ros::NodeHandle nh;
 ros::Subscriber sub = nh.subscribe("cmd_vel",100, &callback);
 ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("vel_manipulated",100);
 
 vel_msg.linear.z=0;
 vel_msg.angular.x=0;
 vel_msg.angular.y=0;
 vel_msg.angular.z=0;
 
 out_msg.linear.y=0;
 out_msg.linear.z=0;
 out_msg.angular.x=0;
 out_msg.angular.y=0;

 while (ros::ok()){
 pub.publish(out_msg);
 ROS_INFO("Left Velocity = %f, Right velocity = %f",vr, vl);
 ros::spinOnce();
 }
 return 0;
}