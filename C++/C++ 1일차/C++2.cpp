//OOP (object Oriented Programming)
//         Encapsulation
//          Inheritance
//         Polymorphism <-��ƴ�  
//#incldue <stdio.h>
#include <iostream>  
#include <stdlib.h>
//https://web.yonsei.ac.kr/hgjung/Lectures/GEN131/%EC%A0%9C13%EC%9E%A5%20%EA%B5%AC%EC%A1%B0%EC%B2%B4.pdf
using namespace std;

int main(int argc,char *argv[]){
	int n =5;
	char c='a';
	char buf[20];
	
	 
	cout << "Hello" <<endl;      // <<  << �ó����� �¿� ������  
	cout << n <<endl;  
	cout << c <<endl; 
	
	cout << "Hello" <<n<<", - "<<c<<endl; 
	printf("Hello %d, -%c\n",n,c);
	
	cin>>n;
	cout<<"Value of n: "<<n<<endl;
	
	cout<<"Your String: ";
	cin >>buf; //scanf
	cout<<"Your String was: "<<buf <<endl;
	////////////////////////////////////////////////////
	int *p;
	//p=(int*)malloc(sizeof(int)*1);
	//free(p);
	
	p =new int(10);  //��  �ʱ�ȭ 
	*p=10;           
	delete p;
	///////////////////////////
	//p=(int*)malloc(sizeof(int)*5);
	//free(p);
	
	p =new int[5];
	delete [] p; // ������ �Ҵ�  
	
	
	return 0;
}
