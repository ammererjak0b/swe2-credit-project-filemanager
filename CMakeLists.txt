cmake_minimum_required(VERSION 3.29)
project(swe2_credit_project_filemanager C)

set(CMAKE_C_STANDARD 11)

add_executable(swe2_credit_project_filemanager cmake-build-debug/src/FileManager/main.c
        cmake-build-debug/src/Include/FileManger.h
        cmake-build-debug/src/FileManager/FileManager.c
        cmake-build-debug/src/FileManager/BinarySearchTree.c
        cmake-build-debug/src/Include/BinarySearchTree.h
        cmake-build-debug/src/Include/DoublyLinkedList.h
        cmake-build-debug/src/FileManager/DoublyLinkedList.c
        cmake-build-debug/src/Include/Converter.h
        cmake-build-debug/src/FileManager/Converter.c
)
