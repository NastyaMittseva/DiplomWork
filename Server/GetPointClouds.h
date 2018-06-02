#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
//using namespace pcl;

class GetPointClouds
{
private:
	const float f = 570.3;
	const float cx = 320.0, cy = 240.0;
public:
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr ImageConvertToRGBCloud(string color, string depth, int r, int g, int b);
	void KeyPointsConvertTo3D(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in1, vector<KeyPoint> keypoints1, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in2, vector<KeyPoint> keypoints2, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &controlPoints1, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &controlPoints2);
};