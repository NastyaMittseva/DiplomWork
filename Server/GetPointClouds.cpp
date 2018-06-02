#include "GetPointClouds.h"

pcl::PointCloud<pcl::PointXYZRGB>::Ptr GetPointClouds::ImageConvertToRGBCloud(string color, string depth, int r, int g, int b)
//преобразует цветные снимки и снимки глубины в трехмерные цветные облака точек 
{
	Mat rgb_image = imread(color);
	Mat depth_image = imread(depth, cv::IMREAD_ANYDEPTH);

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	cloud->width = rgb_image.cols;
	cloud->height = rgb_image.rows;
	cloud->is_dense = false;

	for (int y = 0; y < rgb_image.rows; ++y) {
		for (int x = 0; x < rgb_image.cols; ++x) {
			pcl::PointXYZRGB pt;
			if (depth_image.at<unsigned short>(y, x) != 0)
			{
				pt.z = depth_image.at<unsigned short>(y, x) / 1000.0;
				pt.x = (x - cx)*pt.z / f;
				pt.y = (y - cy)*pt.z / f;
				pt.r = r;
				pt.g = g;
				pt.b = b;
			}
			else
			{
				pt.z = 0;
				pt.x = 0;
				pt.y = 0;
				pt.r = 0;
				pt.g = 0;
				pt.b = 0;
			}
			cloud->points.push_back(pt);
		}
	}
	rgb_image.release();
	depth_image.release();
	return cloud;
}

void GetPointClouds::KeyPointsConvertTo3D(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in1, vector<KeyPoint> keypoints1, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in2, vector<KeyPoint> keypoints2, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &controlPoints1, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &controlPoints2)
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr keyPoints1 = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr keyPoints2 = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
	controlPoints1 = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
	controlPoints2 = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>);

	double maxZ = 0.0;
	double minZ = 100.0;
	for (int i = 0; i < keypoints1.size(); i++)
	{

		pcl::PointXYZRGB point1, point2;
		point1.z = (*cloud_in1).at(keypoints1[i].pt.x, keypoints1[i].pt.y).z;
		point1.x = (*cloud_in1).at(keypoints1[i].pt.x, keypoints1[i].pt.y).x;
		point1.y = (*cloud_in1).at(keypoints1[i].pt.x, keypoints1[i].pt.y).y;
		point1.r = 0;
		point1.g = 0;
		point1.b = 0;

		point2.z = (*cloud_in2).at(keypoints2[i].pt.x, keypoints2[i].pt.y).z;
		point2.x = (*cloud_in2).at(keypoints2[i].pt.x, keypoints2[i].pt.y).x;
		point2.y = (*cloud_in2).at(keypoints2[i].pt.x, keypoints2[i].pt.y).y;
		point2.r = 0;
		point2.g = 0;
		point2.b = 0;

		if (!(point1.x == 0.0 || point1.y == 0.0 || point1.z == 0.0 || point2.x == 0.0 || point2.y == 0.0 || point2.z == 0.0))
		{
			keyPoints1->points.push_back(point1);
			keyPoints2->points.push_back(point2);
			if (abs(point1.z - point2.z) < minZ)
				minZ = abs(point1.z - point2.z);
			if (abs(point1.z - point2.z) > maxZ)
				maxZ = abs(point1.z - point2.z);
		}
	}

	if (abs(maxZ - minZ) < 0.35)
	{
		for (int i = 0; i < keyPoints1->points.size(); i++)
		{
			controlPoints1->points.push_back(keyPoints1->points[i]);
			controlPoints2->points.push_back(keyPoints2->points[i]);
		}
	}
	else
	{
		for (int i = 0; i < keyPoints1->points.size(); i++)
		{

			if (abs(keyPoints1->points[i].z - keyPoints2->points[i].z) < minZ + (maxZ - minZ) * 0.3)
			{
				controlPoints1->points.push_back(keyPoints1->points[i]);
				controlPoints2->points.push_back(keyPoints2->points[i]);
			}
		}
	}
}