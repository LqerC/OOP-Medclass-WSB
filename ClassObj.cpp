#include "meds.h"
#include <string>
#include <iostream>  
#include "conio.h"
void enterNewMed(Medicaments& med);
void deleteSomeMed(Medicaments& clse);
void showPrice(Medicaments& clse);
void showPrice(Medicaments& clse, bool isT); // input funkcje.
void precisedInfo(Medicaments& clse);
void changePrice(Medicaments& clse); //zmienic cene dla leku TODO
void showMenu(Medicaments& clse);
int main()
{
	std::cout << "Zrobic liste popularnych lekow na start? Czy stworzyc czysta? \n";
	std::cout << "1 : Leki na start \n";
	std::cout << "kazdy inny przycisk : Czysta\n";
	char temp = '0'; bool isEmpty = false;
	std::cin >> temp;
	std::cin.clear(); 
	std::cin.ignore(32767, '\n');
	if (temp == '1')
	{
		bool isEmpty = true;
		std::cout << "Wybrano gotowa liste\n";
		std::cout << "ENTER wrocic do menu \n"; _getch();
	}
	else
	{
		std::cout << "Wybrano czysta liste\n";
		std::cout << "ENTER wrocic do menu \n"; _getch();
	}
	Medicaments meds(isEmpty);
	bool isCon = true;
	while (isCon)
	{
		showMenu(meds);
		switch (_getch()) //conio_h
		{
		case '1':
			std::cout << "1 : Dodac nowy lek \n";
			enterNewMed(meds);
			break;
		case '2':
			std::cout << "2 : Usunac lek z listy \n";
			deleteSomeMed(meds);
			break;
		case '3':
			std::cout << "3 : Wyswietlic cene dla leku bez refundacji nfz \n";
			showPrice(meds);
			break;
		case '4':
			std::cout << "4 : Wyswietlic cene dla leku z refundacja nfz \n";
			showPrice(meds, true);
			break;
		case '5':
			std::cout << "5 : Wyswietlic maksymalna refundacji nfz \n";
			meds.maksymalnaRefundacji(meds);
			break;
		case'6':
			std::cout << "6 : EXIT \n";
			isCon = false;
			break;
		case '7':
			std::cout << "7 : Zapisz liste \n";
			meds.saveList(meds);
			break;
		case '8':
			std::cout << "8 : Zmien cene \n";
			changePrice(meds);
			break;

		case '9':
			std::cout << "9 : Dodatkowe informacje o leku\n";
			precisedInfo(meds);
			break;
		default:
			std::cout << "Takiej opcji nie istnieje \n";
			std::cout << "ENTER wrocic do menu \n"; _getch();
			break;
		}
	}
}

void enterNewMed(Medicaments& clse)
{
	std::string somemed; double price = -1;
	std::cout << "Prosze wprowadzic nazwe nowego leku np. : \"Streprils_forte\" \n";
	getline(std::cin, somemed);
	std::cout << "Prosze wprowadzic cene dla : " << somemed << "\n";

	std::cin >> price;
	if(price<0)
		std::cout << "UWAGA! Cena ustawiona zostala ujemna cena \n";
	std::cin.clear();
	std::cin.ignore(32767, '\n');
	clse.addNewMed(somemed, price, clse);
	std::cout << "ENTER wrocic do menu \n"; _getch();
}
void deleteSomeMed(Medicaments& clse)
{
	std::string somemed;
	std::cout << "Prosze wprowadzic nazwe leku z listy dla usuniecia :  \n";
	clse.showAllMeds(clse);
	getline(std::cin, somemed);
	clse.deleteMed(clse, somemed);
	std::cout << "ENTER wrocic do menu \n"; _getch();
}
void showPrice(Medicaments& clse)
{
	std::string somemed;
	std::cout << "Prosze wprowadzic nazwe leku dla ktorego pokazac cene :  \n";
	clse.showAllMeds(clse);
	getline(std::cin, somemed);
	clse.cena(clse, somemed);
	std::cout << "ENTER wrocic do menu \n"; _getch();
}
void showPrice(Medicaments& clse, bool isT)
{
	if (isT)
	{
		std::string somemed;
		std::cout << "Prosze wprowadzic nazwe leku dla ktorego pokazac cene :  \n";
		clse.showAllMeds(clse);
		getline(std::cin, somemed);
		clse.cena(clse, somemed, true);
	}
	std::cout << "ENTER wrocic do menu \n"; _getch();
}
void precisedInfo(Medicaments& clse)
{
	std::string somemed;
	std::cout << "Prosze wprowadzic nazwe leku dla ktorego pokazac informacje szczegolne :  \n";
	clse.showAllMeds(clse);
	getline(std::cin, somemed);
	clse.wyswietl(clse, somemed);
	std::cout << "ENTER wrocic do menu \n"; _getch();
}
void changePrice(Medicaments& clse)
{
	std::string somemed; double value = -1;
	std::cout << "Prosze wprowadzic nazwe leku dla ktorego zmienic cene :  \n";
	clse.showAllMeds(clse);
	getline(std::cin, somemed);
	std::cout << "Prosze wprowadzic cene w PLN :  \n";
	std::cin >> value;
	if (value < 0)
		std::cout << "UWAGA! Cena ustawiona zostala ujemna cena \n";
	std::cin.clear();
	std::cin.ignore(32767, '\n');
	clse.changePriceForMed(clse, somemed, value);
	std::cout << "ENTER wrocic do menu \n"; _getch();
}
void showMenu(Medicaments& clse)
{
	system("cls");
	std::cout << "1 : Dodac nowy lek \n";
	std::cout << "2 : Usunac lek z listy \n";
	std::cout << "3 : Wyswietlic cene dla leku bez refundacji nfz \n";
	std::cout << "4 : Wyswietlic cene dla leku z refundacja nfz \n";
	std::cout << "5 : Wyswietlic maksymalna refundacji nfz \n";
	std::cout << "6 : EXIT \n";
	std::cout << "7 : Zapisz liste \n";
	std::cout << "8 : Zmien cene dla leku\n";
	std::cout << "9 : Dodatkowe informacje o leku\n";
	std::cout << "\n\n\n";
	clse.showAllMeds(clse);
}
