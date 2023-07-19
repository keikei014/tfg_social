#include "social_pkg/narrow_space_bhv.hpp"

Narrow_Space_Bhv::Narrow_Space_Bhv(){

    // publisher initializers
    message_pub = nh.advertise<std_msgs::String>("/narrow_info",1000);
    goal_pub = nh.advertise<geometry_msgs::Pose>("/move_base_simple/goal", 1000);

    // subscriber initializers
    laser_sub = nh.subscribe("laser_scan", 1000, &Narrow_Space_Bhv::laserCallback, this);
    gt_sub = nh.subscribe("base_pose_ground_truth", 1000, &Narrow_Space_Bhv::gtCallback, this);
    ppl_sub = nh.subscribe("people_detection", 1000, &Narrow_Space_Bhv::pplCallback, this);

}

// simple getters and setters for private variables
void Narrow_Space_Bhv::set_Narrow(bool narrow){
    _narrow = narrow;
}

bool Narrow_Space_Bhv::get_Narrow(){
    return _narrow;
}

void Narrow_Space_Bhv::set_SafetyGoal(geometry_msgs::Pose goal){
    safety_goal = goal;
}

geometry_msgs::Pose Narrow_Space_Bhv::get_SafetyGoal(){
    return safety_goal;
}

void Narrow_Space_Bhv::set_robotPose(geometry_msgs::Pose pose){
    robotPose = pose;
}

geometry_msgs::Pose Narrow_Space_Bhv::get_robotPose(){
    return robotPose;
}

// simple publishing methods
void Narrow_Space_Bhv::publish_NS(std_msgs::String is_ns){
    message_pub.publish(is_ns);
}

void Narrow_Space_Bhv::publish_goal(geometry_msgs::Pose goal){
    goal_pub.publish(goal);
}

/* The ground-truth callback keeps the localization of the robot updated. This
   position is required to calculate the safety position at the laser callback */
void Narrow_Space_Bhv::gtCallback(const nav_msgs::Odometry::ConstPtr &msg){
    set_robotPose(msg->pose.pose);
}

/* This function uses a range of measures from the laser scan publisher to determine whether
   the robot is at a narrow space or not, and calculates a safety goal to be sent in case
   a person is detected while being at that narrow space */
void Narrow_Space_Bhv::laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg){

    std_msgs::String message;
    std_msgs::String is_narrow;

    geometry_msgs::Pose goal;

    double accumulate = 0;
    double safe_accumulate_right = 0;
    double safe_accumulate_left = 0;
    double narrow_limit = 2.2;

    for( int i = 70; i < 100; i++ ){
        accumulate += msg->ranges[i];
    }

    for( int i = 551; i < 582; i++){
        accumulate += msg->ranges[i];
    }

    double avg_distance = accumulate/60;

    if( avg_distance < narrow_limit){
        is_narrow.data = "YES";
        set_Narrow(true);

        for( int i = 582; i < 612; i++){
            safe_accumulate_left += msg->ranges[i];
        }

        for( int i = 100; i < 130; i++){
            safe_accumulate_right += msg->ranges[i];
        }

        goal.position.x = get_robotPose().position.x + std::min(safe_accumulate_left, safe_accumulate_right)/30 - 0.3;
        goal.position.y = get_robotPose().position.y + 1.0;
        goal.orientation = get_robotPose().orientation;

        set_SafetyGoal(goal);
    }
    else{
        is_narrow.data = "NO";
        set_Narrow(false);
    }

    message.data = str( boost::format("NARROW SPACE: %s; SAFETY GOAL: [%d, %d]") % is_narrow.data % goal.position.x % goal.position.y );
    publish_NS(message);

}

/* This callback function sends the safety goal to the navigation stack if a person
   is detected while being at a narrow space */
void Narrow_Space_Bhv::pplCallback(const geometry_msgs::PoseArray::ConstPtr &msg){
    if( msg->poses.size() > 1 && get_Narrow() ){
        publish_goal(get_SafetyGoal());
    }
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