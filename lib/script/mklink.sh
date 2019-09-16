#!/bin/bash

echo "Delete symbolic link..."

cd arm-hisiv600
rm -f *.so
cd ..

echo "Link symbolic..."

cd arm-hisiv600
ln -s libglib-2.0.so.0.2200.0 libglib-2.0.so &&
ln -s libgthread-2.0.so.0.2200.0 libgthread-2.0.so &&
ln -s libsqlite3.so.0.8.6 libsqlite3.so &&
ln -s libsqlite3.so.0.8.6 libsqlite3.so.0 &&
cd ..

echo "Sussessful."
