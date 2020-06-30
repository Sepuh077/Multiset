#include "MultiSet.h"
#include <algorithm>
#include <iostream>

using namespace std;

MultiSet::MultiSet() {
	n = 0;
	p = new int[1];
	p[0] = 0;
}
MultiSet::MultiSet(int* a, int n) {
	int ma = 0;
	for (int i = 0; i < n; i++) {
		if (i == 0 || ma < a[i])
			ma = a[i];
	}
	this->n = ma + 1;
	p = new int[this->n];
	for (int i = 0; i < this->n; i++)
		p[i] = 0;
	for (int i = 0; i < n; i++) {
		p[a[i]]++;
	}
}
MultiSet::MultiSet(const MultiSet& a) {
	n = a.n;
	p = new int[n];
	for (int i = 0; i < n; i++)
		p[i] = a.p[i];
}
MultiSet& MultiSet::operator=(const MultiSet& a) {
	if (*this == a)
		return *this;
	n = a.n;
	delete[] p;
	p = new int[n];
	for (int i = 0; i < n; i++)
		p[i] = a.p[i];
	return *this;
}
bool MultiSet::operator==(const MultiSet& a) const {
	if (n != a.n)
		return 0;
	for (int i = 0; i < n; i++) {
		if (p[i] != a.p[i])
			return 0;
	}
	return 1;
}
bool MultiSet::operator!=(const MultiSet& a) const {
	if (*this == a)
		return 0;
	return 1;
}
MultiSet& MultiSet::operator|=(const MultiSet& a) {
	if (a.n > n) {
		int* b = new int[n];
		for (int i = 0; i < n; i++)
			b[i] = p[i];
		delete[] p;
		p = new int[a.n];
		for (int i = 0; i < a.n; i++) {
			if (i < n)
				p[i] = b[i];
			else
				p[i] = 0;
		}
		n = a.n;
	}
	for (int i = 0; i < a.n; i++) {
		p[i] = std::max(p[i], a.p[i]);
	}
	cal_max(*this);
	return *this;
}
MultiSet MultiSet::operator|(const MultiSet& a) const {
	MultiSet b(*this);
	b |= a;
	cal_max(b);
	return b;
}
MultiSet& MultiSet::operator-=(const MultiSet& a) {
	int l = std::min(a.n, n);
	for (int i = 0; i < l; i++) {
		p[i] <= a.p[i] ? p[i] = 0 : p[i] -= a.p[i];
	}
	cal_max(*this);
	return *this;
}
MultiSet MultiSet::operator-(const MultiSet& a) const {
	MultiSet b(*this);
	b -= a;
	cal_max(b);
	return b;
}
MultiSet& MultiSet::operator&=(const MultiSet& a) {
	for (int i = 0; i < n; i++) {
		int x;
		i < a.n ? x = a.p[i] : x = 0;
		p[i] = std::min(p[i], x);
	}
	cal_max(*this);
	return *this;
}
MultiSet MultiSet::operator&(const MultiSet& a) const {
	MultiSet b(*this);
	b &= a;
	cal_max(b);
	return b;
}

void cal_max(MultiSet& a) {
	int x = a.n - 1;
	while (a.p[x] == 0 && x > 0) {
		x--;
	}
	int* b = new int[x + 1];
	for (int i = 0; i <= x; i++)
		b[i] = a.p[i];
	delete[] a.p;
	a.p = new int[x + 1];
	for (int i = 0; i <= x; i++)
		a.p[i] = b[i];
	delete[] b;
	a.n = x + 1;
}
int MultiSet::add_member(int k) {

	if (k >= n) {
		int* b = new int[n];
		for (int i = 0; i < n; i++)
			b[i] = p[i];
		delete[] p;
		p = new int[k + 1];
		for (int i = 0; i < k; i++) {
			i < n ? p[i] = b[i] : p[i] = 0;
		}
		p[k] = 1;
		n = k + 1;
	}
	else
		p[k]++;
	return p[k];
}
int MultiSet::del_member(int k) {
	if (k >= n)
		return 0;
	if (p[k] > 0)
		--p[k];
	return p[k];
}
int MultiSet::count(int k) const {
	return k >= n ? 0 :p[k];
}
bool MultiSet::in(const MultiSet& a) const {
	MultiSet b;
	b = (*this) | a;
	if (b == a)
		return 1;
	else
		return 0;
}


istream& operator>>(istream& in, MultiSet& a) {
	int n, ma;
	in >> n;
	int* p = new int[n];
	for (int i = 0; i < n; i++) {
		in >> p[i];
		if (i == 0 || ma < p[i])
			ma = p[i];
	}
	a.n = ma + 1;
	a.p = new int[a.n];
	for (int i = 0; i < a.n; i++)
		a.p[i] = 0;
	for (int i = 0; i < n; i++) {
		a.p[p[i]]++;
	}
	return in;
}
ostream& operator<<(ostream& out, const MultiSet& a) {
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.p[i]; j++) {
			out << i << " ";
		}
	}
	return out;
}