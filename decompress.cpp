#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	string dict[4096];//creating an array for dictinoary
	for (int i=0;i<256;i++)
		dict[i]=(char) i;//filling the dict with all ascii numbers

	ifstream input;
	ofstream decode;
	input.open("compout.txt");
	decode.open("decompout.txt");

	string line="",compressed,s;
	int number1,number2;

	while(getline(input, line))//get the txt file as a string
		compressed+=line;

	stringstream ss1(compressed);
	string a,b;
	int dictSize = 256;


	while(ss1>>number1){//save the first character
		b=char(number1);
		break;
	}

	string result=b;
	while(ss1>>number2){//reading the rest of the string 
		if(!dict[number2].empty())
			a=dict[number2];

		else if(number2 == dictSize)
			a = b + b[0];

		result+=a;//adding all the outputs to string
		dict[dictSize]=b+a[0];

		if(dictSize<4096)//if number is bigger than the dict. size then it wont store it in dict but it will store the information of txtt
			dictSize++;
		b=a;
	}


	decode<<result;//prints the string which contains all the text

	return 0;
}
