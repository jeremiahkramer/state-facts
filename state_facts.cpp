/******************************************************
 * ** Program: state_facts.cpp
 * ** Author: Jeremiah Kamer
 * ** Date: 04/19/2017
 * ** Description: function definitions for state_facts program
 * ** Input: "screen" or "file"
 * ** Output: state_facts to screen or file
 * ****************************************************/
#include "state_facts.h"

/****************************
 ** Function: is_valid_arguments
 ** Description: reads the input from the user and checks for valid input
 ** Parameters: char *ele[], int arg
 ** Pre- Conditions: needs user input
 ** Post- Conditions: none
 ** Return: true or false
 ***************************/
bool is_valid_arguments(char *ele[], int arg){
	if (arg != 5){
		cout << "Invalid amount of arguments." << endl;
		return false;
	}
	else
		return true;

	for (int i = 1; i < arg; i++){
		if (ele[i][0] != '-' && (ele[i][1] != 's'|| (ele[i][0]!='f'))){	
			return false;
		}
		else
			return true;
	}
}

/****************************
 ** Function: create_states
 ** Description: creates states of size num_states on heap
 ** Parameters: int num_states
 ** Pre- Conditions: needs num_states from command line
 ** Post- Conditions: dynamic memory - need to free it
 ** Return: state *
 ***************************/
state * create_states(int num_states){
	state * state_pointer = NULL;
	state_pointer = new state[num_states];
	return state_pointer;
}

/****************************
 ** Function: get_state_data
 ** Description: populates state array
 ** Parameters: state *state_arr, int i, ifstream &fin
 ** Pre- Conditions: needs state array 
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void get_state_data(state *state_arr, int i, ifstream &fin){
	fin >> state_arr[i].name;
	fin >> state_arr[i].population;
	fin >> state_arr[i].counties;
}

/****************************
 ** Function: create_counties
 ** Description: creates counties of size num_counties on heap
 ** Parameters: int num_counties
 ** Pre- Conditions: needs num_counties from command line
 ** Post- Conditions: dynamic memory - need to free it
 ** Return: county *
 ***************************/
county * create_counties(int num_counties){
	county * county_pointer = NULL;
	county_pointer = new county[num_counties];
	return county_pointer;
}

/****************************
 ** Function: get_county_data
 ** Description: populates county array
 ** Parameters: county *county_arr, int num_counties, ifstream &fin
 ** Pre- Conditions: needs county array 
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void get_county_data(county *county_arr, int num_counties, ifstream &fin){
	for (int i = 0; i < num_counties; i++){
		fin >> county_arr[i].name;
		fin >> county_arr[i].population;
		fin >> county_arr[i].avg_income;
		fin >> county_arr[i].avg_house;
		fin >> county_arr[i].cities;
		county_arr[i].city = new string[county_arr[i].cities];
		for (int j = 0; j < (county_arr[i].cities); j++){
			fin >> county_arr[i].city[j];
		}
	}
}

/****************************
 ** Function: delete_info
 ** Description: frees memory on heap
 ** Parameters: state **, int
 ** Pre- Conditions: needs memory to have been created first
 ** Post- Conditions: no memory leaks
 ** Return: none
 ***************************/
void delete_info(state **pointer_to_state_arr, int num_states){
	for (int i = 0; i < num_states;i++){
		for (int j = 0; j < pointer_to_state_arr[i]->counties; j++){
			for (int  k = 0; k < pointer_to_state_arr[i]->c[j].cities; k++){
				delete [] pointer_to_state_arr[i]->c[j].city;
			}
			delete [] pointer_to_state_arr[i]->c;
		}
		delete [] pointer_to_state_arr;
	}
	*pointer_to_state_arr = NULL;
}

