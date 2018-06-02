#pragma comment(lib, "WS2_32.lib")
#include "GetPointClouds.h"
#include "DrawPointClouds.h"
#include "BearingAngleImage.h"
#include "DetectKeyPoints.h"
#include "ICP.h"
#include <winsock2.h>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
#define DEFAULT_BUFLEN 1024
using namespace pcl;


void CombineTwoCloud(PointCloud<PointXYZRGB>::Ptr &cloud1, PointCloud<PointXYZRGB>::Ptr &cloud2, int i, int j, PointCloud<PointXYZ>::Ptr &cloudXYZ1, PointCloud<PointXYZ>::Ptr &cloudXYZ2, vector<KeyPoint> &keypoints1, vector<KeyPoint> &keypoints2, PointCloud<PointXYZRGB>::Ptr &keyPointsClouds1, PointCloud<PointXYZRGB>::Ptr &keyPointsClouds2, double &error)
{
	BearingAngleImage cloudBA;
	cloudXYZ1 = cloudBA.ConvertCloudToCloudXYZ(cloud1);
	cloudBA.generateBAImage(*cloudXYZ1, "1BAImage.png");

	cloudXYZ2 = cloudBA.ConvertCloudToCloudXYZ(cloud2);
	cloudBA.generateBAImage(*cloudXYZ2, "2BAImage.png");
	
	DetectKeyPoints points;
	points.KeyPointsFromBAImage(keypoints1, keypoints2, "1BAImage.png", "2BAImage.png");

	GetPointClouds clouds;
	DrawPointClouds draw;
	if (!keypoints1.empty())
	{
		clouds.KeyPointsConvertTo3D(cloud1, keypoints1, cloud2, keypoints2, keyPointsClouds1, keyPointsClouds2);
		draw.DrawKeyPoints(cloud1, cloud2, keyPointsClouds1, keyPointsClouds2);
	}

	double newError;
	ICP algorithm;
	if (!keypoints1.empty())
	{
		double newError;
		algorithm.Init(cloud1, keyPointsClouds1, cloud2, keyPointsClouds2);
		cloud2 = algorithm.algorithmICP(newError);
		error += newError;
	}
}

void CombiningClouds(vector<string>names, PointCloud<PointXYZRGB>::Ptr &cloud_in, PointCloud<PointXYZRGB>::Ptr &cloud_out, int &leadTime, double &error)
{
	vector<PointCloud<PointXYZRGB>::Ptr> clouds_in;
	vector<vector<PointCloud<PointXYZRGB>::Ptr>> keyPointsClouds;
	vector<PointCloud<PointXYZ>::Ptr> cloudXYZ;
	vector<vector<vector<KeyPoint>>> keypoints;
	vector<tuple<int, int, int>> colors;
	int count = names.size()/2;

	clouds_in.resize(count);
	keyPointsClouds.resize(count);
	cloudXYZ.resize(count);
	colors.resize(count);
	keypoints.resize(count);
	for (int i = 0; i < count; i++)
	{
		keypoints[i].resize(count - 1);
		keyPointsClouds[i].resize(count - 1);
	}

	int color[7][3] = { {255, 255, 0}, {255, 0, 0}, { 0, 0, 255 }, { 0, 250, 0 }, { 30, 144, 255 }, { 240, 128, 128 } };
	for (int i = 0; i < count; i++) 
	{
		get<0>(colors[i]) = color[i][0]; get<1>(colors[i]) = color[i][1]; get<2>(colors[i]) = color[i][2];
	}

	GetPointClouds clouds;
	DrawPointClouds draw;

	int k = 0;
	for (int i = 0; i < names.size() - 1; i += 2)
	{
		clouds_in[k] = clouds.ImageConvertToRGBCloud(names[i], names[i + 1], get<0>(colors[k]), get<1>(colors[k]), get<2>(colors[k]));
		k++;
	}

	cloud_in = draw.unitClouds(clouds_in);
	draw.DrawClouds("before ICP", cloud_in);

	int j = 0, i = 0;
	error = 0;
	auto t1 = Clock::now();
	while (i < count-1)
	{	
		CombineTwoCloud(clouds_in[i], clouds_in[i+1], i, j, cloudXYZ[i], cloudXYZ[i+1], keypoints[i][j], keypoints[i+1][j], keyPointsClouds[i][j], keyPointsClouds[i+1][j], error);
		i++;
		j++;
	}
	auto t2 = Clock::now();
	leadTime = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
	cout << leadTime << " seconds" << std::endl;
	
	error /= (count - 1);
	cloud_out = draw.unitClouds(clouds_in);
}


int main()
{
	WORD sockVer;
	WSADATA wsaData;
	int retVal;

	sockVer = MAKEWORD(2, 2);

	WSAStartup(sockVer, &wsaData);

	//Создаем сокет
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (servSock == INVALID_SOCKET)
	{
		printf("Unable to create socket\n");
		WSACleanup();
		return SOCKET_ERROR;
	}
	SOCKADDR_IN sin;
	sin.sin_family = PF_INET;
	sin.sin_port = htons(1111);
	sin.sin_addr.s_addr = INADDR_ANY;

	retVal = ::bind(servSock, (LPSOCKADDR)&sin, sizeof(sin));
	if (retVal == SOCKET_ERROR)
	{
		printf("Unable to bind\n");
		WSACleanup();
		return SOCKET_ERROR;
	}

	//Пытаемся начать слушать сокет
	retVal = listen(servSock, 10);
	if (retVal == SOCKET_ERROR)
	{
		printf("Unable to listen\n");
		WSACleanup();
		return SOCKET_ERROR;
	}

	while (true)
	{
		//Ждем клиента
		SOCKET clientSock;

		clientSock = accept(servSock, NULL, NULL);

		if (clientSock == INVALID_SOCKET)
		{
			printf("Unable to accept\n");
			WSACleanup();
			return SOCKET_ERROR;
		}

		char recvbuf[DEFAULT_BUFLEN] = "";
		int recvbuflen = DEFAULT_BUFLEN;
		retVal = recv(clientSock, recvbuf, recvbuflen, 0);

		if (retVal == SOCKET_ERROR)
		{
			printf("Unable to recv\n");
			return SOCKET_ERROR;
		}

		string str(recvbuf);

		if (str == "End")
		{
			printf("The server has completed the connection to the client");
			closesocket(servSock);
			WSACleanup();
			break;
		}

		vector<string> names;
		string delim(" ");
		size_t prev = 0;
		size_t next;
		size_t delta = delim.length();

		while ((next = str.find(delim, prev)) != string::npos) {
			string tmp = str.substr(prev, next - prev);
			names.push_back(str.substr(prev, next - prev));
			prev = next + delta;
		}

		int leadTime;
		double error;
		PointCloud<PointXYZRGB>::Ptr cloud_in(new PointCloud<PointXYZRGB>), cloud_out(new PointCloud<PointXYZRGB>);
		CombiningClouds(names, cloud_in, cloud_out, leadTime, error);

		string response = to_string(leadTime) + " " + to_string(error) + " ";
		const char *szResp = response.c_str();

		printf("Sending response from server\n");
		retVal = send(clientSock, szResp, strlen(szResp), 0);

		if (retVal == SOCKET_ERROR)
		{
			printf("Unable to send\n");
			return SOCKET_ERROR;
		}

		DrawPointClouds draw;
		draw.DrawClouds(cloud_in, cloud_out);
		draw.DrawClouds("after ICP", cloud_out);
		//Закрываем сокет
		closesocket(clientSock);
	}
	system("pause");
}