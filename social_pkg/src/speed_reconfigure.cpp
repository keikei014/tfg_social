#include "social_pkg/speed_reconfigure.hpp"

Speed_Reconfigure::Speed_Reconfigure(){
    detection_sub = nh.subscribe("people_detection", 1000, &Speed_Reconfigure::detectionCallback, this);
    odom_sub = nh.subscribe("base_pose_ground_truth", 1000, &Speed_Reconfigure::odomCallback, this);
}

geometry_msgs::Pose Speed_Reconfigure::get_robotPose(){
    return robotPose;
}

void Speed_Reconfigure::set_robotPose(geometry_msgs::Pose pose){
    robotPose = pose;
}

void Speed_Reconfigure::odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    set_robotPose(msg->pose.pose);
}

void Speed_Reconfigure::detectionCallback(const geometry_msgs::PoseArray::ConstPtr& msg){

    geometry_msgs::Pose robot = get_robotPose();

    double distance;

    double min_distance = 4;

    for(int i = 0; i < msg->poses.size(); ++i){
        distance = sqrt(pow(robot.position.x - msg->poses[i].position.x,2) + 
                        pow(robot.position.y - msg->poses[i].position.y,2) + 
                        pow(robot.position.z - msg->poses[i].position.z,2));

        if(distance < min_distance){
            min_distance = distance;
        }
    }

    double speed = 0.1*min_distance;

    string message = str( boost::format("rosrun dynamic_reconfigure dynparam set /move_base/DWAPlannerROS max_vel_trans %d") % speed );

    system(message.c_str());

}

int main(int argc, char** argv){

    ros::init(argc, argv, "reconfigure_speed");

    Speed_Reconfigure node;

    ros::Rate rate(2);

    while(ros::ok()){
        ros::spin();
        rate.sleep();
    }

}