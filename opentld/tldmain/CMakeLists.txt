add_library(tldmain Config.cpp
                    Gui.cpp
                    Main.cpp
                    Settings.cpp
                    
                    Config.h
                    Gui.h
                    Main.h
                    Settings.h)
target_link_libraries(tldmain libopentld cvblobs libconfig)                    
                    