#include "tlddatabase.h"

namespace KFaceIface

{
class Tlddatabase::unitFaceModel
{
public:

    unitFaceModel()
    {
        int objWidth;

        int objHeight;

        float minVar;

        int numPositivePatches;

        int numNegativePatches;
    }
    class unitPositivePatch
    {
    public:
        unitPositivePatch()
        {
            float unitPositivePatchdata[225];
        }
        ~unitPositivePatch()
        {

        }
    };

    class unitNegativePatch
    {
    public:
        unitNegativePatch()
        {
             float unitNegativePatchdata[225];
        }
        ~unitNegativePatch()
        {

        }
    };

    class unitTree
    {
    public:
        unitTree()
        {
            int numFeatures;
            int numLeaves;
        }
        class unitFeature
        {
        public:
            unitFeature()
            {
                float unitFeaturedata[4];
            }
            ~unitFeature()
            {

            }
        };
        class unitLeave
        {
        public:
            unitLeave()
            {
                int unitLeavedata[3];
            }
            ~unitLeave()
            {

            }
        };
        QList<unitLeave> allLeaves;

        QList<unitFeature> allFeatures;
        ~unitTree()
        {

        }
    };
    QList<unitPositivePatch> allPositivePatches;

    QList<unitNegativePatch> allNegativePatches;

    QList<unitTree> allTrees;

    ~unitFaceModel()
    {

    }
};

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

Tlddatabase::~Tlddatabase()
{
    sqlite3_finalize(databasePreparingObject);

    sqlite3_close(faceDatabase);
}

}


