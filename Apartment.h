#pragma once

#include <string>
#include <iostream>

struct Apartment
{
    std::string address;
    double area;
    double pricePerMonth;

    Apartment* next;
};

struct ApartmentList
{
    std::string city;
    Apartment* head;
    int numOfApartments;
};

std::istream& operator>>(std::istream& is, Apartment& apartment);

std::ostream& operator<<(std::ostream& os, const Apartment& apartment);

void FillApartment(Apartment* apartment, const std::string& str);

Apartment* AllocApartment(const std::string& address = "", double area = 0, double price = 0);

std::ostream& operator<<(std::ostream& os, const ApartmentList& apartmentList);

ApartmentList* AllocApartmentList(const std::string& city);

void ClearApartmentList(ApartmentList* apartmentList);

void FreeApartmentList(ApartmentList* apartmentList);

void AddApartment(ApartmentList* apartmentList, Apartment* apartment);

void PrintApartments(const ApartmentList* apartmentList);
