// MultithreadedQueueExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <deque>
#include <list>
#include <vector>
#include <thread>

#include <stdlib.h> // srand, rand miatt

#include "people.h"

void initialize_random_seed() {
	srand(
		static_cast<unsigned int>(std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now()
		))
	); // rand() random generator seed-je mindig mas lesz
}

void printTellers(const std::list<Teller>& tels) {
	int cnt = 1;
	for (const auto& tel : tels) {
		std::cout << "Teller " << cnt++ << std::endl;
		tel.printServicedCustomers();
	}
}

void printCustomers(const std::deque<Customer>& cus) {
	for (const auto& cu : cus) {
		std::cout << "\t\t" << cu << std::endl;
	}
}

void removeFinishedCustomers(std::deque<Customer>& cus) {
	std::deque<int> positionsToDeleteInReverseOrder; // forditott sorrendbe vannak
	for (unsigned int inx = 0; inx < cus.size(); inx++) {
		if (cus[inx].getTaskComplexityAsInt() == 0) {
			positionsToDeleteInReverseOrder.push_front(inx);
		}
	}
	for (const int pos : positionsToDeleteInReverseOrder) {
		cus.erase(cus.cbegin() + pos);
	}
}

int main()
{
	std::deque<Customer> customers;
	std::list<Teller> tellers;
	typedef std::list<Teller>::iterator TellIt;

	tellers.push_back(Teller(customers));

	initialize_random_seed();

	int customerId = 0;

	while (true) {
		std::cout << "===== New tick =====" << std::endl;

		// Random szamu (0 es 4 kozotti) ugyfel, random igenyelt (1 es 15 mp kozotti) idovel
		for (int i = 0; i < rand() % 5; i++) { // rand() 0 es RAND_MAX kozotti szamot ad vissza, ezert modulozzuk
			customers.push_back(Customer(customerId++, std::chrono::seconds(rand() % 15 + 1)));
		}
		std::cout << '{' << tellers.size() << " tellers}" << std::endl;
		std::cout << "\tCustomers to service:" << std::endl;
		printCustomers(customers);

		std::vector<std::thread> threadsToRun;

		// A kiszolgalok most 5 masodpercig kiszolgaljak az ugyfeleket
		for (TellIt i = tellers.begin(); i != tellers.end(); i++) {
			//(*i).run();
			threadsToRun.push_back(
				std::thread([](TellIt ip) -> void { (*ip).run(); }, i)
			);
		}

		for (std::thread& ttr : threadsToRun) {
			ttr.join();
		}

		std::cout << "\tCustomers remaining:" << std::endl;
		printTellers(tellers);
		printCustomers(customers);

		removeFinishedCustomers(customers);

		// Ha tobb mint 2x annyi ugyfel van mint kiszolgalo, letrehozunk meg 1 kiszolgalot:
		if (customers.size() / tellers.size() > 2) {
			tellers.push_back(Teller(customers));
		}
		// Ha tobb mint 1 kiszolgalo van es nincs 2x annyi ugyfel mint kiszolgalo, 1 kiszolgalo pihenhet
		if (tellers.size() > 1 && customers.size() / tellers.size() < 2) {
			for (TellIt i = tellers.begin(); i != tellers.end(); i++) {
				//if (!(*i).isBusy()) {
					tellers.erase(i);
					break;
				//}
			}
		}

		if (
			customers.empty() //&&
			/*std::find_if(
				tellers.begin(),
				tellers.end(),
				[](const Teller& t) -> bool { return t.isBusy(); }) == tellers.cend()
			*/
			) {
			break;
		}

		std::cin.get();
	}
}