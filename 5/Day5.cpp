#include <fstream>
#include <sstream>
#include <ranges>
#include <string>
#include <charconv>
#include <cstddef>
#include <vector>
#include <algorithm>

int main() {
    // ingredient ids
    std::vector<std::size_t> IDs{};
    // fresh ids
    std::vector<std::size_t> minIDs{};
    std::vector<std::size_t> maxIDs{};
    std::ifstream fin{ "5/input.txt" };
    std::string line{};
    while(std::getline(fin,line)) {
        std::string idStr{};
        std::size_t id{ 0 };
        std::istringstream iss{line};
        // parsing range of fresh ids
        if(line.find('-') != std::string::npos) {
            // get left and right ids
            std::getline(iss,idStr,'-');
            std::from_chars(idStr.c_str(), idStr.c_str() + idStr.size(), id);
            minIDs.push_back(id);
            std::getline(iss,idStr,'-');
            std::from_chars(idStr.c_str(), idStr.c_str() + idStr.size(), id);
            maxIDs.push_back(id);
        }
        // parsing ids
        else if(!line.empty()) {
            std::getline(iss,idStr,'-');
            std::from_chars(idStr.c_str(), idStr.c_str() + idStr.size(), id);
            IDs.push_back(id);
        }
    }
    // determine what ids are fresh (part 1)
    std::size_t numFreshIDs{ 0 };
    for(std::size_t id : IDs) {
        // just check every range
        for(std::size_t i = 0; i < minIDs.size(); ++i) {
            if(minIDs[i] <= id && id <= maxIDs[i]) {
                numFreshIDs++;
                break;
            }
        }
    }
    printf("answer1:%lu\n",numFreshIDs);

    // determine how many ids are fresh (part 2)
    // zip fresh ids and sort by min id for a merge
    auto idRanges = std::views::zip(minIDs,maxIDs) | std::ranges::to<std::vector>();
    std::ranges::sort(idRanges, std::less<>{},
        [](auto const& ids) { return std::get<0>(ids); });
    std::vector<std::tuple<std::size_t,std::size_t>> merged{};
    // can merge while next id range is contained in the current range
    for(std::size_t i = 0; i < idRanges.size(); ) {
        auto [min, max] = idRanges[i];
        // how many can we merge?
        std::size_t numMergable{ 0 };
        std::size_t lastMax{ max };
        for(std::size_t j = i + 1; j < idRanges.size(); ++j) {
            // can merge if next id range's starting id is contained in the current range
            auto [nextMin, nextMax] = idRanges[j];
            if(min <= nextMin && nextMin <= max) {
                ++numMergable;
            }
            else {
                break;
            }
            // set new max of merged range
            max = std::max(max, nextMax);
            lastMax = max;
        }
        // "merge" that many ranges, pop into merged
        merged.emplace_back(min,lastMax);
        i += (numMergable > 0) ? numMergable + 1 : 1;
    }
    // count the elements in the distinct ranges
    std::size_t freshIDs{ 0 };
    for(auto [min, max] : merged) {
        freshIDs += max - min + 1;
    }
    printf("answer2:%lu\n",freshIDs);
    return 0;
}
