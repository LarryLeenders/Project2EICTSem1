// Project2EICTSem1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
using namespace std;

/*#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif*/

//in sequence of when created
void firstStartup();
void checkPerson();
void doFunction(int choice);
void editCustomer();
void createCustomer();
void deleteCustomer();
void addInvoice();
Content* make_Content(int choice);
Customer * make_Customer(int choice);
void findAndPrintContent();
void findAndPrintCustomer();
void findAndPrintInvoice();
void addContent();
void deleteContent();
void addSubscription();
void deleteSubscription();
void findAndPrintSubscription();
void editSubscription();
void editSeries(Series* newSeries);
void editFilm(Film* newFilm);
void editMusic(Music* newMusic);
template<typename Base, typename T>
inline bool instanceof(const T *ptr);
void editContent();
void quitProgram();
inline bool exists(const std::string& name);
void loadValuesFromFiles();

//GLOBAL VARIABLES
bool isOwner = false;
Company thiscompany = Company();

//MAIN FUNCTION
int main()
{
	int choice = -1;
	bool isFirstStartup = false;
	//add check to see if files exist and if not do the firstStartup() function
	if (!exists("CompanySettings.dat")) {
		firstStartup();//company should now be initialized with no customers, content or subscriptions.
		isFirstStartup = true;
	}
	else {
		//load thiscompany with the correct values
		loadValuesFromFiles();
	}
	//ask whether user is owner or just employee and print the correct menu
	checkPerson();
	bool quit = false;
	while (!quit) {
		cout << "Which action do you want to do? \n 0. Quit \n 1. Add Customer \n 2. Change Customer \n 3. Delete Customer \n 4. Create Invoice \n 5. Search Invoice \n 6. Search Customer \n 7. Search Content \n";
		if (isOwner) {
			cout << " 8. Add Content \n 9. Delete Content \n 10. Add Subscription \n 11. Change Subscription \n 12. Delete Subscription \n 13. Search Subscription \n 14. edit Content \n";
		}
		cin >> choice;
		cin.ignore();
		if (isOwner && choice >= 1 && choice <= 14) {
			doFunction(choice);
		}
		else if (choice >= 1 && choice <= 7) {
			doFunction(choice);
		}
		else if (!isOwner && choice > 7 && choice <= 14) {
			cout << "access restricted, employee can only select options 0 through 7" << endl;
		}
		else if (choice > 14) {
			cout << "invalid choice" << endl;
		}
		else if (choice == 0) {
			quit = true;
			quitProgram();
		}
	}
	//cin.get();
    return 0;
}

