TEMPLATE = subdirs
CONFIG *= ordered

SUBDIRS *= \
    3rd_party \
    libcot \
    cot \
    cot-translator\
    tests

DISTFILES *= \
    libcot/save.json \
    libcot/cot-version.rc \
    cot-updater/cot-update.ini \
    cot-updater/cot-update.sh \
    utf-8-converter.sh
