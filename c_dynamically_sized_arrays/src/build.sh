#!/bin/bash

# detect the architecture (if not provided)
# RUNNER_OS=(Linux | Windows | macOS)
# ARCH=(x32 | x64 | arm | arm64)
source ../../build_scripts/detect_runner.sh

# make sure we know the target architecture
if [ -z "$RUNNER_OS" ] || [ -z "$ARCH" ]; then
	echo "Build failed..."
	exit 1
fi

# make sure the build directory exists
mkdir -p ../build/$RUNNER_OS/$ARCH

# compile the output
gcc main.c dynamic_array.c -o ../build/$RUNNER_OS/$ARCH/demo/dynamic_array
gcc dynamic_array.c -c -fPIC -o ../build/$RUNNER_OS/$ARCH/lib/libdynamic_array
