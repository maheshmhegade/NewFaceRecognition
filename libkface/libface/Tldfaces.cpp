#include "Tldfaces.h"
using namespace std;
libface::Tldface::Tldface()
{
    main = new Main();
    imAcq = imAcqAlloc();
    gui = new Gui();
    main->gui = gui;
    main->imAcq = imAcq;
    config.configure(main);
    srand(main->seed);
    imAcqInit(imAcq);
}

libface::Tldface::~Tldface()
{
 //   delete main;
}

int libface::Tldface::writeModelTofile(IplImage *inputImage, const char *faceModelFilename)
{
    float *dummyVariable;
    main->doWork(inputImage,faceModelFilename,1,dummyVariable);
}

float libface::Tldface::getRecognitionConfidence(IplImage *inputImage, const char *faceModelFilename)
{
    float *recognitionConfidence;
    main->doWork(inputImage,faceModelFilename,2,recognitionConfidence);
    return (*recognitionConfidence);
}

int libface::Tldface::updateDatabase(IplImage *inputImage, const char *faceModelFilename)
{
    //main->doWork(inputImage,faceModelFilename,3);
    return 0;
}

IplImage libface::Tldface::QImage2IplImage(QImage qimg)
{

    IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg.width(), qimg.height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData = (char*) qimg.bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg.byteCount());
    memcpy(newdata, qimg.bits(), qimg.byteCount());
    imgHeader->imageData = (char*) newdata;
    return (*imgHeader);
}

