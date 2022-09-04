#!/usr/bin/env python3
import argparse
import logging
import subprocess
import sys
import re

log = logging.getLogger("TestRunner")


def extract_src_tests(filename):
    test_markup = re.compile(r"/\*\s+CHECK:\s*(.*?)\s+\*/", re.MULTILINE | re.DOTALL)
    with open(filename) as f:
        src = f.read()
        matches = test_markup.findall(src)
        log.debug(f"test cases found: {matches}")
        test_cases = [re.compile(x) for x in matches]
        return test_cases


def run_test(test):
    print(f"-------------------------------------------------------")

    (src, exe) = test
    test_cases = extract_src_tests(src)

    if len(test_cases) <= 0:
        log.error(f"No test cases found for {exe} in {src}")
        sys.exit(1)

    log.info(f"running {exe} {test_cases}")
    output = subprocess.run(exe, capture_output=True)
    log.debug(f"{exe} output: [{output}]")

    stderr_log = output.stderr.decode("ascii")
    err_log = b"\n".join(output.stderr.splitlines())
    log.info(f"test stderr:\n\n{err_log}\n")

    if len(stderr_log) <= 0:
        log.error(f"{test} failed to return an error")
        print(f"-------------------------------------------------------")
        sys.exit(1)

    log.debug(f"test cases: {test_cases}")
    for case in test_cases:
        log.info(f"checking {case}")
        result = re.search(case, stderr_log)
        log.debug(f"found {result}")
        if not result:
            log.error(f"test {test} failed")
            print(f"-------------------------------------------------------")
            sys.exit(1)
        else:
            log.info("matched!")

    log.info(f"\t{exe} passed!")
    print(f"-------------------------------------------------------")


def init_stdout_logger(loglevel=logging.INFO):
    root = logging.getLogger()
    root.setLevel(loglevel)
    handler = logging.StreamHandler(sys.stdout)
    handler.setLevel(loglevel)
    formatter = logging.Formatter("%(levelname)s - %(message)s")
    handler.setFormatter(formatter)
    root.addHandler(handler)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-s", "--source", nargs="+", required=True, help="test source")
    parser.add_argument(
        "-t", "--test", nargs="+", required=True, help="test executable"
    )
    parser.add_argument("--verbose", action="store_true")

    args = parser.parse_args()

    if args.verbose:
        init_stdout_logger(logging.DEBUG)
    else:
        init_stdout_logger()

    test_pairs = []
    for src, exe in zip(args.source, args.test):
        test_pairs.append((src, exe))

    for test in test_pairs:
        run_test(test)

    log.info("All tests passed")


if __name__ == "__main__":
    main()
