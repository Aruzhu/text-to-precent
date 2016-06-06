#include <iostream> // text output
#include <sstream> //form convertions
#include <fstream> //text reading
#include <math.h> //calculations
using namespace std;

float stringfloat(string a){
	stringstream stream;
	float b;
	stream << a;
	stream >> b;
	return b;
}
string floatstring(float a){
	stringstream stream;
	string b;
	stream << a;
	stream >> b;
	return b;
}
int stringint(string a){
	stringstream stream;
	int b;
	stream << a;
	stream >> b;
	return b;
}
string charstring(char a){
	stringstream stream;
	string b;
	stream << a;
	stream >> b;
	return b;
}
char stringchar(string a){
	stringstream stream;
	char b;
	stream << a;
	stream >> b;
	return b;
}
//lets get to it
int main(){
	string input;
	
	//source question
	int type = 0;
	while(type == 0){
		cout << "where to get the data from?" << endl;
		cout << "1. data.txt (numbers in precent)" << endl;
		cout << "2. whatpulse csv" << endl;
		cout << "3. exit" << endl;
		getline(cin,input);
	
		type = stringint(input);
		if(type == 0){
			cout << endl << "please enter A NUMBER" << endl;
		}
	}
	
	if(type == 3){return 0;}
	// get data
	ifstream reader( ((type == 1) ? "data.txt" : "keyboard-heatmap.csv") );
	if(!reader){return -1;}
	
	string line;
	int dataiter = 0;
	
	int size1 = 30; // yes i know, but ifstream dosent work in a function
	int size2 = 56;
	string data[ ((type == 1)? size1 : size2)][2];
	
	while(!reader.eof()){
		getline(reader,line);
		switch(type){
			case 1:
				data[dataiter][0] = line.at(0);
				data[dataiter][1] = line.assign(line, 2, line.size());
				break;
			case 2: // 73,"I",31115
				int index = line.find_first_of(',');
				int index2 = line.find(',',index+1);
				
				string letter = "";
				
				if(index+2 == index2-2){
					letter = charstring(line.at(index+2));
				}
				else{
					letter.assign(line, (index+2), (index2-2)); // this no work, i cant figure out why
					letter.assign(letter, 0, letter.find_first_of('"'));
					
					//convertions
					if(letter == "Space"){
						letter = " ";
					}
					if(letter == "Tab"){
						letter = "	";
					}
				}
				
				data[dataiter][0] = letter;
				data[dataiter][1] = line.assign(line, index2+1,line.size());
				break;
		}
		dataiter += 1;
	}
	
	// convert to decimal precent
	float sum = 0;
	if(type == 2){
		for(int b = 0; b<size2; b++){
			sum += stringfloat(data[b][1]);
		}
	}
	for(int a = 0; a<((type == 1)? size1 : size2); a++){
		switch(type){
			case 1 :
				data[a][1] = floatstring( stringfloat(data[a][1])/100 );
				break;
			case 2 :
				data[a][1] = floatstring( stringfloat(data[a][1])/sum );
				break;
		}
	}
	// get input from user
	cin.clear();
	cout << endl;
	
	cout << "please enter phrase or sentence: ";
	//cin.ignore(256,'\n');
	getline(cin,input);
	
	sum = 1;
	string lett;
	for(int a = 0; a<input.size(); a++){
		lett = input.at(a);
		for(int b = 0; b<((type == 1)? size1 : size2); b++){
			if( data[b][0] == lett ){
				sum *= stringfloat(data[b][1]);
				cout << lett+" <==> "+data[b][1]+" <==> "+floatstring(sum) << endl;
			}
		}
	}
	// the facts
	cout << "endsum:" << endl;
	cout << floatstring(sum*100)+"%" << "	with normal writing" << endl;
	cout << floatstring( (1/( pow(54,input.size())))*100 )+"%" << "	with totaly random writing" << endl;
	
	cout << "1 in "+floatstring( (float) pow(54,input.size()) )+" combinations with "+floatstring(input.size())+" characters" << endl;
	cout << endl;
	return 0;
}
