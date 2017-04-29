#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;


int main(int argc, char *argv[]){
	cout<<round((2+1.0)/(3+1))<<endl;	
	uint32_t mynum1;
	uint8_t mynum, mynum2;
	cin>>mynum>>mynum1>>mynum2;
	cout<<"mynum: "<<mynum<<"mynum1: "<<mynum1<<" mynum2: "<<mynum2<<endl;
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
	cout<<"new beginning*************"<<endl;
	map<int, vector<int> > hello;
	hello[0].push_back(10);
	cout<<"hello[0][0]: "<<hello[0][0]<<endl;
	hello[0] = vector<int>(16, 32);
	cout<<"hello[0][11]: "<<hello[0][11]<<endl;
	//pair<int, int> pr(4, 5);
	pair<int, int> pr  = pair<int, int>(2,3);
	vector<double> vec = vector<double>(3,4);
	cout<<"pair: "<<pr.first<<" "<<pr.second<<endl;
	cout<<"vec: "<<vec[0]<<endl;
	cout<<"CPP ROUNDING: "<<round(0.5)<<endl;
	cout<<"CPP ROUNDING: "<<round(1.5)<<endl;
	cout<<"CPP ROUNDING: "<<round(2.5)<<endl;
	cout<<"CPP ROUNDING: "<<round(3.5)<<endl;
	cout<<"CPP ROUNDING: "<<round(4.5)<<endl;
	uint32_t var = 0;
	uint32_t blah = max(0,(int)(var-1));
	cout<<"blah: "<<blah<<endl;	
}
