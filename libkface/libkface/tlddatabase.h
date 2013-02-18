#include <iostream>
#include <sqlite3.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QImage>

#include "../../opentld/tldmain/Config.h"

using namespace std;
using tld::Config;
namespace KFaceIface
{
class Tlddatabase
{
public:
    Main*  main;
    Config config;
public:
    Tlddatabase();
    void openFaceDatabase();
    void createFaceTable();
    int querybyName(QString);
    int  queryNumfacesinDatabase();
    QString querybyFaceid(int faceid);
    void insertFaceModel(unitFaceModel*);
    void configureMain();
    IplImage* QImage2IplImage(const QImage& qimg) const;
    unitFaceModel *getFaceModel(int faceid);
    ~Tlddatabase();

private:
    QSqlDatabase faceDatabase;
};
}
