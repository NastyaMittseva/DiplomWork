#include "ICP.h"

ICP::ICP()
{
}

void ICP::Init(PointCloud<PointXYZRGB>::Ptr &cloud_in1, PointCloud<PointXYZRGB>::Ptr &keypoints1, PointCloud<PointXYZRGB>::Ptr &cloud_in2, PointCloud<PointXYZRGB>::Ptr keypoints2)
{
	staticCloud = PointCloud<PointXYZRGB>::Ptr(new PointCloud<PointXYZRGB>);
	dynamicCloud = PointCloud<PointXYZRGB>::Ptr(new PointCloud<PointXYZRGB>);
	controlPointsDynamicCloud = PointCloud<PointXYZRGB>::Ptr(new PointCloud<PointXYZRGB>);
	controlPointsStaticCloud = PointCloud<PointXYZRGB>::Ptr(new PointCloud<PointXYZRGB>);
	distancesInDynamicCloud = PointCloud<PointXYZRGB>::Ptr(new PointCloud<PointXYZRGB>);
	distancesInStaticCloud = PointCloud<PointXYZRGB>::Ptr(new PointCloud<PointXYZRGB>);

	staticCloud = cloud_in1;
	controlPointsStaticCloud = keypoints1;
	dynamicCloud = cloud_in2;
	controlPointsDynamicCloud = keypoints2;

	for (int i = 0; i < 3; i++)
	{
		T[i] = 0.0;
	}
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
				R[i][j] = 1.0;
			else
				R[i][j] = 0.0;
		}
	}
}

ICP::~ICP()
{

}

void ICP::GetCenter(PointXYZRGB &meanPoint, PointCloud<PointXYZRGB>::Ptr &cloud)
//получает глобальные контрольные точки
{
	meanPoint.x = 0.0;
	meanPoint.y = 0.0;
	meanPoint.z = 0.0;

	for (int i = 0; i<cloud->points.size(); i++)
	{
		meanPoint.x += cloud->points[i].x;
		meanPoint.y += cloud->points[i].y;
		meanPoint.z += cloud->points[i].z;
	}

	meanPoint.x = meanPoint.x / cloud->points.size();
	meanPoint.y = meanPoint.y / cloud->points.size();
	meanPoint.z = meanPoint.z / cloud->points.size();
}

double ICP::Error()
//считает среднеквадратичную ошибку между двумя облаками
{
	double newerr = 0.0, err = 0.0;
	for (int i = 0; i < controlPointsDynamicCloud->points.size(); i++)
	{
		err += abs(controlPointsStaticCloud->points[i].x - controlPointsDynamicCloud->points[i].x) + abs(controlPointsStaticCloud->points[i].y - controlPointsDynamicCloud->points[i].y) + abs(controlPointsStaticCloud->points[i].z - controlPointsDynamicCloud->points[i].z);
	}
	err /= controlPointsDynamicCloud->points.size();
	return err;
}

void ICP::DistancesCloudAndControlCenter()
//для каждой точки в обоих облаках получает расстояния между этой точкой и глобальной контрольной точкой
{
	for (int i = 0; i < controlPointsDynamicCloud->points.size(); i++)
	{
		point.x = controlPointsDynamicCloud->points[i].x - meanPointDynamicCloud.x;
		point.y = controlPointsDynamicCloud->points[i].y - meanPointDynamicCloud.y;
		point.z = controlPointsDynamicCloud->points[i].z - meanPointDynamicCloud.z;
		point.r = controlPointsDynamicCloud->points[i].r;
		point.g = controlPointsDynamicCloud->points[i].g;
		point.b = controlPointsDynamicCloud->points[i].b;
		distancesInDynamicCloud->points.push_back(point);

		point.x = controlPointsStaticCloud->points[i].x - meanPointStaticCloud.x;
		point.y = controlPointsStaticCloud->points[i].y - meanPointStaticCloud.y;
		point.z = controlPointsStaticCloud->points[i].z - meanPointStaticCloud.z;
		point.r = controlPointsStaticCloud->points[i].r;
		point.g = controlPointsStaticCloud->points[i].g;
		point.b = controlPointsStaticCloud->points[i].b;
		distancesInStaticCloud->points.push_back(point);
	}
}

