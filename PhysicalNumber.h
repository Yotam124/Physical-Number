/*
 * PhysicalNumber.hpp
 *
 *  Created on: 1 Apr 2019
 *      Author: yotam dafna, matti stern, tomer hazan.
 */
#include <iostream>
#include "Unit.h"


class PhysicalNumber {
	double number;
	Unit unit;

public :
	//double number;
	//Unit unit;

	PhysicalNumber(double a, Unit unit);
	//Arithmetics
	PhysicalNumber operator+ (PhysicalNumber& other); 								//1
	PhysicalNumber& operator+ ();                   								//2
	PhysicalNumber& operator+= (const PhysicalNumber& other);						//3

	PhysicalNumber operator- (PhysicalNumber& other);								//4
	PhysicalNumber& operator- ();													//5
	PhysicalNumber& operator-= (const PhysicalNumber& other);						//6

	//Comparative actions
	bool operator> (const PhysicalNumber& other);									//7
	bool operator>= (const PhysicalNumber& other);									//8
	bool operator< (const PhysicalNumber& other);									//9
	bool operator<= (const PhysicalNumber& other);									//10
	bool operator== (const PhysicalNumber& other);									//11
	bool operator!= (const PhysicalNumber& other);									//12

	PhysicalNumber operator++(int);													//13
	PhysicalNumber operator--(int);													//14

	friend std::ostream& operator<< (std::ostream& os, const PhysicalNumber& p);	//15
	friend std::istream& operator>> (std::istream& is, PhysicalNumber& p);			//16

	Unit getUnit();
	void setUnit(Unit unit);

	double getNumber();
	void setNumber(double number);

};



