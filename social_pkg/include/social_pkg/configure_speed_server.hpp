#include "ros/ros.h"
#include "social_pkg/configure_speed.h"

class Configure_Speed_Server{
    public:

        Configure_Speed_Server();

    private:

        ros::NodeHandle nh;

        ros::ServiceServer service;

};