#include <vector>
#include <fstream>
#include <ranges>
#include <algorithm>
#include <print>
#include <cstdlib>

int main() {
    constexpr std::string filepath = "6/input.txt";
    // part 1
    auto spaceFilter   = std::views::filter([](char c){return !std::isspace(c);});
    auto emptyFilter   = std::views::filter([](auto&& r){return !std::ranges::empty(r);});
    auto strToNumTrans = std::views::transform([](auto&& r){
        return static_cast<std::size_t>(std::stoull(
            std::string(std::ranges::begin(r),std::ranges::end(r))));
    });

    std::vector<std::vector<std::size_t>> numbers{};
    std::vector<char> operations{};
    std::ifstream fin{filepath};
    std::string line{};
    while(std::getline(fin,line)) {
        if(line.find('+') != std::string::npos and line.find('*') != std::string::npos) {
            operations = line | spaceFilter | std::ranges::to<std::vector>();
        }
        else {
            auto nums = line | std::views::split(' ') | emptyFilter | strToNumTrans | std::ranges::to<std::vector>();
            numbers.push_back(std::move(nums));
        }
    }

    std::size_t result1{ 0 };
    // operators: apply to columns of numbers
    for(std::size_t opIndex = 0; opIndex < operations.size(); ++opIndex) {
        // iterate over the operation for each row
        auto nums = numbers | std::views::transform(
            [opIndex](auto& row) -> std::size_t{
                return row[opIndex];
            }
        );
        if(operations[opIndex] == '+') {
            result1 += std::ranges::fold_left(
                nums,
                0,
                std::plus{}
            );
        }
        else {
            result1 += std::ranges::fold_left(
                nums,
                1,
                [](auto &&r, auto &&l){ return r * l; }
            );
        }
    }
    std::print("result1:{}\n", result1);

    // part 2
    fin.close(); fin.open(filepath);
    // transpose-read a full mapped file buffer
    std::vector<std::vector<char>> buffer{};
    std::size_t n{ 0 }, m{ 0 };
    std:size_t maxLength = { 0 };
    while(std::getline(fin, line)) {
        if(line.find('+') != std::string::npos and line.find('*') != std::string::npos) {
            break;
        }
        buffer.push_back({});
        for(char c : line) buffer[n].push_back(c);
        m = (m < buffer[n].size()) ? buffer[n].size() : m;
        ++n;
    }
    // make buffer transposable, add whitespace
    for(std::size_t i = 0; i < buffer.size(); ++i) {
        while(buffer[i].size() < m) buffer[i].push_back(' ');
    }
    // transpose buffer: cephapods read cols like we read rows
    std::vector<std::vector<char>> transpose{};
    for(std::size_t j = 0; j < m; ++j) {
        transpose.push_back({});
        for(std::size_t i = 0; i < n; ++i) {
            transpose[j].push_back(buffer[i][j]);
        }
    }

    // create a little stack of the numbers that we'll apply the operation to
    std::vector<std::vector<std::size_t>> stacks;
    std::vector<std::size_t> stack;
    for(auto v : transpose) {
        std::string num(v.data(),n);
        bool hasDigit = false;
        for(std::size_t i = 0; i < n; ++i) {
            if(!std::isspace(num[i])) {
                hasDigit = true;
                break;
            }
        }
        if(!hasDigit) {
            stacks.push_back(std::move(stack));
            stack.resize(0);
        }
        else {
            stack.push_back(std::stoll(num));
        }
    }
    // push final stack
    if(!stack.empty()) stacks.push_back(std::move(stack));
    std::size_t result2{};
    // operators: apply to columns of numbers, same as part 1
    // re-use operations array from part 1
    for(std::size_t opIndex = 0; opIndex < operations.size(); ++opIndex) {
        // groups of n
        if(operations[opIndex] == '+') {
            result2 += std::ranges::fold_left(
                stacks[opIndex],
                0,
                std::plus{}
            );
        }
        else {
            result2 += std::ranges::fold_left(
                stacks[opIndex],
                1,
                [](auto &&r, auto &&l){ return r * l; }
            );
        }
    }
    std::print("result2:{}\n", result2);

    return 0;
}
