#include <iostream>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/cloud_viewer.h>
#include <Eigen/Dense>
#include <cmath>

using namespace std;
using namespace pcl;
using namespace Eigen;

class ICP
{
private:
	const float eps = 0.0000001;
	const float threshold = 0.1;
	const int iterations = 10;
	const float a = 20;
	double W = 0;
	double T[3];
	double R[3][3];

	PointXYZRGB meanPointDynamicCloud, meanPointStaticCloud, point;
	PointCloud<PointXYZRGB>::Ptr dynamicCloud, staticCloud, controlPointsDynamicCloud, controlPointsStaticCloud, distancesInDynamicCloud, distancesInStaticCloud;

	void GetCenter(PointXYZRGB &meanPoint, PointCloud<PointXYZRGB>::Ptr &cloud);
	void DistancesCloudAndControlCenter();
	double Error();
	void GetRotateAndTranslate();
	void Update();
	void Clear();
public:
	ICP();
	~ICP();
	void Init(PointCloud<PointXYZRGB>::Ptr &cloud_in1, PointCloud<PointXYZRGB>::Ptr &keypoints1, PointCloud<PointXYZRGB>::Ptr &cloud_in2, PointCloud<PointXYZRGB>::Ptr keypoints2);
	PointCloud<PointXYZRGB>::Ptr algorithmICP(double &newerr);
};

