#include <iostream>

using namespace std;

class class_one{
	private:           //private�� ȥ�ڸ� ���� protected�� �ڽİ� ������.  
		int private_n;
	public:
		void set_n(int x){
			private_n = x;
		}
		void print(){
			cout<<"CLASS_ONE: "<<private_n<<endl;
		}
	friend class class_three; 
};

class class_two: public class_one{ //public ���  
	private:
		int private_m;
	public:
		void print2(){ 
			//cout<<"CLASS_TWO-P2: " <<private_n <<endl;
		}
};

class class_three{
	public:
		void test_fn(){
			class_one testx;
			
			testx.set_n(200);
			testx.private_n =250;
			testx.print();
		}	
};


int main(int argc, char*argv[]){
	
	class_two myclass;
	class_three myclass3;
	
	myclass3.test_fn();
	/*
	myclass.set_n(100);
	//myclass.private_n =200;
	myclass.print();*/
	
	return 0;
}
