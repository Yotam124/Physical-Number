/*
 * PhysicalNumber.cpp
 *
 *  Created on: 1 Apr 2019
 *      Author: yotam dafna, matti stern, tomer hazan.
 */
#include <iostream>
#include "PhysicalNumber.hpp"
using namespace std;



PhysicalNumber::PhysicalNumber(double a, Unit unit){ //Constructor
	this->number = a;
	this->unit = unit;
}

Unit PhysicalNumber::getUnit(){
	return this->unit;
}


//side functions************************************************************************

bool checkUnit(const PhysicalNumber& a, const PhysicalNumber& b) {
	if ((a.unit==Unit::KM || a.unit==Unit::M || a.unit==Unit::CM) && (b.unit==Unit::KM || b.unit==Unit::M || b.unit==Unit::CM)){
		return true;
	}
	else if ((a.unit==Unit::HOUR || a.unit==Unit::MIN || a.unit==Unit::SEC) && (b.unit==Unit::HOUR || b.unit==Unit::MIN || b.unit==Unit::SEC)){
		return true;
	}
	else if ((a.unit==Unit::TON || a.unit==Unit::KG || a.unit==Unit::G) && (b.unit==Unit::TON || b.unit==Unit::KG || b.unit==Unit::G)){
		return true;
	}
	return false;
}

string toString (PhysicalNumber p){
	string st = "";
	switch (p.unit){
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

PhysicalNumber convert(const PhysicalNumber& a, const PhysicalNumber& bb){
	PhysicalNumber b = bb;
		switch (a.unit){
		case Unit::KM: //a.unit == km 		//0
			if (b.unit == Unit::M){
				b.number /= 1000;
			}
			else if (b.unit == Unit::CM){
				b.number /= 100000;
			}
			b.unit = Unit::KM;
			break;
		case Unit::M: //a.unit == m 		//1
			if (b.unit == Unit::KM){
				b.number *= 1000;
			}
			else if (b.unit == Unit::CM){
				b.number /= 100;
			}
			b.unit = Unit::M;
			break;
		case Unit::CM: //a.unit == cm		//2
			if (b.unit == Unit::KM){
				b.number *= 100000;
			}
			else if (b.unit == Unit::M){
				b.number *= 100;
			}
			b.unit = Unit::CM;
			break;
		case Unit::HOUR: //a.unit == hour 	//3
			if (b.unit == Unit::MIN){
				b.number /= 60;
			}
			else if (b.unit == Unit::SEC){
				b.number /= 3600;
			}
			b.unit = Unit::HOUR;
			break;
		case Unit::MIN: //a.unit == min		//4
			if (b.unit == Unit::HOUR){
				b.number *= 60;
			}
			else if (b.unit == Unit::SEC){
				b.number /= 60;
			}
			b.unit = Unit::MIN;
			break;
		case Unit::SEC: //a.unit == sec		//5
			if (b.unit == Unit::HOUR){
				b.number *= 3600;
			}
			else if (b.unit == Unit::MIN){
				b.number *= 60;
			}
			b.unit = Unit::SEC;
			break;
		case Unit::TON: //a.unit == ton		//6
			if (b.unit == Unit::KG){
				b.number /= 1000;
			}
			else if (b.unit == Unit::G){
				b.number /= 1000000;
			}
			b.unit = Unit::TON;
			break;
		case Unit::KG: //a.unit == kg		//7
			if (b.unit == Unit::TON){
				b.number *= 1000;
			}
			else if (b.unit == Unit::G){
				b.number /= 1000;
			}
			b.unit = Unit::KG;
			break;
		case Unit::G: //a.unit == g			//8
			if (b.unit == Unit::TON){
				b.number *= 1000000;
			}
			else if (b.unit == Unit::KG){
				b.number *= 1000;
						}
			b.unit = Unit::G;
			break;
		}
		return b;
}


//End of side functions************************************************************************

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

PhysicalNumber& PhysicalNumber::operator++(){													//13 v
	this->number++;
	return *this;
}
PhysicalNumber& PhysicalNumber::operator--(){													//14 v
	this->number--;
	return *this;
}

ostream& operator<< (ostream& os, const PhysicalNumber& p) {									//15 v
	return os << p.number << toString(p);
}

istream& operator>> (istream& is, PhysicalNumber& p) {											//16 v
	/*string num = st.substr(0,st.size()-4);
	char ch1 = st.substr(st.size()-3, st.size()-2);
	char ch2 = st.substr(st.size()-2, st.size()-1);
*/
	return is;
}











