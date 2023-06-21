#include "utils_pkg/pose_to_people.hpp"

Pose_To_People::Pose_To_People(){

    pub = nh.advertise<people_msgs::People>("/people",1000);
    sub = nh.subscribe("people_detection", 1000, &Pose_To_People::posesCallback, this);

}

void Pose_To_People::posesCallback(const geometry_msgs::PoseArray::ConstPtr& msg){
    people_msgs::Person person;
    people_msgs::People people;

    for(int i = 0; i < msg->poses.size(); ++i){
        person.position.x = msg->poses[i].position.x;
        person.position.y = msg->poses[i].position.y;
        person.position.z = msg->poses[i].position.z;

        people.people.push_back(person);
    }

    publishPeople(people);
}

void Pose_To_People::publishPeople(people_msgs::People message){
    pub.publish(message);
}

int main(int argc, char** argv){

    ros::init(argc, argv, "pose_to_people");

    Pose_To_People node;

    //ros::Rate rate(2);

    while(ros::ok()){
        ros::spin();
        //rate.sleep();
    }

}