cmake_minimum_required(VERSION 3.10)

# Project name
project(CChat)

# Set C standard
set(CMAKE_C_STANDARD 17)

# Include directories
include_directories(include /opt/homebrew/opt/mysql-client/include)

# Source files
set(SERVER_SRC
    src/main.c
    src/server/server_utils.c
    src/server/server_network.c
    src/server/server_commands.c
    src/db.c
)

set(CLIENT_SRC
    src/client/client_network.c
    src/client/client_utils.c
)

set(GROUP_SRC
    src/group/group.c
)

# Add executable for server
add_executable(main ${SERVER_SRC})

# Add executable for client (uncomment if needed)
# add_executable(client ${CLIENT_SRC})

# Link libraries
target_link_libraries(main mysqlclient)
# target_link_libraries(client mysqlclient) # Uncomment if client executable is added

# Set output directory
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Uncomment if client executable is added

# Custom command to cpy .env file to the output directory
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/.env $<TARGET_FILE_DIR:main>/.env
)