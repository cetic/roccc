#!/bin/bash

ROCCC_BINARY_DIR="/vagrant/roccc/"
ROCCC_SOURCE_DIR="./roccc-compiler/"

if [ -d "$ROCCC_BINARY_DIR" ];
then
  if [ -d "$ROCCC_SOURCE_DIR" ];
  then
    cp -f $ROCCC_SOURCE_DIR/src/llvm-2.3/Release/bin/opt $ROCCC_BINARY_DIR/bin/
    cp -f $ROCCC_SOURCE_DIR/src/llvm-2.3/Release/lib/*.so* $ROCCC_BINARY_DIR/lib/
  else
    echo "Error: Couldn't find ROCCC_SOURCE_DIR at '$ROCCC_SOURCE_DIR'"
  fi
else
  echo "Error: Couldn't find ROCCC_BINARY_DIR at '$ROCCC_BINARY_DIR'"
fi
