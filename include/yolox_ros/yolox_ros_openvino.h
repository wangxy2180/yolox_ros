#include <iostream>
#include <string>
#include <iterator>
#include <memory>
#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include <inference_engine.hpp>

#include "yolox_type.h"
#include "timer.h"

using namespace std;
using namespace InferenceEngine;

class YOLOXVINODetector
{
private:
    ros::NodeHandle nh_;
    ros::Publisher info_pub_;
    ros::Subscriber image_sub_;

    string image_source_;
    string video_path_;
    int cam_device_;
    string infer_device_;
    string model_path_;

    Core ie;
    InputInfo::Ptr input_info;
    std::string input_name;
    DataPtr output_info;
    std::string output_name;
    InferRequest infer_request;

    /* data */
public:
    YOLOXVINODetector(/* args */);
    ~YOLOXVINODetector();

    void get_ros_param();
    void detect_callback(const sensor_msgs::Image::ConstPtr &msg);

    void read_image(const sensor_msgs::Image::ConstPtr msgImage, cv::Mat &image);

    cv::Mat static_resize(cv::Mat &img);
    void blobFromImage(cv::Mat &img, Blob::Ptr &blob);
    void generate_grids_and_stride(const int target_w, const int target_h, std::vector<int> &strides, std::vector<GridAndStride> &grid_strides);
    void generate_yolox_proposals(std::vector<GridAndStride> grid_strides, const float *feat_ptr, float prob_threshold, std::vector<Object> &objects);

    inline float intersection_area(const Object &a, const Object &b);
    void qsort_descent_inplace(std::vector<Object> &faceobjects, int left, int right);
    void qsort_descent_inplace(std::vector<Object> &objects);
    void nms_sorted_bboxes(const std::vector<Object> &faceobjects, std::vector<int> &picked, float nms_threshold);
    void decode_outputs(const float *prob, std::vector<Object> &objects, float scale, const int img_w, const int img_h);
    void draw_objects(const cv::Mat &bgr, const std::vector<Object> &objects);

    void load_ie_model();
};
