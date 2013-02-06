#include "../../opentld/libopentld.h"
#include <QImage>

using namespace tld;

namespace libface
{
class Tldface
{
 public:
    Main *main;
    Gui *gui;
    Tldface();

   ~Tldface();

    int updateDatabase(IplImage* ,const char *);

    double recognitionConfidence(IplImage* ,const char *);

    int writeModelTofile(IplImage* ,const char *);

    IplImage QImage2IplImage(QImage );

};
}
