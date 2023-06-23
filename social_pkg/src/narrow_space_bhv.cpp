#include "social_pkg/narrow_space_bhv.hpp"

Narrow_Space_Bhv::Narrow_Space_Bhv(){
    pub = nh.advertise<int>("narrow_space",1000);
    sub = nh.subscribe("laser_scan", 1000, &Narrow_Space_Bhv::laserCallback, this);
}

void Narrow_Space_Bhv::laserCallback(const senosr_msgs::LaserScan::ConstPtr& msg){
    int n_measures = msg->ranges.size();

    publish_NS(n_measures);
}

void Narrow_Space_Bhv::publish_NS(int is_ns){
    pub.publish(is_ns);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "narrow_space_bhv");

    Narrow_Space_Bhv node;

    //ros::Rate rate(2);

    while(ros::ok()){
        ros::spin();
        //rate.sleep();
    }
}