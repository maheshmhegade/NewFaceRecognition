#include "tlddatabase.h"

namespace KFaceIface

{

Tlddatabase::Tlddatabase()
{
    test = "testing";
    sqlite3_open("faceDatabase.db",&faceDatabasepointer);
    sqlite3_prepare_v2(faceDatabasepointer,"CREATE TABLE ",12,&TldPreparingObject,0);

}

Tlddatabase::~Tlddatabase()
{
    sqlite3_finalize(TldPreparingObject);
    sqlite3_close(faceDatabasepointer);
}

}