void quitProgram() {
	//save the company settings
	ofstream companySettings("CompanySettings.dat", ios::out);
	if (!companySettings) {
		cout << "ERROR IN OPENING subscriptionArrayContents.dat" << endl;
	}
	else {
		companySettings << thiscompany.getName()<<endl;
		companySettings << thiscompany.getAddress() << endl;
		companySettings << thiscompany.getVAT() << endl;
	}
	companySettings.close();

	//save _customers
	ofstream customerArrayContents("NormalCustomerArrayContents.dat", ios::out);
	if (!customerArrayContents) {
		cout << "ERROR IN OPENING NormalCustomerArrayContents.dat" << endl;
	}
	else {
		for (int i = 0; i < 1000; i++) {
			if (thiscompany.getCustomers(i) != nullptr) {
				if (thiscompany.getCustomers(i)->getPaying() == false) {
					customerArrayContents << thiscompany.getCustomers(i)->getName() << endl << thiscompany.getCustomers(i)->getAddress() << endl << thiscompany.getCustomers(i)->getBillingaccount() << endl << false << endl;
					//history should be saved as well
					//we only save the names of things the customer watched
					for (int j = 0; j < 100; j++) {
						if (thiscompany.getCustomers(1)->getHistory(j) != nullptr) {
							customerArrayContents << thiscompany.getCustomers(1)->getHistory(j)->getTitle()<<endl;
						}
						else {
							customerArrayContents << "NULL"<<endl;
						}
					}
				}
			}
			else {
				//if there is an empty space we still need 104(name, address, billingaccount, paying or not and 100 histories) lines to be inserted so that our readout stays consistent
				for (int i = 0; i < 104; i++) {
					customerArrayContents << "NULL" << endl;
				}
			}
		}
	}
	customerArrayContents.close();

	//save paying customers (right now paying customers are saved in _customers)
	ofstream payingCustomerArrayContents("PayingCustomerArrayContents.dat", ios::out);
	if (!customerArrayContents) {
		cout << "ERROR IN OPENING PayingCustomerArrayContents.dat" << endl;
	}
	else {
		for (int i = 0; i < 1000; i++) {
			if (thiscompany.getCustomers(i) != nullptr) {
				if (thiscompany.getCustomers(i)->getPaying() == true) {
					Customer* cust = make_Customer(2);
					cust = thiscompany.getCustomers(i);
					Paying* payer = nullptr;
					payer = dynamic_cast<Paying*>(cust);
					payingCustomerArrayContents << payer->getName() << endl << payer->getAddress() << endl << payer->getBillingaccount() << endl << true << endl << payer->getSubscriptiontype()->getName() << endl << payer->getLength() << endl;
					//history should be saved as well
					//we only save the names of things the customer watched
					for (int j = 0; j < 100; j++) {
						if (thiscompany.getCustomers(1)->getHistory(j) != nullptr) {
							customerArrayContents << thiscompany.getCustomers(1)->getHistory(j)->getTitle()<<endl;
						}
						else {
							payingCustomerArrayContents << "NULL"<<endl;
						}
					}
					//for paying customer their downloads need to be saved as well
					//we only save the names of things the customer downloaded
					for (int j = 0; j < 100; j++) {
						if (payer->getDownloads(j) != nullptr) {
							payingCustomerArrayContents << payer->getDownloads(j)->getTitle() << endl;
						}
						else {
							payingCustomerArrayContents << "NULL"<<endl;
						}
					}
					delete cust;
					delete payer;
				}
			}
			else {
				//if there is an empty space we still need 206 lines to be inserted so that our readout stays consistent
				for (int i = 0; i < 206; i++) {
					customerArrayContents << "NULL" << endl;
				}
			}
		}
	}
	payingCustomerArrayContents.close();

	//save _content
	ofstream contentArrayContents("contentArrayContents.dat", ios::out);
	if (!contentArrayContents) {
		cout << "ERROR IN OPENING contentArrayContents.dat" << endl;
	}
	else {
		for (int i = 0; i < 1000; i++) {
			if (thiscompany.getContent(i) != nullptr) {
				if (instanceof<Music>(thiscompany.getContent(i))) {
					Music* newmus = dynamic_cast<Music*>(thiscompany.getContent(i));
					//music has 58 lines
					contentArrayContents << "Music" << endl << newmus->getTitle() << endl << newmus->getGenre() << endl << newmus->getPrice() << endl << newmus->getProducer() << endl << newmus->getYear() << endl << newmus->getAlbum() << endl;
					//music formats
					for (int i = 0; i < 50; i++) {
						if (newmus->getFormat(i) != nullptr) {
							contentArrayContents << newmus->getFormat(i) << endl;
						}
						else {
							contentArrayContents << "NULL" << endl;
						}
					}
					//rest of music params
					contentArrayContents << newmus->getRemix() << endl << newmus->getLength() << endl;
					delete newmus;
				}
				if (instanceof<Series>(thiscompany.getContent(i))) {
					//series has 18 lines but we fill the rest in with NULL so that length stays consistent
					Series* newser = dynamic_cast<Series*>(thiscompany.getContent(i));
					contentArrayContents << "Series" << endl << newser->getTitle() << endl << newser->getGenre() << endl << newser->getPrice() << endl << newser->getProducer() << endl << newser->getYear() << endl << newser->getAirdate() << endl;
					for (int i = 0; i < 50; i++) {
						if (i < 10 && newser->getCharacters(i) != nullptr && strcmp(newser->getCharacters(i),"N/A") != 0) {
							contentArrayContents << newser->getCharacters(i) << endl;
						}
						else {
							contentArrayContents << "NULL" << endl;
						}
					}
					contentArrayContents << newser->getSeasons() << endl << newser->getEpisodes() << endl;
					delete newser;
				}
				if (instanceof<Film>(thiscompany.getContent(i))) {
					//Film has 58 lines
					Film* newfilm = dynamic_cast<Film*>(thiscompany.getContent(i));
					contentArrayContents << "Film" << endl << newfilm->getTitle() << endl << newfilm->getGenre() << endl << newfilm->getPrice() << endl << newfilm->getProducer() << endl << newfilm->getYear() << endl << newfilm->getDescription() << endl;
					for (int i = 0; i < 50; i++) {
						if (newfilm->getActors(i) != nullptr) {
							contentArrayContents << newfilm->getActors(i) << endl;
						}
						else {
							contentArrayContents << "NULL" << endl;
						}
					}
					contentArrayContents << newfilm->getLength() << endl << newfilm->getQuality() << endl;
					delete newfilm;
				}
			}
			else {
				for (int i = 0; i < 58; i++) { //keep the same length
					contentArrayContents << "NULL" << endl;
				}
			}
		}
	}
	contentArrayContents.close();

	//save _subscriptions
	ofstream subscriptionArrayContents("subscriptionArrayContents.dat", ios::out);
	if (!subscriptionArrayContents) {
		cout << "ERROR IN OPENING subscriptionArrayContents.dat" << endl;
	}
	else {
		for (int i = 0; i < 1000; i++) {
			if (thiscompany.getSubscriptions(i) != nullptr) {
				Subscription * newsub = thiscompany.getSubscriptions(i);
				subscriptionArrayContents << newsub->getName() << endl << newsub->getPrice() << endl << newsub->getDownloads() << endl << newsub->getMovies() << endl << newsub->getSerie() << endl << newsub->getSongs() << endl;
				delete newsub;
			}
			else {
				for (int i = 0; i < 6; i++) {
					subscriptionArrayContents << "NULL" << endl;
				}
			}
		}
	}
	subscriptionArrayContents.close();

	//save _invoices
	ofstream invoicesArrayContents("invoicesArrayContents.dat", ios::out);
	if (!invoicesArrayContents) {
cout << "ERROR IN OPENING invoicesArrayContents.dat" << endl;
	}
	else {
		for (int i = 0; i < 1000; i++) {
			if (thiscompany.getInvoice(i) != nullptr) {
				Invoice* newinv = thiscompany.getInvoice(i);
				invoicesArrayContents << newinv->getDate() << endl << newinv->getForCustomer()->getName() << endl << newinv->getNumber() << endl << newinv->getSubscription()->getName() << endl << newinv->getTotalPrice() << endl;
				for (int i = 0; i < 50; i++) {
					if (newinv->getForContent()[i] != nullptr) {
						invoicesArrayContents << newinv->getForContent()[i]->getTitle() << endl;
					}
					else {
						invoicesArrayContents << "NULL" << endl;
					}
				}
				delete newinv;
			}
			else {
				for (int i = 0; i < 55; i++) {
					invoicesArrayContents << "NULL" << endl;
				}
			}
		}
	}
	invoicesArrayContents.close();
}

