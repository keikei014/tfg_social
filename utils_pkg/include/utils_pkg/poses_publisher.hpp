#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"

class Poses_Publisher{
    public:

        Poses_Publisher();

        void Publish_Poses();

    private:

        geometry_msgs::PoseArray patrolPoses;

        ros::NodeHandle nh;

        ros::Publisher pub;

};