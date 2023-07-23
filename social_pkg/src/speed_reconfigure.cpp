#include "social_pkg/speed_reconfigure.hpp"

// constructor sets the two subscribers
Speed_Reconfigure::Speed_Reconfigure(){
    detection_sub = nh.subscribe("people_detection", 1, &Speed_Reconfigure::detectionCallback, this);
    gt_sub = nh.subscribe("base_pose_ground_truth", 1, &Speed_Reconfigure::gtCallback, this);
    info_pub = nh.advertise<std_msgs::String>("/speed_info", 1000);
}

// simple getter function for private attribute robotPose
geometry_msgs::Pose Speed_Reconfigure::get_robotPose(){
    return robotPose;
}

// simple setter function for private attribute robotPose
void Speed_Reconfigure::set_robotPose(geometry_msgs::Pose pose){
    robotPose = pose;
}

// callback listens to the ground truth and updates with current pose of the robot
void Speed_Reconfigure::gtCallback(const nav_msgs::Odometry::ConstPtr& msg){
    set_robotPose(msg->pose.pose);
}

// callback listens to the people detector and adjusts speed
void Speed_Reconfigure::detectionCallback(const geometry_msgs::PoseArray::ConstPtr& msg){

    // get the current pose of the robot 
    geometry_msgs::Pose robot = get_robotPose();

    double distance;

    std_msgs::String message;

    // maximum distance at which a person can be detected (set at the simulation)
    double min_distance = 4;

    // check if at least one person was detected
    if( msg->poses.size() > 0 ){

        // calculate the distance to each person detected
        for(int i = 0; i < msg->poses.size(); ++i){

            distance = hypot(robot.position.x - msg->poses[i].position.x, robot.position.y - msg->poses[i].position.y);

            if(distance < min_distance){
                min_distance = distance;
            }
            ROS_INFO("SE VA A MODIFICAR LA VELOCIDAD DEL ROBOT");
        }
    }

    // compute the new speed using the distance to the closer person
    double speed = 0.25*min_distance;

    // format the command that will be executed by the system() function
    string command = str( boost::format("rosrun dynamic_reconfigure dynparam set /move_base/DWAPlannerROS max_vel_trans %d") % speed );

    // format the information string
    message.data = str( boost::format("People detected: %i, Distance to closest person: %d, Calculated speed: %d") % msg->poses.size() % min_distance % speed );

    // call system to perform the speed reconfiguration
    system(command.c_str());

    // publish node information
    info_pub.publish(message);

}

int main(int argc, char** argv){

    ros::init(argc, argv, "reconfigure_speed");

    Speed_Reconfigure node;

    //ros::Rate rate(2);

  //  while(ros::ok()){
    ros::spin();
        //rate.sleep();
//    }

}