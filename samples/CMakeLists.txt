file(GLOB hdrs "*.h*" "../include/*.h")
file(GLOB srcs "*.cpp" "../src/arithmetic.cpp")

add_executable(postfix ${srcs} ${hdrs})

