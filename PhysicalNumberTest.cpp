/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::Unit;
using ariel::PhysicalNumber;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);


    //For my tests *************************************
    PhysicalNumber p1(10, Unit::TON);
    PhysicalNumber p2(1000, Unit::KG);
    PhysicalNumber p3(5, Unit::HOUR);
    PhysicalNumber p4(60, Unit::MIN);

    //For boolean checks
    PhysicalNumber p5(0, Unit::KM);
    PhysicalNumber p6(0, Unit::KM);
    PhysicalNumber p7(0, Unit::KM);
    PhysicalNumber p8(0, Unit::KM);

    if (p1 > p2){
    	istringstream("3[sec]") >> p5;
    }
    if (p3 < p4) {
    	//do nothing
    }else{
    	istringstream("3[cm]") >> p6;
    }
    if (PhysicalNumber(0.001, Unit::KG) == PhysicalNumber(1, Unit::G)){
    	istringstream("3[g]") >> p7;
    }
    if (p1 != p2){
    	istringstream("3[m]") >> p8;
    }
    //**************************************************


    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")



    // YOUR TESTS - INSERT AS MANY AS YOU WANT

      .setname("Basic output")
	  	  .CHECK_OUTPUT(p1, "10[ton]")
		  .CHECK_OUTPUT(p2, "1000[kg]")
		  .CHECK_OUTPUT(p3, "5[hour]")
		  .CHECK_OUTPUT(p4, "60[min]")
		  .CHECK_OUTPUT(p5, "3[sec]") //checking bool
		  .CHECK_OUTPUT(p6, "3[cm]")  //checking bool
		  .CHECK_OUTPUT(p7, "3[g]")    //checking bool
		  .CHECK_OUTPUT(p8, "3[m]")    //checking bool


	  .setname("Compatible dimensions")
	  	  .CHECK_OUTPUT(p1 - p2, "9[ton]")
		  .CHECK_OUTPUT(p3 - p4, "4[hour]")
		  .CHECK_OUTPUT(p3, "5[hour]") //p3 still remain the same.
		  .CHECK_OUTPUT((p4 -= PhysicalNumber(30, Unit::SEC)), "59.5[min]")
		  .CHECK_OUTPUT(p4, "59.5[min]") //p4 has changed.
		  .CHECK_OUTPUT(p1++, "10[ton]")
		  .CHECK_OUTPUT(p2--, "1000[kg]")
		  .CHECK_OUTPUT(p1, "11[ton]")
		  .CHECK_OUTPUT(p2, "999[kg]")
		  .CHECK_OUTPUT(-p2, "-999[kg]")
		  .CHECK_OUTPUT(+p2, "-999[kg]")
		  .CHECK_OUTPUT(++p7, "4[g]")
		  .CHECK_OUTPUT(--p8, "2[m]")


	  .setname("Basic input")
	  	  .CHECK_OK(istringstream("50[km]") >> p1)
		  .CHECK_OUTPUT(p1, "50[km]")
		  .CHECK_THROWS(istringstream("50[tt]") >> p1) //no such unit


	  .setname("Incompatible dimensions")
		  .CHECK_THROWS(p1 - p3)
		  .CHECK_THROWS(p1 -= p3)
		  .CHECK_THROWS(p2 + p4)
		  .CHECK_THROWS(p2 += p4)



      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
