#!bin/bash

VERBOSE=false
QUIET=false

for arg in "$@"; do
    case "$arg" in
        -v|--verbose)
            export VERBOSE=true
            ;;
        --quiet)
            export QUIET=true
            ;;
        *)
            echo "Unknown option: $arg"
            exit 1
            ;;
    esac
done

