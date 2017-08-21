#!/bin/bash

echo "Delete symbolic link..."

#rm -f lib*

cd arm-hisiv100
rm -f *.so
cd ..

echo "Link symbolic..."

ln -s sqlite3.so.0.8.6 libsqlite3.so
ln -s sqlite3.so.0.8.6 libsqlite3.so.0

cd arm-hisiv100
ln -s libglib-2.0.so.0.2200.0 libglib-2.0.so &&
ln -s libgthread-2.0.so.0.2200.0 libgthread-2.0.so &&
ln -s libintl.so.8.1.1 libintl.so &&
cp -arf libhimem.so.0 ../libhimem.so &&
cd ..

echo "Sussessful."
