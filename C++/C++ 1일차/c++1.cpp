#include<stdio.h>
#include<iostream>
//https://web.yonsei.ac.kr/hgjung/Lectures/GEN131/%EC%A0%9C13%EC%9E%A5%20%EA%B5%AC%EC%A1%B0%EC%B2%B4.pdf 
using namespace std;

class point{                    //������ ������: public, protectedm, private 
	public:
		int x,y;                     //�⺭���� --> �Ӽ�, property 
		
		void set(int a,int b){          //�Լ� --> method 
			if(a<0) a= a*-1; 
			if(b<0) b= b*-1;
			x=a;           
			y=b;
		}
		void print(){
			cout<<"X:"<<x<<", Y:"<<y<<endl;
		}
};
int main(int argc, char *argv[]){
	
	point mypoint; //point -->class, mypoint -->instance 
	
	//mypoint.x =-100;       //porperty access, public �϶��� ���� 
	//mypoint.y =-200;
	//ypoint.print();      //method call
	
	mypoint.set(-150,-200);
	mypoint.print();
	return 0;	
}
