#!/bin/bash


echo "Delete symbolic link..."

cd arm-hisiv600
rm -f *.so
rm -f libsqlite3.so.0
cd ..

echo "Sussessful."
