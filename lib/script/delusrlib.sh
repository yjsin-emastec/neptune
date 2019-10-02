#!/bin/bash

echo "Delete shared library and images." &&

rm -f *.so
rm -f cmdServer mainwidget ipcd sysconfig

echo "Successful."
