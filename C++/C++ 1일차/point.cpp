#include <iostream>
#include "point.cpp"

using namespace std;

point::point(){
	cout<<"POINT CONST."<<endl;
}
point::~point(){
	cout<<"POINT DEST."<<endl;
} 
void set(int a,int b){
	x=a;
	y=b;
}
void point::print(){// �Լ� �̸� �տ� ����  
	cout<<"POINT: "<<x<<", "<<y<<endl;
}
