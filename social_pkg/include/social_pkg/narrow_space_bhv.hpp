#include "ros/ros.h"
#include "sensor_msgs/LaserScan"

class Narrow_Space_Bhv{
    public:

        Narrow_Space_Bhv();

        void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

        void publish_NS(int is_ns);

    private:

        ros::NodeHandle nh;

        ros::Subscriber sub;
        
        ros::Publisher pub;
};