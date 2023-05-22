#include "utils_pkg/poses_publisher.hpp"

Poses_Publisher::Poses_Publisher(){

    pub = nh.advertise<geometry_msgs::PoseArray>("/move_base_sequence/wayposes",1000);

    client = nh.serviceClient<utils_pkg::poses>("get_poses");

}

ros::ServiceClient Poses_Publisher::get_client(){
    return client;
}

void Poses_Publisher::Publish_Poses(geometry_msgs::PoseArray poses){

    pub.publish(poses);

}

int main(int argc, char **argv){

    ros::init(argc,argv,"PosesPublisher");

    Poses_Publisher publisher_node;

    utils_pkg::poses poses_srv;

    if (publisher_node.get_client().call(poses_srv)){

        while(ros::ok){
            publisher_node.Publish_Poses(poses_srv.response.poses);
            ROS_INFO("SE HA LLAMADO CON EXITO AL SERVICIO Y SE HA INTENTADO PUBLICAR");
            ros::spinOnce();
        }


    }

    return 0;
}