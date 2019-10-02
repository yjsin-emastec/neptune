#!/bin/bash

ARCH=`cat ../arch.txt`

echo "Delete symbolic link..."

cd ${ARCH}
rm -f *.so
rm -f libsqlite3.so.0
cd ..

echo "Sussessful."
