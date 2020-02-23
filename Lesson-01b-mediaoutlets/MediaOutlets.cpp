#include "stdafx.h"
#include "MediaOutlets.h"

bool isMediaOutletANewspaper(MediaOutlet* mo) {
	if (dynamic_cast<Newspaper*>(mo) == nullptr) {
		return false;
	}
	return true;
}

Newspaper* convertMediaOutletToNewspaper(MediaOutlet* mo) {
	return dynamic_cast<Newspaper*>(mo);
}

std::string regularity_to_string(Regularity r) {
	if (r == Regularity::DAILY) {
		return "daily";
	}
	if (r == Regularity::MONTHLY) {
		return "monthly";
	}
	if (r == Regularity::YEARLY) {
		return "yearly";
	}
}