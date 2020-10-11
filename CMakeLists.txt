cmake_minimum_required(VERSION 3.10)
project(siloproject)
set(HEADERS silo_define.h)
set(SOURCES silo.c silo_signal.c silo_node.c silo_recycle.c silo_simulate.c silo_nodeconf.c)

add_executable(main ${SOURCES} ${HEADERS})

set_property(TARGET main PROPERTY C_STANDARD 11)


if(MSVC)
  target_compile_definitions(main PRIVATE /W4 /WX /Za /permissive-)
else()
  target_compile_definitions(main PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries(main PRIVATE m)