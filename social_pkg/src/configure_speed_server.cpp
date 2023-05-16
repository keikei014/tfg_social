#include "social_pkg/configure_speed_server.hpp"

bool configure(social_pkg::configure_speed::Request &req,
               social_pkg::configure_speed::Response &res)
{
        if(req.detected){
            ROS_INFO("PEOPLE DETECTED. REDUCING SPEED.");
            system("rosrun dynamic_reconfigure dynparam set /move_base/DWAPlannerROS max_vel_trans 0.25");
        }
        else{
            ROS_INFO("NO PEOPLE DETECTED. RETURNING TO DEFAULT SPEED.");
            system("rosrun dynamic_reconfigure dynparam set /move_base/DWAPlannerROS max_vel_trans 0.55");
        }

        res.state = true;

        return res.state;
}

Configure_Speed_Server::Configure_Speed_Server(){
    service = nh.advertiseService("configure_speed", configure);
}


int main(int argc, char **argv){

    ros::init(argc, argv, "configure_speed_server");

    Configure_Speed_Server node;

    ros::spin();

    return 0;

}