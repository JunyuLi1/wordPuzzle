#include "puzzleSolver.hpp"
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

namespace shindler::ics46::project1 {

bool puzzleSolver(const std::string& addend1, const std::string& addend2,
                  const std::string& sum,
                  std::unordered_map<char, unsigned>& mapping) {
    std::unordered_set<char> uniqueChars;
    std::vector<char> fullunqiueletters;
    std::unordered_set<char> tempchars;
    tempchars.insert(addend1.back());
    tempchars.insert(addend2.back());
    tempchars.insert(sum.back());
    for(const auto&elem:tempchars)
    {
        fullunqiueletters.push_back(elem);
    }
    for (char letter : addend1 + addend2 + sum) {
        uniqueChars.insert(letter);
    }
    for(const auto&elem:uniqueChars)
    {
        if(std::find(fullunqiueletters.begin(), fullunqiueletters.end(), elem) == fullunqiueletters.end())
        {
            fullunqiueletters.push_back(elem);
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
        addend1num = addend1num * 10 + mapping.at(character);
    }
    for(char character : addend2){
        addend2num = addend2num * 10 + mapping.at(character);
    }
    for(char character : sum){
        sumnum = sumnum * 10 + mapping.at(character);
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
    if ((mapping.find(addend1.back()) != mapping.end())&&
        (mapping.find(addend2.back()) != mapping.end() )&&
        (mapping.find(sum.back()) != mapping.end()) ) {
        if ((mapping.at(addend1.back()) + mapping.at(addend2.back())) % 10 != mapping.at(sum.back())) {
            return false;
        }
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
