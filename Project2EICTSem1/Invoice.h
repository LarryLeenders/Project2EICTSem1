#pragma once
#include "Customer.h"
#include "Content.h"
#include "Subscription.h"
class Invoice
{
private: 
	Customer* _forCustomer;
	Content* _forContent[50];
	Subscription* _subscription;
	int _date;
	int _totalPrice;
	int _number;
public:
	Invoice();
	Invoice(Customer * cust, Content * forContent[50], int date, int total, int number);
	Invoice(Subscription * sub, Customer * cust, Content * forContent[50], int date, int total, int number);
	~Invoice();

	Customer* getForCustomer();
	void setForCustomer(Customer* forCustomer);

	Content** getForContent();
	void setForContent(Content* forContent[50]);

	int getDate();
	void setDate(int date);

	Subscription* getSubscription();
	void setSubscription(Subscription* subscription);

	int getTotalPrice();
	void setTotalPrice(int totalPrice);

	int getNumber();
	void setNumber(int number);

	friend std::iostream & operator<<(std::iostream & os, Invoice &foo);
};

