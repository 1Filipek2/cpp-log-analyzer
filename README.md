# C++ Log Analyzer

A small CLI utility for parsing application logs, counting log levels, filtering entries by level, showing top error messages, and exporting a summary to CSV.

## Features

- Parse simple text log files
- Report malformed lines with line numbers
- Count log levels (`INFO`, `WARNING`, `ERROR`), bucketing unrecognized levels (e.g. `DEBUG`, `FATAL`, `TRACE`) as `UNKNOWN`
- Filter entries by level
- Show top error messages
- Export summary results to CSV
- Build with CMake
- Accept both `WARNING` and legacy `WARN` in input logs and CLI filters

## Log format

Expected input format:

```text
2026-03-20 10:15:01 INFO User logged in
2026-03-20 10:15:05 ERROR Database connection failed
2026-03-20 10:16:11 WARNING Disk usage high
```

Each line is parsed as:

```
[date] [time] [level] [message...]
```

Lines that cannot be parsed structurally (missing date, time, level, or message) are
skipped and reported as malformed, with their line number. Lines that are structurally
valid but carry an unrecognized level (such as DEBUG, FATAL, or TRACE) are kept and
counted under the UNKNOWN bucket rather than discarded.

## Build

```sh
cmake -S . -B build
cmake --build build
```

## Usage

### Basic run

```sh
./build/loganalyzer_app sample/sample.log
```

### Filter by level

```sh
./build/loganalyzer_app sample/sample.log --level ERROR
```

### Limit top error messages

```sh
./build/loganalyzer_app sample/sample.log --top-errors 2
```

### Export summary to CSV

```sh
./build/loganalyzer_app sample/sample.log --export sample/summary.csv
```

### Combined example

```sh
./build/loganalyzer_app sample/sample.log --level ERROR --top-errors 2 --export sample/summary.csv
```

## Example output

```
Malformed log line at line 6
Loaded valid entries: 12

Level counts:
ERROR: 4
INFO: 3
WARNING: 2
UNKNOWN: 3

Top error messages:
1. Database connection failed - 2
2. Authentication failed - 1
3. Timeout while reading response - 1
```

### CSV output example

```
Level,Count
ERROR,4
INFO,3
WARNING,2
Error,Count
Database connection failed,2
Authentication failed,1
Timeout while reading response,1
```

## Automated testing

This project includes automated unit tests using the Catch2 framework.

- Tests cover log parsing, statistics analysis, CSV export, and edge cases (invalid/empty input, output validation).
- All tests are located in the `tests/` directory.

### How to run tests

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

All tests should pass. The test suite is a good starting point for further development or refactoring.

## Project structure

- `include/`   headers
- `src/`       implementation
- `sample/`    sample log and output files
- `tests/`     Catch2 unit tests

## Design overview

- `parser` parses raw log lines into LogEntry
- `analyzer` computes statistics and filtering
- `exporter` writes summary results to CSV
- `cli` handles command-line arguments

## Tested scenarios
Key scenarios (parsing, level counting, CSV export, and edge cases) are covered by the
automated Catch2 test suite in `tests/`. Run them with `ctest --test-dir build`.

*Automated tests now cover all key scenarios. Manual test notes are kept for reference in `tests/manual_test_notes.txt`.*
