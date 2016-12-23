#pragma once
#include "Subscription.h"
#include "Content.h"
class Paying :
	public Customer
{
private:
	Subscription* _subscriptiontype;
	int _length;
	Content* _downloads[100];
public:
	Paying();
	Paying(char name[], char address[], char billingaccount[], char mail[], Content * history[], bool paying, Subscription* subscriptiontype, int length, Content * downloads[]);
	~Paying();

	Subscription* getSubscriptiontype();
	void setSubscriptiontype(Subscription* subscriptiontype);

	int getLength();
	void setLength(int length);

	Content* getDownloads(int index);
	void setDownloads(Content* downloads[100]);
};

