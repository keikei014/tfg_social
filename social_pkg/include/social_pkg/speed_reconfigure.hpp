#include "ros/ros.h"
#include <stdlib.h>
#include <cmath>
#include "boost/format.hpp"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
#include "nav_msgs/Odometry.h"
using namespace std;

class Speed_Reconfigure{
    public:

        Speed_Reconfigure();

        void detectionCallback(const geometry_msgs::PoseArray::ConstPtr &msg);

        void gtCallback(const nav_msgs::Odometry::ConstPtr &msg);

        geometry_msgs::Pose get_robotPose();

        void set_robotPose(geometry_msgs::Pose pose);

    private:

        geometry_msgs::Pose robotPose;

        ros::NodeHandle nh;

        ros::Publisher info_pub;

        ros::Subscriber detection_sub;

        ros::Subscriber gt_sub;

};