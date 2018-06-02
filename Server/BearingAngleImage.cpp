#include "BearingAngleImage.h"

PointCloud<PointXYZ>::Ptr BearingAngleImage::ConvertCloudToCloudXYZ(PointCloud<PointXYZRGB>::Ptr cloud_in)
{
	PointCloud<PointXYZ>::Ptr cloud_out(new PointCloud<PointXYZ>);
	cloud_out->width = cloud_in->width;
	cloud_out->height = cloud_in->height;
	for (int i = 0; i < cloud_in->points.size(); i++)
	{
		PointXYZ point;
		point.x = cloud_in->points[i].x;
		point.y = cloud_in->points[i].y;
		point.z = cloud_in->points[i].z;
		cloud_out->points.push_back(point);
	}
	return cloud_out;
}

double BearingAngleImage::getAngle(PointXYZ &point1, PointXYZ &point2)
{
	double a, b, c;
	double theta;
    const Eigen::Vector3f& p1 = point1.getVector3fMap();
	const Eigen::Vector3f& p2 = point2.getVector3fMap();
	a = p1.squaredNorm();
	b = (p1 - p2).squaredNorm();
	c = p2.squaredNorm();

	if (a != 0 && b != 0)
	{
		theta = acos((a + b - c) / (2 * sqrt(a) * sqrt(b))) * 180 / M_PI;
	}
	else
	{
		theta = 0.0;
	}
	return theta;
}

void BearingAngleImage::generateBAImage(PointCloud<PointXYZ>& cloud, const char* name)
{
	unsigned int width = cloud.width, height = cloud.height;
	unsigned char* image = (unsigned char*)malloc(width * height * 4);

	double theta;
	int r, g, b, gray;

	int x, y;
	for (y = 0; y < height - 1; y++)
	{
		for (x = 0; x < width; x++)
		{
			theta = getAngle(cloud.at(x, y), cloud.at(x, y + 1));
			gray = theta;

			r = gray;
			g = gray;
			b = gray;

			image[4 * width * y + 4 * x + 0] = 0;
			image[4 * width * y + 4 * x + 1] = b;
			image[4 * width * y + 4 * x + 2] = g;
			image[4 * width * y + 4 * x + 3] = r;
		}
	}
	unsigned error = lodepng_encode32_file(name, image, width, height);
	if (error) printf("error %u: %s\n", error, lodepng_error_text(error));
}
