#include <iostream>
#include <vector>
#include <cstring> // memset
#include <chrono>
#include <thread>

int main() {
    // 1. 현재 환경의 ulimit 등을 확인하기 위한 정보 출력
    std::cout << "--- Heap Stress Test Context ---" << std::endl;
    system("free -h"); // 현재 가용 메모리 확인

    std::vector<char*> memory_vault;
    const size_t CHUNK_SIZE = 256 * 1024 * 1024; // 256MB씩 할당
    size_t total_pushed = 0;

    std::cout << "\nStarting aggressive heap allocation..." << std::endl;

    try {
        while (true) {
            // 2. 가상 메모리 할당
            char* ptr = new(std::nothrow) char[CHUNK_SIZE];

            if (!ptr) {
                throw std::bad_alloc();
            }

            // 3. 물리 메모리 강제 점유 (이게 없으면 '진짜' 터지지 않음)
            // 모든 페이지에 데이터를 써서 OS가 물리 RAM을 할당하게 강제함
            std::memset(ptr, 0xFF, CHUNK_SIZE);

            memory_vault.push_back(ptr);
            total_pushed += CHUNK_SIZE;

            std::cout << "Current Physical Heap Usage: " << total_pushed / (1024 * 1024) << " MB" << std::endl;

            // 시스템 부하 조절을 위한 미세한 대기
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    } catch (const std::bad_alloc& e) {
        std::cout << "\n[SUCCESS] Heap Allocation Failed at " << total_pushed / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Reason: OS refused to give more memory (Overcommit limit hit)." << std::endl;
    }

    // 할당된 메모리 해제 (테스트 종료 후 시스템 복구)
    for (auto p : memory_vault) delete[] p;
    return 0;
}