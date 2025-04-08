#!/bin/bash

set -eou pipefail

# detect the architecture (if not provided)
# RUNNER_OS=(Linux | Windows | macOS)
# ARCH=(x32 | x64 | arm | arm64)
. "../../build_scripts/detect_runner.sh"

# make sure we know the target architecture
if [ -z "$RUNNER_OS" ] || [ -z "$ARCH" ]; then
	echo "Build failed: Failed to detect operating system/architecture..."
	exit 1
fi

# compiler (override with CC=clang if needed)
CC=${CC:-gcc}

# set up build directories
export BUILD_DIR="../build/$RUNNER_OS/$ARCH"
export INCLUDE_DIR="$BUILD_DIR/include"
export LIB_DIR="$BUILD_DIR/lib"
DEMO_DIR="$BUILD_DIR/demo"

# make sure the build directories exist
mkdir -p "$INCLUDE_DIR"
mkdir -p "$LIB_DIR"
mkdir -p "$DEMO_DIR"

# compile the output

if [ "$RUNNER_OS" = "Linux" ]; then
	OPTIONS="-fPIC -shared"
	RPATH="-Wl,-rpath,./"
	export EXTENSION="so"
elif [ "$RUNNER_OS" = "Windows" ]; then
	OPTIONS="-shared"
	RPATH=""
	export EXTENSION="dll"
elif [ "$RUNNER_OS" = "macOS" ]; then
	OPTIONS="-dynamiclib"
	RPATH="-Wl,-rpath,./"
	export EXTENSION="dylib"
else
	echo "Build failed: Unknown operating system..."
	exit 1
fi

# copy the header file to the include directory
cp dynamic_array.h "$INCLUDE_DIR"

# compile the shared library
set +e
$CC $OPTIONS -I"$INCLUDE_DIR" -DBUILDING_SHARED -o "$LIB_DIR/libdynarr.$EXTENSION" dynamic_array.c || {
	echo "Failed to build shared library..."
	exit 1
}
set -e

# compile the demo executable
set +e
$CC -o "$DEMO_DIR/demo" -I"$INCLUDE_DIR" main.c -L"$LIB_DIR" -ldynarr $RPATH || {
	echo "Failed to build demo executable..."
	exit 1
}
set -e
cp "$LIB_DIR/libdynarr.$EXTENSION" "$DEMO_DIR"

# fin!!

echo "Build completed successfully!"
