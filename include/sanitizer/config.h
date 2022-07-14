#pragma once

/* This file defines default values for all sanitizer functionality */

#ifndef SANITIZER_CONFIG_BACKTRACE_ENABLE
#define SANITIZER_CONFIG_BACKTRACE_ENABLE (0)
#define SANITIZER_CONFIG_BACKTRACE_DEFAULT (0)
#define SANITIZER_CONFIG_BACKTRACE_START_DEPTH (2)
#define SANITIZER_CONFIG_BACKTRACE_DEPTH (1024)
#endif