/****************************
 ** Function: large_state_pop
 ** Description: finds largest state_pop by sorting the state array by pop first
 ** Parameters: state *, int, int, ofstream &
 ** Pre- Conditions: needs state array info
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void large_state_pop(state *state_arr, int print, int num_states, ofstream &fout){
	int temp;
	for (int i = 0; i < num_states; i++){
		if (state_arr[i].population > state_arr[i + 1].population){
			temp = state_arr[i].population;
			state_arr[i].population = state_arr[i + 1].population;
			state_arr[i + 1].population = temp; 
		}
	}
	if (print == 1){
		cout << "Largest state population: " << state_arr[0].population << endl;
	}
	if (print == 2){
		fout << "Largest state population: " << state_arr[0].population << endl;
	}
}

/****************************
 ** Function: large_county_pop
 ** Description: finds largest county_pop by sorting the county array by pop first
 ** Parameters: county *, int, int, ofstream &
 ** Pre- Conditions: needs county array info
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void large_county_pop(county *county_arr, int print, int num_counties, ofstream &fout){
	int temp;
	for (int i = 0; i < num_counties; i++){
		if (county_arr[i].population > county_arr[i].population){
			temp = county_arr[i].population;
			county_arr[i].population = county_arr[i].population;
			county_arr[i].population = temp;
		}
	}
	if (print == 1){
		cout << "Largest county population: " << county_arr[0].population << endl;
	}
	if (print == 2){
		fout << "Largest county population: " << county_arr[0].population << endl;
	}
}

/****************************
 ** Function: counties_income
 ** Description: finds counties income above a certain amount
 ** Parameters: county *, int, int, ofstream &
 ** Pre- Conditions: needs county array info
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void counties_income(county *county_arr, int print, int num_counties, ofstream &fout){
	float amount = 0;
	county * income_arr;
	int count = 0;
	cout << "Enter an income that counties income need to be above: ";
	cin >> amount;
	if (amount < 0){
		cout << "Please enter a number 0 or above: ";
		cin >> amount;
	}
	for (int i = 0; i < num_counties; i++){
		if (county_arr[i].avg_income > amount){
			count++;
		}
	}
	for (int i = 0; i < num_counties; i++){
		if (county_arr[i].avg_income > amount){
			for (int j = 0; j < count; j++){
				income_arr[j].avg_income = county_arr[i].avg_income;
			}
	}
	if (print == 1){
		for (int i = 0; i < count; i++){
			cout << income_arr[i].avg_income << endl;
		}
	}
	if (print == 2){
		for (int i = 0; i < count; i++){
			fout << income_arr[i].avg_income << endl;
		}
	}
}
}

/****************************
 ** Function: state_avg_income
 ** Description: finds state avg income
 ** Parameters: state *, int, int, int, ofstream &
 ** Pre- Conditions: needs state array info
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void state_avg_income(state *state_arr, int print, int num_states, int num_counties, ofstream &fout){
	float sum = 0;
	float avg = 0;
	for (int i = 0; i < num_states; i++){
		for (int j = 0; j < num_counties; j++){
			sum += state_arr[i].c[j].avg_house;
		}
	}
	avg = sum/num_counties;
	if (print == 1){
		cout << "Average household cost: " << avg << endl;
	}
	if (print == 2){
		fout << "Average household cost: " << avg << endl;
	}
}

/****************************
 ** Function: states_by_name
 ** Description: sorts states by name
 ** Parameters: state *, int, int, ofstream &
 ** Pre- Conditions: needs state array info
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void states_by_name(state *state_arr, int print, int num_states, ofstream &fout){
	string temp;
	for (int i = 0; i < num_states; i++){
		if ((int)state_arr[i].name[0] > (int)state_arr[i + 1].name[0]){
			temp = state_arr[i].name;
			state_arr[i].name = state_arr[i + 1].name;
			state_arr[i + 1].name = temp;
		}
	}
	if (print == 1){
		for (int i = 0; i < num_states; i++){
			cout << state_arr[i].name << endl;
		}
	}
	if (print == 2){
		for (int i = 0; i < num_states; i++){
			fout << state_arr[i].name << endl;
		}
	}
}

/****************************
 ** Function: states_by_pop
 ** Description: sorts states by pop
 ** Parameters: state *, int, int, ofstream &
 ** Pre- Conditions: needs state array info
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void states_by_pop(state *state_arr, int print, int num_states, ofstream &fout){
	int temp;
	for (int i = 0; i < num_states; i++){
		if (state_arr[i].population > state_arr[i + 1].population){
			temp = state_arr[i].population;
			state_arr[i].population = state_arr[i + 1].population;
			state_arr[i + 1].population = temp;
		}
	}
	if (print == 1){
		for (int i = 0; i < num_states; i++){
			cout << state_arr[i].population << endl;
		}
	}
	if (print == 2){
		for (int i = 0; i < num_states; i++){
			fout << state_arr[i].population << endl;
		}
	}
}

/****************************
 ** Function: counties_by_name
 ** Description: sorts counties by name
 ** Parameters: county *, int, int, ofstream &
 ** Pre- Conditions: needs county array info
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void counties_by_name(county *county_arr, int print, int num_counties, ofstream &fout){
	string temp;
	for (int i = 0; i < num_counties; i++){
		if ((int)county_arr[i].name[0] > (int)county_arr[i + 1].name[0]){
			temp = county_arr[i].name;
			county_arr[i].name = county_arr[i + 1].name;
			county_arr[i + 1].name = temp;
		}
	}
	if (print == 1){
		for (int i = 0; i < num_counties; i++){
			cout << county_arr[i].name << endl;
		}
	}
	if (print == 2){
		for (int i = 0; i < num_counties; i++){
			fout << county_arr[i].name << endl;
		}
	}
}

/****************************
 ** Function: counties_by_pop
 ** Description: sorts counties by pop
 ** Parameters: county *, int, int, ofstream &
 ** Pre- Conditions: needs county array info
 ** Post- Conditions: none
 ** Return: none
 ***************************/
