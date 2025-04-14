#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <set>
#include <mutex>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <chrono>

std::set<int> global_unique_numbers;
std::mutex global_mutex;

void process_file_section(const std::string& filename, std::streampos start, std::streampos end) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file section: " << filename << "\n";
        return;
    }

    file.seekg(start);
    std::set<int> local_set;
    std::string current_number;
    char ch;

    while (file.tellg() < end && file.get(ch)) {
        if (isdigit(ch) || ch == '-') {
            current_number += ch;
        } else if (!current_number.empty()) {
            local_set.insert(std::stoi(current_number));
            current_number.clear();
        }
    }
    if (!current_number.empty()) {
        local_set.insert(std::stoi(current_number));
    }

    std::lock_guard<std::mutex> lock(global_mutex);
    global_unique_numbers.insert(local_set.begin(), local_set.end());
}

int main() {
    const std::string input_file = "large_input.txt";
    const std::string output_file = "unique_output.txt";

    // Generate input if not found
    if (!std::filesystem::exists(input_file)) {
        std::cout << "Generating " << input_file << " using shuf...\n";
        std::string cmd = "shuf -i 1-1000000 -n 1000000 > " + input_file;
        if (std::system(cmd.c_str()) != 0) {
            std::cerr << "Failed to generate " << input_file << "\n";
            return 1;
        }
        std::cout << "File generated successfully.\n";
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream file(input_file, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open input file: " << input_file << "\n";
        return 1;
    }

    std::streampos file_size = file.tellg();
    file.close();

    int num_threads = std::thread::hardware_concurrency();
    std::streamoff chunk_size = file_size / num_threads;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        std::streampos start = std::streampos(i * chunk_size);
        std::streampos end = (i == num_threads - 1) ? file_size : std::streampos((i + 1) * chunk_size);
        threads.emplace_back(process_file_section, input_file, start, end);
    }

    for (auto& t : threads) t.join();

    std::ofstream out(output_file);
    if (!out) {
        std::cerr << " Failed to open output file: " << output_file << "\n";
        return 1;
    }

    for (const int& num : global_unique_numbers) {
        out << num << "\n";
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Output written to: " << output_file << "\n";
    std::cout << "Total unique numbers: " << global_unique_numbers.size() << "\n";
    std::cout << "Time taken: " << duration.count() << " seconds\n";

    return 0;
}
