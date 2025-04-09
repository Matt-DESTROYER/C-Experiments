#!/bin/bash

set -eou pipefail

BUILD_SCRIPTS_DIR="../../build_scripts"

# parse command line arguments
. "$BUILD_SCRIPTS_DIR/arguments.sh"

# detect the architecture (if not provided)
# RUNNER_OS=(Linux | Windows | macOS)
# ARCH=(x32 | x64 | arm | arm64)
. "$BUILD_SCRIPTS_DIR/detect_runner.sh"

# make sure we know the target architecture
if [ -z "${RUNNER_OS:-}" ] || [ -z "${ARCH:-}" ]; then
	echo "Build failed: Failed to detect operating system/architecture..."
	exit 1
fi

# compiler (override with CC=clang if needed)
if [ -z "${CC:-}" ]; then
	if command -v gcc >/dev/null 2>&1; then
		export CC="gcc"
	elif command -v clang >/dev/null 2>&1; then
		export CC="clang"
	elif command -v tcc >/dev/null 2>&1; then
		export CC="tcc"
	elif command -v icc >/dev/null 2>&1; then
		export CC="icc"
	elif command -v icx >/dev/null 2>&1; then
		export CC="icx"
	elif command -v emcc >/dev/null 2>&1; then
		export CC="emcc"
	else
		echo "Failed to autodetect a known compiler."
		exit 1
	fi
fi
echo "Using compiler: $CC"

# set up build directories
export BUILD_DIR="../build/$RUNNER_OS/$ARCH"
export INCLUDE_DIR="$BUILD_DIR/include"
export LIB_DIR="$BUILD_DIR/lib"
DEMO_DIR="$BUILD_DIR/demo"

# make sure the build directories exist
mkdir -p "$INCLUDE_DIR" "$LIB_DIR" "$DEMO_DIR"

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
if [ "$CC" = "emcc" ]; then
	export EXTENSION="wasm"
fi

# copy the header file to the include directory
cp dynamic_array.h "$INCLUDE_DIR"

# compile the shared library
set +e
"$CC" $OPTIONS -I"$INCLUDE_DIR" -DBUILDING_SHARED -o "$LIB_DIR/libdynarr.$EXTENSION" dynamic_array.c || {
	echo "Failed to build shared library..."
	exit 1
}
set -e

# compile the demo executable (if one exists)
if [ -f main.c ]; then
	set +e
	"$CC" -o "$DEMO_DIR/demo" -I"$INCLUDE_DIR" main.c -L"$LIB_DIR" -ldynarr $RPATH || {
		echo "Failed to build demo executable..."
		exit 1
	}
	set -e
	cp "$LIB_DIR/libdynarr.$EXTENSION" "$DEMO_DIR"
fi

# fin!!

echo "Build completed successfully!"
