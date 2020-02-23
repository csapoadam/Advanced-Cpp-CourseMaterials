#pragma once

#include "helpers.h"

class MediaOutlet {
protected:
	std::string name;
public:
	MediaOutlet(std::string n) : name(n) {}
	virtual void introduce() = 0;
};

class Newspaper : public MediaOutlet {
	Person* editor;
	Regularity regularity;
	int timesPublished;
	std::vector<Person*> subscribers;
public:
	Newspaper(std::string nm, Person* p, Regularity r) : MediaOutlet(nm), editor(p), regularity(r), timesPublished(0) {}
	void publish() {
		timesPublished++;
	}
	void subscribe(Person* p) { subscribers.push_back(p); }
	void introduce() {
		std::cout << "Newspaper called ";
		std::cout << name;
		std::cout << " (editor in chief: ";
		std::cout << editor->getName();
		std::cout << ") appears on a";
		std::cout << regularity_to_string(regularity);
		std::cout << " basis and has been published ";
		std::cout << timesPublished;
		std::cout << " times" << std::endl;
	}
	void printSubscribers() {
		if (subscribers.size() > 0) {
			std::cout << subscribers.size() << " people subscribed";
			std::cout << " to newspaper called " << name << ":";
			std::cout << std::endl;
			for (const auto& subscriber : subscribers) {
				std::cout << " --> " << subscriber->getName() << std::endl;
			}
		}
	}
};

class TVShow : public MediaOutlet {	
	Person* host;
	int numTimesAired;
public:
	TVShow(std::string nm, Person* p) : MediaOutlet(nm), host(p), numTimesAired(0) {}
	void air() {
		numTimesAired++;
	}
	void introduce() {}
};