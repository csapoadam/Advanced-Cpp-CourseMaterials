
// Elvart kimenet:
// 3: very
// 2: this
// 2: string
// 1: short
// 1: is
// 1: a
// 1: one!

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