# C++ Log Analyzer

A small CLI utility for parsing application logs, counting log levels, filtering entries by level, showing top error messages, and exporting a summary to CSV.

## Features

- Parse simple text log files
- Report malformed lines with line numbers
- Count log levels (`INFO`, `WARNING`, `ERROR`)
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

Malformed lines are skipped and reported.

## Build

```sh
cmake -S . -B build
cmake --build build
```

## Usage

### Basic run

```sh
./build/cpp_log_analyzer sample/sample.log
```

### Filter by level

```sh
./build/cpp_log_analyzer sample/sample.log --level ERROR
```

### Limit top error messages

```sh
./build/cpp_log_analyzer sample/sample.log --top-errors 2
```

### Export summary to CSV

```sh
./build/cpp_log_analyzer sample/sample.log --export sample/summary.csv
```

### Combined example

```sh
./build/cpp_log_analyzer sample/sample.log --level ERROR --top-errors 2 --export sample/summary.csv
```

## Example output

```
Invalid log line at line 6
Loaded valid entries: 9

Level counts:
ERROR: 4
INFO: 3
WARNING: 2

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
./build/tests
```

All tests should pass. The test suite is a good starting point for further development or refactoring.

## Project structure

- `include/`   headers
- `src/`       implementation
- `sample/`    sample log and output files
- `tests/`     manual test notes

## Design overview

- `parser` parses raw log lines into LogEntry
- `analyzer` computes statistics and filtering
- `exporter` writes summary results to CSV
- `cli` handles command-line arguments

## Tested scenarios

*Automated tests now cover all key scenarios. Manual test notes are kept for reference in `tests/manual_test_notes.txt`.*
