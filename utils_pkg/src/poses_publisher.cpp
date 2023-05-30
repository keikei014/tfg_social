#include "utils_pkg/poses_publisher.hpp"

Poses_Publisher::Poses_Publisher(){

    pub = nh.advertise<geometry_msgs::PoseArray>("/move_base_sequence/wayposes",1000);

    geometry_msgs::Pose pose1;
    pose1.position.x = 2.73;
    pose1.position.y = 0.351;
    pose1.position.z = 0.0037;
    pose1.orientation.x = 0.866;
    pose1.orientation.y = 0.00;
    pose1.orientation.z = 0.00;
    pose1.orientation.w = 0.50;

    geometry_msgs::Pose pose2;
    pose2.position.x = 1.09;
    pose2.position.y = 4.87;
    pose2.position.z = 0.00434;
    pose2.orientation.x = 0.866;
    pose2.orientation.y = 0.00;
    pose2.orientation.z = 0.00;
    pose2.orientation.w = 0.50;

    geometry_msgs::Pose pose3;
    pose3.position.x = 8.51;
    pose3.position.y = 7.64;
    pose3.position.z = 0.00257;
    pose3.orientation.x = 0.866;
    pose3.orientation.y = 0.00;
    pose3.orientation.z = 0.00;
    pose3.orientation.w = 0.50;

    geometry_msgs::Pose pose4;
    pose4.position.x = 8.63;
    pose4.position.y = -2.39;
    pose4.position.z = 0.00229;
    pose4.orientation.x = 0.866;
    pose4.orientation.y = 0.00;
    pose4.orientation.z = 0.00;
    pose4.orientation.w = 0.50;

    patrolPoses.poses.push_back(pose1);
    patrolPoses.poses.push_back(pose2);
    patrolPoses.poses.push_back(pose3);
    patrolPoses.poses.push_back(pose4);

}

void Poses_Publisher::Publish_Poses(){

    pub.publish(patrolPoses);
    
    ROS_INFO("SE HA INTENTADO PUBLICAR");

}

int main(int argc, char **argv){

    ros::init(argc,argv,"PosesPublisher");

    Poses_Publisher publisher_node;

    while(ros::ok){

        publisher_node.Publish_Poses();
        ROS_INFO("SE HA LLAMADO A LA FUNCIÓN DE PUBLICACIÓN");

        ros::spinOnce();

    }

    return 0;
}