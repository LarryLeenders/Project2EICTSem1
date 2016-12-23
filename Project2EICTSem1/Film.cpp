#include "stdafx.h"
#include "Film.h"
#include <string.h>


Film::Film():Content()
{
	setLength(0);
	setQuality("N/A");
	setDescription("N/A");
	for (int i = 0; i < 50; i++) {
		strcpy_s(_actors[i], "N/A");
	}
}

Film::Film(int length, char actors[][50], char quality[50], char description[50], char title[50], char producer[50], int year, char genre[50], int price) :Content(title, producer, year, genre, price) {
	setLength(length);
	setActors(actors);
	setQuality(quality);
	setDescription(description);
}


Film::~Film()
{
}

int Film::getLength()
{
	return _length;
}
void Film::setLength(int length)
{
	if (length >= 0) {
		_length = length;
	}
}

char* Film::getActors(int index) 
{
	return _actors[index];
}
void Film::setActors(char actors[50][50])
{
	if (sizeof(actors) > 0)
	{
		int bytes = sizeof(actors)*50;
		memcpy(_actors, actors, bytes);
	}
}

void Film::addActor(char actor[50])
{
	//find first free place
	bool found = false;
	int index = -1;
	for (int i = 0; i < 50 && !found; i++) {
		if (_actors[i] == nullptr) {
			found = true;
			index = i;
		}
	}
	if (found) {
		strcpy_s(_actors[index], actor);
	}
}

char* Film::getQuality() 
{
	return _quality;
}
void Film::setQuality(char quality[50]) 
{
	if (strlen(quality) > 0) 
	{
		strcpy_s(_quality, quality);
	}
}

char* Film::getDescription()
{
	return _description;
}
void Film::setDescription(char description[50])
{
	if (strlen(description) > 0)
	{
		strcpy_s(_description, description);
	}
}