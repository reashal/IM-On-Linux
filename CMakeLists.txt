cmake_minimum_required(VERSION 3.20)
project(IM_FOR_Linux)

set(CMAKE_CXX_STANDARD 14)
set(INC_DIR /usr/include/mysql/)
set(LINK_DIR /usr/lib/x86_64-linux-gnu/)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(mysqlclient)

add_executable(IM_FOR_Linux
        config/mysql_config.h DUtil.cpp DUtil.h TimeUtil.cpp TimeUtil.h   User.cpp User.h  main.cpp main.h )
# -L/usr/lib/x86_64-linux-gnu -lmysqlclient

target_link_libraries(IM_FOR_Linux mysqlclient)