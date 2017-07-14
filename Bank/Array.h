/*动态数组类模板，用来动态生成账户*/

#ifndef _ARRAY_H
#define _ARRAY_H
#include<cassert>

//数组类模板定义
template <typename T>

class Array{
private:
	T* list;					//用于存放动态分配的数组内存首地址
	int size;				//数组大小
public:
	Array(int sz = 50);
	Array(const Array<T>&a);	//复制构造函数
	~Array();

	Array<T>& operator = (const Array<T>& rhs);		//重载“=”使数组对象可以整体赋值
	T& operator [] (int i);						//重载“[]”,使数组对象可以起到c++普通数组的作用
	const T& operator [] (int i)const;
	operator T * ();								//重载到T*类型的转换，使数组对象可以起到c++普通数组的作用
	operator const T * () const;
	int getSize()const;							//获取数组大小
	void resize(int size);						//修改数组大小
};

template <typename T>
Array<T>::Array(int sz){
	assert(sz >= 0);								//数组大小不能为负数,这是断言，出错就会抛出异常
	size = sz;
	list = new T[size];							//动态分配size个T类型的元素空间
}

template <typename T>
Array<T>::~Array(){
	delete [] list;
}

//复制构造函数
template <typename T>
Array<T>::Array(const Array<T> &a){
	//从对象a取得数组大小，并赋值给当前对象的成员
	size = a.size;
	//为对象申请内存并进行出错检查
	list = new T[size];
	//从对象a复制数组元素到本对象
	for (int i = 0; i < n; i++){
		list[i] = a.list[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator = (const Array<T>& rhs){
	if (&rhs != this){
		//如果本对象中数组大小与rhs不同，则删除数组原有内存，然后重新分配
		if (size != rhs.size){
			delete[] list;
			size = rhs.size;
			list = new T[list];
		}
		//从对象rhs复制数组元素到本对象
		for (int i = 0; i < rhs.size; i++){
			list[i] = rhs.list[i];
		}
		return *this;					//返回当前对象的引用
	}
}

//重载“[]”,使数组对象可以起到c++普通数组的作用
template <typename T>
T &Array<T>::operator [] (int n){
	assert(n >= 0 && n < size);			//检查下标是否越界
	return list[n];
}

template <typename T>
const T &Array<T>::operator [] (int n)const{
	assert(n >= 0 && n < size);			//检查下标是否越界
	return list[n];
}

//重载到T*类型的转换，使数组对象可以起到c++普通数组的作用
//指向当前对象的私有数组
//因此可以像使用普通数组首地址一样去使用Array对象名
template <typename T>
Array<T>:: operator T* (){
	return list;
}

template <typename T>
Array<T>:: operator const T* ()const{
	return list;
}

//获得当前数组大小
template <typename T>
int Array<T>::getSize()const{
	return size;
}

//将数组的大小修改
template<typename T>
void Array<T>::resize(int sz){
	assert(sz >= 0);
	if (sz == size){								//如果和之前的大小一样什么也不做
		return;
	}
	T* newList = new T[sz];						//申请新的数组内存
	int n = (sz < size) ? sz : size;				//将sz与size中较小的一个值赋值给n
	//将原有数组中的前n个元素复制到新数组中
	for (int i = 0; i < n; i++){
		newList[i] = list[i];
	}
	delete[] list;								//删除原数组
	list = newList;								//使list指向新数组
	size = sz;
}



#endif
