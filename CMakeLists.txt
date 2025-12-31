cmake_minimum_required(VERSION 3.20)
project(TinyDebugger C)

add_executable(TinyDebugger
    main.c
    src/ui/ui_driver.c
    src/ui/cli/commands.c
)

target_include_directories(TinyDebugger
    PRIVATE
        src/ui/include
        src/include
)

target_compile_options(TinyDebugger PUBLIC -O2 -Wall -Wextra -Wpedantic)
