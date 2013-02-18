#include "tlddatabase.h"

namespace KFaceIface

{
Tlddatabase::Tlddatabase()
{
    main        = new Main();
    config.configure(main);
    srand(main->seed);
    this->openFaceDatabase();
    this->createFaceTable();
}
void Tlddatabase::openFaceDatabase()
{
    faceDatabase = QSqlDatabase::addDatabase("QSQLITE");

    faceDatabase.setDatabaseName("faceDatabase.db");

    faceDatabase.open();
}

Tlddatabase::~Tlddatabase()
{

}
void Tlddatabase::createFaceTable()
{
    if (faceDatabase.isOpen())
    {
        QSqlQuery query;
        query.exec("create table faceDatabase "
                   "(id integer primary key, "
                   "modelname varchar, "
                   "modelheight integer, "
                   "modelwidth integer, "
                   "modelminvar float, "
                   "positivepatches varchar, "
                   "negativepatches varchar, "
                   "allfeatures varchar, "
                   "allleaves varchar)");

    }
}
int  Tlddatabase::queryNumfacesinDatabase()
{
    QSqlQuery query(QString("select * from faceDatabase "));
    return query.size();
}
QString Tlddatabase::querybyFaceid(int faceid)
{
    QSqlQuery query(QString("select * from faceDatabase where id = %1").arg(faceid));
    if (query.next())
    {
        return query.value(2).toString();
    }
}

int Tlddatabase::querybyName(QString nametoquery)
{
    QSqlQuery query(QString("select * from faceDatabase where modelname = %1").arg(nametoquery));
    if (query.next())
    {
        return query.value(1).toInt();
    }
}

void Tlddatabase::insertFaceModel(unitFaceModel *facemodel)
{
    int newId = -1;
    bool ret = false;
    if (faceDatabase.isOpen())
    {
        QSqlQuery query;
        cout << "ghere" << endl;
        ret = query.exec(QString("insert into faceDatabase values(NULL,'%1',%2,%3,%4,'%5','%6','%7','%8')")
                         .arg(facemodel->Name).arg(facemodel->objHeight).arg(facemodel->objWidth).arg(facemodel->minVar)
                         .arg(facemodel->serialisedPositivePatches).arg(facemodel->serialisedNegativePatches)
                         .arg(facemodel->serialisedFeatures).arg(facemodel->serialisedLeaves));
        cout << "ia am" << endl;
        // Get database given autoincrement value
        if (ret)
        {
            newId = query.lastInsertId().toInt();
        }

    }
    qDebug()<< newId;
}

/*void Tlddatabase::updateFaceDatabase(QList<Face>& faces, const QImage& ImageToTld)
{
    foreach(Face face, faces)
    {
        int faceid;
        cout << "one" << endl;
        if ((faceid = this->querybyName(face.name())))//TODO:train/update existing facemodel or create newmodel  based on recognition accuracy
        {
            unitFaceModel *facemodeltostore = new unitFaceModel;
            unitFaceModel *existinmodel = this->getFaceModel(faceid);
            QImage facetotld = ImageToTld.copy(face.toFace().getX1(),face.toFace().getY1(),
                                               face.toFace().getWidth(),face.toFace().getHeight());
            this->d->main->learnandUpdate(facemodeltostore,existinmodel,this->QImage2IplImage(facetotld));
        }
        else if(face.name() != NULL)//store the new face for first time
        {
            cout << "two" << endl;
            unitFaceModel *facemodeltostore = new unitFaceModel;
            QImage facetotld = ImageToTld.copy(face.toFace().getX1(),face.toFace().getY1(),
                                               face.toFace().getWidth(),face.toFace().getHeight());
            this->d->main->generateModel(facemodeltostore,this->QImage2IplImage(facetotld));
            cout << facemodeltostore->objHeight << endl;
            cout << facemodeltostore->objWidth << endl;
            cout << facemodeltostore->minVar << endl;
            this->insertFaceModel(facemodeltostore);
        }
    }
}
void Tlddatabase::recogniseFace(QList<Face>& faces, const QImage& ImageToTld)
{
    foreach(Face face, faces)
    {
        vector<float> recognitionconfidence;
        QImage facetotld = ImageToTld.copy(face.toFace().getX1(),face.toFace().getY1(),
                                           face.toFace().getWidth(),face.toFace().getHeight());
        IplImage *tmpfacetotld = this->QImage2IplImage(facetotld);
        int count = -1;
        for (int i=0 ;i < this->queryNumfacesinDatabase() ; i++ )//find recognition confidence with all facemodel in database
        {
            unitFaceModel *comparefacemodel = this->getFaceModel(i);
            recognitionconfidence.push_back(this->d->main->getRecognitionConfidence(comparefacemodel,tmpfacetotld));
            count ++;
        }
        if(count != -1)//find maximum confidence index and set corresponding string
        {
            int maxConfIndex    = 0;
            float maxConfidence = recognitionconfidence[0];

            for(int tmpInt = 0; tmpInt <= count ; tmpInt++ )
            {
                if(recognitionconfidence[tmpInt] > maxConfidence)
                {
                    maxConfIndex  = tmpInt;
                    maxConfidence = recognitionconfidence[tmpInt];
                }
            }
            if(maxConfidence > 0.6 )
            {
                face.setName(this->querybyFaceid(maxConfIndex));
            }
            cout << "executed " << endl;
        }
    }
}
*/

unitFaceModel *Tlddatabase::getFaceModel(int faceid)
{
    unitFaceModel *facemodel = new unitFaceModel;
    QSqlQuery query(QString("select * from faceDatabase"));
    if (query.next())
    {
        facemodel->faceid = query.value(0).toInt();
        facemodel->Name = query.value(1).toString();
        facemodel->objHeight = query.value(2).toInt();
        facemodel->objWidth = query.value(3).toInt();
        facemodel->minVar = query.value(4).toFloat();
        facemodel->serialisedPositivePatches = query.value(5).toString();
        facemodel->serialisedNegativePatches = query.value(6).toString();
        facemodel->serialisedFeatures = query.value(7).toString() ;
        facemodel->serialisedLeaves = query.value(8).toString();
    }
    return facemodel;
}
IplImage* Tlddatabase::QImage2IplImage(const QImage& qimg) const
{

    IplImage* const imgHeader = cvCreateImageHeader(cvSize(qimg.width(), qimg.height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData      = (char*) qimg.bits();

    uchar* const newdata      = (uchar*) malloc(sizeof(uchar) * qimg.byteCount());
    memcpy(newdata, qimg.bits(), qimg.byteCount());
    imgHeader->imageData      = (char*) newdata;

    return imgHeader;
}
}