void loadValuesFromFiles() {
	//read all array values and companysettings from files

	//get values for company from CompanySettings.dat
	ifstream companySettings("CompanySettings.dat", ios::in);
	companySettings >> noskipws; //don't skip whitespaces
	if (companySettings.is_open()) {
		char value[50] = "";
		int counter = 0;
		while (companySettings) {
			companySettings.getline(value, 50);
			//cout << value << endl;
			if (counter == 0) {
				thiscompany.setName(value);
			}
			else if (counter == 1) {
				thiscompany.setAddress(value);
			}
			else if (counter == 2) {
				thiscompany.setVAT(value);
			}
			counter++;
		}
	}
	companySettings.close();
	//	cout << "DEBUG: name:" << thiscompany.getName() << " address:" << thiscompany.getAddress() << " VAT:" << thiscompany.getVAT() << endl;
		//thiscompany now has correct settings

		//restore _content
		//BUILD IN SUPPORT FOR SUBCLASSES
		//consists of contentArrayContents.dat
	/*bug with music, film and series objects
	ifstream content("contentArrayContents.dat", ios::in);
	content >> noskipws;
	if (content.is_open()) {
		char value[50] = "";
		int counter = 0;
		int placecounter = 0;
		int type = -1;
		Content* newcont = new Content();
		Music * newmus = new Music();
		Film* newfilm = new Film();
		Series* newser = new Series();
		while (content) { // 6 lines per object
			content.getline(value, 50);
			if (counter == 0 && value != "NULL") {
				if (value == "Music") {
					type = 0;
				}
				if (value == "Film") {
					type = 1;
				}
				if (value == "Series") {
					type = 2;
				}
			}
			if (counter == 1 && value != "NULL") {
				newcont->setTitle(value);
			}
			else if (counter == 2 && value != "NULL") {
				newcont->setGenre(value);
			}
			else if (counter == 3 && value != "NULL") {
				int price = atoi(value);
				newcont->setPrice(price);
			}
			else if (counter == 4 && value != "NULL") {
				newcont->setProducer(value);
			}
			else if (counter == 5 && value != "NULL") {
				int year = atoi(value);
				newcont->setYear(year);
			}
			else if (counter == 5 && value != "NULL" && type == 0) {
				newmus = dynamic_cast<Music*>(newcont);
				newmus->setAlbum(value);
			}
			else if (counter == 5 && value != "NULL" && type == 1) {
				newfilm = dynamic_cast<Film*>(newcont);
				newfilm->setDescription(value);
			}
			else if (counter == 5 && value != "NULL" && type == 2) {
				newser = dynamic_cast<Series*>(newcont);
				int val = atoi(value);
				newser->setAirdate(val);
			}
			else if (counter > 5 && counter <= 56 && type == 0 && value != "NULL"){
				newmus->addFormat(value);
			}
			else if (counter > 5 && counter <= 56 && type == 1 && value != "NULL") {
				newfilm->addActor(value);
			}
			else if (counter > 5 && counter <= 16 && type == 2 && value != "NULL") {
				newser->addCharacter(value);
			}
			else if (counter == 57 && value != "NULL" && type == 0) {
				newmus->setRemix(value);
			}
			else if (counter == 57 && value != "NULL" && type == 1) {
				int val = atoi(value);
				newfilm->setLength(val);
			}
			else if (counter == 57 && value != "NULL" && type == 2) {
				int val = atoi(value);
				newser->SetSeasons(val);
			}
			else if (counter == 58 && value != "NULL" && type == 0) {
				int val = atoi(value);
				newmus->setLength(val);
				//push into array and reset counter
				thiscompany.addContent(newmus);
				counter = -1;
			}
			else if (counter == 58 && value != "NULL" && type == 1) {
				newfilm->setQuality(value);
				//push into array and reset counter
				thiscompany.addContent(newfilm);
				counter = -1;
			}
			else if (counter == 58 && value != "NULL" && type == 2) {
				int val = atoi(value);
				newser->setEpisodes(val);
				//push into array and reset counter
				thiscompany.addContent(newser);
				counter = -1;
			}
			counter++;
		}
		delete newcont;
		delete newfilm;
		delete newmus;
		delete newser;
	}
	content.close();
	*/
	//restore _subscriptions
	//_subscriptions consists of subscriptionArrayContents.dat

	//restore _customers
	//content needs to be initialized for this to work
	//subscribtions needs to be initialized for this to work
	//_customers consists of NormalCustomerArrayContents.dat and PayingCustomerArrayContents.dat
	//NormalCustomerArrayContents.dat FORMAT:name, address, billingaccount, paying status, 100* history object
	//PayingCustomerArrayContents.dat FORMAT: name, address, billingaccount, paying status, subscription name, subscription length, 100* history object, 100* download object
	ifstream normalCustomers("NormalCustomerArrayContents.dat", ios::in); //104 lines per customer
	normalCustomers >> noskipws;
	if (normalCustomers.is_open()) {
		char value[50] = "";
		int counter = 0;
		Customer* newcust = new Customer();
		while (normalCustomers) {
			normalCustomers.getline(value, 50);
			if (counter == 0 && value != "NULL") {
				newcust->setName(value);
			}
			else if (counter == 1 && value != "NULL") {
				newcust->setAddress(value);
			}
			else if (counter == 2 && value != "NULL") {
				newcust->setBillingaccount(value);
			}
			else if (counter == 3 && value != "NULL") {
				newcust->setPaying(false);
			}
			else if (counter >= 4 && counter < 104 && value != "NULL") {
				if (value != "NULL") {
					//find content object with the name included in this file
					//add it to newcust's history array
				}
			}
			else if (counter == 104 && value != "NULL") { //line 104 is the beginning of the 2nd object so we set the name of the next object and the counter to 0 since it gets incremented immediatly
				newcust = new Customer();
				newcust->setName(value);
				counter = 0;
				
			}
			if (counter == 103) { //each 103rd line is the last line of each object so we add it to the array
				thiscompany.addCustomer(newcust);
			}
			
			counter++;
		}
		delete newcust;
	}
	normalCustomers.close();

	//restore _invoices
	//consists of invoicesArrayContents.dat
}

inline bool exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void checkPerson() {
	int choice = -1;
	cout << "Are you the owner or an employee? \n 1. Owner \n any other number. Employee \n";
	cin >> choice;
	cin.ignore();
	if (choice == 1) {
		isOwner = true;
	}
	else {
		isOwner = false;
	}
}

void doFunction(int choice) {
	switch (choice) {
	default:
		cout << "invalid choice<<please try again" << endl;
		break;

	case 1: // make new customer
		createCustomer();
		break;

	case 2: //change a certain customer
		editCustomer();
		break;

	case 3: //delete customer
		deleteCustomer();
		break;

	case 4: //Create a new Invoice
		addInvoice();
		break;

	case 5: //search 1 Invoice
		findAndPrintInvoice();
		break;

	case 6: //search 1 customer
		findAndPrintCustomer();
		break;

	case 7: //Search content
		findAndPrintContent();
		break;

	case 8: //add content
		addContent();
		break;

	case 9: //delete content
		deleteContent();
		break;

	case 10: //add subscription
		addSubscription();
		break;
	
	case 11: //change subscription
		editSubscription();
		break;
		
	case 12: //delete subscription
		deleteSubscription();
		break;
		
	case 13: //search subscription
		findAndPrintSubscription();
		break;

	case 14: //change content
		editContent();
		break;
		
	}
}

