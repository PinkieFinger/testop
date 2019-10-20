// trytry.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib,"allkeypoints_from_image.lib")
#pragma comment(lib,"opencv_world411.lib")
#pragma comment(lib,"opencv_world411d.lib")


int tutorialApiCpp(image_to_coordinate &tempa,op::Wrapper &opWrapper);

int main()
{
	image_to_coordinate tempa;
	op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };
	// Add hand and face
	opWrapper.configure(op::WrapperStructFace{ false });
	opWrapper.configure(op::WrapperStructHand{ false });
	opWrapper.disableMultiThreading();
	opWrapper.start();
	cv::VideoCapture capture(0);
	while (true)
	{
		//const auto opTimer = op::getTimerInit();
		cv::Mat frame;
		capture >> frame;
		tempa.cvImageToProcess = frame;
		const op::Matrix imageToProcess = op::Matrix((const void* const)&(tempa.cvImageToProcess));
		tutorialApiCpp(tempa, opWrapper);
		const cv::Mat cvMat = (*((cv::Mat*)((opWrapper.emplaceAndPop(imageToProcess)->at(0)->cvOutputData).getConstCvMat())));
		imshow("读取视频", cvMat);
		op::opLog(tempa.coordinate_body, op::Priority::High);
		cv::waitKey(30);	//延时30
		//op::printTime(opTimer, "OpenPose demo successfully finished. Total time: ", " seconds.", op::Priority::High);
	}

	//image_to_coordinate tempa;
	//tempa.cvImageToProcess = (cv::imread("examples/media/COCO_val2014_000000000294.jpg"));
	//tutorialApiCpp(tempa);
	//op::opLog(tempa.coordinate_body, op::Priority::High);
	//op::opLog(tempa.coordinate_face, op::Priority::High);
	//op::opLog(tempa.coordinate_Lhand, op::Priority::High);
	//op::opLog(tempa.coordinate_Rhand, op::Priority::High);

	while (1);
	return 0;
}

