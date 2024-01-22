#include "puzzleSolver.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

namespace shindler::ics46::project1 {

bool puzzleSolver(const std::string& addend1, const std::string& addend2,
                  const std::string& sum,
                  std::unordered_map<char, unsigned>& mapping) {
    std::vector<char> fullunqiueletters;
    for (const auto letter : addend1) {
        if (std::find(fullunqiueletters.begin(), fullunqiueletters.end(), letter) == fullunqiueletters.end()) {
            fullunqiueletters.push_back(letter);
        }
    }
    for (const auto letter : addend2) {
        if (std::find(fullunqiueletters.begin(), fullunqiueletters.end(), letter) == fullunqiueletters.end()) {
            fullunqiueletters.push_back(letter);
        }
    }
    for (const auto letter : sum) {
        if (std::find(fullunqiueletters.begin(), fullunqiueletters.end(), letter) == fullunqiueletters.end()) {
            fullunqiueletters.push_back(letter);
        }
    }
    std::vector<bool> usednumber(10, false);
    return puzzletrier(0, fullunqiueletters, usednumber, addend1, addend2, sum, mapping);
}

bool verifier(const std::string &addend1, const std::string &addend2,const std::string &sum,
              const std::unordered_map<char, unsigned> &mapping) {
    unsigned addend1num = 0;
    unsigned addend2num = 0;
    unsigned sumnum = 0;
    for(char character : addend1){
        addend1num *= 10;
        addend1num += mapping.at(character);
    }
    for(char character : addend2){
        addend2num *= 10;
        addend2num += mapping.at(character);
    }
    for(char character : sum){
        sumnum *= 10;
        sumnum += mapping.at(character);
    }
    return (addend1num+addend2num)==sumnum;
}

bool puzzletrier(unsigned index, const std::vector<char> &fullunqiueletter, std::vector<bool> &usednumber, 
                 const std::string &addend1, const std::string &addend2, const std::string &sum,
                 std::unordered_map<char, unsigned> &mapping)
{
    if (index == fullunqiueletter.size())
    {
        return verifier(addend1, addend2, sum, mapping);
    }
    for (unsigned i = 0; i < 10; i++)
    {
        if (!usednumber[i])
        {
            usednumber[i] = true;
            mapping[fullunqiueletter[index]] = i;
            if (puzzletrier(index + 1, fullunqiueletter, usednumber, addend1, addend2, sum, mapping))
            {
                return true;
            }
            usednumber[i] = false;
            mapping.erase(fullunqiueletter[index]);
        }
    }
    return false;
}

}  // namespace shindler::ics46::project1
