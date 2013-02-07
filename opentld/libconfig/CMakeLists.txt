#This are the defines for building a static libconfig for windows
IF(WIN32)
    ADD_DEFINITIONS(-DLIBCONFIGXX_STATIC -DLIBCONFIG_STATIC -DYY_NO_UNISTD_H -DYY_USE_CONST -D_CRT_SECURE_NO_DEPRECATE -D_STDLIB_H)
ENDIF(WIN32)

ADD_LIBRARY(libconfig
            grammar.c
            libconfig.c
            libconfigcpp.cc
            scanctx.c
            scanner.c
            strbuf.c
           )
