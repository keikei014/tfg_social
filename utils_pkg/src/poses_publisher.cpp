#include "utils_pkg/poses_publisher.hpp"

Poses_Publisher::Poses_Publisher(){

    pub = nh.advertise<geometry_msgs::PoseArray>("/move_base_sequence/wayposes",1000);

    client = nh.serviceClient<utils_pkg::poses>("get_poses");

}

ros::ServiceClient Poses_Publisher::get_client(){
    return client;
}

void Poses_Publisher::Publish_Poses(){

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
    pose3.position.x = 8.51;
    pose3.position.y = 7.64;
    pose3.position.z = 0.00257;

    geometry_msgs::Pose pose4;
    pose4.position.x = 8.63;
    pose4.position.y = -2.39;
    pose4.position.z = 0.00229;

    poseArray.poses.push_back(pose1);
    poseArray.poses.push_back(pose2);
    poseArray.poses.push_back(pose3);
    poseArray.poses.push_back(pose4);

    pub.publish(poseArray);
    
    ROS_INFO("SE HA INTENTADO PUBLICAR");

}

int main(int argc, char **argv){

    ros::init(argc,argv,"PosesPublisher");

    Poses_Publisher publisher_node;

    //utils_pkg::poses poses_srv;

    while(ros::ok){

        publisher_node.Publish_Poses();
        ROS_INFO("SE HA LLAMADO A LA FUNCIÓN DE PUBLICACIÓN");

        ros::spinOnce();

    }

    return 0;
}