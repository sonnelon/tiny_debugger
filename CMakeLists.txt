cmake_minimum_required(VERSION 3.20)
project(TinyDebugger C)

add_executable(TinyDebugger
    main.c
    src/ui/ui_driver.c
    src/ui/cli/ui_cli.c
    src/ui/REPL/repl_driver.c
    src/ui/REPL/repl_dispatcher.c
    src/utils/logger.c
    src/debugger/core/dbg_step.c
    src/debugger/core/dbg_continue_child.c
    src/debugger/core/dbg_exit.c
    src/debugger/core/dbg_core.c
    src/debugger/core/dbg_regs.c
    src/debugger/dbg_driver.c
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
