#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>

using namespace std;


int main(int argc, char *argv[]){
	uint8_t mynum=4;
	cin>>mynum;
	cout<<"mynum: "<<mynum<<endl;
	srand(time(NULL));
	map<int, int> mymap;
	mymap[1] = 2;
	mymap[2] = 3;
	mymap[3]= mymap[3]+2;	
	cout<<"mymap[3]: "<< mymap[3]<<endl;
	cout<<"argc: "<<argc<<" argv[0]: "<<argv[0]<<endl;
	if(mymap[3] == 0){
		cout<<"Gotcha"<<endl;
	}
	if(rand()%1==0){
		cout<<"Betcha"<<endl;
	}
	cout<<time(NULL)<<" "<<time(NULL)+1<<endl;
	cout<<mymap[1]<<" "<<mymap[2]<<" "<<mymap[3]<<endl;
}
