//Main file yoinked from the exercise page
#include"genlist.h"
#include<iostream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>

int main(){

genlist<std::vector<double>> list;
std::string line;
double x;

while(std::getline(std::cin,line)){
    std::istringstream iss(line);
	std::vector<double> numbers;
	while(iss >> x) numbers.push_back(x); //Read elements from input line one at a time and save them in a vector
	
	list.add(numbers); //Put the vector in a generic list
	}

for(int i=0;i<list.size;i++){
	std::cout << "list[" << std::setw(2) << i << "]=";
	for(double x: list[i])
		std::cout << " " << std::scientific << std::setprecision(4) << x;
	std::cout << "\n";
}

//Test remove
genlist<int> ilist;
ilist.add(1);
ilist.add(2);
ilist.add(5);
ilist.add(4);
std::cout << "ilist = "; ilist.print();
std::cout << "ilist.size = " << ilist.size << std::endl;
ilist.remove(1);
std::cout << "ilist.remove(1) = "; ilist.print(); 
std::cout << "ilist.size = " << ilist.size << std::endl;

/* never mind the following... */

genlist<genlist<double>> dlist;
genlist<double> d1;
d1.add(5.4e-2);
dlist.add(d1);
d1.add(6.7e8);
dlist.add(d1);
d1.add(0.99);
dlist.add(d1);

std::cout << "dlist=" << std::endl;
for(int i=0;i<dlist.size;i++){
	for(int j=0;j<dlist[i].size;j++) std::cout << dlist[i][j] << " ";
	std::cout << std::endl;
	}

return 0;
}//main