void editContent() {
	char name[50] = "";
	cout << "Please enter the name of the content you would like to edit" << endl;
	cin.getline(name, 50);
	if (strcmp(name, "") != 0) {
		bool found = false;
		int index = -1;
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getContent(i) != nullptr) {
				if (strcmp(thiscompany.getContent(i)->getTitle(), name) == 0) {
					index = i;
					found = true;
				}
			}
		}
		//check which type of content we want to edit
		if (found) {
			int type = -1;
			Content * old = thiscompany.getContent(index);
			if (instanceof<Music>(old)) {
				Music* newmusic = dynamic_cast<Music*>(old);
				editMusic(newmusic);
				thiscompany.addContent(newmusic);
			}
			else if (instanceof<Film>(old)) {
				Film* newfilm = dynamic_cast<Film*>(old);
				editFilm(newfilm);
				thiscompany.addContent(newfilm);
			}
			else if (instanceof<Series>(old)) {
				Series* newseries = dynamic_cast<Series*>(old);
				editSeries(newseries);
				thiscompany.addContent(newseries);
			}
			
		}
	}
	else {
		cout << "INVALID PARAMETER PLEASE TRY AGAIN" << endl;
	}
}
void editMusic(Music* newmusic) {
	//select parameter to edit
	int choice = -1;
	cout << "select parameter to edit" << endl;
	cout << "1. Title \n 2. Producer \n 3. Year \n 4. Genre \n 5. Price \n 6. Length \n 7.Formats \n 8. Remix \n 9.Album \n all else: quit" << endl;
	cin >> choice;
	cin.ignore();
	switch (choice) {
		default:
			cout << "INVALID PARAMETER PLEASE TRY AGAIN" << endl;
			break;

		case 1: { //change title
			char title[50] = "";
			cout << "please enter the new title" << endl;
			cin.get(title,50);
			if (strcmp(title, "") != 0) {
				newmusic->setTitle(title);
			}
			break;
		}

		case 2: { //change producer
			char producer[50] = "";
			cout << "please enter the new producer" << endl;
			cin.get(producer,50);
			if (strcmp(producer, "") != 0) {
				newmusic->setProducer(producer);
			}
			break;
		}

		case 3: { //change year
			int year = -1;
			cout << "please enter the new year" << endl;
			cin >> year;
			cin.ignore();
			if (year >= 101011950) {
				newmusic->setYear(year);
			}
			break;
		}

		case 4: { //change genre
			char genre[50] = "";
			cout << "please enter the new genre" << endl;
			cin.get(genre,50);
			if (strcmp(genre, "") != 0) {
				newmusic->setGenre(genre);
			}
			break;
		}

		case 5: { //change price
			int price = -1;
			cout << "please enter the new price" << endl;
			cin >> price;
			cin.ignore();
			if (price >=  0) {
				newmusic->setPrice(price);
			}
			break;
		}

		case 6: { //change length
			int length = -1;
			cout << "please enter the new length" << endl;
			cin >> length;
			cin.ignore();
			if (length >= 0) {
				newmusic->setPrice(length);
			}
			break;
		}
	
		case 7: {//edit the formats
			char formats[50][50];
			for (int i = 0; i < 50; i++) {
				for (int j = 0; j < 50; j++) {
					formats[i][j] = NULL;
				}
			}
			cout << "please enter all the updated formats" << endl;
			bool quit = false;
			for (int i = 0; i < 50 && !quit; i++) {
				char format[50] = "";
				cout << "please enter the " << i - 1 << "th format" << endl;
				cin.get(format,50);
				if (strcmp(format, "") != 0) {
					strcpy_s(formats[i], format);
				}
				else if (strcmp(format, "quit") == 0) {
					quit = true;
				}
			}
			newmusic->setFormat(formats);
			break;
		}

		case 8: { //change remix
			char remix[50] = "";
			cout << "please enter the new remix" << endl;
			cin.get(remix,50);
			if (strcmp(remix, "") != 0) {
				newmusic->setRemix(remix);
			}
			break;
		}

		case 9:{ //change album
			char album[50] = "";
			cout << "please enter the new album" << endl;
			cin.get(album,50);
			if (strcmp(album, "") != 0) {
				newmusic->setAlbum(album);
			}
			break;
		}
	}
}

void editFilm(Film* newFilm) {
	//select parameter to edit
	int choice = -1;
	cout << "select parameter to edit" << endl;
	cout << "1. Title \n 2. Producer \n 3. Year \n 4. Genre \n 5. Price \n 6. Length \n 7. Actors \n 8. Quality \n 9. Description \n all else: quit" << endl;
	cin >> choice;
	cin.ignore();
	switch (choice) {
		default: 
			cout << "INVALID PARAMETER PLEASE TRY AGAIN" << endl;
			break;

		case 1: { //change title
			char title[50] = "";
			cout << "please enter the new title" << endl;
			cin.get(title,50);
			if (strcmp(title, "") != 0) {
				newFilm->setTitle(title);
			}
			break;
		}

		case 2: { //change producer
			char producer[50] = "";
			cout << "please enter the new producer" << endl;
			cin.get(producer,50);
			if (strcmp(producer, "") != 0) {
				newFilm->setProducer(producer);
			}
			break;
		}

		case 3: { //change year
			int year = -1;
			cout << "please enter the new year" << endl;
			cin >> year;
			cin.ignore();
			if (year >= 101011950) {
				newFilm->setYear(year);
			}
			break;
		}

		case 4: { //change genre
			char genre[50] = "";
			cout << "please enter the new genre" << endl;
			cin.get(genre,50);
			if (strcmp(genre, "") != 0) {
				newFilm->setGenre(genre);
			}
			break;
		}

		case 5: { //change price
			int price = -1;
			cout << "please enter the new price" << endl;
			cin >> price;
			cin.ignore();
			if (price >= 0) {
				newFilm->setPrice(price);
			}
			break;
		}

		case 6: { //change length
			int length = -1;
			cout << "please enter the new length" << endl;
			cin >> length;
			cin.ignore();
			if (length >= 0) {
				newFilm->setPrice(length);
			}
			break;
		}

		case 7: {//edit the actors
			char actors[50][50];
			for (int i = 0; i < 50; i++) {
				for (int j = 0; j < 50; j++) {
					actors[i][j] = NULL;
				}
			}
			cout << "please enter all the updated actors" << endl;
			bool quit = false;
			for (int i = 0; i < 50 && !quit; i++) {
				char actor[50] = "";
				cout << "please enter the " << i - 1 << "th actor" << endl;
				cin.getline(actor,50);
				if (strcmp(actor, "") != 0) {
					strcpy_s(actors[i], actor);
				}
				else if (strcmp(actor, "quit") == 0) {
					quit = true;
				}
			}
			newFilm->setActors(actors);
			break;
		}

		case 8: { //change quality
			char quality[50] = "";
			cout << "please enter the new quality" << endl;
			cin.getline(quality,50);
			if (strcmp(quality, "") != 0) {
				newFilm->setQuality(quality);
			}
			break;
		}

		case 9: { //change description
			char description[50] = "";
			cout << "please enter the new description" << endl;
			cin.getline(description,50);
			if (strcmp(description, "") != 0) {
				newFilm->setDescription(description);
			}
			break;
		}
	}
}

