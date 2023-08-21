add_library(filehandler
        FileHandler.cpp
        NamedPipe.cpp
        SharedMemory.cpp
        Logger.cpp
        Requester.cpp
        )

target_include_directories(filehandler PRIVATE ${Boost_INCLUDE_DIRS})

add_executable(fh FileHandlerMain.cpp)
target_link_libraries(fh filehandler ${Boost_LIBRARIES})

add_executable(requester requester_main.cpp)
target_link_libraries(requester filehandler ${Boost_LIBRARIES})
