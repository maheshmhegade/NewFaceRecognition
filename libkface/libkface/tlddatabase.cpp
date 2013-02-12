#include "tlddatabase.h"

namespace KFaceIface

{
Tlddatabase::Tlddatabase()
{
    initialiseDatabase = "CREATE TABLE allFaces(ID INTEGER,FACENAME TEXT,MODELDATA BLOB)";

    sqlite3_open("faceDatabase.db",&faceDatabase); //open database

    //    PrevDatabaseExists =                              //check for previous data in database

    if(~PrevDatabaseExists)
    {
        sqlite3_prepare_v2(faceDatabase, initialiseDatabase, -1, &databasePreparingObject,NULL );
        sqlite3_step(databasePreparingObject);
    }

    //sqlite3_prepare_v2(faceDatabase,,-1,&TldPreparingObject,NULL);


}

Tlddatabase::unitFaceModel::unitFaceModel()
{
    unitTreeObject = new unitTree;
}
Tlddatabase::unitFaceModel::~unitFaceModel()
{
    delete unitTreeObject;
}
Tlddatabase::unitFaceModel::unitTree::unitTree()
{
    unitFeatureObject = new unitFeature;
    unitLeaveObject = new unitLeave;
}
Tlddatabase::unitFaceModel::unitTree::~unitTree()
{
    delete unitFeatureObject;
    delete unitLeaveObject;
}
Tlddatabase::unitFaceModel::unitTree::unitFeature::unitFeature()
{

}
Tlddatabase::unitFaceModel::unitTree::unitFeature::~unitFeature()
{

}
Tlddatabase::unitFaceModel::unitTree::unitLeave::unitLeave()
{

}
Tlddatabase::unitFaceModel::unitTree::unitLeave::~unitLeave()
{

}


Tlddatabase::~Tlddatabase()
{
    sqlite3_finalize(databasePreparingObject);

    sqlite3_close(faceDatabase);
}

}


