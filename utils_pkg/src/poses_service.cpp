#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
#include <utils_pkg/poses.h>

bool get(utils_pkg::poses::Request &req, utils_pkg::poses::Response &res){
    
    geometry_msgs::PoseArray poseArray;

    geometry_msgs::Pose pose1;
    pose1.position.x = 2.73;
    pose1.position.y = 0.351;
    pose1.position.z = 0.0037;

    geometry_msgs::Pose pose2;
    pose2.position.x = 1.09;
    pose2.position.y = 4.87;
    pose2.position.z = 0.00434;

    geometry_msgs::Pose pose3;
    pose2.position.x = 8.51;
    pose2.position.y = 7.64;
    pose1.position.z = 0.00257;

    geometry_msgs::Pose pose4;
    pose2.position.x = 8.63;
    pose2.position.y = -2.39;
    pose1.position.z = 0.00229;

    poseArray.poses.push_back(pose1);
    poseArray.poses.push_back(pose2);
    poseArray.poses.push_back(pose3);
    poseArray.poses.push_back(pose4);

    res.poses = poseArray;
    
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc,argv, "Service_Node");
    ros::NodeHandle nh;

    ros::ServiceServer service = nh.advertiseService("get_poses", get);

    ros::spin();

    return 0;
}

