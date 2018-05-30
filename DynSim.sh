#!/bin/bash

MODE=1
L=20
WIDTH=880
while getopts ":l:m:w:" opt; do
    case $opt in
	l)
	    L=$OPTARG
	    ;;
	m)
	    MODE=$OPTARG
	    ;;
  w)
      WIDTH=$OPTARG
      ;;
	\?)
	    echo "Invalid option: -$OPTARG" >&2
	    exit 1
	    ;;
	:)
	    echo "Option -$OPTARG requires an argument." >&2
	    exit 1
	    ;;
    esac
done
gcc DynSimOpenGL.c -lm -lGL -lglfw -Dmo=$MODE -DTAM=$L -D WID=$WIDTH -o DynSim
./DynSim
