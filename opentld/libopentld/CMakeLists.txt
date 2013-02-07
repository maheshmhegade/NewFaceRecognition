ADD_LIBRARY(libopentld
            ImAcq.cpp
            BB.cpp
            BBPredict.cpp
            FBTrack.cpp
            Lk.cpp
            Median.cpp
            Clustering.cpp
            DetectionResult.cpp
            DetectorCascade.cpp
            EnsembleClassifier.cpp
            ForegroundDetector.cpp
            MedianFlowTracker.cpp
            NNClassifier.cpp
            TLD.cpp
            TLDUtil.cpp
            VarianceFilter.cpp
           )

TARGET_LINK_LIBRARIES(libopentld ${OpenCV_LIBS})
