/*��̬������ģ�壬������̬�����˻�*/

#ifndef _ARRAY_H
#define _ARRAY_H
#include<cassert>

//������ģ�嶨��
template <typename T>

class Array{
private:
	T* list;					//���ڴ�Ŷ�̬����������ڴ��׵�ַ
	int size;				//�����С
public:
	Array(int sz = 50);
	Array(const Array<T>&a);	//���ƹ��캯��
	~Array();

	Array<T>& operator = (const Array<T>& rhs);		//���ء�=��ʹ�������������帳ֵ
	T& operator [] (int i);						//���ء�[]��,ʹ������������c++��ͨ���������
	const T& operator [] (int i)const;
	operator T * ();								//���ص�T*���͵�ת����ʹ������������c++��ͨ���������
	operator const T * () const;
	int getSize()const;							//��ȡ�����С
	void resize(int size);						//�޸������С
};

template <typename T>
Array<T>::Array(int sz){
	assert(sz >= 0);								//�����С����Ϊ����,���Ƕ��ԣ�����ͻ��׳��쳣
	size = sz;
	list = new T[size];							//��̬����size��T���͵�Ԫ�ؿռ�
}

template <typename T>
Array<T>::~Array(){
	delete [] list;
}

//���ƹ��캯��
template <typename T>
Array<T>::Array(const Array<T> &a){
	//�Ӷ���aȡ�������С������ֵ����ǰ����ĳ�Ա
	size = a.size;
	//Ϊ���������ڴ沢���г�����
	list = new T[size];
	//�Ӷ���a��������Ԫ�ص�������
	for (int i = 0; i < n; i++){
		list[i] = a.list[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator = (const Array<T>& rhs){
	if (&rhs != this){
		//����������������С��rhs��ͬ����ɾ������ԭ���ڴ棬Ȼ�����·���
		if (size != rhs.size){
			delete[] list;
			size = rhs.size;
			list = new T[list];
		}
		//�Ӷ���rhs��������Ԫ�ص�������
		for (int i = 0; i < rhs.size; i++){
			list[i] = rhs.list[i];
		}
		return *this;					//���ص�ǰ���������
	}
}

//���ء�[]��,ʹ������������c++��ͨ���������
template <typename T>
T &Array<T>::operator [] (int n){
	assert(n >= 0 && n < size);			//����±��Ƿ�Խ��
	return list[n];
}

template <typename T>
const T &Array<T>::operator [] (int n)const{
	assert(n >= 0 && n < size);			//����±��Ƿ�Խ��
	return list[n];
}

//���ص�T*���͵�ת����ʹ������������c++��ͨ���������
//ָ��ǰ�����˽������
//��˿�����ʹ����ͨ�����׵�ַһ��ȥʹ��Array������
template <typename T>
Array<T>:: operator T* (){
	return list;
}

template <typename T>
Array<T>:: operator const T* ()const{
	return list;
}

//��õ�ǰ�����С
template <typename T>
int Array<T>::getSize()const{
	return size;
}

//������Ĵ�С�޸�
template<typename T>
void Array<T>::resize(int sz){
	assert(sz >= 0);
	if (sz == size){								//�����֮ǰ�Ĵ�Сһ��ʲôҲ����
		return;
	}
	T* newList = new T[sz];						//�����µ������ڴ�
	int n = (sz < size) ? sz : size;				//��sz��size�н�С��һ��ֵ��ֵ��n
	//��ԭ�������е�ǰn��Ԫ�ظ��Ƶ���������
	for (int i = 0; i < n; i++){
		newList[i] = list[i];
	}
	delete[] list;								//ɾ��ԭ����
	list = newList;								//ʹlistָ��������
	size = sz;
}



#endif