void counties_by_pop(county *county_arr, int print, int num_counties, ofstream &fout){
	int temp;
	for (int i = 0; i < num_counties; i++){
		if (county_arr[i].population > county_arr[i + 1].population){
			temp = county_arr[i].population;
			county_arr[i].population = county_arr[i + 1].population;
			county_arr[i + 1].population = temp;
		}
	}
	if (print == 1){
		for (int i = 0; i < num_counties; i++){
			cout << county_arr[i].population << endl;
		}
	}
	if (print == 2){
		for (int i = 0; i < num_counties; i++){
			fout << county_arr[i].population << endl;
		}
	}
}

/****************************
 ** Function: screen_or_file
 ** Description: asks user to print to screen or file and calls rest of functions
 ** Parameters: state *, county *, int, int, ofstream &
 ** Pre- Conditions: needs county/state array info
 ** Post- Conditions: file has info or screen has info
 ** Return: none
 ***************************/
void screen_or_file(state *state_arr, county *county_arr, int num_states, int num_counties, ofstream &fout){
	int print = 0;
	string choice = "";
	char *filename;
	cout << "Do you want to print to this screen (\"screen\") or a file (\"file\")?" << endl;
	cin >> choice;
	while(choice != "screen" || choice != "file"){
		if (choice == "screen"){
			print = 1;
			large_state_pop(state_arr, print, num_states, fout);
			large_county_pop(county_arr, print, num_counties, fout);
			counties_income(county_arr, print, num_counties, fout);
			state_avg_income(state_arr, print, num_states, num_counties, fout);
			states_by_name(state_arr, print, num_states, fout);
			states_by_pop(state_arr, print, num_states, fout);
			counties_by_name(county_arr, print, num_counties, fout);
			counties_by_pop(county_arr, print, num_counties, fout);
		}
		if (choice == "file"){
			print = 2;
			cout << "Enter the name of your file: ";
			cin >> filename;
			fout.open(filename);
			large_state_pop(state_arr, print, num_states, fout);
			large_county_pop(county_arr, print, num_counties, fout);
			counties_income(county_arr, print, num_counties, fout);
			state_avg_income(state_arr, print, num_states, num_counties, fout);
			states_by_name(state_arr, print, num_states, fout);
			states_by_pop(state_arr, print, num_states, fout);
			counties_by_name(county_arr, print, num_counties, fout);
			counties_by_pop(county_arr, print, num_counties, fout);
		}
		else {
			cout << "Wrong input. Retry please." << endl;
			cin >> choice;
		}
	}
}
