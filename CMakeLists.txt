cmake_minimum_required(VERSION 3.20)
project(TinyDebugger C)

add_executable(TinyDebugger
    main.c
    src/ui/ui_driver.c
    src/ui/cli/ui_cli.c
    src/ui/REPL/repl_driver.c
    src/ui/REPL/repl_dispatcher.c
    src/utils/logger.c
    src/debugger/debugger_driver.c
    src/debugger/debugger_core.c
)

target_include_directories(TinyDebugger
    PRIVATE
        src/ui/REPL/include
        src/ui/include
        src/include
        src/utils/include
        src/debugger/include
)

target_compile_options(TinyDebugger PUBLIC -O2 -Wall -Wextra -Wpedantic)