void editSeries(Series* newSeries) {
	//select parameter to edit
	int choice = -1;
	cout << "select parameter to edit" << endl;
	cout << "1. Title \n 2. Producer \n 3. Year \n 4. Genre \n 5. Price \n 6. Seasons \n 7. Characters \n 8. Episodes \n 9.Airdate \n all else: quit" << endl;
	cin >> choice;
	cin.ignore();
	switch (choice) {
		default: 
			cout << "INVALID PARAMETER PLEASE TRY AGAIN" << endl;
			break;

		case 1: { //change title
			char title[50] = "";
			cout << "please enter the new title" << endl;
			cin.getline(title,50);
			if (strcmp(title, "") != 0) {
				newSeries->setTitle(title);
			}
			break;
		}

		case 2: { //change producer
			char producer[50] = "";
			cout << "please enter the new producer" << endl;
			cin.getline(producer,50);
			if (strcmp(producer, "") != 0) {
				newSeries->setProducer(producer);
			}
			break;
		}

		case 3: { //change year
			int year = -1;
			cout << "please enter the new year" << endl;
			cin >> year;
			cin.ignore();
			if (year >= 101011950) {
				newSeries->setYear(year);
			}
			break;
		}

		case 4: { //change genre
			char genre[50] = "";
			cout << "please enter the new genre" << endl;
			cin.getline(genre,50);
			if (strcmp(genre, "") != 0) {
				newSeries->setGenre(genre);
			}
			break;
		}

		case 5: { //change price
			int price = -1;
			cout << "please enter the new price" << endl;
			cin >> price;
			cin.ignore();
			if (price >= 0) {
				newSeries->setPrice(price);
			}
			break;
		}

		case 6: { //change seasons
			int seasons = -1;
			cout << "please enter the new seasons" << endl;
			cin >> seasons;
			cin.ignore();
			if (seasons >= 0) {
				newSeries->SetSeasons(seasons);
			}
			break;
		}

		case 7: {//edit the characters
			char characters[10][50];
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 50; j++) {
					characters[i][j] = NULL;
				}
			}
			cout << "please enter all the updated characters" << endl;
			bool quit = false;
			for (int i = 0; i < 10 && !quit; i++) {
				char character[50] = "";
				cout << "please enter the " << i << "th character" << endl;
				cin.getline(character,50);
				if (strcmp(character, "") != 0) {
					strcpy_s(characters[i], character);
				}
				else if (strcmp(character, "quit") == 0) {
					quit = true;
				}
			}
			newSeries->setCharacters(characters);
			break;
		}

		case 8: { //change episodes
			int episodes = -1;
			cout << "please enter the new episodes" << endl;
			cin >> episodes;
			cin.ignore();
			if (episodes > 0) {
				newSeries->setEpisodes(episodes);
			}
			break;
		}

		case 9: { //change airdate
			int airdate = -1;
			cout << "please enter the new airdate" << endl;
			cin >> airdate;
			cin.ignore();
			if (airdate >= 101011950) {
				newSeries->setAirdate(airdate);
			}
			break;
		}
	}
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

void editSubscription() {
	char name[50] = "";
	cout << "Please enter the name of the subscription for identification" << endl;
	cin.getline(name,50);
	if (strcmp(name, "") != 0) {
		bool found = false;
		int place = -1; //for insertion into the same place
		Subscription * toEdit = new Subscription();
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getSubscriptions(i) != nullptr) {
				if (strcmp(thiscompany.getSubscriptions(i)->getName(), name) == 0) {
					found = true;
					toEdit = thiscompany.getSubscriptions(i);
					place = i;
				}
			}
		}

		if (found) {
			//SELECT VALUE TO EDIT 
			int choice = -1;
			cout << " 0. Quit \n 1. Edit Name \n 2. Edit price \n 3. Edit songs \n 4. Edit films \n 5. Edit series \n";
			cin >> choice;
			cin.ignore();
			char name[50] = "";
			int price = -1;
			int songs = -1;
			int films = -1;
			int series = -1;
			switch (choice) {
			default: break;
			case 1: cout << "Please enter the new Name \n";
				cin.getline(name,50);
				toEdit->setName(name);
				break;

			case 2: cout << "Please enter the new price \n";
				cin >> price;
				cin.ignore();
				toEdit->setPrice(price);
				break;

			case 3: cout << "Please enter the new songs \n";
				cin >> songs;
				cin.ignore();
				toEdit->setSongs(songs);
				break;

			case 4: cout << "Please enter the new Films \n";
				cin >> films;
				cin.ignore();
				toEdit->setMovies(films);
				break;

			case 5: cout << "Please enter the new Series \n";
				cin >> series;
				cin.ignore();
				toEdit->setSerie(series);
				break;
			}
			//insert the edited object back into place
			thiscompany.setSubscriptionAtPlace(toEdit, place);
		}
	}
	else {
		cout << "INVALID PARAMETER PLEASE TRY AGAIN" << endl;
	}
}


void findAndPrintSubscription() {
	char name[50] = "";
	Subscription* ret = new Subscription();
	cout << "Please give the name of the Subscription" << endl;
	cin.getline(name,50);
	if (strcmp(name, "") != 0) {
		bool found = false;
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getSubscriptions(i) != nullptr) {
				if (thiscompany.getSubscriptions(i)->getName() == name) {
					found = true;
					ret = thiscompany.getSubscriptions(i);
				}
			}
		}
		//DISPLAY ret
		if (found) {
			cout << ret->getName() << endl << ret->getPrice() << endl << ret->getMovies() << endl << ret->getSerie() << endl << ret->getSongs() << endl << ret->getDownloads() << endl;
		}
		else {
			cout << "SUBSCRIPTION NOT FOUND" << endl;
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
		delete ret;
	}
}

void deleteSubscription() {
	char name[50] = "";
	cout << "Please give the name of the subscription" << endl;
	cin.getline(name,50);
	if (strcmp(name,"") != 0) {
		int index = -1;
		bool found = false;

		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getSubscriptions(i) != nullptr) {
				if (strcmp(thiscompany.getSubscriptions(i)->getName(), name) == 0) {
					index = i;
					found = true;
				}
			}
		}
		if (found) {
			thiscompany.setSubscriptionAtPlace(nullptr, index);
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
	}
}

