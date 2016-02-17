#include <ros/ros.h>
#include "serialib.h"
#include "std_msgs/String.h"
#include <sstream>
#include <string>
#include <vector>

#if defined (_WIN32) || defined( _WIN64)
#define         DEVICE_PORT             "COM9"                               // COM1 for windows
#endif

#ifdef __linux__
#define         DEVICE_PORT             "/dev/ttyO1"                         // ttyS0 for linux
#endif


using namespace std;

int main(int argc, char **argv)
{
	serialib LS;                                                            // Object of the serialib class
    int Ret;                                                               // Used for return values

	
	Ret = LS.Open(DEVICE_PORT,115200); 
	if (Ret!=1) {                                                           // If an error occured...
        printf ("Error while opening port. Permission problem ?\n");        // ... display a message ...
        ROS_INFO("Error while opening port");
		return Ret;                                                         // ... quit the application
    }
	
	
	ros::init(argc, argv, "Run");
	ros::NodeHandle nh;
	
	//ros::Publisher data_pub = nh.advertise<std_msgs::String>("Run", 1000);
	
	ros::Rate loop_rate(0.5);//loop at 66Hz   1/15ms = 66.7 = 66
		
	while(ros::ok()) 
	{
		LS.WriteChar(128);
		LS.WriteChar(132);
		LS.WriteChar(146);//send command to roomba to send back data
		LS.WriteChar(0);
		LS.WriteChar(100);
		LS.WriteChar(256);
		LS.WriteChar(156);
		
		LS.WriteChar(146);
		LS.WriteChar(256);
		LS.WriteChar(156);
		LS.WriteChar(0);
		LS.WriteChar(100);
		
	/*	std_msgs::String msg; 
		std::stringstream ss;
		ss << "hello world ";
		msg.data = ss.str();
		data_pub.publish(msg);
		*/
		ros::spinOnce();
		loop_rate.sleep();
	}
}
