#include <QApplication>

#include "CAutomate.h"
#include "uiselecttest.h"

int main(int argc, char *argv[])
{
#if defined(LIBCOT_STATIC_BUILD)
    // Needed for static linking of libcot
    Q_INIT_RESOURCE(cot_resources);
#endif
    QApplication a(argc, argv);
    CAutomate automate;
    UISelectTest *w = new UISelectTest(&automate);
    w->show();
    return a.exec();
}
