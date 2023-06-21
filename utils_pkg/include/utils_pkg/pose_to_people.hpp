#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
#include "people_msgs/Person.h"
#include "people_msgs/People.h"

class Pose_To_People{
    public:

        Pose_To_People();

        void posesCallback(const geometry_msgs::PoseArray::ConstPtr& msg);

        void publishPeople(people_msgs::People message);

    private:

        ros::NodeHandle nh;

        ros::Publisher pub;

        ros::Subscriber sub;

};