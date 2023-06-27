#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "boost/format.hpp"

class Narrow_Space_Bhv{
    public:

        Narrow_Space_Bhv();

        void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

        void publish_NS(std_msgs::String is_ns);

    private:

        ros::NodeHandle nh;

        ros::Subscriber sub;
        
        ros::Publisher pub;
};