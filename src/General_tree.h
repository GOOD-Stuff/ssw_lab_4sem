#ifndef general_tree_H
#define general_tree_H
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class general_tree {

private:
	class node {
	public:
		T value{ 0 };
		std::vector<node*> points;

		explicit node(T data) {
			value = data;
			points.clear();
		}
		~node() = default;
	};

	std::vector<node*> forfind;
	std::vector<int> forhight;
	node* root{ nullptr };
	size_t size{ 0 };
	void PrintPreorder(const node* p);
	void FindNode(T data, node* p);
	void FindParent(node* p);
	size_t NodeHeight(const node* p);
	int NodePath(const node* p, T data);
	bool ComparisonEqually(const node* p, const node* p1);
	bool ComparisonMore(const node* p, const node* p1);
	void DeleteNode(node* p);
	void recursiveWork(node* root, std::function<void(node*, int)> work, int height = 0);
public:
	general_tree() = default;
	~general_tree() {
		DeleteNode(root);
		size = 0;
		root = nullptr;
	}

	general_tree(const std::initializer_list<T>& list);
	void Push(node* p, T data);
	void Push(T data);
	void Print();
	void Pop(node* p);
	std::vector<general_tree<T>*> split();
	std::variant<int, std::vector<int>> Path(T data);

	size_t Count() {
		return size;
	}
	size_t Height();

	std::variant<node*, std::vector<node*>> Find(T data) {
		if (size == 0) throw std::out_of_range("tree is empty");
		forfind.clear();
		FindNode(data, root);
		if (forfind.empty()) throw std::out_of_range(" tree is haven't this element");
		if (forfind.size() == 1) return forfind.front();
		return forfind;
	};

	void swap(general_tree<T>& m);

	bool operator == (general_tree<T> const& m);
	bool operator != (general_tree<T> const& m) {
		return !(this->operator==(m));
	};
	bool operator > (general_tree<T> const& m);
	bool operator < (general_tree<T> const& m) {
		return !(this->operator>=(m));
	};
	bool operator >= (general_tree<T> const& m) {
		return (this->operator>(m) || this->operator==(m));
	};
	bool operator <= (general_tree<T> const& m) {
		return !(this->operator>(m));
	};

	friend std::ostream& operator<<(std::ostream& out, general_tree<T>& tr) {
		tr.recursiveWork(tr.root, [](node* n, int h)
		{
			std::cout << ' ' << std::string(h, '.') << n->value;
		});
		return out;
	}
};

template<class T>
general_tree<T>::general_tree(const std::initializer_list<T>& list) {
	for (int i = 0; i < list.size(); i++) {
		if (i == 0) Push(list.begin()[i]);
		else Push(root, list.begin()[i]);
	}
}

template<class T>
void general_tree<T>::Push(general_tree::node* p, T data) {
	if (size == 0) root = new node(data);
	else {
		p->points.push_back(new node(data));
	}
	size++;
}

template<class T>
void general_tree<T>::Push(T data) {
	if (size != 0) throw std::out_of_range("tree is not empty");
	else root = new node(data);
	size++;
}

template<class T>
void general_tree<T>::Print() {
	if (size == 0) throw std::out_of_range("tree is empty");
	std::cout << std::endl;
	PrintPreorder(root);
	std::cout << std::endl;
}

template<class T>
void general_tree<T>::PrintPreorder(const node* p) {
	if (p == nullptr) {
		std::cout << ".";
		return;
	}
	std::cout << " " << p->value << " ";
	for (int i = 0; i < p->points.size(); i++) {
		PrintPreorder(p->points.begin()[i]);
		std::cout << ".";
	}

}

template<class T>
void general_tree<T>::FindNode(T data, general_tree::node* p) {
	if (p == nullptr) return;
	if (p->value == data) forfind.push_back(p);
	for (int i = 0; i < p->points.size(); i++) {
		FindNode(data, p->points.begin()[i]);
	}
}

template<class T>
void general_tree<T>::Pop(node* p) {
	if (size == 0) throw std::out_of_range("tree is empty");
	if (p->points.size() != 0) throw std::out_of_range("this element is not list");
	forfind.clear();
	forfind.push_back(p);
	FindParent(root);
}

