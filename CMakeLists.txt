<<<<<<< HEAD
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
=======
cmake_minimum_required(VERSION 3.15)
project(silo-newc C)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_C_STANDARD 11)

add_executable(silo-newc
silo.c
silo_gate.c
silo_node.c
silo_nodeconf.c
silo_recycle.c
silo_signal.c
silo_simulate.c
)
>>>>>>> 26ccfa766cdba73047bf9108bf676595cc34d878
