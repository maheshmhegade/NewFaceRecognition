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
class unitFaceModel
{
public:
    unitFaceModel();
    int objHeight;

    int objWidth;

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
class Tlddatabase
{
public:
    Tlddatabase();
    unitFaceModel *getFaceModel(int Id);
    int getNumFacesInDatabase();
    void insertFaceModel(unitFaceModel *,string modelName);
    void deleteFaceModel(const char* modelName);
    ~Tlddatabase();
};
}
