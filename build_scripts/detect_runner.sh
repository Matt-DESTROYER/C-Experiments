#!/bin/bash

# detect OS
if [ -z "${RUNNER_OS:-}" ]; then
	if [ "$OSTYPE" = "linux" ] || [ "$OSTYPE" = "linux-gnu" ]; then
		export RUNNER_OS="Linux"
	elif [ "$OSTYPE" = "win32" ] || [ "$OSTYPE" = "msys" ] || [ "$OSTYPE" = "cygwin" ]; then
		export RUNNER_OS="Windows"
	elif [ "$OSTYPE" = "darwin" ]; then
		export RUNNER_OS="macOS"
	else
		echo "Failed to autodetect OS..."
		exit 1
	fi
fi

# detect architecture
if [ -z "${ARCH:-}" ]; then
	export ARCH=$(uname -m)

	if [ "$ARCH" = "x86_64" ] || [ "$ARCH" = "amd64" ]; then
		export ARCH="x64"
	elif [ "$ARCH" = "i686" ] || [ "$ARCH" = "i386" ] || [ "$ARCH" = "amd" ]; then
		export ARCH="x32"
	elif [ "$ARCH" = "aarch64" ]; then
		export ARCH="arm64"
	elif [ "$ARCH" = "aarmv7l" ]; then
		export ARCH="arm"
	fi
fi
