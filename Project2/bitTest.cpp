#include <iostream>
#include <string>
#include <sstream> 
using namespace std;


short* test(string command, short port){
	
	short *ret = new short[2];
	short data[2];
	string testin;



	ret[0] = 343;
	ret[1] = 117;

	// while(getline(std::cin,testin)){

	std::cout<<"Enter data >> "<<endl;
	std::getline(cin, testin);

  	string a,b;

  	std::istringstream iss (testin);
  	iss >> std::noskipws;
  	iss >> a >> std::ws >> b;
  	std::cout << a << ", " << b << '\n';

  	if (a == "push"){
  		ret[0] = 0;
  	}



  	// ret[0] = a;




	return ret;
}



int main(){

	short* tdat;

	tdat = test("test",28333);

	std::cout<<tdat[0]<<endl;
	std::cout<<tdat[1]<<endl;




}