void ICP::GetRotateAndTranslate()
//Получает матрицы поворота и сдвига на основе сингулярного разложения матриц
{
	double H[3][3] = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };
	double X[1][3];
	double Y[3][1];
	for (int i = 0; i < distancesInDynamicCloud->points.size(); i++)
	{
		X[0][0] = distancesInDynamicCloud->points[i].x;
		X[0][1] = distancesInDynamicCloud->points[i].y;
		X[0][2] = distancesInDynamicCloud->points[i].z;

		Y[0][0] = distancesInStaticCloud->points[i].x;
		Y[1][0] = distancesInStaticCloud->points[i].y;
		Y[2][0] = distancesInStaticCloud->points[i].z;

		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				H[j][k] += Y[j][0] * X[0][k];
			}
		}
	}

	Eigen::Matrix <double, 3, 3> B;
	B << H[0][0], H[1][0], H[2][0],
		H[0][1], H[1][1], H[2][1],
		H[0][2], H[1][2], H[2][2];

	JacobiSVD<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> svd;
	svd.compute(B, Eigen::ComputeThinU | Eigen::ComputeThinV);
	Eigen::Matrix<double, 3, 3> V = svd.matrixU().transpose();
	Eigen::Matrix<double, 3, 3> U = svd.matrixV().transpose();
	Eigen::Matrix<double, 3, 3> Rm = U.transpose() * V;

	int k = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			R[i][j] = Rm(k);
			k++;
		}
	}
	T[0] = meanPointStaticCloud.x - (meanPointDynamicCloud.x * R[0][0] + meanPointDynamicCloud.y * R[1][0] + meanPointDynamicCloud.z * R[2][0]) /*- W * pow(sqrt(pow(meanPointStaticCloud.x,2)) - sqrt(pow(meanPointDynamicCloud.x),2), 2)*/;
	T[1] = meanPointStaticCloud.y - (meanPointDynamicCloud.x * R[0][1] + meanPointDynamicCloud.y * R[1][1] + meanPointDynamicCloud.z * R[2][1]) /*- W * pow(sqrt(pow(meanPointStaticCloud.y,2)) - sqrt(pow(meanPointDynamicCloud.y),2), 2)*/;
	T[2] = meanPointStaticCloud.z - (meanPointDynamicCloud.x * R[0][2] + meanPointDynamicCloud.y * R[1][2] + meanPointDynamicCloud.z * R[2][2]) /*- W * pow(sqrt(pow(meanPointStaticCloud.z,2)) - sqrt(pow(meanPointDynamicCloud.z),2), 2)*/;
}

void ICP::Update()
//обновляет первое облако в соответствии с найденными матрицами поворота и сдвига
{

	for (int i = 0; i < dynamicCloud->points.size(); i++)
	{
		point.x = (dynamicCloud->points[i].x * R[0][0] + dynamicCloud->points[i].y * R[1][0] + dynamicCloud->points[i].z * R[2][0]) + T[0] /*+ W * pow((staticCloud->points[i].x - dynamicCloud->points[i].x), 2)*/;
		point.y = (dynamicCloud->points[i].x * R[0][1] + dynamicCloud->points[i].y * R[1][1] + dynamicCloud->points[i].z * R[2][1]) + T[1] /*+ W * pow((staticCloud->points[i].y - dynamicCloud->points[i].y), 2)*/;
		point.z = (dynamicCloud->points[i].x * R[0][2] + dynamicCloud->points[i].y * R[1][2] + dynamicCloud->points[i].z * R[2][2]) + T[2] /*+ W * pow((staticCloud->points[i].z - dynamicCloud->points[i].z), 2)*/;
		point.r = dynamicCloud->points[i].r;
		point.g = dynamicCloud->points[i].g;
		point.b = dynamicCloud->points[i].b;
		dynamicCloud->points[i] = point;
	}

	for (int i = 0; i < controlPointsDynamicCloud->points.size(); i++)
	{
		point.x = (controlPointsDynamicCloud->points[i].x * R[0][0] + controlPointsDynamicCloud->points[i].y * R[1][0] + controlPointsDynamicCloud->points[i].z * R[2][0]) + T[0] /*+ W * pow((controlPointsStaticCloud->points[i].x - controlPointsDynamicCloud->points[i].x), 2)*/;
		point.y = (controlPointsDynamicCloud->points[i].x * R[0][1] + controlPointsDynamicCloud->points[i].y * R[1][1] + controlPointsDynamicCloud->points[i].z * R[2][1]) + T[1] /*+ W * pow((controlPointsStaticCloud->points[i].y - controlPointsDynamicCloud->points[i].y), 2)*/;
		point.z = (controlPointsDynamicCloud->points[i].x * R[0][2] + controlPointsDynamicCloud->points[i].y * R[1][2] + controlPointsDynamicCloud->points[i].z * R[2][2]) + T[2] /*+ W * pow((controlPointsStaticCloud->points[i].z - controlPointsDynamicCloud->points[i].z), 2)*/;
		point.r = controlPointsDynamicCloud->points[i].r;
		point.g = controlPointsDynamicCloud->points[i].g;
		point.b = controlPointsDynamicCloud->points[i].b;
		controlPointsDynamicCloud->points[i] = point;
	}
}

void ICP::Clear()
{
	distancesInDynamicCloud->points.clear();
	distancesInStaticCloud->points.clear();
}

PointCloud<PointXYZRGB>::Ptr ICP::algorithmICP(double &newerr)
//алгоритм ICP с использованием глобальных контрольных точек
{
	double err = 0;
	GetCenter(meanPointStaticCloud, controlPointsStaticCloud);
	for (int i = 0; i < iterations; i++)
	{
		GetCenter(meanPointDynamicCloud, controlPointsDynamicCloud);
		newerr = Error();
		std::cout << std::setprecision(16);
		cout << "err = " << newerr << endl;
		DistancesCloudAndControlCenter();
		GetRotateAndTranslate();
		Update();
		Clear();
		if (abs(newerr - err) < eps)
		{
			return dynamicCloud;
			break;
		}
		err = newerr;
	}
	return dynamicCloud;
}