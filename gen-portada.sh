#!/bin/bash

x=$(ls $1|grep '1.jpg'|head -n1)
cp -v $1/$x /tmp/portada.jpg
