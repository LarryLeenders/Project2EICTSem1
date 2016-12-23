#include "stdafx.h"
#include "Subscription.h"
#include "string.h"


Subscription::Subscription()
{
	setDownloads(0);
	setMovies(0);
	setSongs(0);
	setSerie(0);
	setPrice(0);
	setName("N/A");
}

Subscription::Subscription(char name[], int price, int songs, int movies, int serie, int downloads)
{
	setName(name);
	setPrice(price);
	setSongs(songs);
	setMovies(movies);
	setSerie(serie);
	setDownloads(downloads);
}
Subscription::~Subscription()
{
	//TODO
}

char* Subscription::getName() 
{
	return _name;
}
void Subscription::setName(char name[50])
{
	if (sizeof(name) * 50 > 0)
	{
		strcpy_s(_name, name);
	}
}

int Subscription::getPrice()
{
	return _price;
}
void Subscription::setPrice(int price)
{
	if (price > 0) {
		_price = price;
	}
}

int Subscription::getSongs()
{
	return _songs;
}
void Subscription::setSongs(int songs)
{
	if (songs > 0) {
		_songs = songs;
	}
}

int Subscription::getMovies()
{
	return _movies;
}
void Subscription::setMovies(int movies)
{
	if (movies > 0) {
		_movies = movies;
	}
}

int Subscription::getSerie()
{
	return _serie;
}
void Subscription::setSerie(int serie)
{
	if (serie > 0) {
		_serie = serie;
	}
}

int Subscription::getDownloads()
{
	return _downloads;
}
void Subscription::setDownloads(int downloads)
{
	if (downloads > 0) {
		_downloads = downloads;
	}
}
std::iostream & operator<<(std::iostream & ret, Subscription & foo)
{
	ret << "Name: " << foo.getName() << endl;
	ret << "Price: " << foo.getPrice() << endl;
	ret << "Songs: " << foo.getSongs() << endl;
	ret << "Movies: " << foo.getMovies() << endl;
	ret << "Series: " << foo.getSerie() << endl;
	return ret;
}