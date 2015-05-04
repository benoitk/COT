#include <QApplication>
#include "uiselecttest.h"

int main(int argc, char *argv[])
{
#if defined(LIBCOT_STATIC_BUILD)
    // Needed for static linking of libcot
    Q_INIT_RESOURCE(cot_resources);
#endif
    QApplication a(argc, argv);
    UISelectTest *w = new UISelectTest();
    w->show();
    return a.exec();
}
