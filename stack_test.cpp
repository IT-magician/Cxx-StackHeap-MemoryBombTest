#include <iostream>
#include <cstring>

// 테스트용 메모리 크기: 10MB (10 * 1024 * 1024 Bytes)
// 리눅스 기본 ulimit -s (Stack size)인 8MB(8192KB)를 초과하도록 설정
constexpr size_t TARGET_ALLOC_SIZE = 10 * 1024 * 1024;

void test_stack_allocation() {
    std::cout << "[Stack] Attempting to allocate " << TARGET_ALLOC_SIZE / (1024 * 1024) << " MB on the Stack..." << std::endl;

    // 함수 내부의 지역 변수 배열 선언 (Stack 영역 할당)
    // 이 순간 스택 포인터(SP)가 10MB만큼 아래로 점프하며 Guard Page를 침범합니다.
    char stack_buffer[TARGET_ALLOC_SIZE];

    // 컴파일러가 배열 선언을 무시하지 못하도록 실제 쓰기 작업 수행
    // 이 줄을 실행하기 전에 이미 메모리 보호 정책에 의해 하드웨어 레벨에서 프로세스가 킬링됩니다.
    std::memset(stack_buffer, 0xAA, TARGET_ALLOC_SIZE);

    std::cout << "[Stack] Allocation Success! (This line will NOT be printed)" << std::endl;
}

int main() {
    std::cout << "=== Stack Memory Limit Test ===" << std::endl;
    std::cout << "Warning: This program is designed to crash (Segmentation fault)." << std::endl;
    
    test_stack_allocation();
    
    return 0;
}