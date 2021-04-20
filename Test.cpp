
#include "doctest.h"
#include <iostream>
#include <fstream>
#include<map>
#include <string>

//#include <sstream>
//#include <cstdlib>
#include <bits/stdc++.h>

//#include <time.h>
#include <cassert>

using namespace std;
#include "NumberWithUnits.hpp"
using namespace ariel;

/*
1 km = 1000 m
1 m = 100 cm
1 kg = 1000 g
1 ton = 1000 kg
1 hour = 60 min
1 min = 60 sec
1 USD = 3.33 ILS
*/
const string UNIT_NAMES_GIVEN_FILE[]={"km","m","cm","kg","g","ton","hour","min","sec","USD","ILS"};
const int UNIT_RANGE_GIVEN_FILE=11;
map<string,map<string,double>> units_conversiones;
//units_conversiones.
const string DISTANCE[]={"km","m","cm"};
const pair<double,string> KM[]={{1000,"m"},{100*1000,"cm"}};
const pair<double,string> CM[]={{0.01,"m"},{0.00001,"km"}};
const pair<double,string> M[]={{0.001,"km"},{100,"cm"}};
const string TIME[]={"hour","min","sec"};
const pair<double,string> HOUR[]={{60,"min"},{60*60,"sec"}};
const pair<double,string> MIN[]={{1/60,"hour"},{0.00001,"km"}};
const pair<double,string> SEC[]={{0.001,"km"},{100,"cm"}};



ifstream units_file{"units.txt"};


TEST_CASE("good tests - read unit"){
}
//Check comparison operators
void check_comparison(NumberWithUnits bigger, NumberWithUnits smaller)
{
    //> check
    CHECK(bigger>smaller);   
    //< check
    CHECK(smaller<bigger);
    //>= check
    CHECK(bigger>=smaller);
    CHECK(smaller>=smaller);
    //<= check
    CHECK(smaller<=bigger);
    CHECK(smaller<=smaller);
    //== seconed check
    CHECK(!(smaller==bigger));
    //!= check
    CHECK(smaller!=bigger);
    CHECK(!(smaller!=smaller));
}


// const int SEED=7;
// srand(SEED);
TEST_CASE("good tests - between the same unit"){
    NumberWithUnits::read_units(units_file);
    for(int i=0; i<30 ; i++)
    {
        double random_a=(rand()/rand()+0.1);
        double random_b=(rand()/rand()+0.1);

        string rand_unit=UNIT_NAMES_GIVEN_FILE[rand()%UNIT_RANGE_GIVEN_FILE];
        cout<<"a: "<<random_a<<" b: "<<random_b<<" unit:"<<rand_unit;

        NumberWithUnits a {random_a,rand_unit};
        NumberWithUnits b {random_b,rand_unit};
        //== check
        CHECK(a==a);
        CHECK(b==b);
        //+ unary check
        CHECK(+a==a);
        CHECK(+b==b);
        //- unary check
        CHECK(-a== NumberWithUnits{-random_a,rand_unit});
        CHECK(-b== NumberWithUnits{-random_b,rand_unit});
        //- binary check
        CHECK(a-b== NumberWithUnits{random_a-random_b,rand_unit});
        CHECK(b-a== NumberWithUnits{random_b-random_a,rand_unit});
        CHECK(b-a==-(a-b));
        //+ binary check
        CHECK(a+b== NumberWithUnits{random_a+random_b,rand_unit});
        CHECK(b+a== NumberWithUnits{random_b+random_a,rand_unit});
        CHECK(b+a==a+b);
        //++ prefix check
        CHECK(++a== NumberWithUnits{random_a+1,rand_unit});
        //++ postfix check
        CHECK(a++== NumberWithUnits{random_a+1,rand_unit});
        //now a=random_a+2 
        //-- prefix check
        CHECK(--a== NumberWithUnits{random_a+1,rand_unit});
        //-- postfix check
        CHECK(a--== NumberWithUnits{random_a+1,rand_unit});
        //now a=random_a
        //+= check
        NumberWithUnits c=a+=b;
        CHECK(a==c);
        CHECK(c==NumberWithUnits{random_a+random_b,rand_unit});
        //-= check
        c=a-=b;
        CHECK(a==c);
        CHECK(c== NumberWithUnits{random_a,rand_unit});
        //* right check
        CHECK(a*random_b== NumberWithUnits{random_a*random_b,rand_unit});
        //* left check
        CHECK(random_b*a== NumberWithUnits{random_a*random_b,rand_unit});

        assert(a==(NumberWithUnits{random_a,rand_unit}));
        assert(b==(NumberWithUnits{random_b,rand_unit}));
        if(random_a>random_b)
        {
           check_comparison(a, b);
        }
        else if (random_b>random_a)
        {
            check_comparison(b, a);
        }

    }
}

