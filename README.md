# Quick Tools

A lightweight, header-only C utility library.

## Features

- **Plug-n-Play:** Just copy paste the required file onto your projects
- **Header-only:** Single-header libraries with an `_IMPL` pattern for implementation
- **Zero dependencies:** Only needs the C standard library
- **Minimal boilerplate:** Declarative macros keeps the codebase concise

## Files

| Header                 | Purpose                         |
| ---------------------- | ------------------------------- |
| `utility/quick_test.h` | Testing / assertion macros      |
| `utility/quick_ansi.h` | ANSI color codes for terminal   |
| `utility/quick_log.h`  | Logging and text styling macros |

## Usage

### 1. Create the implementation file

In exactly **one** translation unit, define the implementation macros before including the headers:

```c
/* quick_impl.c */
#define QUICK_TEST_IMPL
#include "utility/quick_test.h"

#define QUICK_LOG_IMPL
#include "utility/quick_log.h"
```

> Only one source file should define `_IMPL`. All other files just include the headers.

### 2. Include the headers anywhere else

```c
/* main.c */
#include "utility/quick_test.h"
#include "utility/quick_log.h"
```

Compile everything together:

```sh
cc quick_impl.c main.c -o target
```

## License

This project is dedicated to the public domain under the CC0 1.0 Universal (CC0 1.0) Public Domain Dedication.

You can copy, modify, distribute, and perform the work, even for commercial purposes, all without asking permission. For more information, see the [CC0 1.0 Universal Summary](https://creativecommons.org).
