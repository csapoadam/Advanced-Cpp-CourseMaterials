int main() {
    // Elvart kimenet (az elso 2 esetben kiirja a fv nevet is, mert ezek specialis tipusu functorok...):
    // AddTwo(2) = 4
    // AppendLaa(something) = somethingLaa
    // Result of functor = 15
    // Result of functor = 20
    // Result of functor = 15
    // new value of y : 20
    // new value of x : 5


    AddTwo myaddtwo;
    AppendLaa myappendlaa;
    ReturnMultiplyBy3 myretmultby3;
    MultiplyBy5InPlace mymultby5ip;

    int x = 5; int y = 4;
    applyAndPrintFunctor<AddTwo, int>(myaddtwo, 2);
    applyAndPrintFunctor<AppendLaa, const std::string&>(myappendlaa, "something");
    applyAndPrintFunctor(myretmultby3, x);
    applyAndPrintFunctor(mymultby5ip, y);
    applyAndPrintFunctor(myretmultby3, 5);
    //applyAndPrintFunctor(mymultby5ip, 15); // jobb oldali erteket nem lehet helyben szorozni 

    std::cout << "new value of x: " << x << std::endl; // x erteke tovabbra is 5
    std::cout << "new value of y: " << y << std::endl; // y erteke 20
    return 0;
}
