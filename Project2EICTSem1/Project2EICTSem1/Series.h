#pragma once
#include "Content.h"
class Series :
	public Content
{
private:
	int _seasons;
	int _episodes;
	int _airdate; //datum uitzending eerste aflevering
	char _characters[10][50]; 
public:
	Series();
	Series(char title[50], char producer[50], int year, char genre[50], int price, int airdate, int seasons, int episodes, char characters[10][50]);
	~Series();

	int getSeasons();
	void SetSeasons(int seasons);

	int getEpisodes();
	void setEpisodes(int episodes);

	int getAirdate();
	void setAirdate(int airdate);

	char* getCharacters(int index);
	void setCharacters(char characters[10][50]);
	void addCharacter(char character[50]);
};

