#include "DrawPointClouds.h"

PointCloud<PointXYZRGB>::Ptr DrawPointClouds::unitClouds(vector<PointCloud<PointXYZRGB>::Ptr> clouds)
{
	PointCloud<PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>);
	for (int i = 0; i < clouds.size(); i++)
	{
		*cloud += *clouds[i];
	}
	return cloud;
}

void DrawPointClouds::DrawClouds(string name, PointCloud<PointXYZRGB>::Ptr cloud)
//отображает трехмерные облака в одной системе координат
{
	visualization::CloudViewer viewer(name);
	viewer.showCloud(cloud);
	while (!viewer.wasStopped())
	{
	}
}

void DrawPointClouds::DrawClouds(PointCloud<PointXYZRGB>::Ptr cloud_in, PointCloud<PointXYZRGB>::Ptr cloud_out)
//отображает трехмерные облака в одной системе координат
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->initCameraParameters();

	int v1(0);
	viewer->createViewPort(0.0, 0.0, 0.5, 1.0, v1);
	viewer->addText("Clouds before combining", 10, 10, "v1 text", v1);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb1(cloud_in);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud_in, rgb1, "sample cloud1", v1);

	int v2(0);
	viewer->createViewPort(0.5, 0.0, 1.0, 1.0, v2);
	viewer->addText("Clouds after combining", 10, 10, "v2 text", v2);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb2(cloud_out);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud_out, rgb2, "sample cloud2", v2);

	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud1");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud2");
	viewer->addCoordinateSystem(1.0);

	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}

void DrawPointClouds::DrawKeyPoints(PointCloud<PointXYZRGB>::Ptr cloud_in1, PointCloud<PointXYZRGB>::Ptr cloud_in2, PointCloud<PointXYZRGB>::Ptr controlPoints1, PointCloud<PointXYZRGB>::Ptr controlPoints2)
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->initCameraParameters();

	int v1(0);
	viewer->createViewPort(0.0, 0.0, 0.5, 1.0, v1);
	viewer->addText("Cloud 1 with key points", 10, 10, "v1 text", v1);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb1(cloud_in1);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud_in1, rgb1, "sample cloud1", v1);
	for (int i = 0; i < controlPoints1->points.size(); i++)
	{
	stringstream ss;
	ss << 97 + i;
	viewer->addSphere(controlPoints1->points[i], 0.05, 0.5, 0.5, 0.0, ss.str(),v1);
	}

	int v2(0);
	viewer->createViewPort(0.5, 0.0, 1.0, 1.0, v2);
	viewer->addText("Cloud 2 with key points", 15, 15, "v2 text", v2);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb2(cloud_in2);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud_in2, rgb2, "sample cloud2", v2);

	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud1");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud2");
	viewer->addCoordinateSystem(1.0);
	for (int i = 0; i < controlPoints2->points.size(); i++)
	{
	stringstream ss;
	ss << 65 + i;
	viewer->addSphere(controlPoints2->points[i], 0.05, 0.0, 0.5, 0.5, ss.str(),v2);
	}

	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}