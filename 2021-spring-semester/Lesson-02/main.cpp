#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

// ...



int main()
{
    Company innotech{ "Innotech" };
    Company lafabulosa{ "La Fabulosa" };

    Employee doriangray{ "Dorian Gray", 1977, 12321 }; // nev, szuletes eve, employee id
    doriangray.setSalary(500000); // brutto 500.000 havi kereset

    Employee tomsawyer{ "Tom Sawyer", 1982, 19355 };
    tomsawyer.setSalary(565000);

    Employee ernonemecsek{ "Erno Nemecsek", 1955, 20133 };
    ernonemecsek.setSalary(800500);
    
    Subcontractor jenobaradlay{ "Eugene Baradlay", 1967, 45322, &innotech, 1500000 }; // nev, szuletes eve, temporary id, ceg pointer, masfel millios szerzodes

    Subcontractor sandortakaro{ "Alexander Blanket", 1971, 35881, &lafabulosa, 3200000 };

    std::vector<Person*> peopleAtCompany{ &doriangray, &tomsawyer, &ernonemecsek, &jenobaradlay, &sandortakaro };

    std::vector <int> justForFun{ 1,2,3,4,5 };

    int sumOfJustForFun = accumulate(justForFun, [](int x) -> int { return x; });
    int sumOfJustForFunPlus3 = accumulate(justForFun, [](int x) -> int { return x; }, 3);

    std::function <int(int, int)> prod = std::multiplies<int>();
    int productOfJustForFun = accumulate(justForFun, [](int x) -> int {return x; }, 1, prod);

    std::cout << "sum of justForFun     = " << sumOfJustForFun << std::endl; // 15 az osszeg
    std::cout << "sum of justForFun + 3 = " << sumOfJustForFunPlus3 << std::endl; // 18 az osszeg
    std::cout << "product of justForFun = " << productOfJustForFun << std::endl; // 120 a szorzat

    std::cout << "total salary of all employees = "
        << accumulate(peopleAtCompany, returnsSalaryIfEmployeeZeroIfNot)
        << std::endl; // csak az alkalmazottak fizeteset irja ki, vagyis 1.865.500-at

    int totalSubcontractedPeople = std::count_if(
        peopleAtCompany.begin(),
        peopleAtCompany.end(),
        [](Person* person) -> bool { return dynamic_cast<Subcontractor*>(person); }
    );

    std::cout << "total number of subcontracted people: " << totalSubcontractedPeople << std::endl; // 2 alvallalkozo van
    
}