#include "DetectKeyPoints.h"


void DetectKeyPoints::KeyPointsFromBAImage(vector<KeyPoint> &keyPoints_3, vector<KeyPoint> &keyPoints_4, string image_1, string image_2)
{
	Mat image1 = imread(image_1);
	Mat image2 = imread(image_2);
	vector<cv::KeyPoint> keyPoints_1, keyPoints_2, keypoints1, keypoints2, keyPoints_5, keyPoints_6;
	cv::Mat descriptors_1, descriptors_2, descriptors1, descriptors2, descriptors3, descriptors4;

	cv::FeatureDetector * detector = new cv::ORB;
	detector->detect(image1, keyPoints_1);
	detector->detect(image2, keyPoints_2);
	delete detector;

	cv::DescriptorExtractor * extractor = new cv::SIFT;
	extractor->compute(image1, keyPoints_1, descriptors_1);
	extractor->compute(image2, keyPoints_2, descriptors_2);
	delete extractor;

	cv::BFMatcher matcher(cv::NORM_L2, true);
	vector< cv::DMatch > matches, matches1, matches2, matches3;
	matcher.match(descriptors_1, descriptors_2, matches);

	cv::Mat img_matches1;
	cv::drawMatches(image1, keyPoints_1, image2, keyPoints_2, matches, img_matches1);
	cv::imshow("Matches", img_matches1);
	cv::waitKey(0);

	//отбираем по наименьшему расстоянию между дескрипторами
	int i;
	sort(matches.begin(), matches.end());
	if (matches[1].distance - matches[0].distance < 20)
		i = 0;
	else
		i = 1;
	i = 0;
	double min_dist_descriptors = matches[i].distance;
	double avr_distance_points = sqrt(pow((keyPoints_1[matches[i].queryIdx].pt.x - (keyPoints_2[matches[i].trainIdx].pt.x + 640)), 2) + pow((keyPoints_1[matches[i].queryIdx].pt.y - keyPoints_2[matches[i].trainIdx].pt.y), 2));
	double k = (keyPoints_2[matches[i].trainIdx].pt.y - keyPoints_1[matches[i].queryIdx].pt.y) / (keyPoints_2[matches[i].trainIdx].pt.x + 640 - keyPoints_1[matches[i].queryIdx].pt.x);

	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < min_dist_descriptors * 10)
		{
			matches1.push_back(matches[i]);
			keypoints1.push_back(keyPoints_1[matches[i].queryIdx]);
			keypoints2.push_back(keyPoints_2[matches[i].trainIdx]);
		}
	}
	
	cv::DescriptorExtractor * extractor2 = new cv::SIFT;
	extractor2->compute(image1, keypoints1, descriptors1);
	extractor2->compute(image2, keypoints2, descriptors2);
	matcher.match(descriptors1, descriptors2, matches2);
	delete extractor2;

	cv::Mat img_matches2;
	cv::drawMatches(image1, keypoints1, image2, keypoints2, matches2, img_matches2);
	cv::imshow("Matches", img_matches2);
	cv::waitKey(0);

	//отбираем по среднему расстоянию между точками
	vector<double> avarege, angleCoefficient;
	for (int i = 0; i < matches1.size(); i++)
	{
		avarege.push_back(sqrt(pow((keypoints1[i].pt.x - (keypoints2[i].pt.x + 640)), 2) + pow((keypoints1[i].pt.y - keypoints2[i].pt.y), 2)));
		angleCoefficient.push_back((keypoints2[i].pt.y - keypoints1[i].pt.y) / (keypoints2[i].pt.x + 640 - keypoints1[i].pt.x));
	}

	for (int i = 0; i < matches1.size(); i++)
	{
		if (k < 0.01 && k >= 0 || k > -0.01 && k <= 0)
		{
			if ((avarege[i] >= avr_distance_points * 0.95) && (avarege[i] <= avr_distance_points * 1.05) && (abs(angleCoefficient[i]) >= abs(k) * 0) && (abs(angleCoefficient[i]) <= abs(k) * 10))
			{
				keyPoints_3.push_back(keypoints1[i]);
				keyPoints_4.push_back(keypoints2[i]);
			}
		}
		else
		{
			if (k > 0)
			{
				if ((avarege[i] > avr_distance_points * 0.95) && (avarege[i] < avr_distance_points * 1.05) && (angleCoefficient[i] > k * 0.95) && (angleCoefficient[i] < k * 1.05))
				{
					keyPoints_3.push_back(keypoints1[i]);
					keyPoints_4.push_back(keypoints2[i]);
				}
			}
			if (k < 0)
			{
				if ((avarege[i] > avr_distance_points * 0.95) && (avarege[i] < avr_distance_points * 1.05) && (angleCoefficient[i] > k * 1.05) && (angleCoefficient[i] < k * 0.95))
				{
					keyPoints_3.push_back(keypoints1[i]);
					keyPoints_4.push_back(keypoints2[i]);
				}
			}
		}
	}

	cv::DescriptorExtractor * extractor3 = new cv::SIFT;
	extractor3->compute(image1, keyPoints_3, descriptors3);
	extractor3->compute(image2, keyPoints_4, descriptors4);
	matcher.match(descriptors3, descriptors4, matches3);
	delete extractor3;

	cv::Mat img_matches;
	cv::drawMatches(image1, keyPoints_3, image2, keyPoints_4, matches3, img_matches);
	cv::imshow("Matches", img_matches);
	cv::waitKey(0);
}