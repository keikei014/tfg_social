#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"
#include "boost/format.hpp"
#include <algorithm>

class Narrow_Space_Bhv{
    public:

        Narrow_Space_Bhv();

        void set_Narrow(bool narrow);

        bool get_Narrow();

        void set_SafetyGoal(geometry_msgs::Pose goal);

        geometry_msgs::Pose get_SafetyGoal();

        void set_robotPose(geometry_msgs::Pose pose);

        geometry_msgs::Pose get_robotPose();

        void publish_NS(std_msgs::String is_ns);

        void publish_goal(geometry_msgs::Pose goal);

        void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

        void pplCallback(const geometry_msgs::PoseArray::ConstPtr& msg);

        void gtCallback(const nav_msgs::Odometry::ConstPtr& msg);

    private:

        bool _narrow = false;

        geometry_msgs::Pose safety_goal;

        geometry_msgs::Pose robotPose;

        ros::NodeHandle nh;
     
        ros::Publisher message_pub;

        ros::Publisher goal_pub;
        
        ros::Subscriber gt_sub;

        ros::Subscriber laser_sub;

        ros::Subscriber ppl_sub;

};