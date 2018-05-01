// This code subscribes geometry_msgs/Twist with vel_l = vel_msg.linear.y and vel_r = vel_msg.linear.x
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "eklavya4_roboteq/SetSpeed.h"
#include "geometry_msgs/Twist.h"

#define mult_factor  1  // define mult_factor as multipling factor for vel_r and vel_l coming from joy


ros::NodeHandle *n;
ros::ServiceClient *client;

void commandVelCallback(geometry_msgs::Twist vel_msg) {

	eklavya4_roboteq::SetSpeed srv;
	
	int vel_r = int((vel_msg.linear.y)*mult_factor);
	ROS_INFO("Received right velocity : %d", vel_r);

	int vel_l = int((vel_msg.linear.x)*mult_factor);
	ROS_INFO("Received left velocity : %d", vel_l);
	
	//int scaled_val= msg->data * (1000.0/90);
	
	srv.request.v_r = vel_r;
	srv.request.v_l = vel_l;

	if (client->call(srv))
	{
		ROS_INFO("Velocity target set to : %ld", (long int)srv.request.v_r);
		ROS_INFO("Response : %ld", (long int)srv.response.code);
	}
	else
	{
		ROS_ERROR("Failed to call service set speed");
		ROS_INFO("Response : %ld", (long int)srv.response.code);
		return;
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "command_subscriber_motor_controller_client");
	
	ros::NodeHandle n1;
	n = &n1;
	
	ros::ServiceClient serviceClient = n->serviceClient<eklavya4_roboteq::SetSpeed>("motor_controller");
	
	client = &serviceClient;
    
    ros::Subscriber sub = n->subscribe("vel_manipulated", 10, commandVelCallback);
    
    ros::spin();
    
    return 0;
}
