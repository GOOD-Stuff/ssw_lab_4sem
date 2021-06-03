#ifndef BIN_TREE_H
#define BIN_TREE_H
#include <iostream>
#include <vector>
#include <variant>
#include <functional>
#include <vector>

using namespace std;

template <class T>
class bin_tree {
private:
	class node {
	public:

		node* ptrLeft{ nullptr };
		node* ptrRight{ nullptr };
		T value{ 0 };

		explicit node(T data, node* linkLeft = nullptr, node* linkRight = nullptr) {
			ptrLeft = linkLeft;
			ptrRight = linkRight;
			value = data;
		}
		~node() = default;
	};

	node* root{ nullptr };
	size_t size{ 0 };
	void PrintPreorder(const node* head);
	size_t NodeHeight(const node* head);
	size_t WidthNode(const node* p);
	bool ComparisonEqually(const node* p, const node* p1);
	bool ComparisonMore(const node* p, const node* p1);


	int BalanceFactor(const node* p) {
		return NodeHeight(p->ptrRight) - NodeHeight(p->ptrLeft);
	};

	node* RotateRight(node* p) {
		node* q = p->ptrLeft;
		p->ptrLeft = q->ptrRight;
		q->ptrRight = p;
		return q;
	}

	node* RotateLeft(node* q) {
		node* p = q->ptrRight;
		q->ptrRight = p->ptrLeft;
		p->ptrLeft = q;
		return p;
	}

	node* BalanceNode(node* p) {
		if (BalanceFactor(p) == 2)
		{
			if (BalanceFactor(p->ptrRight) < 0)
				p->ptrRight = RotateRight(p->ptrRight);
			return RotateLeft(p);
		}
		if (BalanceFactor(p) == -2)
		{
			if (BalanceFactor(p->ptrLeft) > 0)
				p->ptrLeft = RotateLeft(p->ptrLeft);
			return RotateRight(p);
		}
		return p;
	}

	node* BalanceBranch(node* p) {
		if (p == nullptr) return nullptr;
		p->ptrLeft = BalanceBranch(p->ptrLeft);
		p->ptrRight = BalanceBranch(p->ptrRight);
		p = BalanceNode(p);
		return p;
	}

	void DeleteTree(node* p);
	void recursiveWork(node* root, std::function<void(node*, int)> work, int height = 0);

public:
	bin_tree() = default;
	bin_tree(const std::initializer_list<T>& list);
	~bin_tree() {
		DeleteTree(root);
	}
	void Push(T data);
	void Print();
	void Pop(T data);
	std::vector<bin_tree<T>*> split();
	size_t Height();
	std::variant<int, std::vector<int>> Path(T data);

	node* Find(const T data) {
		node* current = root;
		while (current != nullptr) {
			if (current->value == data) return current;
			if (data < current->value) current = current->ptrLeft;
			else current = current->ptrRight;
		}
		throw std::out_of_range("tree haven't element with this value");
	}

	size_t Count() {
		return size;
	}

	void Swap(bin_tree<T>& m) {
		node* p = this->root;
		this->root = m.root;
		m.root = p;
	}

	bool operator == (bin_tree<T> const& m);
	bool operator != (bin_tree<T> const& m) {
		return !(this->operator==(m));
	};
	bool operator > (bin_tree<T> const& m);
	bool operator < (bin_tree<T> const& m) {
		return !(this->operator>=(m));
	};
	bool operator >= (bin_tree<T> const& m) {
		return (this->operator>(m) || this->operator==(m));
	};
	bool operator <= (bin_tree<T> const& m) {
		return !(this->operator>(m));
	};

	friend std::ostream& operator<<(std::ostream& out, bin_tree<T>& tr) {
		tr.recursiveWork(tr.root, [](node* n, int h)
		{
			std::cout << ' ' << std::string(h, '.') << n->value;
		});
		return out;
	}

};


template<class T>
bin_tree<T>::bin_tree(const std::initializer_list<T>& list) {
	for (int i = 0; i < list.size(); i++) {
		Push(list.begin()[i]);
	}
}

template<class T>
void bin_tree<T>::Push(T data) {
	if (root == nullptr) {
		root = new node(data);
	}
	else {
		node* current = root;
		node* previous = root;
		while (current != nullptr) {
			previous = current;
			if (data < current->value) current = current->ptrLeft;
			else current = current->ptrRight;
		}
		if (data < previous->value) previous->ptrLeft = new node(data);
		else previous->ptrRight = new node(data);
	}
	size++;
	root = BalanceBranch(root);
}

template<class T>
void bin_tree<T>::Print() {
	if (size == 0) throw std::out_of_range("tree is empty");
	std::cout << std::endl;
	PrintPreorder(root);
	std::cout << std::endl;
}

template<class T>
void bin_tree<T>::PrintPreorder(const bin_tree::node* head) {
	if (head == nullptr) {
		std::cout << ".";
		return;
	}
	std::cout << head->value << " ";
	PrintPreorder(head->ptrLeft);
	PrintPreorder(head->ptrRight);
}

