#include <iostream>
#include <sqlite3.h>
#include <QList>
#include "../../opentld/libopentld/NormalizedPatch.h"

using namespace std;
using namespace tld;

namespace KFaceIface
{

class Tlddatabase
{
public:
    Tlddatabase();
    bool PrevDatabaseExists;

    sqlite3 *faceDatabase;

    const char *initialiseDatabase;

    sqlite3_stmt *databasePreparingObject;

    ~Tlddatabase();

    class unitFaceModel
    {
    public:
        unitFaceModel();
        int objWidth;

        int objHeight;

        float minVar;

        int numPositivePatches;

        int numNegativePatches;

        int numTrees;

        int numFeatures;

        class unitTree
        {
        public:
            unitTree();
            int numTrees;
            class unitFeature
            {
            public:
                unitFeature();
            };
            class unitLeave
            {
            public:
                unitLeave();
            };
            QList<unitLeave> allLeaves;

            QList<unitFeature> allFeatures;
        };

        QList<NormalizedPatch> allPositivePatches;
        QList<NormalizedPatch> allNegativePatches;
        QList<unitTree> allTrees;

        QList<unitFaceModel> allFaceModel;

    };

};
}
