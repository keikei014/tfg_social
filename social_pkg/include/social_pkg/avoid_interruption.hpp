#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
#include "people_msgs/Person.h"
#include "people_msgs/People.h"
#include <cmath>

class Avoid_Interruption{
    public:

        Avoid_Interruption();

        void publishAvoid(people_msgs::People people_msg);

        void interactionCallback(const geometry_msgs::PoseArray::ConstPtr& msg);

    private:

        ros::NodeHandle nh;

        ros::Publisher pub;

        ros::Subscriber sub;

};