template<class T>
void bin_tree<T>::Pop(T data) {
	if (size == 0) throw std::out_of_range("tree is empty");
	node* current = root;
	node* previous = root;
	while (current != nullptr) {
		if (current->value != data) previous = current;
		if (data < current->value) current = current->ptrLeft;
		else {
			if (data > current->value) current = current->ptrRight;
			else break;
		}
	}
	if (current == nullptr) throw std::out_of_range("tree haven't element with this value");
	if (current->ptrRight == nullptr && current->ptrLeft == nullptr) {
		delete current;
		if (data < previous->value) previous->ptrLeft = nullptr;
		else previous->ptrRight = nullptr;
	}
	else throw std::out_of_range("tree haven't list with this value");

	size--;
	if (size == 0) root = nullptr;
	else root = BalanceBranch(root);
}

template<class T>
std::vector<bin_tree<T>*> bin_tree<T>::split() {
	std::vector<bin_tree<T>*> result{ new bin_tree<T>(),new bin_tree<T>() };

	int index = -1;
	recursiveWork(root, [&index, &result](node* n, int h)
	{
		if (h == 1)
			index++;
		result[index < 0 ? 0 : index]->Push(n->value);
	});
	return result;
}

template<class T>
size_t bin_tree<T>::NodeHeight(const bin_tree::node* head) {
	size_t s = 0, l = 0, r = 0;
	if (head != nullptr) {
		l = NodeHeight(head->ptrLeft);
		r = NodeHeight(head->ptrRight);
		s = ((l > r) ? l : r) + 1;
	}
	return s;
}

template<class T>
size_t bin_tree<T>::Height() {
	if (size == 0) throw std::out_of_range("tree is empty");
	if (size == 1) return 0;
	return NodeHeight(root);
}

template<class T>
std::variant<int, std::vector<int>> bin_tree<T>::Path(T data) {
	std::vector<int> ans;
	ans.clear();
	int height = 0;
	node* current = root;
	while (current != nullptr) {
		if (data < current->value) current = current->ptrLeft;
		else {
			if (data > current->value) current = current->ptrRight;
			else {
				ans.push_back(height);
				current = current->ptrRight;
			}
		}
		height++;
	}
	if (ans.empty()) throw std::out_of_range("tree is haven't this element");
	if (ans.size() == 1) return ans.front();
	return ans;
}


template<class T>
void bin_tree<T>::DeleteTree(bin_tree::node* p) {
	if (p != nullptr) {
		DeleteTree(p->ptrLeft);
		DeleteTree(p->ptrRight);
		delete p;
		p = nullptr;
	}
	else return;
}

template<class T>
void bin_tree<T>::recursiveWork(node* root, std::function<void(node*, int)> work, int height) {
	work(root, height);
	if (root->ptrLeft)
		recursiveWork(root->ptrLeft, work, height + 1);
	if (root->ptrRight)
		recursiveWork(root->ptrRight, work, height + 1);
}

template<class T>
bool bin_tree<T>::operator==(const bin_tree<T>& m) {
	if (this->size == 0 || m.size == 0) throw std::out_of_range("tree is empty");
	return ComparisonEqually(this->root, m.root);


}

template<class T>
bool bin_tree<T>::operator>(const bin_tree<T>& m) {
	if (this->size == 0 || m.size == 0) throw std::out_of_range("tree is empty");
	return ComparisonMore(this->root, m.root);
}

template<class T>
size_t bin_tree<T>::WidthNode(const bin_tree::node* p) {
	size_t sum = 0;
	if (p->ptrLeft != nullptr) sum++;
	if (p->ptrRight != nullptr) sum++;
	return sum;
}

template<class T>
bool bin_tree<T>::ComparisonEqually(const bin_tree::node* p, const bin_tree::node* p1) {
	if (p == nullptr && p1 == nullptr) return true;
	if (p == nullptr || p1 == nullptr) return false;
	bool ans = true;
	ans = (p->value == p1->value);
	if (!ans) return false;
	ans = WidthNode(p) == WidthNode(p1);
	if (ans) {
		ans = ComparisonEqually(p->ptrLeft, p1->ptrLeft);
		ans = ComparisonEqually(p->ptrRight, p1->ptrRight);
	}
	else return false;
	return ans;
}

template<class T>
bool bin_tree<T>::ComparisonMore(const bin_tree::node* p, const bin_tree::node* p1) {
	if (p != nullptr && p1 == nullptr) return true;
	if (p == nullptr && p1 != nullptr) return false;
	if (p == nullptr && p1 == nullptr) return false;
	bool ans = true;
	ans = (p->value >= p1->value);
	if (!ans) return false;
	ans = WidthNode(p) >= WidthNode(p1);
	if (ans) {
		ans = ComparisonMore(p->ptrLeft, p1->ptrLeft);
		ans = ComparisonMore(p->ptrRight, p1->ptrRight);
	}
	else return false;
	return ans;
}


#endif
