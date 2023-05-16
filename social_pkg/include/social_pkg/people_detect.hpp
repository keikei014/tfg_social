#include "ros/ros.h"
#include "std_msgs/String.h"

class People_Detect{
    public:

        People_Detect();

        void publish_detection();

        void set_detection();

        bool get_detection();

    private:

        bool detection;

        ros::NodeHandle nh;

        ros::Publisher pub;

};