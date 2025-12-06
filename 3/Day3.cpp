#include <fstream>
#include <charconv>

int main() {
    std::ifstream fin{"3/input.txt"};
    std::string x{};
    std::size_t answer1{ 0 }, answer2{ 0 };
    std::vector<std::size_t> voltagesDoubleFor{};
    std::vector<std::size_t> voltagesLinear{};
    while(std::getline(fin,x)) {
        std::size_t n = x.length();
        // linear time: update two pointers
        // first - move down hombre, don't give us a starting case of x[i] < x[j]
        std::size_t i{ 0 }, j{ 1 };
        while(i < n - 1 && j < n && x[i] < x[j]) {
            ++i;
            ++j;
        }
        for(std::size_t k = 2; k < n; ++k) {
            // reset second digit
            if(x[k] > x[j]) {
                j = k;
            }
            // reset first digit
            if(k != n - 1 && x[k] > x[i]) {
                i = k;
                j = k + 1;
            }
        }
        std::string result = std::string(1,x[i]).append(std::string(1,x[j]));
        std::size_t voltage{ 0 };
        std::from_chars(result.c_str(),result.c_str()+2,voltage);
        voltagesLinear.push_back(voltage);
        answer1 += voltage;

        // compute the voltage of a given index vector
        auto voltageFunc = [&x](std::vector<std::size_t> i) {
            std::string voltageStr{};
            for(std::size_t j = 0; j < 12; ++j) {
                voltageStr.push_back(x[i[j]]);
            }
            std::size_t voltage{ 0 };
            std::from_chars(voltageStr.c_str(),voltageStr.c_str()+12,voltage);
            return voltage;
        };

        // if the first digit is necessarily the first largest digit (val x @ index i)
        // from 0 to len(x) - 12
        // the second digit is necessarily the second largest digit from i+1 to len(x) - 11
        std::vector<std::size_t> lastMaxIndex;
        for(std::size_t digit = 0; digit < 12; ++digit) {
            std::size_t digitStart{ 0 }, digitMax{ 0 };
            for(std::size_t k = lastMaxIndex.empty() ? 0 : lastMaxIndex.back() + 1; k < n - (11 - digit); ++k) {
                if(x[k] - '0' > digitMax) {
                    digitStart = k;
                    digitMax = x[k] - '0';
                }
            }
            lastMaxIndex.push_back(digitStart);
        }
        answer2 += voltageFunc(lastMaxIndex);
    }
    printf("answer1 = %lu\n",answer1);
    printf("answer2 = %lu\n",answer2);
    return 0;
}
