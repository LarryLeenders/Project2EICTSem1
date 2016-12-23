#pragma once
#include "Content.h"

class Music :
	public Content
{
private:
	int _length;
	char _format[50][50];
	char _remix[50];
	char _album[50];

public:
	Music();
	Music(char title[50], char producer[50], int year, char genre[50], int price, char album[50], char format[50][50], char remix[50], int lenth);
	~Music();

	int getLength();
	void setLength(int length);

	char* getFormat(int index);
	void addFormat(char format[50]);
	void setFormat(char format[50][50]);

	char* getRemix();
	void setRemix(char remix[50]);

	char* getAlbum();
	void setAlbum(char album[50]);
};

