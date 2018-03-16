/*
subscribing from topic "/joy" via controller_sub
publishing to topic "cmd_vel" via controller_pub
node name - "joy_test"
Y-linear x incremented by 0.1
A-linear x decremented by 0.1
X-angular z incremented by 0.1
B-angular z decremented by 0.1
LB- emergency stop
RB- all velocity zero
*/
#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
using namespace std;




ros::Publisher controller_pub;
ros::Subscriber controller_sub;
geometry_msgs::Twist vel_msg;

void controller_callback(const sensor_msgs::Joy::ConstPtr& msg);

int main(int argc,char **argv)
{

	ros::init(argc, argv, "joy_test");

	ros::NodeHandle n;

	
	controller_pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1000);

	controller_sub = n.subscribe("/joy",1000,controller_callback);

	ros::Rate loop_rate(10.0);
	
	vel_msg.linear.x=0;
	vel_msg.angular.z=0;
	vel_msg.linear.y=0;
	vel_msg.linear.z=0;
	vel_msg.angular.x=0;
	vel_msg.angular.y=0;
	
	
      
	controller_pub.publish(vel_msg);
	
	loop_rate.sleep();
	
	while(ros::ok())
	{
	controller_pub.publish(vel_msg);
	ros::spinOnce();
	ROS_INFO("%f", vel_msg.linear.x);
	}
	return 0;

}

void controller_callback(const sensor_msgs::Joy::ConstPtr& msg)
{
	ROS_INFO("%f", vel_msg.linear.x);

	if(msg->buttons[3]==1)
	(vel_msg.linear.x)=vel_msg.linear.x+0.1;
	
	if(msg->buttons[0]==1)
	(vel_msg.linear.x)=vel_msg.linear.x-0.1;

	if(msg->buttons[1]==1)
	(vel_msg.angular.z)=vel_msg.angular.z+0.1;

	if(msg->buttons[2]==1)
	(vel_msg.angular.z)=vel_msg.angular.z-0.1;

	if(msg->buttons[5]==1)
	{
	vel_msg.angular.z=0;
	vel_msg.linear.x=0;
	}
	
	if(msg->buttons[4]==1)
	{
	vel_msg.angular.z=0;
	vel_msg.linear.x=0;
	ROS_INFO("Emergency Stop");
	
	}
	
	//controller_pub.publish(vel_msg);

	//ROS_INFO("%f", vel_msg.linear.x);


}

