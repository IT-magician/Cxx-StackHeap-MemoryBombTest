cmake_minimum_required(VERSION 3.10)
project(MemoryBehaviorTest CXX)

# C++ 최신 표준 설정 및 최적화 해제 (-O0)
# 최적화가 켜지면 컴파일러가 사용하지 않는 메모리 할당을 지워버릴 수 있으므로
# 정확한 테스트를 위해 디버그 및 최적화 해제 옵션을 줍니다.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -Wall")

# 1. 스택 메모리 폭발 테스트용 실행 파일
add_executable(stack_test stack_test.cpp)

# 2. 힙 메모리 정상 할당 테스트용 실행 파일
add_executable(heap_test heap_test.cpp)