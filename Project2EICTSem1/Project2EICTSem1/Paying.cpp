#include "stdafx.h"
#include "Paying.h"
#include <string.h>


Paying::Paying():Customer()
{
	Subscription* newtype = new Subscription();
	setSubscriptiontype(newtype);
	setLength(1);
	Content* newDownloads[100];
	for (int i = 0; i < 100; i++) {
		newDownloads[i] = new Content();
	}
	setDownloads(newDownloads);
}

Paying::Paying(char name[], char address[], char billingaccount[], char mail[], Content* history[], bool paying, Subscription* subscriptiontype, int length, Content* downloads[]) :Customer(name, address, billingaccount, mail, history, paying) {
	setSubscriptiontype(subscriptiontype);
	setLength(length);
	setDownloads(downloads);
}


Paying::~Paying()
{
}

Subscription* Paying::getSubscriptiontype() {
	return _subscriptiontype;
}
void Paying::setSubscriptiontype(Subscription* subscriptiontype) {
	if ( (strcmp(subscriptiontype->getName(), "N/A") != 0 )){ //checken of subscriptiontype wel een geldige naam heeft
		_subscriptiontype = subscriptiontype;
	}
}

int Paying::getLength() {
	return _length;
}
void Paying::setLength(int length) {
	if (length > 0) {
		_length = length;
	}
}

Content* Paying::getDownloads(int index){
	return _downloads[index];
}
void Paying::setDownloads(Content* downloads[100]) {
	if (sizeof(downloads) > 0) {
		int bytes = sizeof(downloads) * 50;
		memcpy(_downloads, downloads, bytes);
	}
}