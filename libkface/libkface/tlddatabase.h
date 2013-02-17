#include <iostream>
#include <sqlite3.h>
#include <QList>
#include <QBuffer>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QObject>

#include "../../opentld/libopentld/NormalizedPatch.h"

using namespace std;
using namespace tld;

namespace KFaceIface
{
class unitFaceModel
{
public:
    unitFaceModel();

    int faceid;

    QString Name;

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

public:
    bool openFaceDatabase();
    bool createFaceTable();
    int insertFaceModel(unitFaceModel*);
    unitFaceModel *getFaceModel(int id);

private:
    QSqlDatabase faceDatabase;
};
}
