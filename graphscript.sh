#!/bin/bash

echo 'digraph G {' > graphfile.gv

g++ graphpound.cpp -o graph.out

./graph.out 1 >> graphfile.gv

echo '}' >> graphfile.gv

dot -Tpng graphfile.gv -o graphimage.png

#rm graphfile.gv
#rm graph.out