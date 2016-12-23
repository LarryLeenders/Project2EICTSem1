#include "stdafx.h"
#include "Series.h"
#include <string.h>


Series::Series():Content()
{
	setAirdate(101011950);
	for (int i = 0; i < 10; i++) {
		strcpy_s(_characters[i], "N/A");
	}
	SetSeasons(-1);
	setEpisodes(-1);
}

Series::Series(char title[50], char producer[50], int year, char genre[50], int price, int airdate, int seasons, int episodes, char characters[10][50]) :Content(title, producer, year, genre, price) {
	setAirdate(airdate);
	SetSeasons(seasons);
	setEpisodes(episodes);
	setCharacters(characters);
}


Series::~Series()
{
}

int Series::getSeasons() {
	return _seasons;
}
void Series::SetSeasons(int seasons) {
	if (seasons > 0 || seasons == -1) { //-1 voor initialisatie
		_seasons = seasons;
	}
}

int Series::getEpisodes() {
	return _episodes;
}
void Series::setEpisodes(int episodes) {
	if (episodes > 0 || episodes == -1) {//-1 voor initialisatie
		_episodes = episodes;
	}
}

int Series::getAirdate() {
	return _airdate;
}
void Series::setAirdate(int airdate) {
	if (airdate > 101011950) { //formatting eerste 1 is nutteloos 0101 = 1 januari 1950 => jaar 1950
		_airdate = airdate;
	}
}

char* Series::getCharacters(int index) {
	return _characters[index];
}
void Series::setCharacters(char characters[10][50]) {
	if (sizeof(characters) > 0) {
		int bytes = sizeof(characters) * 50;
		memcpy(_characters, characters, bytes);
	}
}

void Series::addCharacter(char character[50])
{
	//find first free place
	bool found = false;
	int index = -1;
	for (int i = 0; i < 50 && !found; i++) {
		if (_characters[i] == nullptr) {
			found = true;
			index = i;
		}
	}
	if (found) {
		strcpy_s(_characters[index], character);
	}
}
