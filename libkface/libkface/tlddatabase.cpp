#include "tlddatabase.h"

namespace KFaceIface

{
Tlddatabase::Tlddatabase()
{

}

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
    QByteArray readArr = QByteArray::fromBase64( serialisedPositivePatches.toAscii());
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
int Tlddatabase::getNumFacesInDatabase()
{
    sqlite3 *faceDatabase;

    sqlite3_stmt *databasePreparingObject;
    sqlite3_open("faceDatabase.db",&faceDatabase); //open database
    return (int)sqlite3_last_insert_rowid(faceDatabase);
}
unitFaceModel *Tlddatabase::getFaceModel(int ID)
{
    sqlite3 *faceDatabase;
    sqlite3_open("faceDatabase.db",&faceDatabase); //open database
    sqlite3_stmt *databasePreparingObject;
    unitFaceModel *faceModel;// = new unitFaceModel;
    const char *getSql = "select * from allFaces";
    sqlite3_prepare_v2(faceDatabase, getSql, -1, &databasePreparingObject, NULL);
    sqlite3_step(databasePreparingObject);
    faceModel = (unitFaceModel *) sqlite3_column_blob(databasePreparingObject,1);
    return faceModel;
}
void Tlddatabase::insertFaceModel(unitFaceModel *serialisedFaceModel,string modelName)
{
    sqlite3 *faceDatabase;

    sqlite3_stmt *databasePreparingObject;
    sqlite3_open("faceDatabase.db",&faceDatabase); //open database

    string insertSqlOne = "INSERT INTO allFaces(ID,MODELDATA) VALUES('1'";
    string insertSqlTwo = ",?)";
    string insertSql = insertSqlOne+insertSqlTwo;
    cout << insertSql << endl;
    //if (sqlite3_prepare_v2(faceDatabase,(const char*)insertSql.c_str() ,-1, &databasePreparingObject, NULL) != SQLITE_OK)
    //{
    //  cout << "inside database" << endl;
    const char *initialiseDatabase = "CREATE TABLE allFaces(ID INTEGER,MODELDATA BLOB)";
    sqlite3_prepare_v2(faceDatabase,initialiseDatabase ,-1, &databasePreparingObject, NULL);
    sqlite3_step(databasePreparingObject);
    sqlite3_prepare_v2(faceDatabase,(const char*)insertSql.c_str() ,-1, &databasePreparingObject, NULL);
    /*}
    else
    {
        cout << "i am" << endl;
    }*/
    sqlite3_bind_blob(databasePreparingObject, 1, serialisedFaceModel, sizeof(serialisedFaceModel), SQLITE_TRANSIENT);
    sqlite3_step(databasePreparingObject);
    sqlite3_finalize(databasePreparingObject);
    sqlite3_exec(faceDatabase, "COMMIT", NULL, NULL, NULL);
    sqlite3_close(faceDatabase);
}

void Tlddatabase::deleteFaceModel(const char* modelName)
{

}

Tlddatabase::~Tlddatabase()
{

}

}
