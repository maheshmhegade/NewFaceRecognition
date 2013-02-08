#include <sqlite3.h>

namespace KFaceIface
{

class Tlddatabase
{
public:
    sqlite3 *faceDatabasepointer;
    const char *test;
    sqlite3_stmt *TldPreparingObject;
    Tlddatabase();
    ~Tlddatabase();

};

}

