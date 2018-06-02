#include <pcl/registration/icp.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "lodepng.h"

using namespace std;
using namespace pcl;
using namespace cv;

class BearingAngleImage
{
private:
	double getAngle(PointXYZ &point1, PointXYZ &point2);
public:
	PointCloud<PointXYZ>::Ptr ConvertCloudToCloudXYZ(PointCloud<PointXYZRGB>::Ptr cloud_in);
	void generateBAImage(PointCloud<PointXYZ>& cloud, const char* name);
};