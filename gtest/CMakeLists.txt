project(Google_tests)

#add_subdirectory(lib)

file(GLOB testSRC "*.cpp")
add_executable(Google_Tests_run ${testSRC})

find_package(GTest REQUIRED)

set(GOOGLE_MOCK_LIBRARIES GTest::gmock GTest::gmock_main)

target_link_libraries(Google_Tests_run PUBLIC FiniteFields)

target_link_libraries(
        Google_Tests_run
        PUBLIC
        GTest::GTest
        GTest::Main
        ${GOOGLE_MOCK_LIBRARIES}
        ${${CMAKE_PROJECT_NAME}_TEST_LIB}
)


add_test(gTests_run Google_Tests_run)