#include "social_pkg/avoid_interruption.hpp"

Avoid_Interruption::Avoid_Interruption(){

    // initialize publisher for the extra cost if interaction is detected
    pub = nh.advertise<people_msgs::People>("/people",1000);

    // initialize publisher for information string
    info_pub = nh.advertise<std_msgs::String>("/information", 1000);

    // initialize subscription to people detector simulator
    sub = nh.subscribe("/people_detection", 1000, &Avoid_Interruption::interactionCallback, this);
}

void Avoid_Interruption::interactionCallback(const geometry_msgs::PoseArray::ConstPtr& msg){

    // minimum distance to consider two detected people for possible interaction
    double distance_lim = 2.5;

    // orientation limit to consider two close people are facing each other
    double orientation_lim = 0.25;

    double orientation_sum;

    // variables to store the Euler angles of the two people
    double roll_1, pitch_1, yaw_1, roll_2, pitch_2, yaw_2;

    double distance;

    if( msg->poses.size() > 1 ){
        // distance = sqrt(pow(msg->poses[0].position.x-msg->poses[1].position.x, 2) -
        //                        pow(msg->poses[0].position.y-msg->poses[1].position.y, 2));

        // equation to compute distance between two detected people
        distance = hypot(msg->poses[0].position.x - msg->poses[1].position.x, msg->poses[0].position.y-msg->poses[1].position.y);
        
        // check if the two detected people are close enough
        if( distance < distance_lim ){
            // gamma_1 = atan2(2.0*(msg->poses[0].orientation.x*msg->poses[0].orientation.w + msg->poses[0].orientation.y*msg->poses[0].orientation.z),
            //                      1 - 2 * (msg->poses[0].orientation.y*msg->poses[0].orientation.y + msg->poses[0].orientation.z*msg->poses[0].orientation.z));
            // gamma_2 = atan2(2.0*(msg->poses[1].orientation.x*msg->poses[1].orientation.w + msg->poses[1].orientation.y*msg->poses[1].orientation.z),
            //                      1 - 2 * (msg->poses[1].orientation.y*msg->poses[1].orientation.y + msg->poses[1].orientation.z*msg->poses[1].orientation.z));

            // turn the quaternion messages received into tf::Quaternion
            tf::Quaternion quat_p1, quat_p2;
            tf::quaternionMsgToTF(msg->poses[0].orientation, quat_p1);
            tf::quaternionMsgToTF(msg->poses[1].orientation, quat_p2);

            // extract Euler angles from the quaternions
            tf::Matrix3x3(quat_p1).getRPY(roll_1, pitch_1, yaw_1);
            tf::Matrix3x3(quat_p2).getRPY(roll_2, pitch_2, yaw_2);

            // check if the two detected people are facing each other
            orientation_sum = abs(yaw_1) + abs(yaw_2);
            
            if( orientation_sum < M_PI + orientation_lim && orientation_sum > M_PI - orientation_lim ){
                
                // add aditional cost to the map to make sure the robot avoids any interruption
                people_msgs::People people_msg;
                people_msgs::Person person;

                people_msg.header.frame_id = "map";

                person.position.x = (msg->poses[0].position.x + msg->poses[1].position.x)/2;
                person.position.y = (msg->poses[0].position.y + msg->poses[1].position.y)/2;

                people_msg.people.push_back(person);

                ROS_INFO("SE HAN DETECTADO DOS PERSONAS QUE ESTAN HABLANDO");
                
                publishAvoid(people_msg);
            }
        }
    }

    // format and publish the information string
    std_msgs::String info_msg;

    info_msg.data = str( boost::format("First person orientation: %d Second person orientation: %d Orientation diff: %d Distance between them: %d") % yaw_1 % yaw_2 % orientation_sum % distance);

    info_pub.publish(info_msg);
}

void Avoid_Interruption::publishAvoid(people_msgs::People people_msg){

    pub.publish(people_msg);

}

int main(int argc, char** argv){
    ros::init(argc, argv, "avoid_interruption");

    Avoid_Interruption node;

    ros::Rate rate(2);

    while(ros::ok()){
        ros::spin();
        rate.sleep();
    }
}