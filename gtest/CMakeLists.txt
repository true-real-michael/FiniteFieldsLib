project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB testSRC "*.cpp")
add_executable(Google_Tests_run ${testSRC})

target_link_libraries(Google_Tests_run FiniteFields)
#target_link_libraries(Google_Tests_run gtest gtest_main)

target_link_libraries(
        Google_Tests_run
        PUBLIC
        GTest::GTest
        GTest::Main
        ${GOOGLE_MOCK_LIBRARIES}
        ${${CMAKE_PROJECT_NAME}_TEST_LIB}
)


add_test(gTests_run Google_Tests_run)