// WordCount.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

typedef std::vector<std::string> VectorOfStrings;
typedef std::unordered_map<std::string, int> UmapStringsToInts;
typedef std::pair<int, std::string> PairIntString;
typedef std::vector< PairIntString > VectorOfIntStringPairs;

VectorOfStrings words(const std::string& s) {
    VectorOfStrings elems;
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, ' ')) {
        elems.push_back(item);
    }
    return elems;
}

UmapStringsToInts count(std::vector<std::string> words) {
    UmapStringsToInts mymap;
    for (auto w : words) {
        if (mymap.find(w) != mymap.end()) {
            mymap[w] = mymap[w] + 1;
        }
        else {
            mymap.insert({ w, 1 });
        }
    }
    return mymap;
}

VectorOfIntStringPairs reverse(UmapStringsToInts x) {
    VectorOfIntStringPairs result;
    for (auto xe : x) {
        result.push_back(std::make_pair(xe.second, xe.first));
    }
    return result;
}

VectorOfIntStringPairs sortVectorOfIntStringPairs (VectorOfIntStringPairs voisp) {
    std::sort(voisp.begin(), voisp.end(), [](PairIntString pisa, PairIntString pisb) -> bool { return pisa.first > pisb.first; });
    return voisp;
}


int main() {
    VectorOfIntStringPairs voisp =
        sortVectorOfIntStringPairs(
            reverse(
                count(
                    words("this string is a very very very short string this one!")
                )
            )
        );

    for (auto& v : voisp) {
        std::cout << v.first << ": " << v.second << std::endl;
    }
    return 0;
}