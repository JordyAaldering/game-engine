#!/bin/bash

pushd ../
vendor/premake/premake5 gmake2
make
popd
