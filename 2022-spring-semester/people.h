#pragma once

class Customer {
	int customerId;
	std::chrono::seconds taskComplexity;
	bool isCurrentlyWaiting;
	bool isAlreadyDone;
public:
	friend std::ostream& operator<<(std::ostream&, const Customer&);
	Customer(int id, std::chrono::seconds taskComplexity) :
		customerId{ id },
		taskComplexity{taskComplexity},
		isCurrentlyWaiting{true},
		isAlreadyDone{false}
	{}
	int getId() { return customerId; }
	bool isWaiting() { return isCurrentlyWaiting; }
	void startServing() { isCurrentlyWaiting = false; }
	void stopServing() { isCurrentlyWaiting = true; }
	int getTaskComplexityAsInt() { return static_cast<int>(taskComplexity.count()); }
	void setToDone() { isAlreadyDone = true; setComplexityTo(0); }
	void setComplexityTo(int newcompl) { taskComplexity = std::chrono::seconds(newcompl); }
};

std::ostream& operator<<(std::ostream& os, const Customer& customerRef) {
	return os << "Customer with id: " << customerRef.customerId << ". Remaining time: " << customerRef.taskComplexity.count();
}

class Teller {
	std::deque<Customer>& customersRef;
	bool isCurrentlyBusy;
	std::vector<Customer*> servicedCustomers;
public:
	Teller(std::deque<Customer>& waitingCustomers) :
		customersRef{waitingCustomers},
		isCurrentlyBusy{false}
	{}
	bool isBusy() const {
		return isCurrentlyBusy;
	}
	void run() {
		servicedCustomers.clear();
		int timeAvailable = 5; // 5 szekundumig szolgalja ki az ugyfeleket
		while (timeAvailable > 0) {
			
			for (unsigned int custinx = 0; custinx < customersRef.size(); custinx++) {
				Customer& cust = customersRef[custinx];
				if (cust.isWaiting()) {
					isCurrentlyBusy = true;
					cust.startServing();
					servicedCustomers.push_back(&cust);

					int remainingTimeForCustomer = cust.getTaskComplexityAsInt();
					if (timeAvailable >= remainingTimeForCustomer) {
						cust.setToDone();
						timeAvailable = timeAvailable - remainingTimeForCustomer;
					}
					else {
						cust.setComplexityTo(remainingTimeForCustomer - timeAvailable);
						cust.stopServing();
						timeAvailable = 0;
					}
					isCurrentlyBusy = false;
				}
			}

			// mi tortenik, ha 1 ugyfelet se talal akit kiszolgalhatna?
			timeAvailable = timeAvailable - 1;
		}
	}
	void printServicedCustomers() const {
		for (auto& cust : servicedCustomers) {
			std::cout << "\t\tServed customer " << cust->getId();
			std::cout << " Remaining time: " << cust->getTaskComplexityAsInt() << std::endl;
		}
	}
};