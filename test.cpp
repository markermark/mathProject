#include <string>
#include <iostream>
#include <fstream>
#include "Apartment.h"

int main(int argc, char* argv[])
{
    const char* inFile = "addressBook.txt";
    const char* outFile = "addressBookOut.txt";

    std::ifstream addressBook;
    if (argc < 2)
        addressBook.open(inFile);
    else
        addressBook.open(argv[1]);
   
    ApartmentList* apartmentList = AllocApartmentList("Moscow");
    char str[1024];
    while (addressBook.getline(str, 1024))
    {
        Apartment* apartment = AllocApartment();
        FillApartment(apartment, str);
        AddApartment(apartmentList, apartment);
    }

    addressBook.close();

    PrintApartments(apartmentList);
    
    std::ofstream wAddressBook;
    if (argc < 2)
        wAddressBook.open(outFile);
    else
        wAddressBook.open(argv[1]);

    wAddressBook << *apartmentList;

    wAddressBook.close();

    ClearApartmentList(apartmentList);

    PrintApartments(apartmentList);

    FreeApartmentList(apartmentList);

	return 0;
}