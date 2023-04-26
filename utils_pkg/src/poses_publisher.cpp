#include "utils_pkg/poses_publisher.hpp"

Poses_Publisher::Poses_Publisher(){

    pub = nh.advertise<geometry_msgs::PoseArray>("/move_base_sequence/wayposes",1000);

    client = nh.serviceClient<utils_pkg::poses>("get_poses");

}

void Poses_Publisher::Publish_Poses(geometry_msgs::PoseArray poses){

    pub.publish(poses);

}

int main(int argc, char **argv){

    ros::init(argc,argv,"PosesPublisher");

    Poses_Publisher publisher_node;

    utils_pkg::poses poses_srv;

    

    if (client.call(poses_srv)){

        publisher_node.Publish_Poses(poses_srv.response.poses);

    }

    return 0;
}