void addSubscription() {
	char name[50] = "";
	int price = -1;
	int songs = -1;
	int movies = -1;
	int series = -1;
	int downloads = -1;

	cout << "Please provide the name for the subscription" << endl;
	cin.getline(name, 50);
	cout << "please enter the price of the subscription" << endl;
	cin >> price;
	cin.ignore();
	cout << "please enter the amount of songs in the subscription" << endl;
	cin >> songs;
	cin.ignore();
	cout << "please enter the amount of movies in the subscription" << endl;
	cin >> movies;
	cin.ignore();
	cout << "please enter the amount of series in the subscription" << endl;
	cin >> series;
	cin.ignore();
	cout << "please enter the amount of downloads in the subscription" << endl;
	cin >> downloads;
	cin.ignore();

	if ((strcmp(name, "") != 0 && price > -1 && songs > -1 && movies > -1 && series > -1 && downloads > -1)) {
		int index = -1;
		bool found = false;
		for (int i = 0; i < 1000 && !found; i++) {
			if (nullptr == thiscompany.getSubscriptions(i)) {
				found = true;
				index = i;
			}
		}

		if (index > -1) {
			Subscription * toadd = new Subscription(name, price, songs, movies, series, downloads);
			thiscompany.setSubscriptionAtPlace(toadd, index);
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
	}
}

void deleteContent() {
	int index = -1;
	char name[50] = "";
	cout << "please give the title of the content" << endl;
	cin.getline(name, 50);
	bool found = false;
	if (strcmp(name, "") != 0) {
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getContent(i) != nullptr) {
				if (strcmp(thiscompany.getContent(i)->getTitle(), name) == 0) {
					found = true;
					index = i;
				}
			}
		}
		if (index != -1) {
			delete thiscompany.getContent(index);
			thiscompany.setContentAtPlace(nullptr, index);
		}
		else {
			cout << "NOT FOUND" << endl;
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
	}
}

void addContent() {
	//create the newcontent object
	cout << "what type of content would you like to add?" << endl;
	int choice = 0;
	cin >> choice;
	cin.ignore();
	if (choice >= 1 && choice <= 3) {
		Content * newcontent = make_Content(choice);

		char genre[50];
		char producer[50];
		char title[50];
		int price;
		int year;

		cout << "Genre?" << endl;
		cin.getline(genre,50);
		cout << "Price?" << endl;
		cin >> price;
		cin.ignore();
		cout << "Producer?" << endl;
		cin.getline(producer, 50);
		cout << "Title?" << endl;
		cin.getline(title, 50);
		cout << "Year?" << endl;
		cin >> year;
		cin.ignore();
		if (strcmp(genre, "") != 0 && price >= 0 && strcmp(producer, "") != 0 && strcmp(title, "") != 0 && year >= 1950) {
			newcontent->setGenre(genre);
			newcontent->setPrice(price);
			newcontent->setProducer(producer);
			newcontent->setTitle(title);
			newcontent->setYear(year);

			switch (choice) {
			case 1: { // the { serves as a scope declaration so that we can declare variables inside the switch case statement
				Music * newmusic = dynamic_cast <Music *>(newcontent);
				int length = -1;
				char formats[50][50];
				char remix[50] = "";
				char album[50] = "";
				int amountFormats = -1;

				for (int i = 0; i < 50; i++) {
					for (int j = 0; j < 50; j++) {
						formats[i][j] = NULL;
					}
				}

				cout << "Length?" << endl;
				cin >> length;
				cin.ignore();
				cout << "please give the title of the album of this song" << endl;
				cin.getline(album, 50);
				cout << "please give the remix of this song" << endl;
				cin.getline(remix, 50);
				cout << "How many formats do we offer of this song?" << endl;
				cin >> amountFormats;
				cin.ignore();

				if (amountFormats <= 0 || length <= 0 || strcmp(album, "") == 0 || strcmp(remix, "") == 0) {
					cout << "detected invalid parameters, please try again" << endl;
					delete newmusic;
					break;
				}
				else {
					
					for (int i = 0; i < amountFormats; i++) {
						char format[50] = "";
						//cout << "please give the " << i + 1 << "th format" << endl;
						cout << "How many formats do we offer of this song?" << endl;
						cin.getline(format, 50);
						strcpy_s(formats[i], format);
					}
					newmusic->setRemix(remix);
					newmusic->setAlbum(album);
					newmusic->setLength(length);
					newmusic->setFormat(formats);
					thiscompany.addContent(newmusic);
				}

				break;
			}
			
			case 2: { //create film
				Film * newfilm = dynamic_cast <Film *>(newcontent);
				int length = -1;
				char actors[50][50];
				char quality[50] = "";
				char description[50] = "";
				int amountActors = -1;

				for (int i = 0; i < 50; i++) {
					for (int j = 0; j < 50; j++) {
						actors[i][j] = NULL;
					}
				}

				cout << "please enter the length of the film" << endl;
				cin >> length;
				cin.ignore();
				cout << "please enter the quality of the film" << endl;
				cin.getline(quality, 50);
				cout << "please enter the description of the film" << endl;
				cin.getline(description, 50);
				cout << "please enter the amount of actors in the film" << endl;
				cin >> amountActors;
				cin.ignore();

				if (amountActors <= 0 || length <= 0 || strcmp(quality, "") == 0 || strcmp(description, "") == 0) {
					cout << "detected invalid parameters, please try again" << endl;
					delete newfilm;
					break;
				}
				else {
					for (int i = 0; i < amountActors; i++) {
						char actor[50] = "";
						cout << "Please give the name of the " << i+1 << "th actor." << endl;
						cin.getline(actor, 50);
						strcpy_s(actors[i], actor);
					}
					newfilm->setActors(actors);
					newfilm->setDescription(description);
					newfilm->setQuality(quality);
					newfilm->setLength(length);
					thiscompany.addContent(newfilm);
				}

				break;
			}
			case 3: { //create series
				Series * newseries = dynamic_cast <Series *>(newcontent);

				char characters[10][50];
				int seasons = -1;
				int episodes = -1;
				int airdate = -1;
				int amountCharacters = -1;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 50; j++) {
						characters[i][j] = NULL;
					}
				}

				cout << "How many seasons are there?" << endl;
				cin >> seasons;
				cin.ignore();
				cout << "How many episodes per season?" << endl;
				cin >> episodes;
				cin.ignore();
				cout << "When was the first airdate? format: 1DDMMYYYY" << endl;
				cin >> airdate;
				cin.ignore();
				cout << "How many characters are there?" << endl;
				cin >> amountCharacters;
				cin.ignore();

				if (amountCharacters <= 0 || seasons <= 0 || episodes <= 0 || airdate <= 101011950) {
					cout << "detected invalid parameters, please try again" << endl;
					delete newseries;
					break;
				}
				else {
					for (int i = 0; i < amountCharacters; i++) {
						char character[50] = "";
						cout << "Please give the name of the " << i+1 << "th character." << endl;
						cin.getline(character, 50);
						strcpy_s(characters[i], character);
					}
					newseries->setCharacters(characters);
					newseries->setAirdate(airdate);
					newseries->setEpisodes(episodes);
					newseries->SetSeasons(seasons);
					thiscompany.addContent(newseries);
				}

				break;
			}
			default: {
				cout << "invalid choice!" << endl << "Please try again." << endl;
				delete newcontent;
				break;
			}
			}
		}
	else {
		cout << "INVALID PARAMETERS, PLEASE TRY AGAIN" << endl;
		delete newcontent;
	}
	}else {
		cout << "invalid choice, please try again" << endl;
	}
}

