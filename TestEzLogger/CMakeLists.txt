add_executable(TestEzLogger TestEzLogger.cpp)

target_link_libraries(TestEzLogger eurointroduction ${Boost_LIBRARIES})

add_test(TestEzLogger TestEzLogger)
