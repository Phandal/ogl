#!/bin/bash

cmake --build build
case $1 in
  "" | "window")
    ./build/window
    ;;
  *)
  ./build/ex_$1
  ;;
esac
