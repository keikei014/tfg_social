#include "social_pkg/people_detect.hpp"

People_Detect::People_Detect(){
    pub = nh.advertise<std_msgs::String>("presence",1000);
    detection = true;
}

void People_Detect::set_detection(){
    detection = !detection;
}

bool People_Detect::get_detection(){
    return detection;
}

void People_Detect::publish_detection(){

    if(get_detection()){
        std_msgs::String message;
        message.data = "true";
        pub.publish(message);
    }

}

int main(int argc, char** argv){
    ros::init(argc,argv,"people_detection");

    People_Detect node;

    node.publish_detection();

    ros::spinOnce();

    return 0;
}