#include "../libkface/tlddatabase.h"
#include <opencv/cv.h>

#include <iostream>

using namespace KFaceIface;

class Tldclassify
{
public:
    void groupFaces(QList<QList<IplImage *> > inputFaceList);
public:
    QList<QList<IplImage*> > resizedinputFaceList;
    QList<QList<bool> > tagged;
    QList<QString> groupnames;
    QList<QList<IplImage*> > allGrouped;
    QList<unitFaceModel *> modelsToStore;
};
