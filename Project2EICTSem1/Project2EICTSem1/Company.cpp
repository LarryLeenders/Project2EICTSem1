#include "stdafx.h"
#include "Company.h"
#include "string.h"



Company::Company()
{	
	setName("N/A");
	setAddress("N/A");
	setVAT("N/A");
	for (int i = 0; i < 1000; i++) {
		_customers[i] = nullptr;
		_content[i] = nullptr;
		_subscriptions[i] = nullptr;
	}
}
Company::Company(char name[], char address[], char VAT[], Customer* customer[], Content* content[], Subscription* subscriptions[]) //errors omdat klasses niet gedeclareerd zijn
{	
	for (int i = 0; i < 1000; i++) {
		_customers[i] = nullptr;
		_content[i] = nullptr;
		_subscriptions[i] = nullptr;
	}
	setName(name);
	setAddress(address);
	setVAT(VAT);
	setContent(content);
	setCustomers(customer);
	setSubscriptions(subscriptions);
}


Company::~Company()
{
	//TODO
}

char* Company::getName()
{
	return name;
}
void Company::setName(char newName[])
{
	if (sizeof(newName) * 50 > 0)
	{
		strcpy_s(name, newName);
	}
}

char* Company::getAddress() 
{
	return address;
}
void Company::setAddress(char newAddress[])
{
	if (sizeof(newAddress) * 50 > 0)
	{
		strcpy_s(address, newAddress);
	}
}

char* Company::getVAT()
{
	return VAT;
}
void Company::setVAT(char newVAT[])
{
	if (sizeof(newVAT) * 50 > 0)
	{
		strcpy_s(VAT, newVAT);
	}
}

Customer* Company::getCustomers(int index)
{
	return _customers[index];
}
void Company::setCustomers(Customer* newCustomers[])//for initialisation
{
	if (sizeof(newCustomers) > 0) {
		memcpy(_customers, newCustomers, sizeof(newCustomers)*1000);
	}
}
void Company::addCustomer(Customer* newCustomer) //adds 1 customer
{
	if (strcmp((*newCustomer).getName(), "N/A") != 0) 
	{
		bool stop = false;
		for (int i = 0; i < 1000 && !stop; i++) {
			if (_customers[i] == nullptr) {
				_customers[i] = newCustomer;
				stop = true;
			}
		}
	}
}

void Company::setCustomerAtPlace(Customer * newCustomer, int place)
{
	if (newCustomer != nullptr) {
		if (strcmp((*newCustomer).getName(), "N/A") != 0)
			_customers[place] = newCustomer;
	}
}

Content* Company::getContent(int index)
{
	return _content[index];
}
void Company::setContent(Content* newContent[])
{
	if (sizeof(newContent) > 0) {
		memcpy(_content, newContent, sizeof(newContent) * 1000);
	}
}

void Company::setContentAtPlace(Content * newContent, int index)
{
	_content[index] = newContent;
}

void Company::addContent(Content * newContent)
{
	if (nullptr != newContent) {
		//find first free position in array
		bool found = false;
		int index = -1;
		for (int i = 0; i < 1000 && !found; i++) {
			if (nullptr == _content[i]) {
				index = i;
				found = true;
			}
		}
		if (index != -1) {
			_content[index] = newContent;
		}
	}
}

Subscription* Company::getSubscriptions(int index)
{
	return _subscriptions[index];
}
void Company::setSubscriptions(Subscription* newSubscriptions[])
{
	if (sizeof(newSubscriptions) > 0) {
		memcpy(_subscriptions, newSubscriptions, sizeof(newSubscriptions)*1000); //size van de array is 1000, pointer = 4byte groot => er moet dus 1000x4byte gekopieerd worden
	}
}

void Company::setSubscriptionAtPlace(Subscription * toAdd, int index)
{
	_subscriptions[index] = toAdd;
}

Invoice * Company::getInvoice(int index)
{
	return _invoices[index];
}

void Company::setInvoices(Invoice * newInvoices[])
{
	if (sizeof(newInvoices) > 0) {
		memcpy(_invoices, newInvoices, sizeof(newInvoices) * 1000); //size van de array is 1000, pointer = 4byte groot => er moet dus 1000x4byte gekopieerd worden
	}
}

void Company::addInvoice(Invoice * newInvoice)
{
	//vrije plaats zoeken in invoices en newInvoice hierbij zetten
	bool stop = false;
	for (int i = 0; i < 1000 && !stop; i++) {
		if (_invoices[i] == nullptr) {
			_invoices[i] = newInvoice;
			stop = true;
		}
	}
}

