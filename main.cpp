#include<stdio.h>

template <typename T0,typename T1>
class Compare {
public:
	T0 Min(const T0& a, const T1& b) {
		return a < b ? a : b;
	};
};
int main() {
	
	

	return 0;
}