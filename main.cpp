#include "ImageProcessing.h"

using namespace Inspection;
using namespace System;


//std::string getexepath()
//{
//	char result[MAX_PATH];
//	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
//}

ImageProcessing::ImageProcessing()
{
	// Model file path
	//ImageProcessing_networkPath = L".\\data\\model\\Dynamo_new.net";
	wcout << L"networkPath " << networkPath << endl;

	// Device setting
	//DeviceDescriptor ImageProcessing_device = DeviceDescriptor::GetDefaultDevice();
	if (device.GetDeviceKind() == DeviceKind::DeviceKind_GPU) {
		std::cout << "use gpu Device" << endl;
	}
	else {
		std::cout << "use cpu Device" << endl;
	}

	// Define the evaluator network input size
	// It is best if your image size and network input size are the same. (for result accuracy)
	// And usually the bigger the network input size, the better the performance. (for runtime speed)
	//SuaKIT_UInt64 networkH = 1600;
	//SuaKIT_UInt64 networkW = 1600;
	//SuaKIT_UInt64 networkC = 1; // we currently support 1channel or BGR 3channel or BGRA 4channel 

	//	You can select InputDataType from SINGLE, COMPARISON, or MULITIMG.
	// inputDataType and multiImgCount ​​must match the settings of the trained network to be entered.
	/*
	SINGLE (default) : The unit of evalute is one image so multiImgCount value must be 1 (default).
	COMPARISON : The unit of evalute is two images so multiImgCount value must be 2.
	MULITIMG : The unit of evalute is N images. N is set to the value of multiImgCount.
	*/
	//InputDataType inputDataType = InputDataType::SINGLE;
	//SuaKIT_UInt64 multiImgCount = 1;

	maxNetSize = SegmentationEvaluator::GetMaxNetworkSize(networkPath.c_str(), device);


	if (networkH * networkW > maxNetSize) 
	{
		std::cout << "The network size is greater than the maximum size." << endl;
	}
	else
	{
		// Init Evaluator
		//SegmentationEvaluator seg(ImageProcessing_networkPath.c_str(), ImageProcessing_device, networkH, networkW, networkC, inputDataType, multiImgCount);
		status = seg.GetStatus();
		if (status != Status::SUCCESS) {
			std::cout << "Segmentation Initialize Error : " << status << endl;
			std::cout << UnitFunction::GetErrorMessage() << endl;
		}
		else
			std::cout << endl << "Segmentation Initialize Complete" << endl << endl;
	}
	//std::string y = string_cast<std::string>(networkPath);

	//size_t posF1 = networkPath.find_last_of("\\");
	//size_t posF2 = networkPath.find_last_of(".");
	//FolderName = networkPath.substr(pos1 + 1, pos2 - pos1 - 1);
	//

	numDefect = 0;// var 4

}

ImageProcessing::~ImageProcessing()
{
	seg.Finalize();
	cout << "Suakit model finalized (destroyed).\n";
}

//void ImageProcessing::test2(int x) { }
//int ImageProcessing::test(string x) { return 2; } 
//String ImageProcessing::test1(string x) { return ("try me")->ToString; }
//Object  = test1;
//Result ImageProcessing::SegmentationEvaluatorTest(string rawImagePath)


