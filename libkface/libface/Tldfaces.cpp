/** ===========================================================
 * @file
 *
 * This file is a part of libface project
 * <a href="http://libface.sourceforge.net">http://libface.sourceforge.net</a>
 *
 * @date    2010-03-03
 * @brief   openTLD interface.
 * @section DESCRIPTION
 *
 * Face detection through openTLD interface.
 *
 * @author Copyright (C) 2012-2013 by Mahesh Hegde
 *         <a href="mailto:maheshmhegade at gmail dot com">maheshmhegade at gmail dot com</a>
 * @author Copyright (C) 2013 by Gilles Caulier
 *         <a href="mailto:caulier dot gilles at gmail dot com">caulier dot gilles at gmail dot com</a>
 *
 * @section LICENSE
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

#include "Tldfaces.h"

using namespace std;

namespace libface
{

class Tldface::Private
{

public:

    Private()
    {
        main  = 0;
    }

    Main*  main;
    Config config;
};

Tldface::Tldface()
    : d(new Private)
{
    d->main        = new Main();
    d->config.configure(d->main);
    srand(d->main->seed);
}

Tldface::~Tldface()
{
//    delete d->main;
    delete d;
}

int Tldface::writeModelTofile(IplImage* const inputImage, const char* const faceModelFilename) const
{
    float dummyVariable;
    d->main->doWork(inputImage, faceModelFilename, 1, &dummyVariable);
    return 0;
}

float Tldface::getRecognitionConfidence(IplImage* const inputImage, const char* const faceModelFilename) const
{
    float recognitionConfidence;
    d->main->doWork(inputImage, faceModelFilename, 2, &recognitionConfidence);
    return recognitionConfidence;
}

int Tldface::updateDatabase(IplImage* const /*inputImage*/, const char* const /*faceModelFilename*/) const
{
//    d->main->doWork(inputImage, faceModelFilename, 3);
    return 0;
}

IplImage* Tldface::QImage2IplImage(const QImage& qimg) const
{

    IplImage* const imgHeader = cvCreateImageHeader(cvSize(qimg.width(), qimg.height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData      = (char*) qimg.bits();

    uchar* const newdata      = (uchar*) malloc(sizeof(uchar) * qimg.byteCount());
    memcpy(newdata, qimg.bits(), qimg.byteCount());
    imgHeader->imageData      = (char*) newdata;

    return imgHeader;
}

} // namespace libface
