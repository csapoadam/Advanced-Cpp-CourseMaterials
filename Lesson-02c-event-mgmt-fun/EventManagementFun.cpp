// EventManagementFun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>

class EventManager {
	std::vector<
		std::pair<
			std::string, // mi az event tipus neve?
			std::function<void(std::vector<std::string>) >
		>
	> clients;
public:
	EventManager() {}
	void notify(std::string eventName, std::vector<std::string> values) {
		for (auto client : clients) {
			if (client.first == eventName) {
				client.second(values);
			}
		}
	}
	void registerEvent(
		std::string eventName,
		std::function<void(std::vector<std::string>)> func) {
		clients.push_back(std::make_pair(
			eventName, func
		));
	}
};

class EventEmitter {
	EventManager* emgr;
public:
	EventEmitter(EventManager* ep) : emgr(ep) {}
	void emit(std::string eventName, std::vector<std::string> values) {
		emgr->notify(eventName, values);
	}
};

class Thermostat : public EventEmitter {
	int temperature;
public:
	Thermostat(EventManager* ep) : EventEmitter(ep) { temperature = 0; }
	void setTemperature(int t) {
		temperature = t;
		if (temperature > 30) {
			emit("highTemp", std::vector<std::string>());
		}
		if (temperature < 2) {

			emit("lowTemp", std::vector<std::string>());
		}
	}
};

class Refrigerator : public EventEmitter {

};

int main()
{
	EventManager em;
	Thermostat t(&em);

	auto triggerWhenTemperatureIsHigh = [](auto t) {std::cout << "Temperature is high" << std::endl; };
	auto triggerWhenTemperatureIsLow = [](auto t) {std::cout << "Temperature is low" << std::endl; };
	em.registerEvent("highTemp", triggerWhenTemperatureIsHigh);
	em.registerEvent("lowTemp", triggerWhenTemperatureIsLow);

	for (int i = 0; i < 10; i++) {
		std::cout << "What is the temperature? " << std::endl;
		int temp;
		std::cin >> temp;
		t.setTemperature(temp);
	}

	std::cin.get();
    return 0;
}

