#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

int main() {
    std::vector<std::vector<char>> rawgrid{};
    // read the grid
    std::ifstream fin{ "4/input.txt" };
    std::string line{};
    while(std::getline(fin,line)) {
        std::vector<char> slice{};
        for(char c : line) {
            slice.push_back(c);
        }
        rawgrid.push_back(std::move(slice));
    }
    std::size_t nX = rawgrid[0].size();
    std::size_t nY = rawgrid.size();
    // check adjacent spaces (traverse CW about (x-1,y-1))
    std::array<std::ptrdiff_t, 8> dx{-1,  0,  1, 1, 1, 0, -1, -1};
    std::array<std::ptrdiff_t, 8> dy{-1, -1, -1, 0, 1, 1,  1,  0};
    auto numEmptyAdjacent = [&rawgrid,&dx,&dy,&nX,&nY](std::ptrdiff_t x, std::ptrdiff_t y) {
        std::size_t countAdjacent{ 0 };
        for(std::ptrdiff_t i = 0; i < 8; ++i) {
            auto ax{ x + dx[i]}, ay{ y + dy[i] };
            // skip off-grid points
            if(ax < 0 || ax >= nX || ay < 0 || ay >= nY) continue;
            if(rawgrid[ay][ax] == '@') ++countAdjacent;
        }
        return countAdjacent;
    };
    // count adjacent spaces for each roll
    std::size_t totalAccessible{ 0 };
    for(std::ptrdiff_t y = 0; y < nY; ++y) {
        for(std::ptrdiff_t x = 0; x < nX; ++x) {
            // don't count adjacent spaces for empty spaces
            if(rawgrid[y][x] == '.') continue;
            std::size_t countEmptyAdjacent = numEmptyAdjacent(x,y);
            if(countEmptyAdjacent < 4) ++totalAccessible;
        }
    }
    std::size_t removable{ totalAccessible };
    std::size_t totalRemovable{ 0 };
    while(removable > 0) {
        std::size_t removed{ 0 };
        for(std::ptrdiff_t y = 0; y < nY; ++y) {
            for(std::ptrdiff_t x = 0; x < nX; ++x) {
                // don't count adjacent spaces for empty spaces
                if(rawgrid[y][x] == '.') continue;
                std::size_t countEmptyAdjacent = numEmptyAdjacent(x,y);
                if(countEmptyAdjacent < 4) {
                    ++removed;
                    rawgrid[y][x] = '.';
                }
            }
        }
        removable = removed;
        totalRemovable += removed;
    }
    printf("answer1:%lu\n",totalAccessible);
    printf("answer2:%lu\n",totalRemovable);
    return 0;
}
