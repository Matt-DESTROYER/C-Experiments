#!/bin/bash

# detect OS
if [ -z "$RUNNER_OS" ]; then
	if [ "$OSTYPE" = "linux" ] || [ "$OSTYPE" = "linux-gnu" ]; then
		export RUNNER_OS="Linux"
	elif [ "$OSTYPE" = "msys" ] || [ "$OSTYPE" = "cygwin" ]; then
		export RUNNER_OS="Windows"
	elif [ "$OSTYPE" = "darwin" ]; then
		export RUNNER_OS="macOS"
	else
		echo "Failed to autodetect OS..."
		exit 1
	fi
fi

# detect architecture
if [ -z "$ARCH" ]; then
	export ARCH=$(uname -m)

	if [ "$ARCH" = "x64" ] || [ "$ARCH" = "x86_64" ] || [ "$ARCH" = "amd64" ]; then
		export ARCH="x64"
	elif [ "$ARCH" = "x32" ] || [ "$ARCH" = "i686" ] || [ "$ARCH" = "amd" ]; then
		export ARCH="x32"
	fi
fi
