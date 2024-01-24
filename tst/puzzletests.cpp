#include <catch2/catch_amalgamated.hpp>
#include <puzzleSolver.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace {
namespace proj1 = shindler::ics46::project1;

/*

Note that this IS NOT a comprehensive set of test cases.
You should still write additional test cases.

This is to get you started and serve as a sanity check.


Note that "gradeYesAnswer" is provided for use in your test cases, but
you may NOT use it in any code you write otherwise for this project.
That is, your code may not call it -- although you may write your own version
of it for your own usage, if you want.

 */

// Function definitions
bool lettersInMap(const std::string &letters,
                  const std::unordered_map<char, unsigned> &mapping);
unsigned convertStringToUnsigned(
    const std::string &string,
    const std::unordered_map<char, unsigned> &mapping);
bool gradeYesAnswer(const std::string &addend1, const std::string &addend2,
                    const std::string &sum,
                    const std::unordered_map<char, unsigned> &mapping);

// Function implementations
bool gradeYesAnswer(const std::string &addend1, const std::string &addend2,
                    const std::string &sum,
                    const std::unordered_map<char, unsigned> &mapping) {
    const unsigned int MAX_ONES_PLACE = 9;

    std::unordered_set<unsigned> numbersUsedSoFar;

    for (auto [character, mappedNumber] : mapping) {
        if (mappedNumber > MAX_ONES_PLACE ||
            numbersUsedSoFar.contains(mappedNumber)) {
            return false;
        }

        numbersUsedSoFar.insert(mappedNumber);
    }

    if (!lettersInMap(addend1, mapping) || !lettersInMap(addend2, mapping) ||
        !lettersInMap(sum, mapping)) {
        return false;
    }

    unsigned convertedAddend1 = convertStringToUnsigned(addend1, mapping);
    unsigned convertedAddend2 = convertStringToUnsigned(addend2, mapping);
    unsigned convertedSum = convertStringToUnsigned(sum, mapping);

    return convertedAddend1 + convertedAddend2 == convertedSum;
}

// converts a string to an unsigned integer, according to the mapping provided.
// this is different from std::stoul
unsigned convertStringToUnsigned(
    const std::string &string,
    const std::unordered_map<char, unsigned> &mapping) {
    static const int BASE10_PLACE_OFFSET = 10;
    unsigned convertedNumber = 0;

    for (char character : string) {
        convertedNumber *= BASE10_PLACE_OFFSET;
        convertedNumber += mapping.at(character);
    }

    return convertedNumber;
}

bool lettersInMap(const std::string &letters,
                  const std::unordered_map<char, unsigned> &mapping) {
    for (char letter : letters) {
        if (!mapping.contains(letter)) {
            return false;
        }
    }
    return true;
}

TEST_CASE("Solver:POT-PAN-BIB:ExpectSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved = proj1::puzzleSolver("POT", "PAN", "BIB", puzzleMapping);

    CHECK(canBeSolved);
    REQUIRE(gradeYesAnswer("POT", "PAN", "BIB", puzzleMapping));
}

TEST_CASE("Solver:UCI-ALEX-MIKE:ExpectSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver("UCI", "ALEX", "MIKE", puzzleMapping);

    CHECK(canBeSolved);
    REQUIRE(gradeYesAnswer("UCI", "ALEX", "MIKE", puzzleMapping));
}

TEST_CASE("Solver:LARRY-CAREER-LEGEND:ExpectNoSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver("LARRY", "CAREER", "LEGEND", puzzleMapping);

    REQUIRE_FALSE(canBeSolved);
}

TEST_CASE("Solver:SMALL-DOG-PUPPY:ExpectSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver("SMALL", "DOG", "PUPPY", puzzleMapping);
    CHECK(canBeSolved);
    REQUIRE(gradeYesAnswer("SMALL", "DOG", "PUPPY", puzzleMapping));
}

TEST_CASE("Solver:LARRYEE-CAREERNC-LEGENDAE:ExpectNoSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver("LARRYEE", "CAREERNC", "LEGENDAE", puzzleMapping);

    REQUIRE_FALSE(canBeSolved);
}

TEST_CASE("Solver:WOSHISHABI-SHABISHIWO-APPLEAPPLE:ExpectNoSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver("WOSHISHABI", "SHABISHIWO", "APPLEAPPLE", puzzleMapping);

    REQUIRE_FALSE(canBeSolved);
}

TEST_CASE("Solver:MLARRYEEC-CAREERNCM-LEGENDMAE:ExpectNoSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver("MLARRYEEC", "CAREERNCM", "LEGENDMAE", puzzleMapping);

    REQUIRE_FALSE(canBeSolved);
}


TEST_CASE("Solver:ABCDFEIGJA-ABEGFHICJA-JIHGFEDCBAE:ExpectNoSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver("ABCDFEIGJA", "ABEGFHICJA", "JIHGFEDCBAE", puzzleMapping);

    REQUIRE_FALSE(canBeSolved);
}

TEST_CASE("Solver:PAL-WORLD-WALDW:ExpectSolution", "[Required][Solver]") {
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver("PAL", "WORLD", "WALDW", puzzleMapping);
    CHECK(canBeSolved);
    REQUIRE(gradeYesAnswer("PAL", "WORLD", "WALDW", puzzleMapping));
}

TEST_CASE("Solver:longTest", "[Customized][Solver]") {
    const std::string ADDEND1 = "GYROSCOPE";
    const std::string ADDEND2 = "GYROSCOPE";
    const std::string SUM = "PRECISION";
    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved =
        proj1::puzzleSolver(ADDEND1, ADDEND2, SUM, puzzleMapping);

    CHECK(canBeSolved);
    REQUIRE(gradeYesAnswer(ADDEND1, ADDEND2, SUM, puzzleMapping));
}

TEST_CASE("Solver:10letters-10letters-10letters:ExpectNoSolution", "[Required][Solver]") {

    std::unordered_map<char, unsigned> puzzleMapping;

    bool canBeSolved = proj1::puzzleSolver("ABCDFEIGJA", "ABEGFHICJA", "JIHGFEDCBA", puzzleMapping);

    REQUIRE_FALSE(canBeSolved);
}
}  // namespace
