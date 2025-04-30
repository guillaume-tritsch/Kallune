#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

enum class Insect {
    ClassicBee,
    Ladybug,
    Butterfly,
    Dragonfly,
    Ant,
    Grasshopper,
    Beetle,
    Wasp,
    Caterpillar,
    Spider,
    GuimielBee
};


size_t folding_string_hash(std::string const& s, size_t max) {
    size_t hash = 0;
    for (char c : s) {
        hash += static_cast<size_t>(c);
    }
    return hash % max;
}

size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t hash = 0;
    size_t pos = 1;
    for (char c : s) {
        hash += static_cast<size_t>(c) * pos;
        ++pos;
    }
    return hash % max;
}

size_t polynomial_rolling_hash(const std::string& s, size_t p, size_t m) {
    size_t hash = 0;
    size_t power = 1;
    
    for (char c : s) {
        hash = (hash + (static_cast<size_t>(c) * power) % m) % m;
        power = (power * p) % m;
    }
    
    return hash;
}

int main()
{
    string str = "Test";

    cout << polynomial_rolling_hash(str, 4, 6) << endl;

    return 0;
}
