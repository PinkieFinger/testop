#include "stdafx.h"
#include <opencv2/opencv.hpp>
#define OPENPOSE_FLAGS_DISABLE_POSE
#include <openpose/headers.hpp>
class image_to_coordinate
{
public:
	std::string coordinate_body;
	std::string coordinate_Lhand;
	std::string coordinate_Rhand;
	std::string coordinate_face;
	cv::Mat cvImageToProcess;
};
_declspec(dllexport) int tutorialApiCpp(image_to_coordinate &tempa,op::Wrapper &opWrapper)
{
	try
	{
		op::opLog("Starting OpenPose demo...", op::Priority::High);
		op::opLog("Configuring OpenPose...", op::Priority::High);
		const op::Matrix imageToProcess = op::Matrix((const void* const)&(tempa.cvImageToProcess));
		auto datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
		if (datumProcessed != nullptr)
		{
			tempa.coordinate_body = datumProcessed->at(0)->poseKeypoints.toString();
			tempa.coordinate_face = datumProcessed->at(0)->faceKeypoints.toString();
			tempa.coordinate_Lhand = datumProcessed->at(0)->handKeypoints[0].toString();
			tempa.coordinate_Rhand = datumProcessed->at(0)->handKeypoints[1].toString();
			tempa.coordinate_body.erase(0, 22);
			tempa.coordinate_face.erase(0, 22);
			tempa.coordinate_Lhand.erase(0, 22);
			tempa.coordinate_Rhand.erase(0, 22);
		}
		else
			op::opLog("Image could not be processed.", op::Priority::High);
		// Measuring total time
		// Return
		return 0;
	}
	catch (const std::exception&)
	{
		return -1;
	}
}