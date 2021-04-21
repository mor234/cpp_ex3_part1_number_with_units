#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel{

    NumberWithUnits::NumberWithUnits(double num,string unit){}
    
    void NumberWithUnits::read_units(ifstream &units_file){}
    //-------------------------------------
    // operators
    //-------------------------------------

    //----------------------------------
    // unary operators
    //----------------------------------

    //Addition
    NumberWithUnits NumberWithUnits::operator+() const
    {
        return *this;
    }
    // prefix increment:
  
    NumberWithUnits & NumberWithUnits::operator++() 
    {
        //add
        //return NumberWithUnits(*this-1)
        return *this;

    }
    // postfix increment:
    NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix)
    {
        //add
        //return NumberWithUnits(*this-1)
        return NumberWithUnits(1,"test");
    }

    
    //Subtraction
    NumberWithUnits NumberWithUnits::operator-() const {
        return NumberWithUnits(1,"test");
    }
    // prefix decrement:
    NumberWithUnits& NumberWithUnits::operator--() 
    {
        //sub
        return *this;
    }
    // postfix decrement:
    NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix)
    {
        //return this+1
       return NumberWithUnits(1,"test");

    }


    //----------------------------------------
    // binary operators
    //----------------------------------------

    //Addition
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits & otherNum) const
    {
        return NumberWithUnits(1,"test");
    }
    NumberWithUnits &  NumberWithUnits::operator+=(const NumberWithUnits & otherNum)
    {
        //add
        return *this;
    }

    //Subtraction
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits & otherNum) const
    {
        return NumberWithUnits(1,"test");

    }
    NumberWithUnits & NumberWithUnits::operator-=(const NumberWithUnits & otherNum)
    {
        //sub
        return *this;
    }

    //multiplication
    NumberWithUnits NumberWithUnits::operator*(const double & otherDoubleNum) const
    {
        return NumberWithUnits(1,"test");

    }
    NumberWithUnits operator*(const double & otherDoubleNum,const NumberWithUnits & otherNum)
    {
        return otherNum*otherDoubleNum;
    }


    //Comparison operators
    bool NumberWithUnits::operator<( const NumberWithUnits& otherNum) const
    {
        return true;
    }
    bool NumberWithUnits::operator> (const NumberWithUnits& otherNum)const
    {
        return otherNum < (*this);
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits& otherNum)const
    { 
        return !((*this) > otherNum);
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits& otherNum)const
    { 
        return !(*this < otherNum);
    }
    bool NumberWithUnits::operator==(const NumberWithUnits & otherNum) const
    {
        return true;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits& otherNum) const
    {
        return !(*this==otherNum);
    }


    //----------------------------------
    // friend global IO operators
    //----------------------------------
    std::ostream& operator<< (std::ostream& output, const NumberWithUnits& num)
    {
        return (output<<"hello");
    }
    std::istream& operator>> (std::istream& input , NumberWithUnits& num)//
    {
        return input;

    }
}