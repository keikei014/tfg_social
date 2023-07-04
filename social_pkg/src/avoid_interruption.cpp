#include "social_pkg/avoid_interruption.hpp"

Avoid_Interruption::Avoid_Interruption(){
    pub = nh.advertise<people_msgs::People>("/people",1000);
    sub = nh.subscribe("/people_detection", 1000, &Avoid_Interruption::interactionCallback, this);
}

void Avoid_Interruption::interactionCallback(const geometry_msgs::PoseArray::ConstPtr& msg){

    double distance_lim = 2.5;
    double orientation_lim = 0.25;

    if( msg->poses.size() > 1 ){
        double distance = sqrt(pow(msg->poses[0].position.x-msg->poses[1].position.x, 2) -
                               pow(msg->poses[0].position.y-msg->poses[1].position.y, 2));
        
        if( distance < distance_lim ){
            double gamma_1 = atan2(2.0*(msg->poses[0].orientation.x*msg->poses[0].orientation.w + msg->poses[0].orientation.y*msg->poses[0].orientation.z),
                                 1 - 2 * (msg->poses[0].orientation.y*msg->poses[0].orientation.y + msg->poses[0].orientation.z*msg->poses[0].orientation.z));
            double gamma_2 = atan2(2.0*(msg->poses[1].orientation.x*msg->poses[1].orientation.w + msg->poses[1].orientation.y*msg->poses[1].orientation.z),
                                 1 - 2 * (msg->poses[1].orientation.y*msg->poses[1].orientation.y + msg->poses[1].orientation.z*msg->poses[1].orientation.z));
            
            if( (abs(gamma_1) + abs(gamma_2) < M_PI + orientation_lim) && (abs(gamma_1) + abs(gamma_2) > M_PI - orientation_lim) ){
                
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