#pragma once
#include <iostream>
#include <fstream>

namespace ariel {
    class NumberWithUnits{
        private:
            //NumberWithUnits(NumberWithUnits other_num);

        public:
            NumberWithUnits(double num,std::string unit);
            static void read_units(std::ifstream &units_file);
            //-------------------------------------
            // operators
            //-------------------------------------

            //----------------------------------
            // unary operators
            //----------------------------------


            //Addition
            NumberWithUnits operator+() const;
            // prefix increment:
            NumberWithUnits& operator++() ;
            // postfix increment:
            NumberWithUnits operator++(int dummy_flag_for_postfix);
            
            //Subtraction
            NumberWithUnits operator-() const ;
            // prefix decrement:
            NumberWithUnits& operator--() ;
            // postfix decrement:
            NumberWithUnits operator--(int dummy_flag_for_postfix);
        

            //----------------------------------------
            // binary operators
            //----------------------------------------

            //Addition
            NumberWithUnits operator+(const NumberWithUnits & otherNum) const;
            NumberWithUnits & operator+=(const NumberWithUnits & otherNum);

            //Subtraction
            NumberWithUnits operator-(const NumberWithUnits & otherNum) const;
            NumberWithUnits & operator-=(const NumberWithUnits & otherNum);

            //multiplication
            NumberWithUnits operator*(const double & otherDoubleNum) const;
            friend NumberWithUnits operator*(const double & otherDoubleNum,const NumberWithUnits & otherNum) ;


            //Comparison operators
            bool operator<( const NumberWithUnits& otherNum) const;
            bool operator> (const NumberWithUnits& otherNum) const;
            //{ return (otherNum < *this); }
            bool operator<=(const NumberWithUnits& otherNum) const;
            //{ return !(otherNum > (*this)); }
            bool operator>=(const NumberWithUnits& otherNum) const;
            bool operator==(const NumberWithUnits & otherNum) const;
            bool operator!=(const NumberWithUnits& otherNum) const;

        
            //----------------------------------
            // friend global IO operators
            //----------------------------------
            friend std::ostream& operator<< (std::ostream& output, const NumberWithUnits& num);
            friend std::istream& operator>> (std::istream& input , NumberWithUnits& num);
        };
}