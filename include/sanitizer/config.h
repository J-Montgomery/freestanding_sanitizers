#pragma once

/* This file defines default values for all sanitizer functionality */

/* Allow the user to define SANITIZER_CONFIG_BACKTRACE_ENABLE
 * themselves if it exists
 */
#ifndef SANITIZER_CONFIG_BACKTRACE_ENABLE
#if defined(__linux__) || defined(__APPLE__)
/* If there's a reasonable chance backtrace exists, enable it by default */
#define SANITIZER_CONFIG_BACKTRACE_ENABLE (1)
#else
#define SANITIZER_CONFIG_BACKTRACE_ENABLE (0)
#endif /* __linux__ || __APPLE__ */

#if SANITIZER_CONFIG_BACKTRACE_ENABLE == 1
#define SANITIZER_CONFIG_BACKTRACE_RUNTIME_DEFAULT_STATE (0)
#define SANITIZER_CONFIG_BACKTRACE_START_DEPTH (2)
#define SANITIZER_CONFIG_BACKTRACE_DEPTH (1024)
#endif

#endif /* SANITIZER_CONFIG_BACKTRACE_OVERRIDE */
