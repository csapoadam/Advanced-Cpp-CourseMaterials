// Callables.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>


struct Company {
    std::string name;
public:
    Company(const std::string& nm) : name{nm} {}
};

class Person {
    std::string name;
    int yearOfBirth;
public:
    Person(const std::string& nm, int yob) : name{ nm }, yearOfBirth{yob} {}
    virtual std::string getName() { return name; }
};

class Employee : public Person {
    int employeeId;
    int salary;
public:
    Employee(const std::string& nm, int yob, int empId) : Person{ nm, yob }, employeeId{empId}, salary{0} {}
    Employee& setSalary(int s) {
        salary = s;
        return *this;
    }
    int getSalary() { return salary; }
};

class Subcontractor : public Person {
    int temporaryId;
    Company* companyFrom;
    int contractFee;
public:
    Subcontractor(const std::string& nm, int yob, int tempId, Company* comp, int cfee) :
        Person{ nm, yob }, temporaryId{ tempId }, companyFrom{ comp }, contractFee{ cfee } {}
};

template <typename IterableCollection,
    typename CollectionElementType,
    typename UnwrappedType = int,
    typename ResultType = int>
ResultType accumulate(
        IterableCollection& collection,
        std::function<UnwrappedType(CollectionElementType)> unwrapper,
        ResultType initValue = 0,
        std::function<ResultType(ResultType, UnwrappedType)> aggregator = std::plus<int>()) {

    ResultType result = initValue;
    for (auto it = collection.begin(); it != collection.end(); it++) {
        result = aggregator(result, unwrapper(*it));
    }
    return result;
}

std::function<int(Person*)> returnsSalaryIfEmployeeZeroIfNot = [](Person* person) -> int {
    if (Employee* e = dynamic_cast<Employee*>(person)) {
        return e->getSalary();
    }
    return 0;
};

int main()
{
    Company innotech{ "Innotech" };

    std::string valami{ "valami" };
    Company comp2{ valami };
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

    std::function<int(int)> identity = [](int x) -> int { return x; };
    std::function<int(int,int)> prod = std::multiplies<int>();

    int sumOfJustForFun = accumulate(justForFun, identity);
    int sumOfJustForFunPlus3 = accumulate(justForFun, identity, 3);
    int productOfJustForFun = accumulate(justForFun, identity, 1, prod);

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


    int currentInx = -1;
    std::function<std::pair<int,int>(Person*)> salaryUnwrapper = [&currentInx](Person* p) -> std::pair<int,int> {
        currentInx++;
        if (Employee* e = dynamic_cast<Employee*>(p)) {
            return std::make_pair(e->getSalary(), currentInx);
        }
        return std::make_pair(0, currentInx);
    };

    int highestSalarySoFar = -1;
    std::function<int(int, std::pair<int,int>)> salaryAggregator = [&highestSalarySoFar](int acc, std::pair <int, int> cur) -> int {
        if (cur.first > highestSalarySoFar) {
            highestSalarySoFar = cur.first;
            return cur.second;
        }
        else {
            return acc;
        }
    };

    int indexOfEmployeeWithHighestSalary = accumulate(
        peopleAtCompany,
        salaryUnwrapper,
        -1,
        salaryAggregator
    );

    std::cout << "Person with highest salary: " << peopleAtCompany.at(indexOfEmployeeWithHighestSalary)->getName() << std::endl;
    // Erno Nemecsek
}