void findAndPrintContent() {
	Content * ret = new Content();
	char name[50] = "";
	cout << "please give the title of the content" << endl;
	cin.getline(name, 50);
	if (strcmp(name, "") != 0) {
		bool found = false;
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getContent(i) != nullptr) {
				if (strcmp(thiscompany.getContent(i)->getTitle(), name) == 0) {
					found = true;
					ret = thiscompany.getContent(i);
				}
			}
		}
		if (found) {
			cout << ret->getTitle() << endl << ret->getPrice() << endl << ret->getGenre() << endl << ret->getProducer() << endl << ret->getYear() << endl;
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
		delete ret;
	}
}
void findAndPrintCustomer() {
	Customer * ret = make_Customer(1);
	char mail[50] = "";
	cout << "please give the mailaddress of the customer" << endl;
	cin.getline(mail, 50);
	if (strcmp(mail, "") != 0) {
		bool found = false;
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getCustomers(i) != nullptr) {
				if (strcmp(thiscompany.getCustomers(i)->getMail(), mail) == 0) {
					found = true;
					ret = thiscompany.getCustomers(i);
				}
			}
		}
		if (found) {
			cout << ret->getName() << " " << ret->getAddress() << " " << ret->getBillingaccount() << " " << ret->getMail() << " " << ret->getPaying() << endl;
		}
		else {
			cout << "Customer not found" << endl;
			delete ret;
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
		delete ret;
	}
}

void findAndPrintInvoice() {
	int id = -1;
	Invoice * ret;
	char idstring[50] = "";
	cout << "Please give the ID of the invoice" << endl;
	cin.getline(idstring,50);
	id = atoi(idstring);
	if (id >= 0 && strcmp(idstring, "") != 0) {
		bool found = false;
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getInvoice(i) != nullptr) {
				if (thiscompany.getInvoice(i)->getNumber() == id) {
					found = true;
					ret = thiscompany.getInvoice(i);
				}
			}
		}
		//DISPLAY ret
		if (found) {

			cout << ret->getDate() << endl << ret->getForCustomer()->getName() << endl << ret->getNumber() << endl << ret->getSubscription()->getName() << endl << ret->getTotalPrice() << endl;
			int counter = 0;
			bool end = false;
			while (!end) {
				if (ret->getForContent()[counter] == nullptr) {
					end = true;
				}
				else {
					cout << ret->getForContent()[counter]->getTitle() << endl;
					counter++;
				}
			}
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
	}
}


void firstStartup() {
	char name[50] = "";
	char address[50] = "";
	char VAT[50] = "";
	cout << "Please give the name for the company.\n";
	cin.getline(name, 50);
	cout << "Please give the address of the company.\n";
	cin.getline(address, 50);
	cout << "Please give the VAT number of the company.\n";
	cin.getline(VAT, 50);
	thiscompany.setName(name);
	thiscompany.setAddress(address);
	thiscompany.setVAT(VAT);
}

//FACTORY METHOD
Content* make_Content(int choice) 
{
	switch(choice){
		case 1: return new Music();
			
		case 2: return new Film();

		case 3: return new Series();	
	}
	return new Music(); //gets rid of the warning: not every control path returns a value

}

//FACTORY METHOD
Customer * make_Customer(int choice)
{
	switch (choice) {
		case 1: return new Customer();

		case 2: return new Paying();

	}
	return new Customer(); //gets rid of the warning: not every control path returns a value
}

void createCustomer() {
	int choice = -1;
	cout << "Type of customer?"<<endl<<" 1. Normal Customer" <<endl<<" 2. Paying Customer" << endl;
	cin >> choice;
	cin.ignore();
	cout << endl;
	if (choice >= 1 && choice <= 2) {
		Customer* newCust = nullptr;
		newCust = make_Customer(choice);
		switch (choice) {
			case 1: { //create normal customer
				char name[50] = "";
				char address[50] = "";
				char mail[50] = "";
				char billingaccount[50] = "";

				cout << "please give the name"<<endl;
				cin.getline(name, 50);
				cout << "please give the address"<<endl;
				cin.getline(address, 50);
				cout << "please give the mailaddress"<<endl;
				cin.getline(mail, 50);
				cout << "please give the BA"<<endl;
				cin.getline(billingaccount, 50);
			
				if (strcmp(name, "") != 0 && strcmp(address, "") != 0 && strcmp(mail, "") != 0 && strcmp(billingaccount, "") != 0) {

					newCust->setName(name);
					newCust->setAddress(address);
					newCust->setMail(mail);
					newCust->setBillingaccount(billingaccount);
					newCust->setPaying(false);
					thiscompany.addCustomer(newCust);
				
				}
				else {
					cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
				}
				break;
			}
			case 2: {
				Paying* newCust = new Paying();
				newCust = dynamic_cast<Paying*>(newCust);

				char name[50] = "";
				char address[50] = "";
				char mail[50] = "";
				char billingaccount[50] = "";
				int length = -1;
				Content* downloads[100];
				Subscription* sub = new Subscription();

				//we assume that the new customer does not have any downloads yet
				for (int i = 0; i < 100; i++) {
					downloads[i] = nullptr;
				}

				cout << "please give the name"<<endl;
				cin.getline(name, 50);
				cout << "please give the address"<<endl;
				cin.getline(address, 50);
				cout << "please give the mailaddress"<<endl;
				cin.getline(mail, 50);
				cout << "please give the BA"<<endl;
				cin.getline(billingaccount, 50);
				cout << "please give the length"<<endl;
				cin >> length;
				cin.ignore();
			
				//search subscription
				char subname[50] = "";
				cout << "please give the subscriptionname" << endl;
				cin.getline(subname, 50);
				bool found = false;
				int index = -1;
				for (int i = 0; i < 1000 && !found; i++) {
					if (thiscompany.getSubscriptions(i) != nullptr) {
						if (strcmp(thiscompany.getSubscriptions(i)->getName(), subname) == 0) {
							found = true;
							index = i;
						}
					}
				}

				sub = thiscompany.getSubscriptions(index);

				if (strcmp(name, "") != 0 && strcmp(address, "") != 0 && strcmp(mail, "") != 0 && strcmp(billingaccount, "") != 0 && length > 0 && found) {
					newCust->setName(name);
					newCust->setAddress(address);
					newCust->setMail(mail);
					newCust->setBillingaccount(billingaccount);
					newCust->setLength(length);
					newCust->setSubscriptiontype(sub);
					newCust->setDownloads(downloads);
					newCust->setPaying(true);
					thiscompany.addCustomer(newCust);
				}
				else {
					cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
					delete newCust;
				}
				break;
			}
		}
		//cout << "DEBUG:" << (newCust) << endl;
	}
	else {
		cout << "Invalid choice, please try again" << endl;
	}
}

