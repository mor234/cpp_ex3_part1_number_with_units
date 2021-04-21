
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
const string DISTANCE[]={"km","m","cm"};
const string TIME[]={"hour","min","sec"};
const int SEED=7;
ifstream units_file{"units.txt"};

/**
 * @brief 
 * 
 * @param units_conversions 
 */
void add_units(map<string,map<string,double>>& units_conversions)
{
    //distances
    units_conversions["km"]["m"]=1000;
    units_conversions["km"]["cm"]=1000*100; 
    units_conversions["m"]["km"]=1/1000;
    units_conversions["m"]["cm"]=100;
    units_conversions["cm"]["km"]=1/100*1000;
    units_conversions["cm"]["m"]=1/100;
    //times
    units_conversions["hour"]["min"]=60;
    units_conversions["hour"]["sec"]=60*60;
    units_conversions["min"]["hour"]=1/60;
    units_conversions["min"]["sec"]=60;
    units_conversions["sec"]["hour"]=1/60*60;
    units_conversions["sec"]["min"]=1/60;
}


/*
* Check comparison operators
*/
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
    //== second check
    CHECK(!(smaller==bigger));
    //!= check
    CHECK(smaller!=bigger);
    CHECK(!(smaller!=smaller));
}

// TEST_CASE("good tests - read unit"){
// }
/**
 * @brief 
 * 
 * @return int -1 or 1 randomly
 */
int genrate_random_positive_negative()
{
    int negative_positive=rand()%2;// 0 or 1
    return-1+negative_positive;//return 1 or -1
}
int genrate_random_double()
{
    double tmp_rand=( (double)rand() / (rand()+0.1) );
    return tmp_rand*genrate_random_positive_negative();
}
TEST_CASE("good tests - between the same unit")
{
    srand(SEED);
    NumberWithUnits::read_units(units_file);
    for(int i=0; i<30 ; i++)
    {
        double random_a=genrate_random_double();
        double random_b=genrate_random_double();
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

TEST_CASE("good tests - between different units")
{

    NumberWithUnits::read_units(units_file);
    map<string,map<string,double>> units_conversions;
    add_units(units_conversions);
    for(int i=0; i<5 ; i++)
    {
        double random_distance_a=genrate_random_double();
        double random_distance_b=genrate_random_double();

        double random_time_a=genrate_random_double();
        double random_time_b=genrate_random_double();

        int rand_unit_index_d=rand()%3;
        //cout<<"a: "<<random_a<<" b: "<<random_b<<" unit:"<<rand_unit;
        NumberWithUnits a_distance (random_distance_a,DISTANCE[rand_unit_index_d]);
        NumberWithUnits a_distance_diff_u (random_distance_a,DISTANCE[(rand_unit_index_d+1)%3]);
        NumberWithUnits b_distance (random_distance_b,DISTANCE[(rand_unit_index_d+1)%3]);
       
        int rand_unit_index_t=rand()%3;
        NumberWithUnits a_time (random_distance_a,TIME[rand_unit_index_t]);
        NumberWithUnits a_time_diff_u (random_time_a,TIME[(rand_unit_index_t+1)%3]);
        NumberWithUnits b_time (random_time_b,TIME[(rand_unit_index_t+1)%3]);


        //== check
        CHECK(a_distance==a_distance_diff_u);
        CHECK(a_time==a_time_diff_u);
        //+ unary check
        CHECK(+a_distance==a_distance_diff_u);
        CHECK(+a_time==a_time_diff_u);
        //- unary check
        CHECK(-a_distance==-a_distance_diff_u);
        CHECK(-a_time==-a_time_diff_u);

        double mul_d=units_conversions[DISTANCE[(rand_unit_index_d+1)%3]][DISTANCE[rand_unit_index_d]];//convert b to a
        double mul_t=units_conversions[TIME[(rand_unit_index_t+1)%3]][TIME[rand_unit_index_t]];//convert b to a

        //- binary check
    
        CHECK((a_distance-b_distance)== (NumberWithUnits{random_distance_a-random_distance_b*mul_d,DISTANCE[rand_unit_index_d]}));
        CHECK((a_time-b_time)==  (NumberWithUnits{random_time_a-random_time_b*mul_t,TIME[rand_unit_index_d]}));

        //+ binary check
        CHECK((a_distance+b_distance)== (NumberWithUnits{random_distance_a+random_distance_b*mul_d,DISTANCE[rand_unit_index_d]}));
        CHECK((a_time+b_time)==  (NumberWithUnits{random_time_a+random_time_b*mul_t,TIME[rand_unit_index_d]}));

/*************************************************************************************************/  
        //+= check
        NumberWithUnits c=a_distance+=b_distance;
        CHECK(a_distance==c);
        CHECK(c==(NumberWithUnits{random_distance_a+random_distance_b*mul_d,DISTANCE[rand_unit_index_d]}));
        //-= check
        c=a_distance-=b_distance;
        CHECK(a_distance==c);
        CHECK(c==(NumberWithUnits{random_distance_a+random_distance_b*mul_d,DISTANCE[rand_unit_index_d]}));
    

        
        if(random_distance_a>random_distance_b*mul_d)
        {
            check_comparison(a_distance, b_distance);
        }
        else if (random_distance_a!=random_distance_b)
        {
            check_comparison(b_distance, a_distance);
        }

    }
}

TEST_CASE("bad tests - between different units")
{

    NumberWithUnits::read_units(units_file);
    map<string,map<string,double>> units_conversions;
    add_units(units_conversions);
    for(int i=0; i<5 ; i++)
    {
        double random_distance_a=genrate_random_double();
        double random_time_a=genrate_random_double();

        int rand_unit_index_d=rand()%3;
        //cout<<"a: "<<random_a<<" b: "<<random_b<<" unit:"<<rand_unit;
        NumberWithUnits a_distance (random_distance_a,DISTANCE[rand_unit_index_d]);
       
        int rand_unit_index_t=rand()%3;
        NumberWithUnits a_time (random_distance_a,TIME[rand_unit_index_t]);


        //- binary check
        CHECK_THROWS(a_distance-a_time);
        //+ binary check
        CHECK_THROWS(a_distance+a_time);

/*************************************************************************************************/  
        //+= check
        CHECK_THROWS(a_distance+=a_time);
        //-= check
        CHECK_THROWS(a_distance-=a_time); 
        //> check
        CHECK_THROWS(a_distance.operator>(a_time));   
        CHECK_THROWS(a_time.operator>(a_distance));  
        //< check
        CHECK_THROWS(a_distance.operator<(a_time));
        CHECK_THROWS(a_time.operator<(a_distance));
        //>= check
        CHECK_THROWS(a_distance.operator>=(a_time));
        CHECK_THROWS(a_time.operator>=(a_distance));
        //<= check
        CHECK_THROWS(a_distance.operator<=(a_time));
        CHECK_THROWS(a_time.operator<=(a_distance));
        //==  check
        CHECK_THROWS(a_time.operator==(a_distance));
        CHECK_THROWS(a_distance.operator==(a_time));
        //!= check
        CHECK_THROWS(a_time.operator!=(a_distance));
        CHECK_THROWS(a_distance.operator!=(a_time));

    }
}

