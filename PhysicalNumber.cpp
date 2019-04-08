/*
 * PhysicalNumber.cpp
 *
 *  Created on: 1 Apr 2019
 *      Author: yotam dafna, matti stern, tomer hazan.
 */
#include <iostream>
#include "PhysicalNumber.h"
using namespace std;


//side functions************************************************************************

Unit toUnit (string st){
	Unit u;
	if (st == "[km]"){
		u = Unit::KM;
	}
	else if (st == "[m]"){
		u = Unit::M;
	}
	else if (st == "[cm]"){
		u = Unit::CM;
	}
	else if (st == "[hour]"){
		u = Unit::HOUR;
	}
	else if (st == "[min]"){
		u = Unit::MIN;
	}
	else if (st == "[sec]"){
		u = Unit::SEC;
	}
	else if (st == "[ton]"){
		u = Unit::TON;
	}
	else if (st == "[kg]"){
		u = Unit::KG;
	}
	else if (st == "[g]"){
			u = Unit::G;
	}
	else{
		throw std::invalid_argument("There is no such Unit");
	}
	return u;
}


bool checkUnit(PhysicalNumber& a,const PhysicalNumber& b) {
	PhysicalNumber bb = b;
	if ((a.getUnit()==Unit::KM || a.getUnit()==Unit::M || a.getUnit()==Unit::CM) && (bb.getUnit()==Unit::KM || bb.getUnit()==Unit::M || bb.getUnit()==Unit::CM)){
		return true;
	}
	else if ((a.getUnit()==Unit::HOUR || a.getUnit()==Unit::MIN || a.getUnit()==Unit::SEC) && (bb.getUnit()==Unit::HOUR || bb.getUnit()==Unit::MIN || bb.getUnit()==Unit::SEC)){
		return true;
	}
	else if ((a.getUnit()==Unit::TON || a.getUnit()==Unit::KG || a.getUnit()==Unit::G) && (bb.getUnit()==Unit::TON || bb.getUnit()==Unit::KG || bb.getUnit()==Unit::G)){
		return true;
	}
	return false;
}

string toString (PhysicalNumber p){
	string st = "";
	switch (p.getUnit()){
	case Unit::KM: st = "[km]"; break;
	case Unit::M: st = "[m]"; break;
	case Unit::CM: st = "[cm]"; break;
	case Unit::HOUR: st = "[hour]"; break;
	case Unit::MIN: st = "[min]"; break;
	case Unit::SEC: st = "[sec]"; break;
	case Unit::TON: st = "[ton]"; break;
	case Unit::KG: st = "[kg]"; break;
	case Unit::G: st = "[g]"; break;
	}
	return st;
}

PhysicalNumber convert(PhysicalNumber& a, const PhysicalNumber& bb){
	PhysicalNumber b = bb;
		switch (a.getUnit()){
		case Unit::KM: //a.unit == km 		//0
			if (b.getUnit() == Unit::M){
				b.setNumber(b.getNumber()/1000);
			}
			else if (b.getUnit() == Unit::CM){
				b.setNumber(b.getNumber()/100000);
			}
			b.setUnit(Unit::KM);
			break;
		case Unit::M: //a.unit == m 		//1
			if (b.getUnit() == Unit::KM){
				b.setNumber(b.getNumber()*1000);
			}
			else if (b.getUnit() == Unit::CM){
				b.setNumber(b.getNumber()/100);
			}
			b.setUnit(Unit::M);
			break;
		case Unit::CM: //a.unit == cm		//2
			if (b.getUnit() == Unit::KM){
				b.setNumber(b.getNumber()*100000);
			}
			else if (b.getUnit() == Unit::M){
				b.setNumber(b.getNumber()*100);
			}
			b.setUnit(Unit::CM);
			break;
		case Unit::HOUR: //a.unit == hour 	//3
			if (b.getUnit() == Unit::MIN){
				b.setNumber(b.getNumber()/60);
			}
			else if (b.getUnit() == Unit::SEC){
				b.setNumber(b.getNumber()/3600);
			}
			b.setUnit(Unit::HOUR);
			break;
		case Unit::MIN: //a.unit == min		//4
			if (b.getUnit() == Unit::HOUR){
				b.setNumber(b.getNumber()*60);
			}
			else if (b.getUnit() == Unit::SEC){
				b.setNumber(b.getNumber()/60);
			}
			b.setUnit(Unit::MIN);
			break;
		case Unit::SEC: //a.unit == sec		//5
			if (b.getUnit() == Unit::HOUR){
				b.setNumber(b.getNumber()*3600);
			}
			else if (b.getUnit() == Unit::MIN){
				b.setNumber(b.getNumber()*60);
			}
			b.setUnit(Unit::SEC);
			break;
		case Unit::TON: //a.unit == ton		//6
			if (b.getUnit() == Unit::KG){
				b.setNumber(b.getNumber()/1000);
			}
			else if (b.getUnit() == Unit::G){
				b.setNumber(b.getNumber()/1000000);
			}
			b.setUnit(Unit::TON);
			break;
		case Unit::KG: //a.unit == kg		//7
			if (b.getUnit() == Unit::TON){
				b.setNumber(b.getNumber()*1000);
			}
			else if (b.getUnit() == Unit::G){
				b.setNumber(b.getNumber()/1000);
			}
			b.setUnit(Unit::KG);
			break;
		case Unit::G: //a.unit == g			//8
			if (b.getUnit() == Unit::TON){
				b.setNumber(b.getNumber()*1000000);
			}
			else if (b.getUnit() == Unit::KG){
				b.setNumber(b.getNumber()*1000);
						}
			b.setUnit(Unit::G);
			break;
		}
		return b;
}


