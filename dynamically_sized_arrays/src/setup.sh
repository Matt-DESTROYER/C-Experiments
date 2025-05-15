#!/bin/bash

set -eou pipefail

# attempt to build the correct binaries
. ./build.sh

if [ "$RUNNER_OS" = "Linux"] || [ "$RUNNER_OS" = "macOS" ]; then
	cp $INCLUDE_DIR/dynamic_array.h /usr/local/include
	cp $LIB_DIR/libdynarr.$EXTENSION /usr/local/lib
elif [ "$RUNNER_OS" = "Windows" ]; then
	echo "Windows auto-setup is unfortunately currently unsupported."
else
	echo "Unknown operating system..."
fi
