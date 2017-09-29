#!/bin/bash

echo "Delete shared library and images." &&

#rm -f *.so
#rm -f libsqlite3.so.0 mainwidget ipcd sysconfig
rm -r libutils.so
rm -f mainwidget

echo "Successful."
