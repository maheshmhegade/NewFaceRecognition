#include <iostream>
#include <sqlite3.h>
#include <QList>

using namespace std;

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

    class unitFaceModel;

    QList<unitFaceModel> allFaceModel;

};

}

