cmake_minimum_required(VERSION 3.17)
project(Kontaktbok)

set(CMAKE_CXX_STANDARD 17)

# Vcpkg integration
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(Curses REQUIRED)
find_package(MySQL REQUIRED)
find_package(unofficial-pdcurses CONFIG REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})
include_directories(${MYSQL_INCLUDE_DIRS})

add_executable(Kontaktbok main.cpp DatabaseManager.cpp TUI.cpp)
target_link_libraries(Kontaktbok ${CURSES_LIBRARIES} ${MYSQL_LIBRARIES})
target_link_libraries(${Kontaktbok} PRIVATE unofficial::pdcurses::pdcurses)
