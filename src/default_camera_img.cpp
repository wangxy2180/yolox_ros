#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <unistd.h>

using namespace std;
using namespace ros;
int main(int argc, char **argv)
{

	ros::init(argc, argv, "default_camera_img");
	ros::NodeHandle nh("~");

	bool is_video;
	string image_source;
	int cam_device;
	string video_path;

	// nh.getParam("is_video", is_video);
	nh.param<std::string>("image_source", image_source, "camera");
	nh.param<int>("cam_device", cam_device, 0);

	cv::VideoCapture capture;

	if (image_source == "video")
	{
		// string video_path = "";
		nh.param<std::string>("video_path", video_path, "video_path");
		// nh.getParam("video_path", video_path);
		// 是不是可以直接assert啊
		sleep(40);
		if (!capture.open(video_path))
		{
			ROS_ERROR("Failed to open video.");
			return -1;
		}
		ROS_INFO("image source:%s",video_path.c_str());
	}
	else if (image_source == "camera")
	{
		// cv::VideoCapture capture(1);
		if (!capture.open(0))
		{
			ROS_ERROR("Failed to open camera.");
			return -1;
		}
		ROS_INFO("image source:camera");
	}
	else
	{
		ROS_ERROR("image source type error!");
		return -1;
	}
	if (!capture.isOpened())
	{
		cout << "open device or video failed" << endl;
		return -1;
	}

	cv::Mat frame;
	sensor_msgs::ImagePtr default_camera_img;

	image_transport::ImageTransport it(nh);

	string pub_topic = "/default_image_source";
	// image_transport::Publisher pub = it.advertise("default_camera/img", 1);
	image_transport::Publisher pub = it.advertise(pub_topic, 1);

	ros::Rate loop_rate(5);
	while (nh.ok())
	{
		capture >> frame;
		if (!frame.empty())
		{

			// opencv格式的图像转化为ROS所支持的消息类型，从而发布到相应的话题上。
			default_camera_img = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
			pub.publish(default_camera_img);
			cv::imshow("hhhh", frame);
			cv::waitKey(30);
			// imwrite("/home/wxy/frame.jpg",frame);
			// string cur_path = getcwd(NULL, 0);
			// cout<<cur_path<<endl;
		}
		// ROS_INFO("wohaihuozhe . . .");
		// ROS_INFO("alive . . .");
		ros::spinOnce();
	}
}
