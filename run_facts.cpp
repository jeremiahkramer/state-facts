/***************************
 ** Program: run_facts.cpp
 ** Author: Jeremiah Kramer
 ** Date: 4/19/17
 ** Description: runs the state_facts.cpp functions. Manages and prints out state/county info from file
 ** Input: states and filename
 ** Output: state/county info
 **************************/
#include "state_facts.h"


int main (int argc, char *argv[]){

	char *file_name;
	int num_states = 0; 
	for (int i= 1; i < argc; i++){
		for (int j = 0; j < 2;j++){
			if (argv[i][j] == '-' && argv[i][j + 1] == 's'){
				num_states = atoi(argv[i + 1]);
			}
			if (argv[i][j] == '-' && argv[i][j + 1] == 'f'){
				file_name = argv[i + 1];
			}
		}
	}	
	ifstream fin(file_name);
	ofstream fout;
	state *state_array;

	bool check = true;
	
	check = is_valid_arguments(argv, argc);
	if (check == false){
		cout << "Invalid input. Restart program." << endl;
		return 0;
	}
	
	while(true){
		while(!fin.good()){
			fin.open(file_name);
				if (!fin.good()){
					cout << "Invalid file. Please enter a valid filename." << endl;
					cin.clear();
					cin >> file_name;
					cout << file_name << endl;
				}
		}
		state_array = create_states(num_states);

		for (int i = 0; i < num_states; i++){
			get_state_data(state_array, i, fin);
			state_array[i].c = create_counties(state_array[i].counties);
			get_county_data(state_array[i].c, state_array[i].counties, fin);
		}

		screen_or_file(state_array, state_array->c, num_states, state_array->counties, fout);

		delete_info(&state_array, num_states);

		cout << "Enter new number of states: ";
		cin >> num_states;
		cout << endl;
		cout << "Enter filename: ";
		cin >> file_name;
	}
	
	

	return 0;
}