int ImageProcessing::SegmentationEvaluatorTest() // 0 = no issue, 1 = fail at initialising, 2 = fail to find folder, 3 = fail to find file
{
	{
	////////////////////////////////////////////////////////////////////////////////13/11

	//using namespace SuaKIT::API; //good practice

	//// Model file path
	//wstring networkPath = L".\\data\\model\\Dynamo_new.net";
	//wcout << L"networkPath " << networkPath << endl;

	//// Device setting
	//DeviceDescriptor device = DeviceDescriptor::GetDefaultDevice();
	//if (device.GetDeviceKind() == DeviceKind::DeviceKind_GPU) {
	//	std::cout << "use gpu Device" << endl;
	//}
	//else {
	//	std::cout << "use cpu Device" << endl;
	//}
	//
	//// Define the evaluator network input size
	//// It is best if your image size and network input size are the same. (for result accuracy)
	//// And usually the bigger the network input size, the better the performance. (for runtime speed)
	//SuaKIT_UInt64 networkH = 1600;
	//SuaKIT_UInt64 networkW = 1600;
	//SuaKIT_UInt64 networkC = 1; // we currently support 1channel or BGR 3channel or BGRA 4channel 

	////	You can select InputDataType from SINGLE, COMPARISON, or MULITIMG.
	//// inputDataType and multiImgCount ​​must match the settings of the trained network to be entered.
	///*
	//SINGLE (default) : The unit of evalute is one image so multiImgCount value must be 1 (default).
	//COMPARISON : The unit of evalute is two images so multiImgCount value must be 2.
	//MULITIMG : The unit of evalute is N images. N is set to the value of multiImgCount.
	//*/
	//InputDataType inputDataType = InputDataType::SINGLE;
	//SuaKIT_UInt64 multiImgCount = 1;

	//SuaKIT_UInt64 maxNetSize = SegmentationEvaluator::GetMaxNetworkSize(networkPath.c_str(), device);
	//if (networkH * networkW > maxNetSize) {
	//	std::cout << "The network size is greater than the maximum size." << endl; 
	//	return;
	//}

	//// Init Evaluator
	//SegmentationEvaluator seg(networkPath.c_str(), device, networkH, networkW, networkC, inputDataType, multiImgCount);
	//Status status = seg.GetStatus();
	//if (status != Status::SUCCESS) {
	//	std::cout << "Segmentation Initialize Error : " << status << endl;
	//	std::cout << UnitFunction::GetErrorMessage() << endl;
	//	return;
	//}
	//std::cout << endl << "Segmentation Initialize Complete" << endl << endl;


	//// Query class names
	//size_t numClass = seg.GetClassTotalNum();

	//// Define probability threshold vector (optional)
	//FloatArray probabilityThresVec(numClass);
	//for (int i = 0; i < numClass; ++i)
	//{
	//	float curThres = 0;	// user can choose the threshold value for each class.
	//	probabilityThresVec.SetAt(i, curThres);
	//}

	//// Define uncertainty threshold vector (optional)
	//FloatArray uncertaintyThresVec(numClass);
	//for (int i = 0; i < numClass; ++i)
	//{
	//	float curThres = 0;	// user can choose the threshold value for each class.
	//	uncertaintyThresVec.SetAt(i, curThres);
	//}
	//
	//// Define minimum defect size (optional)
	//SizeArray minDefectSizes(numClass);
	//for (int i = 0; i < numClass; ++i)
	//{
	//	Size curSize = { 0, 0 };	// user can choose the min defect size for each class.
	//	minDefectSizes.SetAt(i, curSize);
	//}

	//// Evaluation
	//ImageData resultImg;
	//RectArray resultRects;
	//FloatArray resultProbMap;
	//FloatArray resultUncertaintyMap;


	//std::string folder = "../../../../Image Processing/DynamoImage";
	//std::vector<cv::String> filenames;

	//vector<string> checkedFiles;
	//int numDefect = 0;//var 1

///////////////////////////////////////////////////////////////////////////////
	}

	// Query class names
	numClass = seg.GetClassTotalNum();

	// Define probability threshold vector (optional)
	FloatArray probabilityThresVec(numClass);
	for (int i = 0; i < numClass; ++i)
	{
		float curThres = 0;	// user can choose the threshold value for each class.
		probabilityThresVec.SetAt(i, curThres);
	}

	// Define uncertainty threshold vector (optional)
	FloatArray uncertaintyThresVec(numClass);
	for (int i = 0; i < numClass; ++i)
	{
		float curThres = 0;	// user can choose the threshold value for each class.
		uncertaintyThresVec.SetAt(i, curThres);
	}

	// Define minimum defect size (optional)
	SizeArray minDefectSizes(numClass);
	for (int i = 0; i < numClass; ++i)
	{
		Size curSize = { 0, 0 };	// user can choose the min defect size for each class.
		minDefectSizes.SetAt(i, curSize);
	}

	// Evaluation
	/*ImageData resultImg;
	RectArray resultRects;
	FloatArray resultProbMap;
	FloatArray resultUncertaintyMap;*/ //14/11


	//ifstream ifile(imgFilePath);//26/11
	//if (ifile)
	//{
	

		// Make a reference to a directory.

		// Get a reference to each directory in that directory.
		diArr = dir->GetDirectories();
		nn = diArr->Length;

		DirectoryInfo^ directory = diArr[nn - 1];

		System::String^ directoryString = directory->FullName;

		msclr::interop::marshal_context context;
		std::string standardString = context.marshal_as<std::string>(directoryString);

		//Console::WriteLine("directoryString:"+ directoryString);
		
		//std::string folderrrr= diArr[nn-1];

		//// Display the names of the directories.
		//Collections::IEnumerator^ myEnum = diArr->GetEnumerator();
		//while (myEnum->MoveNext())
		//{
		//	DirectoryInfo^ dri = safe_cast<DirectoryInfo^>(myEnum->Current);
		//	Console::WriteLine(dri->Name);
		//}
	

	//std::string folderFolder = generalFolderPath; //TODO: use Directory.GetDirectories
	//std::vector<cv::String> latestFolder;
	//cv::glob(generalFolderPath, latestFolder);
	//nn = latestFolder.size();

		//std::string folder = folderFilePath + std::to_string(folderCounter);
		
		std::vector<cv::String> filePathBatch;//actual
		//vector<string> checkedFiles;
		//cout << folderFilePath + std::to_string(folderCounter) << endl;
		//{//removed: while loop{true}
		cv::glob(standardString, filePathBatch); //filename is a [vector] with a list of (all) full file names in that folder //actual
		n = filePathBatch.size();//actual
		//std::cout << n << endl;
		

		//for (int i = 0; i < filenames.size(); i++)
		//{
		//	if (std::find(checkedFiles.begin(), checkedFiles.end(), filenames.at(i)) == checkedFiles.end()) {
		//		cout << "To process " << filenames.at(i) << endl;
		//		checkedFiles.push_back(filenames.at(i));
		//	}
		//}

		//while (true) {
		//	cv::glob(folder, filenames);
		//	if (filenames.size() > 0)
		//	{
		//		cout << filenames[0] << endl;
		//		break;
		//	}

		//	std::cout << "Waiting for images..." << endl;
		//	Sleep(2000);
		//}

			//for (int i = 0; i < filenames.size(); i++) //image count TODO:imagename
			//{
			//	if (std::find(checkedFiles.begin(), checkedFiles.end(), filenames.at(i)) != checkedFiles.end()) {
			//		continue;
			//	}
			//	checkedFiles.push_back(filenames.at(i));

			//}//loop suppose to close whole fn


			//numDefect = 0;

			size_t pos1 = filePathBatch[n - 1].find_last_of("\\");
			size_t pos2 = filePathBatch[n - 1].find_last_of(".");
			string FileName = filePathBatch[n - 1].substr(pos1 + 1, pos2 - pos1 - 1);

			//cv::Mat imgMat = cv::imread(filenames[i], 0);

		ifstream fileExist(filePathBatch[n - 1]); 
		if (fileExist)
		{
			//std::cout << "FileName: " << filePathBatch[n - 1] << endl;
			
			cv::Mat imgMat = cv::imread(filePathBatch[n - 1], 0); //actual
			//cv::Mat imgMat = cv::imread("C:/Users/Inspection/Desktop/crp6/crp6-commercialaievaluation/Image Results/test/test1.png", 0); //test
			
			cv::Mat resMat;
			cvtColor(imgMat, resMat, cv::COLOR_GRAY2RGB);

			int64 t1 = cv::getTickCount();

			// We recommend using the same value as the roi size used during training.
			Rect roi(0, 0, 640, 512); // dynamo

			// Prepare ImageData
			// If memory is already available for the image data 
			// and you do not want to copy it when ImageData is created, you can set CopyOption to false.
			// When CopyOption is false, the user is responsible for resource management for the memory area(dataPtr).
			ImageData curImg(imgMat.data, imgMat.step, imgMat.cols, imgMat.rows, imgMat.channels(), true, roi);

			if (multiImgCount > 1) {
				// If InputDataType is used as COMPARISON or MULITIMG, then the evaluation unit, multiImgCount, is at least 2
				// In this case, the constructor can create an object by bringing the first image of the Evalution unit into the constructor and pushing the rest of the image through the PushImage.
				// Alternatively, you can create an ImageData with the default constructor, then pushImage multiImgCount times.
				for (int j = 1; j < multiImgCount; j++) {
					status = curImg.PushImage(imgMat.data, imgMat.step, imgMat.cols, imgMat.rows, imgMat.channels(), true);
					/* Also You can check the validity of the input value with the returned Status value. */
					if (status != Status::SUCCESS) {
						cout << UnitFunction::GetErrorMessage() << endl;
						return 1;
					}
				}
				// Roi uses the same value as all images in the ImageData object, so it can be used with the value specified in the initial constructor or set with the SetRoi method.
			}

			/* You can check with GetStatus() whether ImageData has been properly Created.*/
			if (curImg.GetStatus() != Status::SUCCESS) {
				std::cout << UnitFunction::GetErrorMessage() << endl;
				return 1;
			}

			status = seg.Evaluate(curImg, resultImg, resultRects, resultProbMap, resultUncertaintyMap, minDefectSizes, probabilityThresVec, uncertaintyThresVec);
			if (status != Status::SUCCESS) {
				std::cout << "Evaluate Error : " << status << endl;
				std::cout << "Error Message: " << UnitFunction::GetErrorMessage() << endl;
				return 1;
			}

			if (resultRects.GetLength() == 0)
			{
				int64 t2 = cv::getTickCount();
				std::cout << "processing takes" << (t2 - t1) / cv::getTickFrequency() << endl;
				//continue;
			}

			// save result label image
			cv::Mat resultMat(resultImg.GetHeight(), resultImg.GetWidth(), CV_MAKE_TYPE(CV_8U, resultImg.GetChannel()), resultImg.GetDataPtr());


			// calculate the average probability/uncertainty per each detected area
			cv::Mat label(imgMat.size(), CV_8UC1, cv::Scalar(255));

			for (int classId = 0; classId < numClass - 1; ++classId) //var 1
			{
				cv::Mat binary = (resultMat == classId);
				cv::Mat binaryClone = binary.clone();

				std::vector<std::vector<cv::Point>> contours;
				cv::findContours(binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				int defect_cnt = 0; //var 5 not needed to print
				for (int j = 0; j < contours.size(); ++j)
				{
					double probs = 0.0; //var 2
					double uncertainties = 0.0; //var 3
					size_t count = 0;
					cv::Rect bdRect = cv::boundingRect(contours[j]);

					if (bdRect.width < 5 || bdRect.height < 5)
						continue;

					cv::drawContours(label, contours, j, cv::Scalar(0), -1);
					auto jumpingRate = resultMat.rows * resultMat.cols;
					for (int r = bdRect.y; r < bdRect.y + bdRect.height; ++r)
					{
						for (int c = bdRect.x; c < bdRect.x + bdRect.width; ++c)
						{
							auto defectId = static_cast<int>(*(binaryClone.data + r * binaryClone.step + c * binaryClone.channels() * sizeof(unsigned char)));

							if (defectId == 255)
							{
								probs += resultProbMap.GetAt(classId * jumpingRate + r * resultMat.cols + c);
								uncertainties += resultUncertaintyMap.GetAt(r * resultMat.cols + c);
								++count;
							}
						}
					}

					if (count > 0)
					{
						numDefect++;
						probs /= count;
						uncertainties /= count;

						std::setprecision(5);
						std::fixed;
						if (uncertainties > 0.5)
							continue;

						std::stringstream stream;

						stream << std::fixed << std::setprecision(2) << probs << " ";
						std::string s = stream.str();
						cv::putText(resMat, s, cv::Point(bdRect.x, bdRect.y - 10), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255)); 

						stream << std::fixed << std::setprecision(2) << uncertainties;
						std::string ss = stream.str();
						cv::putText(resMat, ss, cv::Point(bdRect.x, bdRect.y - 10), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0));

						cv::putText(resMat, "Legend:", cv::Point(0, 505), CV_FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(0, 0, 255));
						cv::putText(resMat, "(probabilities uncertainties)", cv::Point(50, 505), CV_FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0));

						//std::cout << "classId: " << classId << endl;
						//std::cout << "avg prob: " << probs << endl;
						//std::cout << "avg uncert: " << uncertainties << endl;


						//imgStats = "\nclassId: " + to_string(classId) + "\navg prob: " + to_string(probs) + "\navg uncert: " + to_string(uncertainties);  


						//DefectData defect0;
						//DefectData defect0;
						//defect0.classId = classId;
						//defect0.probability = probs;
						//defect0.uncertainty = uncertainties;
						//results.listDefect.push_back(defect0);
					}


					//if (bdRect.width > 10 || bdRect.height > 10)
					cv::rectangle(resMat, bdRect, cv::Scalar(0, 0, 255), 1);
					//else 
					//	cv::rectangle(resMat, bdRect, cv::Scalar(255, 0, 0), 3);
					defect_cnt++;

				}
				// save result rect drawn image
				if (defect_cnt > 0)
				{

					//cv::imwrite(".\\11Sept_shoulder_result_16\\" + FileName + ".png", resMat);
					std::string procFolder = standardString + "/Processed Images";
					mkdir(procFolder.c_str());//actual

					//Directory::CreateDirectory(pImgFilePathHard);
					//System.IO.Directory.CreateDirectory(pImgFilePathHard);

					//putText(resMat, "\nTotal defects detected: " + to_string(numDefect), cvPoint(30, 30), CV_FONT_HERSHEY_SIMPLEX, 0.8, cvScalar(200, 200, 250), 1, CV_AA);//TODO: remove
					//cv::imwrite(pImgFilePath + FileName + "_Processed" + ".png", resMat); 
					//String^ MyString = gcnew String(rawImageName.c_str());
					//nameWFilepath = pImgFilePath + MyString + ("_Processed.png")->ToString;

					ProcFullFilePath = standardString + "/Processed Images/" + FileName + "_Processed.png";
					
					
					cv::imwrite(ProcFullFilePath, resMat); //actual
					//cv::imwrite("C:/Users/Inspection/Desktop/crp6/crp6-commercialaievaluation/Image Results/test/test1_processed.png", resMat);//test
					
					//cv::namedWindow("Inspection Result", cv::WINDOW_NORMAL);// no need
					//cv::resizeWindow("Inspection Result", 640, 512);        //
					//cv::imshow("Inspection Result", resMat);                //
					//cv::waitKey(0);                                         //

				}
				int64 t2 = cv::getTickCount();
				//std::cout << "processing takes" << (t2 - t1) / cv::getTickFrequency() << endl;
			}
			//std::cout << "Defects detected: " << numDefect << endl;
			//results.defectCount = numDefect; //13/11
			//std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			numDefect = 0;
			std::cout << endl;
		}
		else 
		{ //nameWFilepath = ("File NIL")->ToString; 
			return 3;
		}

			//}
			//std::cout << "Waiting for images..." << endl;
			//Sleep(2000);
		//}

		//seg.Finalize();
		//String^ test = gcnew String(nameWFilepath.c_str());
		return 0; 
		//return results;
	/*}
	else return 2;*/
	
}

