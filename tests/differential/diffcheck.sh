#!/usr/bin/env bash
# Compares the current build's decode output against the reference dumps captured from the
# pre-refactoring baseline (stored untracked in .diffref/).
set -euo pipefail
cd "$(dirname "$0")/../.."
for corpus in bash random; do
    case "$corpus" in
        bash)   input=.diffref/bash_text.bin;  ref=.diffref/ref_bash.txt ;;
        random) input=.diffref/random16m.bin;  ref=.diffref/ref_random.txt ;;
    esac
    ./build/ZydisDiffDump dump "$input" > .diffref/cur.txt
    if ! diff -q "$ref" .diffref/cur.txt > /dev/null; then
        echo "DIFF MISMATCH for $corpus (first differing lines):"
        diff "$ref" .diffref/cur.txt | head -20
        echo "Bisect with: ./build/ZydisDiffDump dump $input <start> <end>"
        exit 1
    fi
    echo "DIFF OK $corpus"
done
