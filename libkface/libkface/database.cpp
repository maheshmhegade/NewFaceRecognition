/** ===========================================================
 * @file
 *
 * This file is a part of digiKam project
 * <a href="http://www.digikam.org">http://www.digikam.org</a>
 *
 * @date   2010-06-16
 * @brief  The Database class wraps the libface database
 *
 * @author Copyright (C) 2010-2013 by Marcel Wiesweg
 *         <a href="mailto:marcel dot wiesweg at gmx dot de">marcel dot wiesweg at gmx dot de</a>
 * @author Copyright (C) 2010 by Aditya Bhatt
 *         <a href="mailto:adityabhatt1991 at gmail dot com">adityabhatt1991 at gmail dot com</a>
 * @author Copyright (C) 2010-2013 by Gilles Caulier
 *         <a href="mailto:caulier dot gilles at gmail dot com">caulier dot gilles at gmail dot com</a>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "database.h"

// Qt includes

#include <QMutex>
#include <QMutexLocker>
#include <QSharedData>
#include <QFile>

// KDE includes

#include <kdebug.h>
#include <kstandarddirs.h>

// Libface includes

#include "../libface/LibFace.h"
#include "../libface/Face.h"

// Local includes

#include "kfaceutils.h"
#include "image_p.h"

using namespace std;
using namespace libface;

namespace KFaceIface
{

class Database::Private : public QSharedData
{
public:

    Private()
        : mappingFilename(QString("/dictionary")),
          haarCascasdePath(KStandardDirs::installPath("data") + QString("libkface/haarcascades"))
    {
        libface          = 0;
        configDirty      = false;
    }

    ~Private()
    {
        saveConfig();

        try
        {
            delete libface;
        }
        catch (cv::Exception& e)
        {
            kError() << "cv::Exception:" << e.what();
        }
        catch(...)
        {
            kDebug() << "cv::Exception";
        }
    }

    void saveConfig()
    {
        try
        {
            if ((initFlags & Database::InitRecognition) && configDirty)
            {
                libface->saveConfig(configPath.toStdString());
                configDirty = false;
            }
        }
        catch (cv::Exception& e)
        {
            kError() << "cv::Exception:" << e.what();
        }
        catch(...)
        {
            kDebug() << "cv::Exception";
        }
    }

public:

    libface::LibFace*   libface;
    Database::InitFlags initFlags;
    QHash<QString, int> hash;
    QString             configPath;
    bool                configDirty;
    const QString       mappingFilename;
    const QString       haarCascasdePath;
};

Database::Database(InitFlags flags, const QString& configurationPath)
    : d(new Private)
{
    // Note: same lines in RecognitionDatabase. Keep in sync.
    if (configurationPath.isNull())
        d->configPath = KStandardDirs::locateLocal("data", "libkface/database/", true);
    else
        d->configPath = configurationPath;

    d->hash      = KFaceUtils::hashFromFile(d->configPath + d->mappingFilename);
    d->initFlags = flags;

    try
    {
        if (flags == InitDetection)
        {
            d->libface = new libface::LibFace(libface::DETECT, d->configPath.toStdString(), d->haarCascasdePath.toStdString());
        }
        else
        {
            libface::Mode mode;

            if (flags == InitAll)
                mode = libface::ALL;
            else
                mode = libface::EIGEN;

            d->libface = new libface::LibFace(mode, d->configPath.toStdString(), d->haarCascasdePath.toStdString());
        }
    }
    catch (cv::Exception& e)
    {
        kError() << "cv::Exception:" << e.what();
    }
    catch(...)
    {
        kDebug() << "cv::Exception";
    }

    if (flags & InitDetection)
        this->setDetectionAccuracy(3);
}

Database::Database(const Database& other)
{
    d = other.d;
}

Database& Database::operator=(const KFaceIface::Database& other)
{
    d = other.d;
    return *this;
}

Database::~Database()
{
    // note: saveConfig is done in Priv destructor!
}

QList<Face> Database::detectFaces(const Image& image) const
{
    const IplImage* const img = image.imageData();
    //cvShowImage("show1",img );
    cvWaitKey(0);
    CvSize originalSize       = cvSize(0,0);

    if (!image.originalSize().isNull())
        originalSize = KFaceUtils::toCvSize(image.originalSize());

    std::vector<libface::Face> result;

    try
    {
        result = d->libface->detectFaces(img, originalSize);
    }
    catch (cv::Exception& e)
    {
        kError() << "cv::Exception:" << e.what();
    }
    catch(...)
    {
        kDebug() << "cv::Exception";
    }

    QList<Face>                          faceList;
    std::vector<libface::Face>::iterator it;

    for (it = result.begin(); it != result.end(); ++it)
    {
        faceList << Face::fromFace(*it, Face::ShallowCopy);
    }

    return faceList;
}

bool Database::updateFaces(QList<Face>& faces, const QImage& ImageToTld) const
{
    Tlddatabase *tlddatabase = new Tlddatabase();
    foreach(Face face, faces)
    {
        tlddatabase->configureMain();
        int faceid;
        if (false)//(faceid = this->querybyName(face.name())))//TODO:train/update existing facemodel or create newmodel  based on recognition accuracy
        {
            unitFaceModel *facemodeltostore = new unitFaceModel;
            unitFaceModel *existinmodel = tlddatabase->getFaceModel(faceid);
            QImage facetotld = ImageToTld.copy(face.toFace().getX1(),face.toFace().getY1(),
                                               face.toFace().getWidth(),face.toFace().getHeight());
            tlddatabase->main->learnandUpdate(facemodeltostore,existinmodel,tlddatabase->QImage2IplImage(facetotld));
        }
        else if(face.name() != NULL)//store the new face for first time
        {
            unitFaceModel *facemodeltostore;
            QImage facetotld = ImageToTld.copy(face.toFace().getX1(),face.toFace().getY1(),
                                               face.toFace().getWidth(),face.toFace().getHeight());
            facemodeltostore = tlddatabase->main->generateModel(tlddatabase->QImage2IplImage(facetotld));
            facemodeltostore->Name = face.name();
            tlddatabase->insertFaceModel(facemodeltostore);
        }
    }
}
void Database::recognizeFaces(QList<Face>& faces, const QImage& imageToTld) const
{
    Tlddatabase *tlddatabase = new Tlddatabase();
    foreach(Face face, faces)
    {
        vector<float> recognitionconfidence;
        QImage facetotld = imageToTld.copy(face.toFace().getX1(),face.toFace().getY1(),
                                           face.toFace().getWidth(),face.toFace().getHeight());
        IplImage *tmpfacetotld = tlddatabase->QImage2IplImage(facetotld);
        int count = -1;
        for (int i=1 ;i < 3 ; i++ )//find recognition confidence with all facemodel in database
        {
            tlddatabase->configureMain();
            unitFaceModel *comparefacemodel = tlddatabase->getFaceModel(i);
            recognitionconfidence.push_back(tlddatabase->main->getRecognitionConfidence(comparefacemodel,tlddatabase->QImage2IplImage(facetotld)));
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
                face.setName(tlddatabase->querybyFaceid(maxConfIndex));
            }
        }
    }
}

void Database::clearTraining(const QString& name)
{
    Q_UNUSED(name)
    //TODO
}

void Database::clearTraining(int id)
{
    Q_UNUSED(id)
    //TODO
}

void Database::clearAllTraining()
{
    d->libface->loadConfig(std::map<std::string, std::string>());
}

void Database::saveConfig()
{
    d->saveConfig();
}

QString Database::configPath() const
{
    return d->configPath;
}

void Database::setDetectionAccuracy(double value)
{
    d->libface->setDetectionAccuracy(value);
}

double Database::detectionAccuracy() const
{
    return d->libface->getDetectionAccuracy();
}

void Database::setDetectionSpecificity(double value)
{
    d->libface->setDetectionSpecificity(value);
}

double Database::detectionSpecificity() const
{
    return d->libface->getDetectionSpecificity();
}

int Database::peopleCount() const
{
    return d->libface->count();
}

QString Database::nameForId(int id) const
{
    return d->hash.key(id);
}

int Database::idForName(const QString& name) const
{
    return d->hash.value(name, -1);
}

QList<int> Database::allIds() const
{
    return d->hash.values();
}

QStringList Database::allNames() const
{
    return d->hash.keys();
}

int Database::recommendedImageSizeForDetection(const QSize& size) const
{
    return d->libface->getRecommendedImageSizeForDetection(KFaceUtils::toCvSize(size));
}

QSize Database::recommendedImageSizeForRecognition(const QSize& size) const
{
    return KFaceUtils::fromCvSize(d->libface->getRecommendedImageSizeForRecognition(KFaceUtils::toCvSize(size)));
}

} // namespace KFaceIface
