#!/usr/bin/env python3
import argparse
import logging
import json
import os.path
import subprocess
import sys
import re

log = logging.getLogger("TestRunner")


def run_test(config, test):
    print(f'-----------------------------------------------\n')
    test_regexes = []
    for test_case in config:
        log.debug(f"Found test for {test_case}: {config[test_case]}")
        test_regexes.append(re.compile(config[test_case]))

    test_regexes.reverse()

    log.info(f"running {test} {test_regexes}")
    output = subprocess.run(test, capture_output=True)
    log.debug(f"{test} output: [{output}]")

    stderr_log = output.stderr.splitlines()
    out_log = b'\n'.join(output.stdout.splitlines())
    err_log = b'\n'.join(output.stderr.splitlines())
    log.debug(f"\t\tstdout:\n\t{out_log}\n\t\tstderr:\n{err_log}")

    if len(stderr_log) <= 0:
        log.error(f'\t{test} failed to return an error')
        print(f'-------------------------------------------------------\n\n')
        sys.exit(1)

    for line in stderr_log:
        if test_regexes is None or len(test_regexes) == 0:
            print("skipping")
            break

        regex = test_regexes.pop()
        result = regex.search(line.decode('ascii'))
        log.debug(f'found {result}')
        if not result:
            log.error(f"\t{test} failed")
            log.error(f"\t\t{regex} does not match '{line}'")
            print(f'-------------------------------------------------------\n\n')
            sys.exit(1)
    log.info(f"\t{test} passed!")
    print(f'-------------------------------------------------------\n\n')


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
    parser.add_argument("-c", "--config", default="test_config.json", required=True)
    parser.add_argument("-t", "--test", action="append", help="Run test executable")
    parser.add_argument('--verbose', action='store_true')
    parser.add_argument("test_list", nargs=argparse.REMAINDER)

    args = parser.parse_args()

    if args.verbose:
        init_stdout_logger(logging.DEBUG)
    else:
        init_stdout_logger()

    with open(args.config) as conf:
        config = json.load(conf)

    tests = []
    if args.test is not None:
        tests.extend(args.test)
    if args.test_list is not None:
        tests.extend(args.test_list)

    for test in tests:
        if not os.path.exists(test):
            log.fatal(f"Could not find test '{test}'")
            sys.exit(1)

    log.debug(f"args {args}")
    log.debug(f"tests {tests}")
    log.debug(f"config {config}")

    for test in tests:
        base = os.path.basename(test)
        subconfig = dict()
        try:
            subconfig = config[base]
        except Exception as e:
            log.fatal(f"Test config {args.config} missing entry for {test}: {e}")
            sys.exit(1)
        run_test(subconfig, test)

    log.info("All tests passed")


if __name__ == "__main__":
    main()
