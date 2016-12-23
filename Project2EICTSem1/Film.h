#pragma once
#include "Content.h"
class Film :
	public Content
{
public:
	Film();
	Film(int length, char actors[][50], char quality[50], char description[50], char title[50], char producer[50], int year, char genre[50], int price);
	~Film();

	int getLength();
	void setLength(int length);

	char* getActors(int index);
	void setActors(char actors[50][50]);
	void addActor(char actor[50]);

	char* getQuality();
	void setQuality(char quality[50]);

	char* getDescription();
	void setDescription(char description[50]);

private:
	int _length;
	char _actors[50][50];
	char _quality[50];
	char _description[50];
};

