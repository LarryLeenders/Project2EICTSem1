#pragma once
#include "Content.h"
#include <iostream>


class Customer
{
private:
	char name[50];
	char address[50];
	char billingaccount[50];
	char mail[50];
	Content* history[100];
	bool paying;
public:
	Customer();
	Customer(char name[], char address[], char billingaccount[], char mail[], Content* history[], bool paying);
	~Customer();

	virtual void dummy();

	char* getName();
	void setName(char newName[]);

	char* getAddress();
	void setAddress(char newAddress[]);

	char* getBillingaccount();
	void setBillingaccount(char newBillingaccount[]);

	char* getMail();
	void setMail(char newMail[]);

	Content* getHistory(int index);
	void setHistory(Content* newHistory[]);
	void setHistoryAtPlace(Content* newHistory, int index);

	bool getPaying();
	void setPaying(bool newPaying);

	//friend std::iostream & operator<<(std::iostream & ret, Customer* foo);

};
