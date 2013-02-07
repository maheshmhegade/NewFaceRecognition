ADD_LIBRARY(tldmain
            Config.cpp
            Gui.cpp
            Main.cpp
            Settings.cpp
           )

TARGET_LINK_LIBRARIES(tldmain
                      libopentld
                      cvblobs
                      libconfig
                     )
