#include "../../opentld/libopentld/ImAcq.h"
#include "../../opentld/tldmain/Config.h"
#include "../../opentld/tldmain/Main.h"
#include "../../opentld/tldmain/Gui.h"

#include <QImage>

using namespace tld;
using tld::Config;
using tld::Gui;
using tld::Settings;

namespace libface
{
class Tldface
{
 public:
    Main *main;
    Config config;
    ImAcq *imAcq;
    Gui *gui;
    Tldface();

   ~Tldface();

    int updateDatabase(IplImage* ,const char *);

    float getRecognitionConfidence(IplImage* ,const char *);

    int writeModelTofile(IplImage* ,const char *);

    IplImage* QImage2IplImage(QImage );

};
}
