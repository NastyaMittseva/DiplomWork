#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace pcl;
using namespace std;

class DrawPointClouds
{
public:
	PointCloud<PointXYZRGB>::Ptr unitClouds(vector<PointCloud<PointXYZRGB>::Ptr> clouds);
	void DrawClouds(string name, PointCloud<PointXYZRGB>::Ptr cloud);
	void DrawClouds(PointCloud<PointXYZRGB>::Ptr cloud_in, PointCloud<PointXYZRGB>::Ptr cloud_out);
	void DrawKeyPoints(PointCloud<PointXYZRGB>::Ptr cloud_in1, PointCloud<PointXYZRGB>::Ptr cloud_in2, PointCloud<PointXYZRGB>::Ptr controlPoints1, PointCloud<PointXYZRGB>::Ptr controlPoints2);
};
