#include "social_pkg/speed_reconfigure.hpp"

Speed_Reconfigure::Speed_Reconfigure(){
    sub = nh.subscribe("presence", 1000, &Speed_Reconfigure::detectionCallback, this);
}

void Speed_Reconfigure::detectionCallback(const std_msgs::String::ConstPtr& msg){

    const char* message = msg->data.c_str();

    ROS_INFO(message);

    const char* check = "true";

    if (strcmp(message,check)){
        srv.request.detected = true;
    }
    else{
        srv.request.detected = false;
    }

    if(client.call(srv)){
        ROS_INFO("SPEED WAS SUCCESSFULLY RECONFIGURED.");
    }
    else{
        ROS_ERROR("Failed to call service configure_speed.");
    }

}

int main(int argc, char** argv){

    ros::init(argc, argv, "reconfigure_speed");

    Speed_Reconfigure node;

    ros::spin();

}