template<class T>
std::vector<general_tree<T>*> general_tree<T>::split() {
	std::vector<general_tree<T>*> result{ new general_tree<T>(),new general_tree<T>() };
	int index = 0;

	int counter = 0;
	const int part = root->points.size() / 2;

	recursiveWork(root, [part, &counter, &index, &result](node* n, int h)
	{
		if (h == 1) {
			counter++;
			if (counter > part) {
				index++;
				counter = 0;
			}
		}
		general_tree<T>* r = result[index];
		r->Push(r->root, n->value);
	});
	return result;
}

template<class T>
void general_tree<T>::FindParent(node* p) {
	for (int i = 0; i < p->points.size(); i++) {
		if (p->points.begin()[i] == forfind.begin()[0]) {
			forfind.push_back(p);
			auto res = p->points;
			res.erase(res.begin()[i]);
			break;
		}
		FindParent(p->points.begin()[i]);
	}
}

template<class T>
size_t general_tree<T>::NodeHeight(const general_tree::node* p) {
	if (p == nullptr) return 0;
	size_t maxHeight = 0;
	for (int i = 0; i < p->points.size(); i++) {
		size_t height = NodeHeight(p->points.begin()[i]);
		if (height > maxHeight) maxHeight = height;
	}
	return maxHeight + 1;
}

template<class T>
size_t general_tree<T>::Height() {
	if (size == 0) throw std::out_of_range("tree is empty");
	if (size == 1) return 0;
	return NodeHeight(root);
}

template<class T>
std::variant<int, std::vector<int>> general_tree<T>::Path(T data) {
	if (size == 0) throw std::out_of_range("tree is empty");
	forhight.clear();
	NodePath(root, data);
	if (forhight.size() == 0) throw std::out_of_range("tree is haven't this element");
	if (forhight.size() == 1) return forhight.begin()[0];
	else return forhight;
}

template<class T>
int general_tree<T>::NodePath(const node* p, T data) {
	int height = 0;
	for (int i = 0; i < p->points.size(); i++) {
		height = NodePath(p->points.begin()[i], data);
	}
	height++;
	if (p->value == data) forhight.push_back(height + 1);
	return height;
}

template<class T>
void general_tree<T>::swap(general_tree<T>& m) {
	node* cur = this->root;
	m.root = this->root;
	this->root = cur;
}

template<class T>
bool general_tree<T>::operator==(const general_tree<T>& m) {
	if (this->size == 0 || m.size == 0) throw std::out_of_range("tree is empty");
	return ComparisonEqually(this->root, m.root);
}

template<class T>
bool general_tree<T>::operator>(const general_tree<T>& m) {
	if (this->size == 0 || m.size == 0) throw std::out_of_range("tree is empty");
	return ComparisonMore(this->root, m.root);
}

template<class T>
bool general_tree<T>::ComparisonEqually(const general_tree::node* p, const general_tree::node* p1) {
	if (p == nullptr && p1 == nullptr) return true;
	if (p == nullptr || p1 == nullptr) return false;
	bool ans = true;
	ans = (p->value == p1->value);
	if (!ans) return false;
	ans = p->points.size() == p1->points.size();
	if (ans) {
		for (int i = 0; i < p->points.size(); i++) {
			ans = ComparisonEqually(p->points.begin()[i], p1->points.begin()[i]);
		}
	}
	else return false;
	return ans;
}

template<class T>
bool general_tree<T>::ComparisonMore(const general_tree::node* p, const general_tree::node* p1) {
	if (p != nullptr && p1 == nullptr) return true;
	if (p == nullptr && p1 != nullptr) return false;
	if (p == nullptr && p1 == nullptr) return true;
	bool ans = true;
	ans = (p->value >= p1->value);
	if (!ans) return false;
	if (p->points.size() > p1->points.size()) return true;
	ans = p->points.size() == p1->points.size();
	if (ans) {
		for (int i = 0; i < p->points.size(); i++) {
			ans = ComparisonEqually(p->points.begin()[i], p1->points.begin()[i]);
		}
	}
	else return false;
	return ans;
}

template<class T>
void general_tree<T>::DeleteNode(general_tree::node* p) {
	if (p->points.size() == 0) {
		delete p;
		return;
	}
	for (int i = 0; i < p->points.size(); i++) {
		DeleteNode(p->points.begin()[i]);
	}
	p->points.clear();
	delete p;
}

template<class T>
void general_tree<T>::recursiveWork(node* root, std::function<void(node*, int)> work, int height) {
	work(root, height);
	for (node* p : root->points) {
		recursiveWork(p, work, height + 1);
	}
}

#endif
