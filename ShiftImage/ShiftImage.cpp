// ShiftImage.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <string.h>
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <fstream>
#include <string>
//#define OPEN_DEBUG 1
using namespace cv;
using namespace std;
//float rotate_angle = 0;
int x_offset_val = 0;
int y_offset_val = 0;


void Shifting(IplImage* img_in, char *outputpath, int &file_num_count, int layer_num)
{
	IplImage* img_working = cvCreateImage(cvGetSize(img_in), 8, 1);
	IplImage* img_bigger;
	int x_offset = x_offset_val;
	int y_offset = y_offset_val;
	cvCvtColor(img_in, img_working, CV_BGR2GRAY);
	char outputimgname[128] = { 0 };
	//sprintf(outputimgname, "%s%d.jpg", outputpath,i);
	//----------------------先貼到一個向外擴兩倍的 black image----------------------  
	CvSize bigger_cvsize;
	bigger_cvsize.width = img_working->width * 2;
	bigger_cvsize.height = img_working->height * 2;
	img_bigger = cvCreateImage(bigger_cvsize, img_working->depth, img_working->nChannels);
	cvSet(img_bigger, cvScalar(0, 0, 0));
	CvRect bigger_rect;
	bigger_rect.x = (bigger_cvsize.width - img_working->width) / 2;
	bigger_rect.y = (bigger_cvsize.height - img_working->height) / 2;
	bigger_rect.width = img_working->width;
	bigger_rect.height = img_working->height;
	cvSetImageROI(img_bigger, bigger_rect);
	cvCopy(img_working, img_bigger);
	cvResetImageROI(img_bigger);
	#ifdef OPEN_DEBUG
	cvShowImage("img_in", img_in);
	cvWaitKey(0);
	cvShowImage("img_bigger", img_bigger);
	cvWaitKey(0);
	#endif
	//sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //0
	//file_num_count++;
	//cvSaveImage(outputimgname, img_in);
	//---------------------------------------------------------------------

	CvRect Grab_rect;
	Grab_rect.x = (bigger_cvsize.width - img_working->width) / 2;
	Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2);
	Grab_rect.width = img_working->width;
	Grab_rect.height = img_working->height;
	IplImage* cropped = cvCreateImage(cvSize(Grab_rect.width, Grab_rect.height), img_working->depth, img_working->nChannels);

	//---------------------------------------------------------------------
	for (int i = 0; i < layer_num; i++)
	{
		Grab_rect.x = ((bigger_cvsize.width - img_working->width) / 2) - x_offset;
		Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2);
		cvSetImageROI(img_bigger, Grab_rect);
		cvCopy(img_bigger, cropped);
#ifdef OPEN_DEBUG
		cvShowImage("cropped", cropped);
		cvWaitKey(0);
#endif
		cvResetImageROI(img_bigger);
		sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //1
		cvSaveImage(outputimgname, cropped);
		file_num_count++;
		//---------------------------------------------------------------------
		Grab_rect.x = ((bigger_cvsize.width - img_working->width) / 2) + x_offset;
		Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2);
		cvSetImageROI(img_bigger, Grab_rect);
		cvCopy(img_bigger, cropped);
#ifdef OPEN_DEBUG
		cvShowImage("cropped", cropped);
		cvWaitKey(0);
#endif
		cvResetImageROI(img_bigger);
		sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //2
		cvSaveImage(outputimgname, cropped);
		file_num_count++;
		//---------------------------------------------------------------------
		Grab_rect.x = ((bigger_cvsize.width - img_working->width) / 2);
		Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2) - y_offset;
		cvSetImageROI(img_bigger, Grab_rect);
		cvCopy(img_bigger, cropped);
#ifdef OPEN_DEBUG
		cvShowImage("cropped", cropped);
		cvWaitKey(0);
#endif
		cvResetImageROI(img_bigger);
		sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count);//3
		cvSaveImage(outputimgname, cropped);
		file_num_count++;
		//---------------------------------------------------------------------
		Grab_rect.x = ((bigger_cvsize.width - img_working->width) / 2);
		Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2) + y_offset;
		cvSetImageROI(img_bigger, Grab_rect);
		cvCopy(img_bigger, cropped);
#ifdef OPEN_DEBUG
		cvShowImage("cropped", cropped);
		cvWaitKey(0);
