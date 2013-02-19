#include "tlddatabase.h"

namespace KFaceIface

{

Tlddatabase::Tlddatabase()
{
    this->openFaceDatabase();
    this->createFaceTable();
}
void Tlddatabase::openFaceDatabase()
{
    faceDatabase = QSqlDatabase::addDatabase("QSQLITE");

    faceDatabase.setDatabaseName("faceDatabase.db");

    faceDatabase.open();
}

Tlddatabase::~Tlddatabase()
{
    faceDatabase.close();
}
void Tlddatabase::createFaceTable()
{
    if (faceDatabase.isOpen())
    {
        QSqlQuery query;
        query.exec("create table faceDatabase "
                   "(id integer primary key, "
                   "modelname varchar, "
                   "modelheight integer, "
                   "modelwidth integer, "
                   "modelminvar float, "
                   "positivepatches varchar, "
                   "negativepatches varchar, "
                   "allfeatures varchar, "
                   "allleaves varchar)");

    }
}
int  Tlddatabase::queryNumfacesinDatabase()
{
    QSqlTableModel query;
    query.setTable("faceDatabase");
    query.select();
    return query.rowCount();
}
QString Tlddatabase::querybyFaceid(int faceid)
{
    QSqlQuery query(QString("select * from faceDatabase where id = %1").arg(faceid));
    if (query.next())
    {
        return query.value(1).toString();
    }

    return QString();
}

int Tlddatabase::querybyName(QString nametoquery)
{
    QSqlQuery query(QString("select * from faceDatabase where modelname = %1").arg(nametoquery));
    if (query.next())
    {
        return query.value(1).toInt();
    }

    return -1;
}

void Tlddatabase::insertFaceModel(unitFaceModel *facemodel)
{
    int newId = -1;
    bool ret = false;
    if (faceDatabase.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("insert into faceDatabase values(NULL,'%1',%2,%3,%4,'%5','%6','%7','%8')")
                         .arg(facemodel->Name).arg(facemodel->objHeight).arg(facemodel->objWidth).arg(facemodel->minVar)
                         .arg(facemodel->serialisedPositivePatches).arg(facemodel->serialisedNegativePatches)
                         .arg(facemodel->serialisedFeatures).arg(facemodel->serialisedLeaves));
        // Get database given autoincrement value
        if (ret)
        {
            newId = query.lastInsertId().toInt();
        }
    }
}

unitFaceModel *Tlddatabase::getFaceModel(int faceid)
{
    unitFaceModel *facemodel = new unitFaceModel;
    QSqlQuery query(QString("select * from faceDatabase where id = %1").arg(faceid));
    if (query.next())
    {
        facemodel->faceid = query.value(0).toInt();
        facemodel->Name = query.value(1).toString();
        facemodel->objHeight = query.value(2).toInt();
        facemodel->objWidth = query.value(3).toInt();
        facemodel->minVar = query.value(4).toFloat();
        facemodel->serialisedPositivePatches = query.value(5).toString();
        facemodel->serialisedNegativePatches = query.value(6).toString();
        facemodel->serialisedFeatures = query.value(7).toString() ;
        facemodel->serialisedLeaves = query.value(8).toString();
    }
    return facemodel;
}

IplImage* Tlddatabase::QImage2IplImage(QImage& qimg)
{

    IplImage* const imgHeader = cvCreateImageHeader(cvSize(qimg.width(), qimg.height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData      = (char*) qimg.bits();

    uchar* const newdata      = (uchar*) malloc(sizeof(uchar) * qimg.byteCount());
    memcpy(newdata, qimg.bits(), qimg.byteCount());
    imgHeader->imageData      = (char*) newdata;

    return imgHeader;
}

}
