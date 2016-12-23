#pragma once
#include "Customer.h"
#include "Content.h"
#include "Subscription.h"
#include "Invoice.h"
using namespace std;
class Company
{
private:
	char name[50];
	char address[50];
	char VAT[50];
	Customer* _customers[1000];
	Content* _content[1000];
	Subscription* _subscriptions[1000];
	Invoice* _invoices[1000];
public:
	Company();
	Company(char name[], char address[], char VAT[], Customer * customer[], Content * content[], Subscription * subscriptions[]);
	virtual ~Company();

	char* getName();
	void setName(char newName[]);

	char* getAddress();
	void setAddress(char newAddress[]);

	char* getVAT();
	void setVAT(char newVAT[]);

	Customer * getCustomers(int index);
	void setCustomers(Customer* newCustomers[]);
	void addCustomer(Customer* newCustomer);
	void setCustomerAtPlace(Customer* newCustomer, int place);

	Content * getContent(int index);
	void setContent(Content* newContent[]);
	void setContentAtPlace(Content * newContent, int index);
	void addContent(Content* newContent);

	Subscription* getSubscriptions(int index);
	void setSubscriptions(Subscription* newSubscriptions[]);
	void setSubscriptionAtPlace(Subscription* toAdd, int index);

	Invoice* getInvoice(int index);
	void setInvoices(Invoice* newInvoices[]);
	void addInvoice(Invoice* newInvoice);
};