#endif
		cvResetImageROI(img_bigger);
		sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //4
		cvSaveImage(outputimgname, cropped);
		file_num_count++;
		//---------------------------------------------------------------------
		/*Grab_rect.x = (bigger_cvsize.width - img_working->width) / 2 + x_offset;
		Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2) + y_offset;
		cvSetImageROI(img_bigger, Grab_rect);
		cvCopy(img_bigger, cropped);
#ifdef OPEN_DEBUG
		cvShowImage("cropped", cropped);
		cvWaitKey(0);
#endif
		cvResetImageROI(img_bigger);
		sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //5
		cvSaveImage(outputimgname, cropped);
		file_num_count++;
		//---------------------------------------------------------------------
		Grab_rect.x = (bigger_cvsize.width - img_working->width) / 2 + x_offset;
		Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2) - y_offset;
		cvSetImageROI(img_bigger, Grab_rect);
		cvCopy(img_bigger, cropped);
#ifdef OPEN_DEBUG
		cvShowImage("cropped", cropped);
		cvWaitKey(0);
#endif
		cvResetImageROI(img_bigger);
		sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //6
		cvSaveImage(outputimgname, cropped);
		file_num_count++;
		//---------------------------------------------------------------------
		Grab_rect.x = (bigger_cvsize.width - img_working->width) / 2 - x_offset;
		Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2) + y_offset;
		cvSetImageROI(img_bigger, Grab_rect);
		cvCopy(img_bigger, cropped);
#ifdef OPEN_DEBUG
		cvShowImage("cropped", cropped);
		cvWaitKey(0);
#endif
		cvResetImageROI(img_bigger);
		sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //7
		cvSaveImage(outputimgname, cropped);
		file_num_count++;
		//---------------------------------------------------------------------
		Grab_rect.x = (bigger_cvsize.width - img_working->width) / 2 - x_offset;
		Grab_rect.y = ((bigger_cvsize.height - img_working->height) / 2) - y_offset;
		cvSetImageROI(img_bigger, Grab_rect);
		cvCopy(img_bigger, cropped);
#ifdef OPEN_DEBUG
		cvShowImage("cropped", cropped);
		cvWaitKey(0);
#endif
		cvResetImageROI(img_bigger);
		sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //8
		cvSaveImage(outputimgname, cropped);
		file_num_count++;*/
		//----------------------------------------------------------------------
		y_offset += y_offset_val;
		x_offset += x_offset_val;
	}
}
void Crop_16x16(IplImage* img_in, char *outputpath, int &file_num_count)
{
	IplImage* img_working = cvCreateImage(cvGetSize(img_in), 8, 1);
	cvCvtColor(img_in, img_working, CV_BGR2GRAY);
	char outputimgname[128] = { 0 };
	int x_center = (28 - 16) / 2;
	int y_center = (28 - 16) / 2;

	CvRect Grab_rect;
	Grab_rect.x = x_center - 2;
	Grab_rect.y = y_center - 2;
	Grab_rect.width = 16;
	Grab_rect.height = 16;
	IplImage* cropped = cvCreateImage(cvSize(Grab_rect.width, Grab_rect.height), img_working->depth, img_working->nChannels);
	cvSetImageROI(img_working, Grab_rect);
	cvCopy(img_working, cropped);
	cvResetImageROI(img_working);

	CvSize bigger_cvsize;
	bigger_cvsize.width = 28;
	bigger_cvsize.height = 28;
	IplImage* img_bigger = cvCreateImage(bigger_cvsize, img_working->depth, img_working->nChannels);
	cvSet(img_bigger, cvScalar(0, 0, 0));
	CvRect bigger_rect;
	bigger_rect.x = (bigger_cvsize.width - cropped->width) / 2;
	bigger_rect.y = (bigger_cvsize.height - cropped->height) / 2;
	bigger_rect.width = cropped->width;
	bigger_rect.height = cropped->height;
	cvSetImageROI(img_bigger, bigger_rect);
	cvCopy(cropped, img_bigger);
	cvResetImageROI(img_bigger);
	//--------------------------------------------------------------
	/*
	sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count);
	file_num_count++;
	cvSaveImage(outputimgname, cropped);

	//--------------------------------------------------------------
	Grab_rect.x = x_center + 2;
	Grab_rect.y = y_center + 2;
	cvSetImageROI(img_working, Grab_rect);
	cvCopy(img_working, cropped);
	cvResetImageROI(img_working);

	cvSet(img_bigger, cvScalar(0, 0, 0));
	cvSetImageROI(img_bigger, bigger_rect);
	cvCopy(cropped, img_bigger);
	cvResetImageROI(img_bigger);
	sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count);
	file_num_count++;
	cvSaveImage(outputimgname, cropped);
	//--------------------------------------------------------------
	Grab_rect.x = x_center - 2;
	Grab_rect.y = y_center + 2;
	cvSetImageROI(img_working, Grab_rect);
	cvCopy(img_working, cropped);
	cvResetImageROI(img_working);

	cvSet(img_bigger, cvScalar(0, 0, 0));
	cvSetImageROI(img_bigger, bigger_rect);
	cvCopy(cropped, img_bigger);
	cvResetImageROI(img_bigger);
	sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count);
	file_num_count++;
	cvSaveImage(outputimgname, cropped);
	//--------------------------------------------------------------
	Grab_rect.x = x_center + 2;
	Grab_rect.y = y_center - 2;
	cvSetImageROI(img_working, Grab_rect);
	cvCopy(img_working, cropped);
	cvResetImageROI(img_working);

	cvSet(img_bigger, cvScalar(0, 0, 0));
	cvSetImageROI(img_bigger, bigger_rect);
	cvCopy(cropped, img_bigger);
	cvResetImageROI(img_bigger);
	sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count);
	file_num_count++;
	cvSaveImage(outputimgname, cropped);*/

	//--------------------------------------------------------------
	Grab_rect.x = x_center;
	Grab_rect.y = y_center;
	cvSetImageROI(img_working, Grab_rect);
	cvCopy(img_working, cropped);
	cvResetImageROI(img_working);

	cvSet(img_bigger, cvScalar(0, 0, 0));
	cvSetImageROI(img_bigger, bigger_rect);
	cvCopy(cropped, img_bigger);
	cvResetImageROI(img_bigger);
	sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count);
	file_num_count++;
	cvSaveImage(outputimgname, img_bigger);
}


