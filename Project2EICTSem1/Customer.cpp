#include "stdafx.h"
#include "Customer.h"
#include "string.h"
#include "Content.h"


Customer::Customer()
{
	setName("N/A");
	setAddress("N/A");
	setBillingaccount("N/A");
	setMail("N/A");
	for (int i = 0; i < 100; i++) {
		history[i] = nullptr;
	}
	setPaying(false);
}

Customer::Customer(char name[], char address[], char billingaccount[], char mail[], Content* history[], bool paying)
{
	setName(name);
	setAddress(address);
	setBillingaccount(billingaccount);
	setMail(mail);
	setHistory(history);
	setPaying(paying);
}

Customer::~Customer()
{
}

void Customer::dummy()
{
}



char* Customer::getName()
{
	return name;
}
void  Customer::setName(char newName[])
{
	if (sizeof(newName) * 50 > 0) {
		strcpy_s(name, newName);
	}
}

char* Customer::getAddress()
{
	return address;
}
void  Customer::setAddress(char newAddress[])
{
	if (sizeof(newAddress) * 50 > 0) {
		strcpy_s(address, newAddress);
	}
}

char* Customer::getBillingaccount()
{
	return billingaccount;
}
void  Customer::setBillingaccount(char newBillingaccount[])
{
	if (sizeof(newBillingaccount) * 50 > 0) {
		strcpy_s(billingaccount, newBillingaccount);
	}
}

char* Customer::getMail()
{
	return mail;
}
void  Customer::setMail(char newMail[])
{
	if (sizeof(newMail) * 50 > 0) {
		strcpy_s(mail, newMail);
	}
}

Content* Customer::getHistory(int index)
{
	return history[index];
}
void  Customer::setHistory(Content* newHistory[])
{
	if (newHistory != NULL) {
		memcpy(history, newHistory, sizeof(newHistory) * 100);
	}
}

void Customer::setHistoryAtPlace(Content * newHistory, int index)
{
	if (newHistory != NULL) {
		memcpy(history[index], newHistory, sizeof(newHistory));
	}
}

bool Customer::getPaying()
{
	return paying;
}
void  Customer::setPaying(bool newPaying)
{
	if ((newPaying == true || newPaying == false) && newPaying != NULL) {
		paying = newPaying;
	}
}

/*std::iostream & operator<<(std::iostream & ret, Customer* foo) { //does not work
	ret << foo->getName() << endl;
	ret << foo->getMail() << endl;
	ret << foo->getPaying() << endl;;
	ret << foo->getBillingaccount() << endl;;
	ret << foo->getAddress() << endl;
	return ret;
}*/
;
