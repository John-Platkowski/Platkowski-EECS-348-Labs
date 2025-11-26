#include <iostream>
#include <vector>

bool faulty_fail_lecture(const std::vector<int>& attendance_records)
{
    int absent_count = 0;
    for (int i = 1; i < attendance_records.size(); ++i)
    {
        absent_count += attendance_records[i] == 0;
    }

    return absent_count >= 3;
}

bool fail_lecture(const std::vector<int>& attendance_records)
{
    int absent_count = 0;
    for (int i = 0; i < attendance_records.size(); ++i)
    {
        absent_count += attendance_records[i] == 0;
    }

    return absent_count >= 3;
}


int main()
{
    std::cout << "Test 1: Fault executes but no error state \n";
    std::vector<int> test1 = {1, 0, 0, 0, 1, 1, 1, 1, 1, 1};
    std::cout << "Input: {1, 0, 0, 0, 1, 1, 1, 1, 1, 1}\n";
    std::cout << "Faulty absent_count: 3 (correct, but missed a 1 at index 0)\n";
    std::cout << "Expected output: true (3 absences >= 3)\n";
    std::cout << "Faulty output: " << (faulty_fail_lecture(test1) ? "true" : "false") << "\n";
    std::cout << "Correct output: " << (fail_lecture(test1) ? "true" : "false") << "\n";
    std::cout << "Error state: No (internal count is correct)\n";
    std::cout << "Failure: No (output matches expected)\n";
    std::cout << "\n";

    std::cout << "Test 2: Error state but no failure \n";
    std::vector<int> test2 = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1};
    std::cout << "Input: {0, 0, 1, 1, 1, 1, 1, 1, 1, 1}\n";
    std::cout << "Faulty absent_count: 1 (should be 2)\n";
    std::cout << "Expected output: false (2 absences < 3)\n";
    std::cout << "Faulty output: " << (faulty_fail_lecture(test2) ? "true" : "false") << "\n";
    std::cout << "Correct output: " << (fail_lecture(test2) ? "true" : "false") << "\n";
    std::cout << "Error state: Yes (internal count is incorrect)\n";
    std::cout << "Failure: No (output matches expected)\n";
    std::cout << "\n";

    std::cout << "Test 3: Failure (error state propagates to output) \n";
    std::vector<int> test3 = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1};
    std::cout << "Input: {0, 0, 0, 1, 1, 1, 1, 1, 1, 1}\n";
    std::cout << "Faulty absent_count: 2 (should be 3)\n";
    std::cout << "Expected output: true (3 absences >= 3)\n";
    std::cout << "Faulty output: " << (faulty_fail_lecture(test3) ? "true" : "false") << "\n";
    std::cout << "Correct output: " << (fail_lecture(test3) ? "true" : "false") << "\n";
    std::cout << "Error state: Yes (internal count is incorrect)\n";
    std::cout << "Failure: Yes (output does not match expected)\n";
    std::cout << "\n";

    return 0;
}