void editCustomer() {
	char mail[50] = "";
	cout << "Please enter the customer Email for identification"<<endl;
	cin.getline(mail,50);
	if (strcmp(mail, "") != 0) {
		bool found = false;
		int place = -1; //for insertion into the same place
		Customer * toEdit = new Customer();
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getCustomers(i) != nullptr) {
				if (strcmp(thiscompany.getCustomers(i)->getMail(), mail) == 0) {
					found = true;
					toEdit = thiscompany.getCustomers(i);
					place = i;
				}
			}

		}
		if (found) {
			//SELECT VALUE TO EDIT 
			int choice2 = -1;
			cout << " 0. Quit \n 1. Edit Name \n 2. Edit Address \n 3. Edit Billingaccount \n 4. Edit Mail \n 5. Edit Paying \n";
			cin >> choice2;
			cin.ignore();
			char name[50] = "";
			char address[50] = "";
			char billingaccount[50] = "";
			char mail2[50] = "";
			bool newstatus = false;
			switch (choice2) {
			default: break;
			case 1: cout << "Please enter the new Name \n";
				cin.getline(name, 50);
				toEdit->setName(name);
				break;

			case 2: cout << "Please enter the new Address \n";
				cin.getline(address, 50);
				toEdit->setAddress(address);
				break;

			case 3: cout << "Please enter the new Billingaccount \n";
				cin.getline(billingaccount, 50);
				toEdit->setBillingaccount(billingaccount);
				break;

			case 4: cout << "Please enter the new Mail \n";
				cin.getline(mail2, 50);
				toEdit->setMail(mail2);
				break;

			case 5: cout << "Please enter the new Paying status \n";
				cin >> newstatus;
				cin.ignore();
				toEdit->setPaying(newstatus);
				break;
			}
			//insert the edited object back into place
			thiscompany.setCustomerAtPlace(toEdit, place);
		}
		else {
			cout << "Customer not found, please try again" << endl;
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
	}
}

void deleteCustomer() {
	char mail[50] = "";
	cout << "Please enter the customer Email for identification" << endl;
	cin.getline(mail, 50);
	if (strcmp(mail, "") != 0) {
		bool found = false;
		int place = -1; //for insertion into the same place
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getCustomers(i) != nullptr) {
				if (strcmp(thiscompany.getCustomers(i)->getMail(), mail) == 0) {
					found = true;
					place = i;
				}
			}
		}
		//now we will move each element behind of INT place one place to the front
		for (int i = place; i < 1000; i++) {
			thiscompany.setCustomerAtPlace(thiscompany.getCustomers(i + 1), i);
		}
		//place 999 now has an unknown value so we set it to nullptr
		thiscompany.setCustomerAtPlace(nullptr, 999);
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
	}
}

void addInvoice() {
	bool found = false;
	Customer * cust = nullptr;
	char mail[50] = "";
	cout << "Please enter the customer Email for identification"<<endl;
	cin.getline(mail, 50);
	if (strcmp(mail, "") != 0) {
		for (int i = 0; i < 1000 && !found; i++) {
			if (thiscompany.getCustomers(i) != nullptr) {
				if (strcmp(thiscompany.getCustomers(i)->getMail(), mail) == 0) {
					found = true;
					cust = thiscompany.getCustomers(i);
				}
			}
		}
		if (!found) {
			cout << "Customer was not found, stopping this action\n";
			delete cust;
		}
		else {
			int input = -1;
			Content* consumed[50];
			for (int i = 0; i < 50; i++) {
				consumed[i] = nullptr;
			}
			int place = 0;
			do {
				cout << "Please give the title of the consumed content\n";
				char titel[50] = "";
				cin.getline(titel, 50);
				bool found2 = false;
				for (int i = 0; i < 1000 && !found2; i++) {
					if (thiscompany.getContent(i) != nullptr) {
						if (strcmp(thiscompany.getContent(i)->getTitle(), titel) == 0) {
							found2 = true;
							cout << "FOUND" << endl;
							consumed[place] = thiscompany.getContent(i);
							place++;
						}
					}
				}
				if (!found2) {
					cout << "Content was not found, please try again" << endl;
				}
			} while (input >= 0);
			//now we have added all the consumed content to VAR consumed and we can determine the totalprice 
			int totalprice = 0;
			if (!cust->getPaying()) {
				for (int i = 0; i < 50; i++) {
					if (consumed[i] != nullptr)
						totalprice += consumed[i]->getPrice();
				}
			}
			else { //untested
				Paying * pay = dynamic_cast<Paying*>(cust);
				int consumedsongs = 0;
				int consumedfilms = 0;
				int consumedseries = 0;
				for (int i = 0; i < 50; i++) {
					if (consumed[i] != nullptr)
						if (instanceof<Music>(consumed[i])) {
							consumedsongs++;
						}
						else if (instanceof<Series>(consumed[i])) {
							consumedseries++;
						}
						else if (instanceof<Film>(consumed[i])) {
							consumedfilms++;
						}
						else {

						}

						if (consumedsongs > pay->getSubscriptiontype()->getSongs()) {
							totalprice += totalprice += consumed[i]->getPrice();
						}
						else if (consumedfilms > pay->getSubscriptiontype()->getMovies()) {
							totalprice += totalprice += consumed[i]->getPrice();
						}
						else if (consumedseries > pay->getSubscriptiontype()->getSerie()) {
							totalprice += totalprice += consumed[i]->getPrice();
						}
						else {

						}
				}
				totalprice += pay->getSubscriptiontype()->getPrice();
			}
			//now we have the totalprice
			cout << "Please give the date in the format '1DDMMYYYY'" << endl;
			int date = 0;
			cin >> date;
			cin.ignore();
			//DATE HAS BEEN ACQUIRED
			cout << "Please give the ID"<<endl;
			int id = -1;
			cin >> id;
			cin.ignore();
			if (!cust->getPaying()) {
				Invoice * newInv = new Invoice(cust, consumed, date, totalprice, id);
				//add newInv to thiscompany
				thiscompany.addInvoice(newInv);
			}
			else { // untested
				Paying * pay = dynamic_cast<Paying*>(cust);
				Subscription * sub = pay->getSubscriptiontype();
				Invoice * newInv = new Invoice(sub, cust, consumed, date, totalprice, id);
				//add newInv to thiscompany
				thiscompany.addInvoice(newInv);
			}
		}
	}
	else {
		cout << "INVALID PARAMETERS PLEASE TRY AGAIN" << endl;
		delete cust;
	}
}