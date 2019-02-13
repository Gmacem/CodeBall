cmake_minimum_required(VERSION 3.0)

add_executable(MyStrategy
    Strategy.cpp
    RemoteProcessClient.cpp
    MyStrategy.cpp
    Runner.cpp
    csimplesocket/PassiveSocket.cpp
    csimplesocket/ActiveSocket.cpp
    csimplesocket/HTTPActiveSocket.cpp
    csimplesocket/SimpleSocket.cpp)

install(TARGETS MyStrategy RUNTIME DESTINATION bin)
