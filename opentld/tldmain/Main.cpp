#include "Main.h"

#include "Config.h"
#include "../libopentld/TLDUtil.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace tld;
using namespace cv;

unitFaceModel* Main::generateModel(IplImage* faceImage)
{
    unitFaceModel *generatedmodel = new unitFaceModel;
    Mat grey(faceImage->height, faceImage->width, CV_8UC1);
    cvtColor(cv::Mat(faceImage), grey,CV_BGR2GRAY);// CV_BGR2GRAY);

    tld->detectorCascade->imgWidth = grey.cols;
    tld->detectorCascade->imgHeight = grey.rows;
    tld->detectorCascade->imgWidthStep = grey.step;
    initialBB = new int[4];
    initialBB[0] = 5;
    initialBB[1] = 5;
    initialBB[2] = faceImage->width-5;
    initialBB[3] = faceImage->height-5;
    Rect bb = tldArrayToRect(initialBB);
    tld->selectObject(grey, &bb);
    cvtColor(cv::Mat(faceImage), grey, CV_BGR2GRAY);
    generatedmodel = tld->putObjModel();//dataBase->getFaceModel(0);
    return generatedmodel;
}

float Main::getRecognitionConfidence(unitFaceModel* comparefacemodel,IplImage* faceimgae)
{
    tld->getObjModel(comparefacemodel);
    Mat grey(faceimgae->height, faceimgae->width, CV_8UC1);
    cvtColor(cv::Mat(faceimgae), grey,CV_BGR2GRAY);// CV_BGR2GRAY);
    tld->processImage(faceimgae);
    return tld->currConf;
}

bool Main::learnandUpdate(unitFaceModel *unifacemodel,unitFaceModel *existingmodel,IplImage* faceimage)
{
    return false;//return new facemodel if confidence is below thresshold otherwise update the model
}
