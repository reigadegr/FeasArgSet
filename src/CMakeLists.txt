cmake_minimum_required(VERSION 3.22)
project(src)


set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(src
        include/Check.h
        include/function.h
        include/GameList.h
        include/LockValue.h
        include/NodePermission.h
        include/Path.h
        Base.cpp
        FeasArgSet.cpp
        FindPerfmgr.cpp
        NodeCtrl.cpp
        Package.cpp
        Profile.cpp
        Sm8475opt.cpp
        Time.cpp)
        