//End of side functions************************************************************************



PhysicalNumber::PhysicalNumber(double a, Unit unit){ //Constructor
	this->number = a;
	this->unit = unit;
}

Unit PhysicalNumber::getUnit(){
	return this->unit;
}
void PhysicalNumber::setUnit(Unit unit){
	this->unit = unit;
}

double PhysicalNumber::getNumber(){
	return this->number;
}
void PhysicalNumber::setNumber(double number){
	this->number = number;
}


PhysicalNumber PhysicalNumber::operator+ (PhysicalNumber& other){							    //1 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this, other);
		PhysicalNumber ans(this->number + newB.number, this->unit);
		return ans;
	}else{
		throw std::invalid_argument("The measurement units are different");
	}
}
PhysicalNumber& PhysicalNumber::operator+ () { //Unary 															//2 v **

	return *this;
}

PhysicalNumber& PhysicalNumber::operator+= (const PhysicalNumber& other){						//3 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this, other);
		this->number += newB.number;
		return *this;
	}else{
		throw std::invalid_argument("The measurement units are different");
	}
}

PhysicalNumber PhysicalNumber::operator- (PhysicalNumber& other){								//4 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this, other);
		PhysicalNumber ans(this->number - newB.number, this->unit);
		return ans;
	}else{
		throw std::invalid_argument("The measurement units are different");
	}
}


PhysicalNumber&  PhysicalNumber::operator- (){ //Unary											//5 x
	this->number = -(this->number);
	return *this;
}

PhysicalNumber& PhysicalNumber::operator-= (const PhysicalNumber& other){						//6 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this, other);
		this->number -= newB.number;
		return *this;
	}else{
			throw std::invalid_argument("The measurement units are different");
	}
}

	//Comparative actions
bool PhysicalNumber::operator> (const PhysicalNumber& other){ 									//7 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this,other);
		return (this->number > newB.number);
	}else{
		throw std::invalid_argument("The measurement units are different");
	}
}
bool PhysicalNumber::operator>= (const PhysicalNumber& other){									//8 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this,other);
		return (this->number >= newB.number);
	}else{
		throw std::invalid_argument("The measurement units are different");
	}

}
bool PhysicalNumber::operator< (const PhysicalNumber& other){									//9 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this,other);
		return (this->number < newB.number);
	}else{
		throw std::invalid_argument("The measurement units are different");
	}

}
bool PhysicalNumber::operator<= (const PhysicalNumber& other){									//10 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this,other);
		return (this->number <= newB.number);
	}else{
		throw std::invalid_argument("The measurement units are different");
	}


}
bool PhysicalNumber::operator== (const PhysicalNumber& other){									//11 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this,other);
		if (this->number == newB.number){
			return true;
		}else {
			return false;
		}
	}else{
		throw std::invalid_argument("The measurement units are different");
	}

}
bool PhysicalNumber::operator!= (const PhysicalNumber& other){									//12 v
	if (checkUnit(*this, other) == true){
		PhysicalNumber newB = convert(*this,other);
		return (this->number != newB.number);
	}else{
		throw std::invalid_argument("The measurement units are different");
	}
}

PhysicalNumber PhysicalNumber::operator++(int){													//13 v
	this->number++;
	return *this;
}
PhysicalNumber PhysicalNumber::operator--(int){													//14 v
	this->number--;
	return *this;
}

ostream& operator<< (ostream& os, const PhysicalNumber& p) {									//15 v
	return os << p.number << toString(p);
}

istream& operator>> (istream& is, PhysicalNumber& p) {											//16 v
	string s;
	is >> p.number >> s;
	p.unit = toUnit(s);
	return is;
}











