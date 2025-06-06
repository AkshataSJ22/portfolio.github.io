#include <iostream>
#include <vector>
#include <string>
#include <functional> // for std::hash
using namespace std;

class BloomFilter {
private:
    vector<bool> bitArray;
    int size;

    // Hash functions with different seeds
    size_t hash(const string& data, int seed) const {
        std::hash<string> hasher;
        return (hasher(data) + seed * seed) % size;
    }

public:
    BloomFilter(int size) : size(size), bitArray(size, false) {}

    void insert(const string& item) {
        for (int i = 1; i <= 3; i++) {
            bitArray[hash(item, i)] = true;
        }
    }

    bool possiblyContains(const string& item) const {
        for (int i = 1; i <= 3; i++) {
            if (!bitArray[hash(item, i)])
                return false;
        }
        return true;
    }
};

int main() {
    BloomFilter spamFilter(1000);  // Bit array of size 1000

    // Add known spam domains
    spamFilter.insert("buycheapmeds.com");
    spamFilter.insert("lotterywinner.net");
    spamFilter.insert("spamdomain.co");

    // Test emails
    string test1 = "buycheapmeds.com";
    string test2 = "gmail.com";

    if (spamFilter.possiblyContains(test1)) {
        cout << test1 << " might be spam.\n";
    } else {
        cout << test1 << " is definitely not spam.\n";
    }

    if (spamFilter.possiblyContains(test2)) {
        cout << test2 << " might be spam.\n";
    } else {
        cout << test2 << " is definitely not spam.\n";
    }

    return 0;
}
