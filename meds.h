#ifndef MEDS_H
#define MEDS_H
//#define DEBUG

#include <string> 
#include <map>
#include <iostream>
#include <fstream>
#include "conio.h"
class Medicaments
{
private:

	std::map<std::string, double> medlist = { {"STREPTILS",12},{"Plastry_Novox",3},{"Viltaren_MAX",23} };

	template <typename T>
	double calculateNFZ(T param)
	{
		double NFZ = 0;
		if (param > 10 && param <= 30)
			NFZ = 0.40;
		else if (param > 30 && param <= 70)
			NFZ = 0.30;
		else if (param > 70 && param <= 90)
			NFZ = 0.20;
		else if (param > 90)
			NFZ = 0.05;
		else
			NFZ = 0.50;
		return param * NFZ;
	}
	template <typename T>
	double calculateNFZ(T param,bool is)
	{
		double NFZ = 0;
		if (param > 10 && param <= 30)
			NFZ = 0.40;
		else if (param > 30 && param <= 70)
			NFZ = 0.30;
		else if (param > 70 && param <= 90)
			NFZ = 0.20;
		else if (param > 90)
			NFZ = 0.05;
		else
			NFZ = 0.50;
		return NFZ;
	}
public:
	Medicaments(bool isEmpty = false)
	{
		if(isEmpty)
			medlist = {};
	}
#ifdef DEBUG
	~Medicaments()
	{
		std::cout << "destructor_check";
	}
#endif
	Medicaments operator = (Medicaments clse) //TODO
	{
		this->medlist = clse.medlist;
		return *this;
	}
	Medicaments operator + (Medicaments clse) //TODO
	{
		for (std::map<std::string, double>::iterator it = clse.medlist.begin(); it != clse.medlist.end(); it++)
		{
			if (this->medlist.find(it->first) == this->medlist.end())
				this->medlist.insert(std::pair<std::string, double>(it->first, it->second));
			else
				std::cout << "Lek " << it->first << " juz istnieje w tej liscie";
		}
		return *this;
	}
	void maksymalnaRefundacji(Medicaments& clse)
	{
		double rMax = NULL; std::string temp;
		for (std::map<std::string, double>::iterator it = clse.medlist.begin(); it != clse.medlist.end(); it++)
		{
			if (calculateNFZ(it->second) > rMax)
			{
				rMax = calculateNFZ(it->second);
				temp = it->first;
			}
		}
		std::cout << "Maksymalna refundacji z listy wynosi : " << rMax << " PLN dla leku o nazwie : " << temp << "\n";
		std::cout << "\n ENTER wrocic do menu \n"; _getch();
	}
	void wyswietl(Medicaments& clse, std::string param)
	{
		if (clse.medlist.find(param) == clse.medlist.end())
			std::cout << "Danego Leku nie istnieje w liscie \n";
		else
			std::cout << "Szczegolne informacje o leku : " << param << "  Cena :\t" << clse.medlist[param] << "  Procent refundacji NFZ :\t" << calculateNFZ(clse.medlist[param],true) * 100 <<" %\n" ;

	}
	void addNewMed(std::string& lek, double value, Medicaments& clse)
	{
		if (clse.medlist.find(lek) == clse.medlist.end())
		{
			clse.medlist.insert(std::pair<std::string, double>(lek, value));
			std::cout << "Lek o nazwie " << lek << " zostal dodany! \n";
		}
		else
			std::cout << "Lek o nazwie " << lek << " juz jest w liscie! \n";
		//return clse;
	}
	void showAllMeds(Medicaments& clse)
	{
		for (std::map<std::string, double>::iterator it = clse.medlist.begin(); it != clse.medlist.end(); it++)
		{
			std::cout << "Nazwa Leku  : \"" << it->first << "\"\t Cena Leku : " << it->second << " PLN\n";
		}
	}
	void changePriceForMed(Medicaments& clse, std::string lek, double value)
	{
		if (clse.medlist.find(lek) == clse.medlist.end())
		{
			std::cout << "Danego Leku nie istnieje w liscie \n";
		}
		else
		{
			clse.medlist[lek] = value;
			std::cout << "Lek o nazwie " << lek << " Kosztuje : \n" << value << std::endl;
		}

	}
	void deleteMed(Medicaments& clse, std::string lek)
	{
		if (clse.medlist.find(lek) == clse.medlist.end())
		{
			std::cout << "Danego Leku nie istnieje w liscie \n";
		}
		else
		{
			clse.medlist.erase(clse.medlist.find(lek));
			std::cout << "Lek o nazwie "<< lek << " zostal usuniety! \n" << std::endl;
		}
	}
	void cena(Medicaments& clse,std::string lek, bool ubiezpieczony = false)
	{
		if (clse.medlist.find(lek) == clse.medlist.end())
			std::cout << " Danego Leku nie istnieje w liscie \n";
		else if (ubiezpieczony)
			std::cout << "Cena Leku : " << lek << "\t" << clse.medlist[lek] - calculateNFZ(clse.medlist[lek]) << " PLN\n"; 
		else
			std::cout << "Cena Leku : " << lek << "\t" << clse.medlist[lek] << " PLN\n"; 
	}
	void saveList(Medicaments clse)
	{	
		std::string listname;
		std::cout << "Wybierz nazwe dla pliku z lista lekow ... \n";
		std::cin >> listname;
		listname += ".txt";
		std::fstream out;
		out.open(listname, std::fstream::app);
		if (!out.is_open())
			std::cout << "Wystapil blad... \n";
		else
		{
			for (auto it : clse.medlist)
			{
				out << it.first << "\t: " << it.second << " PLN"<< '\n';
			}
			std::cout << "Lista zostala zapisana w folderze programu jako \"txt\" plik o nazwie :   " << listname;
		}
		out.close();
		std::cout << "\n ENTER wrocic do menu \n"; _getch();
	}
	/*void loadList(Medicaments clse)
	{
		std::string listname;
		std::cout << " \"dodaj liste\"...Wybierz nazwe pliku z lista ... \n";
		std::cin >> listname;
		listname += ".txt";
		std::fstream in;
		in.open(listname);
		if (!in.is_open())
			std::cout << "Wystapil blad... \n";
		else
		{
			in.read((char*)&clse, sizeof(Medicaments));
			std::cout << "Lista lekow dodana! \n";
			
		}
		clse.showAllMeds(clse);
		in.close();
		std::cout << "ENTER wrocic do menu \n"; _getch();
	}*/

};
#endif // !MEDS_H