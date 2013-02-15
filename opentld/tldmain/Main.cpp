#include "Main.h"

#include "Config.h"
#include "../libopentld/TLDUtil.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace tld;
using namespace cv;

void Main::doWork(IplImage* img,const char* faceModelFileName,int mode,float *recognitionCaonfidence)
{
    Mat grey(img->height, img->width, CV_8UC1);

    cvtColor(cv::Mat(img), grey,CV_BGR2GRAY);// CV_BGR2GRAY);
    //imshow("ty",im);
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

        cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);
        tld->writeToFile(faceModelFileName);
        printFaceModel();
    }

    else if(mode == 2)//return recognitionconfidence
    {
        tld->readFromFile(faceModelFileName);//modelPath);
        cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);
        tld->processImage(img);
        (*recognitionCaonfidence) = tld->currConf;
    }
    else

        return;
}

void Main::printFaceModel()//for verifying object parameters
{
/*    faceModelObject = tld->putObjModel();
    cout << faceModelObject->objWidth << endl;
    cout << faceModelObject->objHeight << endl;
    cout << faceModelObject->minVar << endl;
    cout << faceModelObject->numPositivePatches <<endl;
    cout << faceModelObject->numNegativePatches <<endl;
    cout << faceModelObject->numFeatures <<endl;
    cout << faceModelObject->numTrees <<endl;
    for (int j=0;j < faceModelObject->numPositivePatches;j++)
    {
        for (int i=0; i< 225;i++)
        {
            cout << faceModelObject->allPositivePatches.at(j).imageData[i] << endl;
        }
    }
    for (int i=0;i<faceModelObject->numTrees;i++)
    {
        for(int j=0;j<faceModelObject->numFeatures;j++)

        {
            for(int k=0;k<4;k++)
            {
                cout<<faceModelObject->allTrees.at(i).allFeatures.at(j).unitFeaturedata[k] <<"\t";
            }
            cout << endl;
        }

        for (int j=0;j<faceModelObject->allTrees.at(i).numLeaves;j++)
        {
            for(int k=0;k<3;k++)
            {
                cout<< faceModelObject->allTrees.at(i).allLeaves.at(j).unitLeavePositivedata[k]<< "\t";
                cout <<faceModelObject->allTrees.at(i).allLeaves.at(j).unitLeaveNegativedata[k] << "\t";
            }
            cout << endl;
        }
    }
*/
}
