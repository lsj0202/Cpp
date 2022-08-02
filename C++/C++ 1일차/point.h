#ifndef __POINT_H__
#define __POINT_H__

class point{
	private:
		int x,y;
	public:
		point();    //constructor 持失切  
		~point();    //destructor 社瑚切  
		void set(int a,int b);
		void print();
};

#endif
