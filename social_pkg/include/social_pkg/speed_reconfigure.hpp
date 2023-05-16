#include "ros/ros.h"
#include "social_pkg/configure_speed.h"
#include <stdlib.h>
#include "std_msgs/String.h"

class Speed_Reconfigure{
    public:

        Speed_Reconfigure();

        void detectionCallback(const std_msgs::String::ConstPtr &msg);

    private:

        ros::NodeHandle nh;

        ros::Subscriber sub;

        ros::ServiceClient client;

        social_pkg::configure_speed srv;

};