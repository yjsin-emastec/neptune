#!/bin/bash

ARCH=`cat ../arch.txt`

echo "Delete symbolic link..."

rm -f lib*

cd ${ARCH}
rm -f *.so
cd ..

echo "Link symbolic..."

cd ${ARCH}
ln -s libglib-2.0.so.0.2200.0 libglib-2.0.so &&
ln -s libgthread-2.0.so.0.2200.0 libgthread-2.0.so &&
ln -s libsqlite3.so.0.8.6 libsqlite3.so &&
ln -s libsqlite3.so.0.8.6 libsqlite3.so.0 &&
if [ "${ARCH}" = "arm-hisiv100" ]; then
ln -s libintl.so.8.1.1 libintl.so &&
cp -arf libhimem.so.0 ../libhimem.so
fi
cd ..

echo "Sussessful."
