#pragma once
class Subscription
{
private:
	char _name[50];
	int _price;
	int _songs;
	int _movies;
	int _serie;
	int _downloads;
public:
	Subscription();
	Subscription(char name[], int price, int songs, int movies, int serie, int downloads);
	~Subscription();

	char* getName();
	void setName(char name[50]);

	int getPrice();
	void setPrice(int price);

	int getSongs();
	void setSongs(int songs);

	int getMovies();
	void setMovies(int movies);

	int getSerie();
	void setSerie(int serie);

	int getDownloads();
	void setDownloads(int downloads);

	friend std::iostream & operator<<(std::iostream & ret, Subscription &foo);
};

