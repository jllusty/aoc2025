#include <fstream>
#include <sstream>
#include <charconv>

int main() {
    auto isInvalid1 = [](std::string id) {
        // sequence must have an even number of digits
        if(id.length() % 2 != 0) {
            return false;
        }
        std::size_t incr = id.length()/2;
        for(std::size_t x = 0; x < incr; ++x) {
            if(id[x] != id[x+incr]) {
                return false;
            }
        }
        return true;
    };

    auto isInvalid2 = [](std::string id) {
        std::size_t len = id.length();
        // construct prefix
        for(std::size_t l = 1; l <= id.length()/2; ++l) {
            if(len % l != 0) continue;
            std::string seq = id.substr(0,l);
            // see if we have seq repeating
            bool subsequenceRepeats = true;
            for(std::size_t n = l; n <= id.length() - l; n += l) {
                std::string nextSeq = id.substr(n,l);
                if(seq.compare(nextSeq) != 0) {
                    subsequenceRepeats = false;
                    break;
                }
            }
            if(subsequenceRepeats) {
                return true;
            }
        }
        return false;
    };

    std::size_t result1{ 0 };
    std::size_t result2{ 0 };

    std::ifstream fin{"2/input.txt"};
    std::string line{};
    while(std::getline(fin, line)) {
        std::istringstream lineiss{line};
        std::string range{};
        while(std::getline(lineiss, range, ',')) {
            std::istringstream sstr{range};
            std::string firstStr{}, lastStr{};
            std::getline(sstr, firstStr, '-');
            std::getline(sstr, lastStr, '-');

            std::size_t first{ 0 }, last{ 0 };
            std::from_chars(firstStr.data(),firstStr.data()+firstStr.size(),first);
            std::from_chars(lastStr.data(),lastStr.data()+lastStr.size(),last);

            for(std::size_t x = first; x <= last; ++x) {
                if(isInvalid1(std::to_string(x))) {
                    result1 += x;
                }
                if(isInvalid2(std::to_string(x))) {
                    result2 += x;
                }
            }
        }
    }
    printf("result1 = %lu\n",result1);
    printf("result2 = %lu\n",result2);
    return 0;
}
