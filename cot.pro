TEMPLATE = subdirs
CONFIG *= ordered

SUBDIRS *= \
    libcot \
    cot \
    cot-translator \
    tests

DISTFILES *= \
    libcot/save.json \
    cot-updater/cot-update.ini \
    cot-updater/cot-update.sh \
    utf-8-converter.sh
