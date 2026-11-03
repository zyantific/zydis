#!/usr/bin/env python3
import os
import sys
import shlex
import argparse
import difflib

from subprocess import Popen, PIPE

TEST_CASE_DIRECTORY = os.path.join('.', 'cases')

# InitVT100 in tools/ZydisToolsShared.c turns color on for a non-empty FORCE_COLOR whatever
# NO_COLOR says, so NO_COLOR alone would not keep escape sequences out of the captured output.
CHILD_ENV = os.environ.copy()
CHILD_ENV.pop('FORCE_COLOR', None)
CHILD_ENV['NO_COLOR'] = '1'


def get_exitcode_stdout_stderr(path, cmd):
    """
    Executes an external command and returns the exitcode, stdout and stderr.
    """
    args = [path]
    args.extend(shlex.split(cmd))
    proc = Popen(args, stdout=PIPE, stderr=PIPE, env=CHILD_ENV)
    out, err = proc.communicate()
    exitcode = proc.returncode
    return exitcode, out, err


def to_text(data):
    return data.decode().replace('\r\n', '\n')


parser = argparse.ArgumentParser(description="Regression testing.")
parser.add_argument(dest="operation", choices=["test", "rebase"])
parser.add_argument(dest="zydis_info_path", type=str)
args = parser.parse_args()

has_failed = False

for case in os.listdir(TEST_CASE_DIRECTORY):
    if not case.endswith(".in"):
        continue

    path = os.path.join(TEST_CASE_DIRECTORY, case)
    print(path)

    with open(path, mode="r") as f:
        payload = f.read()

    exitcode, out, err = get_exitcode_stdout_stderr(args.zydis_info_path, payload)

    pre, ext = os.path.splitext(case)
    path = os.path.join(TEST_CASE_DIRECTORY, pre + ".out")
    # A rejected input prints only its status line, on stderr. Comparing stdout alone would pass
    # such a case for any failure, so the expected text holds both streams.
    out = to_text(out) + to_text(err)

    if exitcode < 0:
        print(f"FAILED: '{case}' [Terminated by signal {-exitcode}]")
        has_failed = True
        continue

    if not out:
        print(f"FAILED: '{case}' [No output]")
        has_failed = True
        continue

    if args.operation == "rebase":
        with open(path, mode="wb") as f:
            f.write(out.encode())
        continue

    try:
        with open(path, mode="rb") as f:
            expected = to_text(f.read())

        if expected != out:
            print(f"FAILED: '{case}' [{payload}]")
            print('\n'.join(difflib.unified_diff(
                expected.split('\n'),
                out.split('\n'),
                fromfile='expected',
                tofile='got',
            )))
            has_failed = True
    except FileNotFoundError:
        print(f"FAILED: '{case}' [Output file missing]")
        has_failed = True

if has_failed:
    print("\nSOME TESTS FAILED.")
    sys.exit(-1)
else:
    print("\nALL TESTS PASSED.")
    sys.exit(0)