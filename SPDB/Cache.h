#pragma once

#include<unordered_map>
#include<string>


/*
	TODO��
		1.ʵ��CacheProperty������������ʵ��
		2.���CacheContent��ʵ�֣�ʵ�ֶԻ������ݵĲ���
		3.��ɶ�Cache��ʵ�֣�ʵ�ֶԻ������ݵĴ�ȡ��ɾ��
		4.����Cache������ģʽ
*/


/*
	CacheProperty������ÿ��cachecontent��������ʵ������صķ�����֤Cache��д���̰߳�ȫ��
*/
class CacheProperty {
	//TODO����Ӷ�д���Լ���д����ز�����ע��Ҫͳһ���������ֹ�����������һ����֮�󣬽���ǰ���ܼ���һ������

public:

	/***********������***********/
	/*��ref��mutex��http://www.cnblogs.com/haippy/p/3237213.html ��*/
	//��������
	void rlock();
	//��������
	void runlock();

	//д������
	void wlock();
	//д������
	void wunlock();


	/***************�ֹ���****************/
	/*��ref��CAS������http://blog.csdn.net/syzcch/article/details/8075830 ��*/
	////��������
	void atomic_rlock();
	//��������
	void atomic_runlock();

	//д������
	void atomic_wlock();
	//д������
	void atomic_wunlock();
};


/*
	CacheContent��Cache�����ݣ���װ�����ݱ���T����ص�������֤���̷߳��ʵİ�ȫ
	Note��
		1.����ͨ����ӹ��캯�������setMode���������������ͣ����������ֹ���������������ʹ��Ĭ�ϲ������Լ򻯺�������
*/
template<typename T>
class CacheContent {
private:
	CacheProperty cproperty;
	T* content;
public:
	//ֱ�ӽ�ָ����Ϊcontent
	CacheContent(T*);
	//����������Ϊcontent
	CacheContent(T&&);

	//��ȡ����
	T& getContent();
	//�޸�����
	void setContent(T*);
	void setContent(T&&);

	//TODO:���������Ա
};


/*
	Cacheʵ������mapһ����Cache���ݽ��в���������cache���ݽ���
	��ȡ��ɾ�ġ�ͨ���ڹ��캯������Ӳ����������set���������޸�
	Cache Mode�����������ֹ������������ȣ�
*/
template<typename K, typename T>
class Cache {
private:
	std::unordered_map<K, CacheContent<T>> content;

public:
	//ʹ��[]����������content
	T& operator[](K& key);
	//��ָ��������Ϊcontent
	void put(K&, T*);
	//ɾ������
	void remove(K&);

	//TODO:���������Ա
};



/********************OPTIONAL*********************/
//Mode�����

/*
	modeһ����������ַ�ʽ���壺
		1.ö������
			enum Mode { Mode1, Mode2, ....... }
			enum Mode { Mode1 = xxx, Mode2 = xxx, .......}
		2.�궨��
			#define Mode1 xxx
			#define Mode2 xxx

	��ά��ģʽ�Ķ��弼�ɣ�
		�ٶ�����Ҫ���һ�������ģʽ����������ά���϶���--��״����ɫ���߿���ʽ��ͬ��ģʽ��
			#define ������ 0x1
			#define ������ 0x2
			#define ���� 0x3

			#define ��ɫ 0x4
			#define ��ɫ 0x8
			#define ��ɫ 0xc

			#define ϸ�� 0x10
			#define �ֱ� 0x20

			��ôһ�������κ�ɫ�ֱߵĴ���ģʽ���ǣ�(������ | ��ɫ | �ֱ�) 
			��Ȼ����ʵ�����˲�ͬά��ʹ�ò�ͬλ�õ�bit����ʾ��ά�ȵ�ģʽ
			��״ʹ����ǰ2λ����ɫʹ����3~4λ���߿�ʹ����5~6λ������ʹ��ģʽ
			��ֱ���ּ򵥡���Ӧ�ģ����ж�һ�������Ƿ��Ǻ�ɫʱ����ʹ�����·�����
						��mode & ��ɫ == ��ɫ��
*/