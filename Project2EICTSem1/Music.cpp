#include "stdafx.h"
#include "Music.h"
#include "string.h"


Music::Music():Content()
{
	setAlbum("N/A");
	for (int i = 0; i < 50; i++) {
		strcpy_s(_format[i], "N/A");
	}
	setRemix("N/A");
	setLength(0);
}

Music::Music(char title[50], char producer[50], int year, char genre[50], int price, char album[50], char format[50][50], char remix[50], int length) :Content(title, producer, year, genre, price) {
	setAlbum(album);
	setFormat(format);
	setRemix(remix);
	setLength(length);
}

Music::~Music()
{
}

char* Music::getAlbum() {
	return _album;
}
void Music::setAlbum(char album[50]) {
	if (sizeof(album) > 0) {
		int bytes = sizeof(album) * 50;
		memcpy(_album, album, bytes);
	}
}

char* Music::getFormat(int index) {
	return _format[index];
}
void Music::addFormat(char format[50])
{
	//find first free place
	bool found = false;
	int index = -1;
	for (int i = 0; i < 50 && !found; i++) {
		if (_format[i] == nullptr) {
			found = true;
			index = i;
		}
	}
	if (found) {
		strcpy_s(_format[index], format);
	}
}
void Music::setFormat(char format[50][50]) {
	if (sizeof(format) > 0) {
		int bytes = sizeof(format) * 50;
		memcpy(_format, format, bytes);
	}
}

char* Music::getRemix() {
	return _remix;
}
void Music::setRemix(char remix[50]) {
	if (sizeof(remix) > 0) {
		strcpy_s(_remix, remix);
	}
}

int Music::getLength() {
	return _length;
}
void Music::setLength(int length) {
	if (length >= 0) {
		_length = length;
	}
}