void ImageProcessing::pathArr(char modelPathArrCS, int modelPathArrPos)
{
	//for (int ii = 0; ii < modelPathArrLength; ii++) 
	//{
		modelPathArr[modelPathArrPos] = modelPathArrCS;
		cout << modelPathArr[modelPathArrPos];
	//}
}

bool ImageProcessing::changeModel()
{
	//seg.Finalize();
	//cout << " Suakit model finalized (destroyed).\n"<<endl;

	string modelPath(modelPathArr);
	//cout << modelPath << endl;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wideModelPath = converter.from_bytes(modelPath);

	// Model file path
		//ImageProcessing_networkPath = L".\\data\\model\\Dynamo_new.net";
		wcout << L"networkPath " << wideModelPath << endl;

	// Device setting
	//DeviceDescriptor ImageProcessing_device = DeviceDescriptor::GetDefaultDevice();
	if (device.GetDeviceKind() == DeviceKind::DeviceKind_GPU) {
		std::cout << "using gpu Device" << endl;
	}
	else {
		std::cout << "using cpu Device" << endl;
	}

	// Define the evaluator network input size
	// It is best if your image size and network input size are the same. (for result accuracy)
	// And usually the bigger the network input size, the better the performance. (for runtime speed)
	//SuaKIT_UInt64 networkH = 1600;
	//SuaKIT_UInt64 networkW = 1600;
	//SuaKIT_UInt64 networkC = 1; // we currently support 1channel or BGR 3channel or BGRA 4channel 

	//	You can select InputDataType from SINGLE, COMPARISON, or MULITIMG.
	// inputDataType and multiImgCount ​​must match the settings of the trained network to be entered.
	/*
	SINGLE (default) : The unit of evalute is one image so multiImgCount value must be 1 (default).
	COMPARISON : The unit of evalute is two images so multiImgCount value must be 2.
	MULITIMG : The unit of evalute is N images. N is set to the value of multiImgCount.
	*/
	//InputDataType inputDataType = InputDataType::SINGLE;
	//SuaKIT_UInt64 multiImgCount = 1;

	maxNetSize = SegmentationEvaluator::GetMaxNetworkSize(wideModelPath.c_str(), device);


	if (networkH * networkW > maxNetSize)
	{
		std::cout << "The network size is greater than the maximum size." << endl;
		return false;
	}
	else
	{
		// Init Evaluator
		//SegmentationEvaluator seg(ImageProcessing_networkPath.c_str(), ImageProcessing_device, networkH, networkW, networkC, inputDataType, multiImgCount);
		status = seg.GetStatus();
		if (status != Status::SUCCESS) {
			std::cout << "Segmentation Initialize Error : " << status << endl;
			std::cout << UnitFunction::GetErrorMessage() << endl;
			return false;

		}
		else
		{
			std::cout << endl << "Segmentation Initialize Complete" << endl << endl;
			numDefect = 0;// var 4
			return true;
		}
	}
}


