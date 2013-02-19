#include <iostream>
#include <sqlite3.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QObject>
#include <QImage>
#include <opencv/cv.h>

#include "Tldrecognition.h"

using namespace std;

namespace KFaceIface
{

class Tlddatabase
{
public:
    Tlddatabase();
    void openFaceDatabase();
    void createFaceTable();
    int querybyName(QString);
    int  queryNumfacesinDatabase();
    QString querybyFaceid(int faceid);
    void insertFaceModel(unitFaceModel*);
    unitFaceModel *getFaceModel(int faceid);
    IplImage* QImage2IplImage(QImage&) ;
    ~Tlddatabase();

private:
    QSqlDatabase faceDatabase;
};
}
