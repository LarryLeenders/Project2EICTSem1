#pragma once
#include <iostream>
class Content
{
private:
	char title[50];
	char producer[50];
	int year;
	char genre[50];
	int price;
public:
	Content();
	Content(char title[], char producer[], int year, char genre[], int price);
	virtual ~Content();
	

	char* getTitle();
	void setTitle(char newTitle[]);

	char* getProducer();
	void setProducer(char newProducer[]);

	int getYear();
	void setYear(int newYear);

	char* getGenre();
	void setGenre(char newGenre[]);

	int getPrice();
	void setPrice(int newPrice);

	friend std::iostream & operator<<(std::iostream & ret, Content &foo);
};

