cmake_minimum_required(VERSION 3.20)
project(TinyDebugger C)

add_executable(TinyDebugger
    main.c
    src/ui/ui_driver.c
    src/ui/cli/commands.c
    src/ui/REPL/repl_driver.c
)

target_include_directories(TinyDebugger
    PRIVATE
        src/ui/REPL/include
        src/ui/include
        src/include
)

target_compile_options(TinyDebugger PUBLIC -O2 -Wall -Wextra -Wpedantic)
