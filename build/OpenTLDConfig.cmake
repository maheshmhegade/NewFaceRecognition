find_package(OpenCV)

set(bin_dir "/home/mmh/softwares/FaceRecognition/build")
set(src_dir "/home/mmh/softwares/FaceRecognition")

set(OPENTLD_INCLUDE_DIRS ${src_dir})
INCLUDE_DIRECTORIES(${OPENTLD_INCLUDE_DIRS})

SET(OPENTLD_LIB_DIRS ${LIBRARY_OUTPUT_PATH})
LINK_DIRECTORIES(${OPENTLD_LIB_DIRS})

set(OPENTLD_LIBS cvblobs libconfig libopentld)



