#include <sstream>
#include <iostream>
using namespace std;

int main(){
	 stringstream stream;
	 float out;
	 stream << "16.63";
	 stream >> out;
	 cout << out << endl;
	 stream.clear();
}