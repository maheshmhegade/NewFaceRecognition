#include "tlddatabase.h"

namespace KFaceIface

{
Tlddatabase::Tlddatabase()
{
    sqlite3_open("faceDatabase.db",&faceDatabase); //open database
}

Tlddatabase::unitFaceModel::unitFaceModel()
{

}
void Tlddatabase::unitFaceModel::serialisePositivePatches(const QList<QList<float> >& allPositivePatches)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allPositivePatches;

    writeBuffer.close();

    serialisedPositivePatches = QString(byteArray.toBase64());
}
void Tlddatabase::unitFaceModel::serialiseNegativePatches(const QList<QList<float> >& allNegativePatches)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allNegativePatches;

    writeBuffer.close();

    serialisedNegativePatches = QString(byteArray.toBase64());
}
void Tlddatabase::unitFaceModel::serialiseFeatures(const QList<QList<QList<float> > >& allFeatures)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allFeatures;

    writeBuffer.close();

    serialisedFeatures = QString(byteArray.toBase64());
}
void Tlddatabase::unitFaceModel::serialiseLeaves(const QList<QList<QList<int> > >& allLeaves)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allLeaves;

    writeBuffer.close();

    serialisedLeaves = QString(byteArray.toBase64());
}

QList<QList<float> > Tlddatabase::unitFaceModel::deserialisePositivePatches()
{
    QByteArray readArr = QByteArray::fromBase64( serialisedPositivePatches.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<float> > allPositivePatches;

    in >> allPositivePatches;

    return allPositivePatches;
}

QList<QList<float> > Tlddatabase::unitFaceModel::deserialiseNegativePatches()
{
    QByteArray readArr = QByteArray::fromBase64( serialisedNegativePatches.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<float> > allNegativePatches;

    in >> allNegativePatches;

    return allNegativePatches;
}
QList<QList<QList<float> > > Tlddatabase::unitFaceModel::deserialiseFeatures()
{
    QByteArray readArr = QByteArray::fromBase64( serialisedFeatures.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<QList<float> > > allFeatures;

    in >> allFeatures;

    return allFeatures;
}
QList<QList<QList<int> > > Tlddatabase::unitFaceModel::deserialiseLeaves()
{
    QByteArray readArr = QByteArray::fromBase64( serialisedLeaves.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<QList<int> > > allLeaves;

    in >> allLeaves;

    return allLeaves;
}

void Tlddatabase::insertFaceModel(unitFaceModel serialisedFaceModel,string modelName)
{
    string insertSqlOne = "INSERT INTO allFaces(FACENAME,MODELDATA) VALUES(";
    string insertSqlTwo = "serialisedFaceModel)";
    string insertSql = insertSqlOne+modelName+insertSqlTwo;
    if (sqlite3_prepare_v2(faceDatabase,insertSql.c_str() ,-1, &databasePreparingObject, NULL) != SQLITE_OK)
    {
        const char *initialiseDatabase;
        initialiseDatabase = "CREATE TABLE allFaces(ID INTEGER,FACENAME TEXT,MODELDATA BLOB)";
        sqlite3_prepare_v2(faceDatabase,insertSql.c_str() ,-1, &databasePreparingObject, NULL);
    }
    sqlite3_step(databasePreparingObject);
    sqlite3_finalize(databasePreparingObject);
    sqlite3_exec(faceDatabase, "COMMIT", NULL, NULL, NULL);
}

void Tlddatabase::deleteFaceModel(const char* modelName)
{

}

Tlddatabase::~Tlddatabase()
{
    sqlite3_finalize(databasePreparingObject);

    sqlite3_close(faceDatabase);
}

}
