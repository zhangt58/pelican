#!/bin/bash

rm *out* 2> /dev/null
echo mod.in | genesis 
getcur mod.out > curfile
echo "rad.in" | genesis
echo "rad1.in" | genesis
