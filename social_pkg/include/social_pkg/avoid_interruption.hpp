#include "ros/ros.h"
#include "std_msgs/String.h"
#include <cmath>
#include <numeric>
#include "boost/format.hpp"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
#include "people_msgs/Person.h"
#include "people_msgs/People.h"
#include "tf/LinearMath/Quaternion.h"
#include "tf/LinearMath/Matrix3x3.h"
#include "tf/transform_datatypes.h"


class Avoid_Interruption{
    public:

        Avoid_Interruption();

        void publishAvoid(people_msgs::People people_msg);

        void interactionCallback(const geometry_msgs::PoseArray::ConstPtr& msg);

    private:

        ros::NodeHandle nh;

        ros::Publisher pub;

        ros::Publisher info_pub;

        ros::Subscriber sub;

};