void rotateImage(const Mat& source, double angle, char *outputpath, int count)
{
	char outputimgname[128] = { 0 };
	Point2f src_center(source.cols / 2.0F, source.rows / 2.0F);
	Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);
	Mat dst;
	warpAffine(source, dst, rot_mat, source.size());
	sprintf(outputimgname, "%s%d.jpg", outputpath, count);
	imwrite(outputimgname, dst);
#ifdef OPEN_DEBUG
	namedWindow("rotateImage", CV_WINDOW_AUTOSIZE);
	imshow("rotateImage", dst);
	waitKey(0);
#endif
}

void UpScaling(IplImage *img_input, float Scaling_scale, char *outputpath, int count)
{
	char outputimgname[128] = { 0 };
	IplImage *bigger = 0;
	CvSize bigger_cvsize;
	bigger_cvsize.width = img_input->width * Scaling_scale;
	bigger_cvsize.height = img_input->height * Scaling_scale;
	bigger = cvCreateImage(bigger_cvsize, img_input->depth, img_input->nChannels);
	cvResize(img_input, bigger, CV_INTER_CUBIC);
#ifdef OPEN_DEBUG
	cvShowImage("bigger", bigger);
	cvWaitKey(0);
#endif
	CvRect bigger_rect;
	bigger_rect.x = (bigger_cvsize.width - img_input->width) / 2;
	bigger_rect.y = (bigger_cvsize.height - img_input->height) / 2;
	bigger_rect.width = img_input->width;
	bigger_rect.height = img_input->height;
	IplImage* img_cropped = cvCreateImage(cvSize(bigger_rect.width, bigger_rect.height), img_input->depth, img_input->nChannels);
	cvSetImageROI(bigger, bigger_rect);
	cvCopy(bigger, img_cropped);
	cvResetImageROI(bigger);

	sprintf(outputimgname, "%s%d.jpg", outputpath, count);
	cvSaveImage(outputimgname, img_cropped);
#ifdef OPEN_DEBUG
	cvShowImage("img_cropped", img_cropped);
	cvWaitKey(0);
#endif

}

void DownScaling(IplImage *img_input, float Scaling_scale, char *outputpath, int count)
{
	char outputimgname[128] = { 0 };
	IplImage *smaller = 0;
	CvSize smaller_cvsize;
	smaller_cvsize.width = img_input->width * Scaling_scale;
	smaller_cvsize.height = img_input->height * Scaling_scale;
	smaller = cvCreateImage(smaller_cvsize, img_input->depth, img_input->nChannels);
	cvResize(img_input, smaller, CV_INTER_CUBIC);
#ifdef OPEN_DEBUG
	cvShowImage("bigger", smaller);
	cvWaitKey(0);
#endif
	CvRect smaller_rect;
	smaller_rect.x = abs((smaller_cvsize.width - img_input->width)) / 2;
	smaller_rect.y = abs((smaller_cvsize.height - img_input->height)) / 2;
	smaller_rect.width = smaller_cvsize.width;
	smaller_rect.height = smaller_cvsize.height;
	IplImage* img_cropped = cvCreateImage(cvSize(img_input->width, img_input->height), img_input->depth, img_input->nChannels);
	cvSet(img_cropped, cvScalar(0, 0, 0));
	cvSetImageROI(img_cropped, smaller_rect);
	cvCopy(smaller, img_cropped);
	cvResetImageROI(img_cropped);

	sprintf(outputimgname, "%s%d.jpg", outputpath, count);
	cvSaveImage(outputimgname, img_cropped);
#ifdef OPEN_DEBUG
	cvShowImage("img_cropped", img_cropped);
	cvWaitKey(0);
#endif
}


