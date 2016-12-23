#include "stdafx.h"
#include "Invoice.h"


Invoice::Invoice()
{
	Customer* newCust = new Customer();
	for (int i = 0; i < 50; i++) {
		_forContent[i] = nullptr;
	}
	setForCustomer(newCust);
	setDate(101011950);
	setTotalPrice(0);
	setNumber(0);
}

Invoice::Invoice(Customer* cust, Content * forContent[50], int date, int total, int number) {
	for (int i = 0; i < 50; i++) {
		_forContent[i] = nullptr;
	}
	setForContent(forContent);
	setForCustomer(cust);
	setDate(date);
	setTotalPrice(total);
	setNumber(number);
}

Invoice::Invoice(Subscription * sub, Customer * cust, Content * forContent[50], int date, int total, int number)
{
	for (int i = 0; i < 50; i++) {
		_forContent[i] = nullptr;
	}
	setForContent(forContent);
	setForCustomer(cust);
	setDate(date);
	setTotalPrice(total);
	setNumber(number);
	setSubscription(sub);
}

Invoice::~Invoice()
{
}

Customer * Invoice::getForCustomer()
{
	return _forCustomer;
}
void Invoice::setForCustomer(Customer * forCustomer)
{
	if (strcmp(forCustomer->getName(), "N/A") != 0) {
		_forCustomer = forCustomer;
	}
}

Content ** Invoice::getForContent()
{
	return _forContent;
}
void Invoice::setForContent(Content * forContent[50])
{
	if (sizeof(forContent) > 0) {
		int bytes = sizeof(forContent) * 50;
		memcpy(_forContent, forContent, bytes);
	}
}

int Invoice::getDate()
{
	return _date;
}
void Invoice::setDate(int date)
{
	if (date > 101011950) { //formatting eerste 1 is nutteloos 0101 = 1 januari 1950 => jaar 1950
		_date = date;
	}
}

Subscription * Invoice::getSubscription()
{
	return _subscription;
}

void Invoice::setSubscription(Subscription * subscription)
{
	if (subscription != nullptr) {
		_subscription = subscription;
	}
}

int Invoice::getTotalPrice()
{
	return _totalPrice;
}
void Invoice::setTotalPrice(int totalPrice) {
	if (totalPrice >= 0) {
		_totalPrice = totalPrice;
	}
}

int Invoice::getNumber() {
	return _number;
}
void Invoice::setNumber(int number) {
	if (number >= 0) {
		_number = number;
	}
}

std::iostream & operator<<(std::iostream & ret, Invoice &foo) {
	ret << "ID: " << foo.getNumber() << endl;
	ret << "Date: " << foo.getDate() << endl;
	bool end = false;
	ret << "Consumed content: " << endl;
	for (int i = 0; i < 50 && !end; i++) {
		if (foo.getForContent()[i] == nullptr) {
			end = true;
		}
		else {
			ret << foo.getForContent()[i];
		}
	}
	//ALL CONTENT IS NOW ADDED
	ret << endl;
	ret << "Customer: " << foo.getForCustomer() << endl;
	return ret;
}

