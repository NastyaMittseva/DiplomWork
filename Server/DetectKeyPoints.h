#include <iostream>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"

using namespace std;
using namespace pcl;
using namespace cv;

class DetectKeyPoints
{
	public:
		void KeyPointsFromBAImage(vector<KeyPoint> &keypoints1, vector<KeyPoint> &keypoints2, string image_1, string image_2);
};

