
cmake_minimum_required(VERSION 3.1...3.29)
project(
  BacktestEngine
  VERSION 1.0
  LANGUAGES CXX)

project(
  BacktestEngineTest
  VERSION 1.0
  LANGUAGES CXX)



include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(src/include)
add_executable(BacktestEngine 
  src/Main.cpp 
  src/Engine.cpp 
  src/BarTypes.cpp 
  src/DataReader.cpp
  src/PriceSeries.cpp)
add_executable(BacktestEngineTest 
  src/Engine.cpp 
  src/BarTypes.cpp 
  src/DataReader.cpp 
  src/PriceSeries.cpp
  test/MainTest.cpp)
target_link_libraries(BacktestEngineTest GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(BacktestEngineTest)