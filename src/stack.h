#ifndef CLASS_STACK_INCLUDED_H
#define CLASS_STACK_INCLUDED_H

#include "vector.h"

template <typename T>
class stack : public vector<T>
{
public:
	T& at(int index) const = delete;
	
	friend std::ostream& operator << (std::ostream& out, const stack<T>& st)
	{
		for (int i = st.count - 1; i >= 0; i--) {
			out << st.data[i] << "\n";
		}
		
		return out;
	}
};

#endif