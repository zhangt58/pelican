#!/bin/bash

sed 1d DCL.beam > DCLsmth.beam
./smthbeam.m DCLsmth.beam
size=$(wc -l < DCLsmth.beam)
sed -i "1i\ ${size}" DCLsmth.beam
