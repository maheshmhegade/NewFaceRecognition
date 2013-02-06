#include "Main.h"

#include "Config.h"
#include "../libopentld/ImAcq.h"
#include "Gui.h"
#include "../libopentld/TLDUtil.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace tld;
using namespace cv;

void Main::doWork(IplImage* img,const char* faceModelFileName,int mode)
{
    Mat grey(img->height, img->width, CV_8UC1);
    cvNamedWindow("jok");
    cvShowImage("jok",img);
    cvWaitKey(0);
    cvtColor(cv::Mat(img), grey,0);// CV_BGR2GRAY);

    tld->detectorCascade->imgWidth = grey.cols;
    tld->detectorCascade->imgHeight = grey.rows;
    tld->detectorCascade->imgWidthStep = grey.step;

    if(mode == 1)//write modeltofile
    {
        initialBB = new int[4];
        initialBB[0] = 5;
        initialBB[1] = 5;
        initialBB[2] = img->width-5;
        initialBB[3] = img->height-5;
        Rect bb = tldArrayToRect(initialBB);

        tld->selectObject(grey, &bb);
        cout << "he he" << endl;
        cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);

        tld->processImage(img);

        tld->writeToFile(faceModelFileName);
    }

    else if(mode == 2)//return recognitionconfidence
    {
        tld->readFromFile(faceModelFileName);//modelPath);
        cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);
        tld->processImage(img);
        std::cout<< tld->currConf<<std::endl;
    }
    else

      return;
}
