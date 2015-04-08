#!/bin/bash -e

# Small check to be sure we are in a git folder in case of...
if [ ! -d "../.git" ]; then
    echo "It looks like you are not in a Git repository, aborting."
    exit 1
fi

# Find latin1 files
LATIN1_FILES=`find "${PWD}" -exec file {} \; | grep "ISO-8859" | cut -d ':' -f1`

# Convert them to utf8
for file in ${LATIN1_FILES}; do
    echo "Converting latin1 `basename \"${file}\"`..."
    mv "${file}" "${file}.latin1"
    iconv -f ISO-8859-1 -t UTF-8 "${file}.latin1" > "${file}"
    rm "${file}.latin1"
done
