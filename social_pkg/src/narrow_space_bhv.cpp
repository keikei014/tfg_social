#include "social_pkg/narrow_space_bhv.hpp"

Narrow_Space_Bhv::Narrow_Space_Bhv(){
    pub = nh.advertise<std_msgs::String>("/narrow_space",1000);
    sub = nh.subscribe("laser_scan", 1000, &Narrow_Space_Bhv::laserCallback, this);
}

void Narrow_Space_Bhv::laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg){

    std_msgs::String message;

    double accumulate = 0;
    double narrow_limit = 2.2;

    for( int i = 70; i < 100; i++ ){
        accumulate += msg->ranges[i];
    }

    for( int i = 582; i < 612; i++){
        accumulate += msg->ranges[i];
    }

    double avg_distance = accumulate/60;

    if( avg_distance < narrow_limit){
        message.data = "NARROW SPACE";
    }
    else{
        message.data = "WIDE SPACE";
    }

    publish_NS(message);

}

void Narrow_Space_Bhv::publish_NS(std_msgs::String is_ns){
    pub.publish(is_ns);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "narrow_space_bhv");

    Narrow_Space_Bhv node;

    ros::Rate rate(2);

    while(ros::ok()){
        ros::spin();
        rate.sleep();
    }
}