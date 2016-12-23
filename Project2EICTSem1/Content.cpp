#include "stdafx.h"
#include "Content.h"
#include "string.h"
#include <ctime>


Content::Content()
{
	setTitle("N/A");
	setProducer("N/A");
	setYear(1800);
	setGenre("N/A");
	setPrice(0);
}

Content::Content(char title[], char producer[], int year, char genre[], int price)
{
	setTitle(title);
	setProducer(producer);
	setYear(year);
	setGenre(genre);
	setPrice(price);
}

Content::~Content()
{
}


char* Content::getTitle()
{
	return title;
}
void Content::setTitle(char newTitle[])
{
	if (sizeof(newTitle) * 50 > 0)
	{
		strcpy_s(title, newTitle);
	}
}

char* Content::getProducer()
{
	return producer;
}
void Content::setProducer(char newProducer[])
{
	if (sizeof(newProducer) * 50 > 0)
	{
		strcpy_s(producer, newProducer);
	}
}

int Content::getYear()
{
	return year;
}
void Content::setYear(int newYear) //damages a heap when called on a wrongly formatted number
{
	if (newYear >= 1800 && newYear <= 2016) //kijken of het ingegeven jaar tussen 1800 en het huidige jaar valt
	{
		year = newYear;
	}
}

char* Content::getGenre()
{
	return genre;
}
void Content::setGenre(char newGenre[])
{
	if (sizeof(newGenre) * 50 > 0)
	{
		strcpy_s(genre, newGenre);
	}
}

int Content::getPrice()
{
	return price;
}
void Content::setPrice(int newPrice)
{
	if (newPrice >= 0)
	{
		price = newPrice;
	}
}

std::iostream & operator<<(std::iostream & ret, Content & foo)
{
	ret << "Title: " << foo.getTitle() << endl;
	ret << "Price: " << foo.getPrice() << endl;
	return ret;
}
