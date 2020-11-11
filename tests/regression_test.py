import os
import sys
import shlex
from subprocess import Popen, PIPE

ZYDIS_INFO_PATH = "F:/Development/GitHub/zydis/Build64/Release/ZydisInfo.exe"
TEST_CASE_DIRECTORY = "./cases"

def get_exitcode_stdout_stderr(cmd):
    """
    Executes an external command and returns the exitcode, stdout and stderr.
    """
    args = shlex.split(cmd)

    proc = Popen(args, stdout=PIPE, stderr=PIPE)
    out, err = proc.communicate()
    exitcode = proc.returncode
    
    return exitcode, out, err

# sys.argv

has_failed = False

for case in os.listdir(TEST_CASE_DIRECTORY):
    if case.endswith(".in"):
        path = os.path.join(TEST_CASE_DIRECTORY, case)
        print(path)

        with open(path, mode="r") as f: 
            payload = f.read()

        exitcode, out, err = get_exitcode_stdout_stderr(f"{ZYDIS_INFO_PATH} {payload}")

        pre, ext = os.path.splitext(case)
        path = os.path.join(TEST_CASE_DIRECTORY, pre + ".out")

        try:
            with open(path, mode="rb") as f:
                s = f.read()

            if s != out:
                print(f"FAILED: '{case}' [{payload}]")
                has_failed = True
        except:
            print(f"FAILED: '{case}' [Output file missing]")
            has_failed = True

sys.exit(-1 if has_failed else 0)