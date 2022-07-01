#!/usr/bin/env python3
import argparse
import logging
import json
import os.path
import subprocess
import sys
import re

log = logging.getLogger('TestRunner')

def run_test(config, test):
    test_regexes = []
    for test_case in config:
        log.debug(f'{test_case} -> {config[test_case]}')
        test_regexes.append(re.compile(config[test_case]))
    test_regexes = test_regexes.reverse()

    log.info(f'running {test}')
    output = subprocess.run(test, capture_output=True, text=True)
    log.debug(f'{test} output: [{output}]')

    stderr_log = output.stderr.splitlines()
    out_log = "".join(output.stdout)
    err_log = "".join(output.stderr)
    log.info(f'\t\tstdout:\n\t{out_log}\n\t\tstderr:\n{err_log}')

    for line in stderr_log:
        if test_regexes is None:
            break
        regex = test_regexes.pop()
        if not regex.match(line):
            log.error(f'\t{test} failed')
            log.error(f'\t\t{regex} does not match \'{line}\'')
            sys.exit(1)
    log.info(f'\t{test} passed!')

def init_stdout_logger():
    loglevel = logging.INFO
    root = logging.getLogger()
    root.setLevel(loglevel)
    handler = logging.StreamHandler(sys.stdout)
    handler.setLevel(loglevel)
    formatter = logging.Formatter('%(levelname)s - %(message)s')
    handler.setFormatter(formatter)
    root.addHandler(handler)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', '--config', default='test_config.json', required=True)
    parser.add_argument('-t', '--test', action='append', help='Run test executable')
    parser.add_argument('test_list', nargs=argparse.REMAINDER)

    args = parser.parse_args()

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
            log.fatal(f'Could not find test \'{test}\'')
            sys.exit(1)

    log.debug(f'args {args}')
    log.debug(f'tests {tests}')
    log.debug(f'config {config}')

    for test in tests:
        base = os.path.basename(test)
        subconfig = dict()
        try:
            subconfig = config[base]
        except Exception as e:
            log.fatal(f'Test config {args.config} missing entry for {test}: {e}')
            sys.exit(1)
        run_test(subconfig, test)

    log.info('All tests passed')

if __name__ == '__main__':
    main()