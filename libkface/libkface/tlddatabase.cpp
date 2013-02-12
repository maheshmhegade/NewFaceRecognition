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

        float unitPositivePatch[225];

        float unitNegativePatch[225];

        int numTrees;

    }
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
                int unitFeaturedata[3];
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


