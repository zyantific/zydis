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

has_failed = False

for case in os.listdir(TEST_CASE_DIRECTORY):
    if case.endswith(".in"):
        path = os.path.join(TEST_CASE_DIRECTORY, case)
        print(path)

        file = open(path, mode='r')
        payload = file.read()
        file.close()

        exitcode, out, err = get_exitcode_stdout_stderr('{} {}'.format(ZYDIS_INFO_PATH, payload))

        pre, ext = os.path.splitext(case)
        path = os.path.join(TEST_CASE_DIRECTORY, pre + ".out")

        try:
            file = open(path, mode='rb')
            s = file.read()
            file.close()

            if s != out:
                print("FAILED: '{}' [{}]".format(case, payload))
                has_failed = True
        except:
            print("FAILED: '{}' [{}]".format(case, "Output file missing"))
            has_failed = True

sys.exit(-1 if has_failed else 0)