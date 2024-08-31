//Author: Tyler Migitsch
//Class: CMPSC 121
//Project 2
//Purpose: Read details from a file to output invoices with full details.
//Sources of logic assistance: None
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

ofstream fout;
int main() {
	ifstream fin;
	string filePath = "C:\\Users\\dougi\\OneDrive\\Documents\\school\\CMPSC 121, Intro prgmg tech\\Projects\\Project2-Invoices\\input.txt";
	fin.open(filePath);
	fout.open("C:\\Users\\dougi\\OneDrive\\Documents\\school\\CMPSC 121, Intro prgmg tech\\Projects\\Project2-Invoices\\output.txt");
	//verifying input and output files opened correctly
	if (!fin) {
		cout << "Input File opening failed." << endl;
		exit(3);
	}
	if (!fout) {
		cout << "Output File opening failed." << endl;
		exit(4);
	}

	void printReportHeader(), printInvoiceHeader(string), printLine(string, string, int, double, double),
		printTotal(double);
	int numItems, quantity;
	string date = "", name, itemNo;
	double totalCost, unitCost=0.0, invoiceCost=0.0,
		calcCost(int, double), accTotal(double, double);

	printReportHeader();
	//reads items and dates until end of file
	while (fin >> numItems >> date) {
		totalCost = 0;
		printInvoiceHeader(date);
		//reads invoice items and displays them
		for (int i = 0; i < numItems; i++) {
			fin >> itemNo >> name >> quantity >> unitCost;
			totalCost = calcCost(quantity, unitCost);
			invoiceCost = accTotal(invoiceCost, totalCost);
			printLine(itemNo, name, quantity, unitCost, totalCost);
		}
		printTotal(invoiceCost);
		//resets invoice cost, so it doesn't accumulate all invoice totals
		invoiceCost = 0;
	}
	fin.close();
	fout.close();

	return 0;
}
//calculates cost of single item
double calcCost(int quantity, double unitCost) {
	double totalCost = quantity * unitCost;
	return totalCost;
}
//calculates total cost of the invoice
double accTotal(double totalCost, double itemCost) {
	double newTotalCost = totalCost + itemCost;
	return newTotalCost;
}
//prints one line of the invoice
void printLine(string itemNo, string name, int quantity, double unitCost, double totalCost) {
	cout << fixed << setprecision(2) << setw(10) << right << itemNo << setw(15) << name << setw(7)
		<< quantity << setw(10) << unitCost	<< setw(10) << totalCost << endl;
	fout << fixed << setprecision(2) << setw(10) << right << itemNo << setw(15) << name << setw(7)
		<< quantity << setw(10) << unitCost	<< setw(10) << totalCost << endl;
}
void printReportHeader() {
	cout << "Erie Industrial Supply Corporation" << endl;
	fout << "Erie Industrial Supply Corporation" << endl;
}
void printInvoiceHeader(string date) {
	cout << "Invoice date: " << date << endl;
	fout << "Invoice date: " << date << endl;
}
//prints many ... then the invoice total
void printTotal(double invoiceTotal) {
	cout << fixed << setprecision(2) << "Total ............................." << invoiceTotal << endl;
	fout << fixed << setprecision(2) << "Total ............................." << invoiceTotal << endl;
}

/*Output printed in VS and in file
Erie Industrial Supply Corporation
Invoice date: 2/12/2017
	134276       Framis-R      8      7.35     58.80
	125790       Framis-L     12     15.76    189.12
	100086          Aglet    395      0.11     43.45
Total .............................291.37
Invoice date: 1/23/2017
	135876         Wrench     12     22.50    270.00
	543287         Henway      4     19.25     77.00
Total .............................638.37
Invoice date: 1/15/2017
	161432         Widget      5      6.50     32.50
	543289         Wodget     10      2.25     22.50
	876234         Gadget      2     10.75     21.50
Total .............................714.87
Invoice date: 2/16/2017
	198765         Corkle      2     12.18     24.36
	107654          Swale      3      8.75     26.25
	987987         Sinter      5      6.43     32.15
	654821         Zangle      6     18.45    110.70
	432165         Lunule      7      9.60     67.20
	333221         Fangle     10     58.49    584.90
	654098      Fwetstock      3     12.65     37.95
	543210         Furnal      3      9.98     29.94
	543287         Bobble     12     19.25    231.00
Total .............................1859.32
Invoice date: 2/26/2017
	654821         Muntin      2     18.45     36.90
	766443      Finwiddie      9      2.22     19.98
	120980         Ferkle    100      0.12     12.00
	123222     Sneedooper    700      1.19    833.00
	876543        Ferrule      2    345.77    691.54
	877721      Uberfrock     14     88.93   1245.02
Total .............................4697.76*/