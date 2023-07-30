#!/bin/bash

export PATH="$PATH:$PWD/_install/lib"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$PWD/_install/lib:/$HOME/Qt/6.2.4/gcc_64/lib"

./_install/bin/test