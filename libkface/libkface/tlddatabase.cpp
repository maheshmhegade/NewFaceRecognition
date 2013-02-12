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

}
Tlddatabase::unitFaceModel::unitTree::unitTree()
{
    int numFeatures;
    int numLeaves;
}
Tlddatabase::unitFaceModel::unitTree::unitFeature::unitFeature()
{
    float unitFeaturedata[4];
}
Tlddatabase::unitFaceModel::unitTree::unitLeave::unitLeave()
{
    int unitLeavedata[3];
}


Tlddatabase::~Tlddatabase()
{
    sqlite3_finalize(databasePreparingObject);

    sqlite3_close(faceDatabase);
}

}


