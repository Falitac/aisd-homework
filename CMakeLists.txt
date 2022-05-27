cmake_minimum_required(VERSION 3.10)
project(lists)

set(SRC
"main.cc"
"bst-tree.cc"
"heap-tree.cc"
)

add_executable(out ${SRC})