void Preprocessing(Mat& img_in, IplImage* Ipl_input, char *outputpath, bool Scalingenable, bool Rotateenable, bool Shiftenable, bool Crop16x16enable, int layer_num, float rotate_angle)
{
	IplImage* img_working = cvCreateImage(cvGetSize(Ipl_input), 8, 1);
	cvCvtColor(Ipl_input, img_working, CV_BGR2GRAY);
	IplImage* img_cropped, *FatImage;
	FatImage = cvCreateImage(cvGetSize(Ipl_input), 8, 1);
	int file_num_count = 0;
	//int layer_num = 5;
	char outputimgname[128] = { 0 };

	sprintf(outputimgname, "%s%d.jpg", outputpath, file_num_count); //0
	file_num_count++;
	cvSaveImage(outputimgname, Ipl_input);

#ifdef OPEN_DEBUG
	cvShowImage("Ipl_input", Ipl_input);
	cvWaitKey(0);
#endif
	//-----------------------------rotate----------------------------
	if (Rotateenable)
	{
		rotateImage(img_in, rotate_angle, outputpath, file_num_count);
		file_num_count++;
	}
	//-----------------------------scaling----------------------------
	if (Scalingenable)
	{
		//UpScaling(img_working,1.2, outputpath, file_num_count);
		//file_num_count++;
		DownScaling(img_working, 0.8, outputpath, file_num_count);
		file_num_count++;
		//UpScaling(img_working, 1.3, outputpath, file_num_count);
		//file_num_count++;
		//UpScaling(img_working, 1.4, outputpath, file_num_count);
		//file_num_count++;
	}
	//----------------------------------------------------------------
	if (Shiftenable)
	{
		Shifting(Ipl_input, outputpath, file_num_count, layer_num);
	}
	if (Crop16x16enable)
	{
		Crop_16x16(Ipl_input, outputpath, file_num_count);
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	char readimgname[128] = { 0 };
	char outputimgname[128] = { 0 };
	int index = 4;
	int filenumber = 100;
	float rotate_angle = 0;
	Mat img;
	bool Scalingenable = true;
	bool Rotateenable = true;
	bool Shiftenable = true;
	bool Crop16x16enable = true;
	int layer_num = 1;
	string file_contents;
	ifstream file("ShiftParam.txt");
	string str;
	int readfile_count = 0;
	while (std::getline(file, str))
	{
		file_contents = str;
		switch (readfile_count)
		{
		case 0:
			index = stoi(file_contents);
			break;
		case 1:
			filenumber = stoi(file_contents);
			break;
		case 2:
			Rotateenable = stoi(file_contents);
			break;
		case 3:
			Scalingenable = stoi(file_contents);
			break;
		case 4:
			Shiftenable = stoi(file_contents);
			break;
		case 5:
			Crop16x16enable = stoi(file_contents);
			break;
		case 6:
			layer_num = stoi(file_contents);
			break;
		case 7:
			rotate_angle = stof(file_contents);
			break;
		case 8:
			x_offset_val = stoi(file_contents);
			break;
		case 9:
			y_offset_val = stoi(file_contents);
			break;
		}
		readfile_count++;
	}

	for (int j = 1; j <= filenumber; j++)
	{
		sprintf(readimgname, "D:\\Skywawtch\\Working\\caffe\\outputROI\\%d\\%d_BoundingBox\\test (%d).jpg", index, index, j);
		sprintf(outputimgname, "D:\\Skywawtch\\Working\\caffe\\%d_BoundingBox\\ImageSet\\test (%d)_", index, j);
		img = imread(readimgname);
		IplImage* img_in = cvLoadImage(readimgname, 1);
		Preprocessing(img, img_in, outputimgname, Scalingenable, Rotateenable, Shiftenable, Crop16x16enable, layer_num, rotate_angle);
		printf("done ");
		printf(readimgname); printf("\r\n");
	}
	printf("finish!");
	return 0;
}

