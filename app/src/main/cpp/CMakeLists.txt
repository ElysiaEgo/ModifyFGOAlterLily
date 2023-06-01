cmake_minimum_required(VERSION 3.22.1)
project("Morgan")


include_directories("./hooker")
aux_source_directory(./hooker hooker_src)

include_directories("./utf8")
aux_source_directory(./utf8 utf8_src)

add_library(Morgan
        SHARED
        Morgan.cpp ${hooker_src}  ${utf8_src})


find_library(log-lib log)

SET_TARGET_PROPERTIES(Morgan PROPERTIES LINK_FLAGS "-Wl,--gc-sections")

target_link_libraries(Morgan ${log-lib})
