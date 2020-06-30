#pragma once
#include <iostream>

using namespace std;

class MultiSet
{
	int n;
	int* p;
	friend istream& operator>>(istream& in, MultiSet& a);
	friend ostream& operator<<(ostream& out, const MultiSet& a);
	friend void cal_max(MultiSet& a);
public:
	MultiSet();
	MultiSet(int* a, int n);
	MultiSet(const MultiSet& a);
	MultiSet& operator=(const MultiSet& a);
	bool operator==(const MultiSet& a) const;
	bool operator!=(const MultiSet& a) const;
	MultiSet& operator|=(const MultiSet& a);
	MultiSet operator|(const MultiSet& a) const;
	MultiSet& operator-=(const MultiSet& a);
	MultiSet operator-(const MultiSet& a) const;
	MultiSet& operator&=(const MultiSet& a);
	MultiSet operator&(const MultiSet& a) const;
	int add_member(int k);
	int del_member(int k);
	int count(int k) const;
	bool in(const MultiSet& a) const;
	~MultiSet() {
		delete[] p;
	}
};