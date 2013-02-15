#include <iostream>
#include <sqlite3.h>
#include <QList>
#include <QBuffer>
#include <QVariant>
#include <boost/lexical_cast.hpp>
#include "../../opentld/libopentld/NormalizedPatch.h"

using namespace std;
using namespace tld;

namespace KFaceIface
{

class Tlddatabase
{
public:
    Tlddatabase();

    sqlite3 *faceDatabase;

    sqlite3_stmt *databasePreparingObject;

    class unitFaceModel
    {
    public:
        unitFaceModel();
        int objWidth;

        int objHeight;

        float minVar;

        QString serialisedPositivePatches;
        QString serialisedNegativePatches;
        QString serialisedFeatures;
        QString serialisedLeaves;

        void serialisePositivePatches(const QList<QList<float> >&);
        void serialiseNegativePatches(const QList<QList<float> >&);
        void serialiseFeatures(const QList<QList<QList<float> > >&);
        void serialiseLeaves(const QList<QList<QList<int> > >&);
        QList<QList<float> > deserialisePositivePatches();
        QList<QList<float> >  deserialiseNegativePatches();
        QList<QList<QList<float> > > deserialiseFeatures();
        QList<QList<QList<int> > > deserialiseLeaves();
        ~unitFaceModel();

    };
    void insertFaceModel(unitFaceModel,string modelName);
    void deleteFaceModel(const char* modelName);
    ~Tlddatabase();
};
}
