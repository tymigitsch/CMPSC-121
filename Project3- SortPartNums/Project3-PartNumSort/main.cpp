//Author: Tyler Migitsch
//Class: CMPSC 121
//Project 3
//Purpose: Read in parts.txt, sort the file using a shell sort,
// then ask the user for a part number to search for and print the part's info,
// if the part doesn't exist ask the user if they want to add the part, if yes ask for part info add it and sort.
// When user is done searching, display # of searches, how many were successful/not in system, and write to 
// a new txt file.
//Sources of logic assistance: None
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// templated swap function – Swaps two items in a vector of any type
// Put this BEFORE main()  Called from sort function
template <class CType>
void swapper(CType& a, CType& b)
{
	CType temp;
	temp = a;
	a = b;
	b = temp;
}

int main() {

	//parallel vectors
	vector <string> partNumber;
	vector <char> partClass;
	vector <int> partOhb;
	vector <double> partCost;
	//function initializations
	void get_data(vector <string>&, vector <char>&, vector <int>&, vector <double>&);
	void sort(vector <string>&, vector <char>&, vector <int>&, vector <double>&);
	void display(const vector <string>&, const vector <char>&, const vector <int>&, const vector <double>&, int);
	void get_more_data(char&, int&, double&);
	void insert_data(vector <string>&, vector <char>&, vector <int>&, vector <double>&, string, char, int, double);
	void print_stats(int, int, int);
	void put_data(const vector <string>&, const vector <char>&, const vector <int>&, const vector <double>&);
	string get_target();
	int bin_search(string, const vector <string>&);
	//other variables
	bool goSearch = false;
	bool goAdd = false;
	char yesNo = 'Y';
	char add = 'Y';
	char pClass = ' ';
	string target;
	int index;
	int pOhb = 0;
	int success = 0;
	int fail = 0;
	int totalSearch = 0;
	double pCost = 0.0;

	//reading file data into vectors and sorting
	get_data(partNumber, partClass, partOhb, partCost);
	sort(partNumber, partClass, partOhb, partCost);
	//loop until user is done searching
	while (yesNo == 'Y') {
		goSearch = false;
		goAdd = false;
		target = get_target();
		index = bin_search(target, partNumber);
		//if search successful
		if (index != -1) {
			++success;
			++totalSearch;
			display(partNumber, partClass, partOhb, partCost, index);
		}
		//if search fails
		else if (index == -1) {
			++fail;
			++totalSearch;
			//asks if they want to add until y or n is entered
			while (goAdd == false) {
				cout << "Add this part? (Y or N)" << endl;
				cin.ignore();
				cin >> add;
				add = toupper(add);
				if (add == 'Y' || add == 'N')
					goAdd = true;
			}
			//if user wants to add part
			if (add == 'Y') {
				//gets part info, adds it to vectors, then sorts vectors 
				get_more_data(pClass, pOhb, pCost);
				insert_data(partNumber, partClass, partOhb, partCost, target, pClass, pOhb, pCost);
				sort(partNumber, partClass, partOhb, partCost);
			}
		}
		//keeps asking for another search until y or n is entered
		while (goSearch == false) {
			cout << "Would you like to do another search? (Y or N)" << endl;
			cin.ignore();
			cin >> yesNo;
			yesNo = toupper(yesNo);
			if (yesNo == 'Y' || yesNo == 'N')
				goSearch = true;
		}
	}
	print_stats(totalSearch, success, fail);
	put_data(partNumber, partClass, partOhb, partCost);
	//print vectors
//	for (int i = 0; i < partNumber.size(); i++)
//	{
//		cout << i << ": " << partNumber[i] << " " << partClass[i] << " " << partOhb[i] << " " << partCost[i] << endl;
//	}
	return 0;
}
//inserts data from parts.txt into parallel vectors
void get_data(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost) {

	ifstream fin;
	fin.open("C:\\Users\\dougi\\OneDrive\\Documents\\school\\CMPSC 121, Intro prgmg tech\\Projects\\Project3- SortPartNums\\parts.txt");
	if (!fin) {
		cout << "File could not be opened." << endl;
		exit(3);
	}
	string partNum = "";
	char partC = ' ';
	int partOhb = 0;
	double partCost = 0.0;
	while (fin) {
		fin >> partNum >> partC >> partOhb >> partCost;
		part_number.push_back(partNum);
		part_class.push_back(partC);
		part_ohb.push_back(partOhb);
		part_cost.push_back(partCost);
		fin.ignore();
	}
	fin.close();
}
// shell sorts vectors based on part numbers ascending  (Calls swapper)
void sort(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost) {
	bool flag = true;
	int d = part_number.size();
	while (flag || (d > 1)) {
		flag = false;
		d = (d + 1) / 2;
		for (int i = 0; i < part_number.size() - d; i++)
		{
			if (part_number[i + d] < part_number[i]) {
				swapper(part_number[i + d], part_number[i]);
				swapper(part_class[i + d], part_class[i]);
				swapper(part_ohb[i + d], part_ohb[i]);
				swapper(part_cost[i + d], part_cost[i]);
				flag = true;
			}
		}
	}
}
//asks user for part number to search for
string get_target() {
	string target = "";
	cout << "What part number would you like to search for?" << endl;
	cin >> target;
	return target;
}
//does binary search returns index if found, -1 if not
int bin_search(string key, const vector <string>& part_number) {
	int high = part_number.size() - 1, low = 0, middle;
	bool found = false;
	while (!found && low <= high) {
		middle = (high + low) / 2;
		if (key == part_number[middle])
			return middle;
		else if (key > part_number[middle]) {
			low = middle + 1;
		}
		else if (key < part_number[middle]) {
			high = middle - 1;
		}
	}
	return -1;
}
//display info on part number
void display(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb,
	const vector <double>& part_cost, int finder) {
	double invValue = part_cost[finder] * part_ohb[finder];
	cout << "There are " << setw(7) << right << part_ohb[finder] << left << " of Part Number " << part_number[finder]
		<< " in inventory. It is a class " << part_class[finder] << " part." << endl << "The cost is $ "
		<< setw(7) << right << fixed << setprecision(2) << part_cost[finder] << left << ". The value of that inventory" << endl
		<< "is $ " << setw(7) << right << invValue << "." << endl;
}
//gets remaining info to add new part number
void get_more_data(char& class_in, int& part_ohb_in, double& part_cost_in) {
	cout << "What class is this part number in?" << endl;
	cin >> class_in;
	class_in = toupper(class_in);
	cout << "What is the on hand balance of this part?" << endl;
	cin >> part_ohb_in;
	cout << "What is the cost of this part?" << endl;
	cin >> part_cost_in;
}
//inserts new part data into vectors
void insert_data(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost,
	string part_in, char class_in, int part_ohb_in, double part_cost_in) {
	part_number.push_back(part_in);
	part_class.push_back(class_in);
	part_ohb.push_back(part_ohb_in);
	part_cost.push_back(part_cost_in);
}
//prints search stats
void print_stats(int searches, int good, int bad) {
	cout << "There were " << searches << " searches performed today." << endl
		<< good << " of them were successful." << endl
		<< bad << " of them were not in the system." << endl;
}
//writes to file to save additions; using newParts.txt intead of parts.txt to prevent saving over it
void put_data(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb,
	const vector <double>& part_cost) {
	ofstream fout;
	fout.open("C:\\Users\\dougi\\OneDrive\\Documents\\school\\CMPSC 121, Intro prgmg tech\\Projects\\Project3- SortPartNums\\newParts.txt");
	if (!fout) {
		cout << "Failed to open output file." << endl;
		exit(4);
	}
	for (int i = 0; i < part_number.size(); i++)
	{
		fout << part_number[i] << " " << part_class[i] << " " << part_ohb[i] << " " << fixed << setprecision(2) <<
			part_cost[i] << endl;
	}
	cout << "The file is now updated.";
	fout.close();
}
