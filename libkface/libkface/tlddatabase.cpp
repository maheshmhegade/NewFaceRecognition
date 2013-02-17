#include "tlddatabase.h"

namespace KFaceIface

{
unitFaceModel::unitFaceModel()
{

}

void unitFaceModel::serialisePositivePatches(const QList<QList<float> >& allPositivePatches)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allPositivePatches;

    writeBuffer.close();

    serialisedPositivePatches = QString(byteArray.toBase64());
}
void unitFaceModel::serialiseNegativePatches(const QList<QList<float> >& allNegativePatches)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allNegativePatches;

    writeBuffer.close();

    serialisedNegativePatches = QString(byteArray.toBase64());
}
void unitFaceModel::serialiseFeatures(const QList<QList<QList<float> > >& allFeatures)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allFeatures;

    writeBuffer.close();

    serialisedFeatures = QString(byteArray.toBase64());
}
void unitFaceModel::serialiseLeaves(const QList<QList<QList<int> > >& allLeaves)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allLeaves;

    writeBuffer.close();

    serialisedLeaves = QString(byteArray.toBase64());
}

QList<QList<float> > unitFaceModel::deserialisePositivePatches()
{
    QByteArray readArr = QByteArray::fromBase64( this->serialisedPositivePatches.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);
    QList<QList<float> > allPositivePatches;

    in >> allPositivePatches;
    return allPositivePatches;
}

QList<QList<float> > unitFaceModel::deserialiseNegativePatches()
{
    QByteArray readArr = QByteArray::fromBase64( serialisedNegativePatches.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<float> > allNegativePatches;

    in >> allNegativePatches;

    return allNegativePatches;
}
QList<QList<QList<float> > > unitFaceModel::deserialiseFeatures()
{
    QByteArray readArr = QByteArray::fromBase64( serialisedFeatures.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<QList<float> > > allFeatures;

    in >> allFeatures;

    return allFeatures;
}
unitFaceModel::~unitFaceModel()
{

}
QList<QList<QList<int> > > unitFaceModel::deserialiseLeaves()
{
    QByteArray readArr = QByteArray::fromBase64( serialisedLeaves.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<QList<int> > > allLeaves;

    in >> allLeaves;

    return allLeaves;
}
bool Tlddatabase::createFaceTable()
{
    bool ret = false;
    if (faceDatabase.isOpen())
    {
        QSqlQuery query;
        ret = query.exec("create table faceDatabase "
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
    return ret;
}

bool Tlddatabase::openFaceDatabase()
{
    faceDatabase = QSqlDatabase::addDatabase("QSQLITE");

    faceDatabase.setDatabaseName("faceDatabase.db");

    return faceDatabase.open();
}

int Tlddatabase::insertFaceModel(unitFaceModel *facemodel)
{
    int newId = -1;
    bool ret = false;
    if (faceDatabase.isOpen())
    {
        QSqlQuery query;
        cout << "ghere" << endl;
        ret = query.exec(QString("insert into faceDatabase values(NULL,'%1',%2,%3,%4,'%5','%6','%7','%8')")
                         .arg(facemodel->Name).arg(facemodel->objHeight).arg(facemodel->objWidth).arg(facemodel->minVar)
                         .arg(facemodel->serialisedPositivePatches).arg(facemodel->serialisedNegativePatches)
                         .arg(facemodel->serialisedFeatures).arg(facemodel->serialisedLeaves));
        cout << "ia am" << endl;
        // Get database given autoincrement value
        if (ret)
        {
            newId = query.lastInsertId().toInt();
        }

    }
    qDebug()<< newId;
    return newId;
}

unitFaceModel *Tlddatabase::getFaceModel(int faceid)
{
    unitFaceModel *facemodel = new unitFaceModel;
    QSqlQuery query(QString("select * from faceDatabase"));
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
}
