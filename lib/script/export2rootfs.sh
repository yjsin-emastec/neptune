#!/bin/bash

echo "Copy image to \"$1\"" &&

cp ipcd $1
cp mainwidget $1
cp sysconfig $1

echo "Copy done."
