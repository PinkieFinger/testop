#include "stdafx.h"
#include<iostream>
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>
#include <opencv2/opencv.hpp>
// Command-line user interface
//#include <openpose/flags.hpp>
// OpenPose dependencies
#include <openpose/headers.hpp>
#include<gflags\gflags_completions.h>

#define OPENPOSE_FLAGS_DISABLE_POSE
class lwj
{
public:
	std::string coordinate;
	cv::Mat cvImageToProcess;
};

_declspec(dllexport) int tutorialApiCpp(lwj &tempa)
{
	try
	{
		op::opLog("Starting OpenPose demo...", op::Priority::High);
		const auto opTimer = op::getTimerInit();

		// Configuring OpenPose
		op::opLog("Configuring OpenPose...", op::Priority::High);
		op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };
		// Set to single-thread (for sequential processing and/or debugging and/or reducing latency)
		//if (FLAGS_disable_multi_thread)
		opWrapper.disableMultiThreading();
		// Starting OpenPose
		op::opLog("Starting thread(s)...", op::Priority::High);
		opWrapper.start();

		// Process and display image
		//const cv::Mat cvImageToProcess = cv::imread(mypath);
		const op::Matrix imageToProcess = op::Matrix((const void* const)&(tempa.cvImageToProcess));
		auto datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
		if (datumProcessed != nullptr)
		{
			tempa.coordinate= datumProcessed->at(0)->poseKeypoints.toString();
			tempa.coordinate.erase(0, 22);
		}
		else
			op::opLog("Image could not be processed.", op::Priority::High);

		// Measuring total time
		op::printTime(opTimer, "OpenPose demo successfully finished. Total time: ", " seconds.", op::Priority::High);

		// Return
		return 0;
	}
	catch (const std::exception&)
	{
		return -1;
	}
}

