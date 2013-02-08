/** ===========================================================
 * @file
 *
 * This file is a part of libface project
 * <a href="http://libface.sourceforge.net">http://libface.sourceforge.net</a>
 *
 * @date    2009-12-27
 * @brief   Libface configuration.
 * @section DESCRIPTION
 *
 * @author Copyright (C) 2009 by Alex Jironkin
 *         <a href="alexjironkin at gmail dot com">alexjironkin at gmail dot com</a>
 * @author Copyright (C) 2009-2013 by Gilles Caulier
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

#ifndef LIBFACE_CONFIG_H
#define LIBFACE_CONFIG_H

// the configured options and settings for Tutorial

#define LibFace_VERSION_MAJOR @libface_MAJOR_VERSION@
#define LibFace_VERSION_MINOR @libface_MINOR_VERSION@
#define DEBUG @DEBUG_MODE@
#define LOG_LEVEL @LOG_LEVEL@
#define APPLE @IS_APPLE@
#define OPENCVDIR "@OpenCV_DIR@"

/* Shared library support, see http://gcc.gnu.org/wiki/Visibility */
#ifdef WIN32
# define FACE_IMPORT __declspec(dllimport)
# define FACE_EXPORT __declspec(dllexport)
# define FACE_DLLLOCAL
# define FACE_DLLPUBLIC
#else
# ifdef FACE_HAVE_GXXCLASSVISIBILITY
#  define FACE_IMPORT __attribute__ ((visibility("default")))
#  define FACE_EXPORT __attribute__ ((visibility("default")))
#  define FACE_DLLLOCAL __attribute__ ((visibility("hidden")))
#  define FACE_DLLPUBLIC __attribute__ ((visibility("default")))
# else
#  define FACE_IMPORT
#  define FACE_EXPORT
#  define FACE_DLLLOCAL
#  define FACE_DLLPUBLIC
# endif /* ! FACE_HAVE_GXXCLASSVISIBILITY */
#endif /* ! WIN32 */

/* Define EXIV2API for DLL builds */
#ifdef FACE_HAVE_DLL
# ifdef FACE_BUILDING_LIB
#  define FACEAPI FACE_EXPORT
# else
#  define FACEAPI FACE_IMPORT
# endif /* ! FACE_BUILDING_LIB */
#else
# define FACEAPI
#endif /* ! FACE_HAVE_DLL */

#endif /* LIBFACE_CONFIG_H */
