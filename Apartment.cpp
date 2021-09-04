#include <iostream>
#include "Apartment.h"

std::istream& operator>>(std::istream& is, Apartment& apartment)
{
    is >> apartment.address
       >> apartment.area
       >> apartment.pricePerMonth;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Apartment& apartment)
{
    const char* delimiter = " ";

    os << apartment.address << delimiter
       << apartment.area << delimiter
       << apartment.pricePerMonth;

    return os;
}

void FillApartment(Apartment* apartment, const std::string& str)
{
    std::stringstream stream(str);
    stream >> *apartment;
}

Apartment* AllocApartment(const std::string& address, double area, double price)
{
    Apartment* apartment = new Apartment();
    apartment->address = address;
    apartment->area = area;
    apartment->pricePerMonth = price;

    return apartment;
}

std::ostream& operator<<(std::ostream& os, const ApartmentList& apartmentList)
{
    const Apartment* apartment = apartmentList.head;
    while (apartment != nullptr)
    {
        os << *apartment << std::endl;
        apartment = apartment->next;
    }
    return os;
}

ApartmentList* AllocApartmentList(const std::string& city)
{
	ApartmentList* apartmentList = new ApartmentList();
	apartmentList->city = city;
	apartmentList->head = nullptr;
	apartmentList->numOfApartments = 0;
	return apartmentList;
}

void ClearApartmentList(ApartmentList* apartmentList)
{
    while (apartmentList->head != nullptr)
    {
        Apartment* apartment = apartmentList->head;
        apartmentList->head = apartment->next;
        delete apartment;
    }

    apartmentList->head = nullptr;
    apartmentList->numOfApartments = 0;
}

void FreeApartmentList(ApartmentList* apartmentList)
{
    ClearApartmentList(apartmentList);
    delete apartmentList;
}

void AddApartment(ApartmentList* apartmentList, Apartment* apartment)
{
    Apartment* oldHead = apartmentList->head;
    apartment->next = oldHead;
    apartmentList->head = apartment;
    apartmentList->numOfApartments++;
}

void PrintApartments(const ApartmentList* apartmentList)
{
    std::cout << "Available "
              << apartmentList->numOfApartments
              << " apartments for "
              << apartmentList->city
              << " city:" << std::endl;

    const Apartment* apartment = apartmentList->head;
    while (apartment != nullptr)
    {
        std::cout << "Address: " << apartment->address << std::endl
                  << "Area: " << apartment->area  << " m2"<< std::endl
                  << "Price: " << apartment->pricePerMonth << "$ per month" << std::endl
                  << std::endl;
            
        apartment = apartment->next;
    }
}