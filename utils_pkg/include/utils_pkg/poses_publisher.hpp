#include "ros/ros.h"
#include "utils_pkg/poses.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"

class Poses_Publisher{
    public:

        Poses_Publisher();

        void Publish_Poses();

        ros::ServiceClient get_client();

        geometry_msgs::PoseArray poses;

    private:

        ros::NodeHandle nh;

        ros::Publisher pub;

        ros::ServiceClient client;

        utils_pkg::poses poses_srv;

};