#!/bin/bash

cur_dir=`pwd`

cd "normal-img-sum";
make clean;
make;
cd "../par-img-sum";
make clean;
make;
cd "../huff";
make clean;
make;
cd $cur_dir;
mkdir -p build;
cp "normal_img_sum/nimageSum" build;
cp "par-img-sum/pimageSum" build;
cp "huff/huffmanCompression" build;
