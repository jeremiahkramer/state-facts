#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

struct county {
	string name; //name of county
	string *city; //name of cities in county
	int cities; //number of cities in county
	int population; //total population of county
	float avg_income; //avg household income
	float avg_house; //avg household price
};

struct state {
	string name; //name of state
	struct county *c; //name of counties
	int counties; //number of counties in state
	int population; //total population of state
};

bool is_valid_arguments(char *[], int);
state * create_states(int);
void get_state_data(state *, int, ifstream &);
county * create_counties(int);
void get_county_data(county *, int, ifstream &);
void delete_info(state **, int);

void large_state_pop(state *, int, int, ofstream &);
void large_county_pop(state *, int, int, int, ofstream &);
void counties_income(county *, int, int, ofstream &);
void state_avg_income(state *, int, int, int, ofstream &);
void states_by_name(state *, int, int, ofstream &);
void states_by_pop(state *, int, int, ofstream &);
void counties_by_name(county *, int, int, ofstream &);
void counties_by_pop(county *, int, int, ofstream &);
void screen_or_file(state *, county *, int, int, ofstream &);
