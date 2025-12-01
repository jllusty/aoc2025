#include <string>
#include <fstream>
#include <charconv>

int main() {
    std::ifstream fin{"1/input.txt"};
    std::string rotation{};
    std::size_t position{50};
    // number of times we end up at position = 0
    std::size_t password1{0};
    // number of times we end up at or pass position = 0
    std::size_t password2{0};
    while(std::getline(fin, rotation)) {
        char direction = rotation[0];
        std::size_t distance{0};
        std::from_chars(rotation.data() + 1, rotation.data() + rotation.size(), distance);
        password2 += distance / 100;
        distance = (distance % 100);
        if(direction == 'L') {
            if(position <= distance && position != 0) ++password2;
            position = (position + 100 - distance) % 100;
        }
        else {
            if(position + distance >= 100) ++password2;
            position = (position + distance) % 100;
        }
        if(position == 0) {
            ++password1;
        }
    }
    printf("password1: %lu\n",password1);
    printf("password2: %lu\n",password2);
}
