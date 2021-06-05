#ifndef CLASS_BSTREE_H
#define CLASS_BSTREE_H

#include <stdexcept>
#include <iostream>

#include <ostream>
#include <initializer_list>

#include <memory>
#include <vector>

using std::weak_ptr;
using std::shared_ptr;
using std::vector;

template<typename T>
class BSTree
{
private:
	friend class Iterator;
	struct Branch;
	
	using SPBranch = shared_ptr<Branch>;
	using SPBranches = vector<SPBranch>;
	
	using WPBranch = weak_ptr<Branch>;
	using WPBranches = vector<WPBranch>;
	
	using Paths = vector<size_t>;

	struct Branch
	{
		T data;

		SPBranch left {nullptr};
		SPBranch right {nullptr};

		Branch(T value) : data(value) {}
	};

	SPBranch root {nullptr};
	size_t size {0};

	size_t height_branch(WPBranch branch) const;
	Paths path(T data, WPBranch branch, size_t distance) const;

	SPBranch remove(T data, WPBranch branch);
	SPBranch make_branch(SPBranches& branches, int start, int end);
	SPBranch make_tree(SPBranch branch);

	void print_recursive(WPBranch branch) const;
	void convert2svector(WPBranch branch, SPBranches& branches) const;
	void convert2wvector(WPBranch branch, WPBranches& branches) const;
	
	static void throw_if(bool condition, const char* message);

public:
	class Iterator;
	
	BSTree() = default;
	BSTree(const std::initializer_list<T>& list);
	BSTree(const BSTree<T>& tree) { *this = tree; }

	void push(T data);
	void pop(T data);
	
	const Iterator find(T data) const;
	
	size_t count() const { return size; }
	size_t height() const;

	Paths path(T data) const;
	
	void print() const { print_recursive(root); }
	void balance() { root = make_tree(root); }

	BSTree<T>& operator = (const BSTree<T>& tree);
	
	bool operator == (const BSTree<T>& tree) const;
	bool operator != (const BSTree<T>& tree) const;

	bool operator < (const BSTree<T>& tree) const;
	bool operator > (const BSTree<T>& tree) const;

	bool operator <= (const BSTree<T>& tree) const;
	bool operator >= (const BSTree<T>& tree) const;

	Iterator begin() const;
	Iterator end() const;
	
	class Iterator
	{
	private:
		friend class BSTree<T>;
		WPBranches branches;
		
		size_t begin_id;
		size_t end_id;
		size_t branch_id;

		Iterator(WPBranches&& branches, bool is_begin) :
			branches(branches),
			begin_id(0),
			end_id(branches.size()),
			branch_id(is_begin ? begin_id : end_id) {}

	public:
		Iterator& operator ++ ()
		{
			throw_if(branch_id == end_id, "Iterator out of range!");

			branch_id++;
			return *this;
		}

		Iterator operator ++ (int)
		{
			throw_if(branch_id == end_id, "Iterator out of range!");
			Iterator old = *this;

			branch_id++;
			return old;
		}

		Iterator& operator -- ()
		{
			throw_if(branch_id == begin_id, "Iterator out of range!");

			branch_id--;
			return *this;
		}

		Iterator operator -- (int)
		{
			throw_if(branch_id == begin_id, "Iterator out of range!");
			Iterator old = *this;
			
			branch_id--;
			return old;
		}
		
		const T& operator * () const
		{
			throw_if(branch_id == end_id, "Iterator out of range!");
			return branches[branch_id].lock()->data;
		}

		bool operator == (const Iterator& it) const { return branch_id == it.branch_id; }
		bool operator != (const Iterator& it) const { return branch_id != it.branch_id; }
	};
};

template <typename T>
BSTree<T>::BSTree(const std::initializer_list<T>& list)
{
	for (auto element : list)
		push(element);
}

template <typename T>
void BSTree<T>::push(T data)
{
	SPBranch sp_branch_1 = root;
	SPBranch sp_branch_2 = nullptr;

	while (sp_branch_1.get() != nullptr)
	{
		sp_branch_2 = sp_branch_1;

		if (data < sp_branch_1->data)
			sp_branch_1 = sp_branch_1->left;
		else
			sp_branch_1 = sp_branch_1->right;
	}

	sp_branch_1 = SPBranch(new Branch(data));

	if (sp_branch_2.get() == nullptr)
		root = sp_branch_1;
	else if (sp_branch_1->data < sp_branch_2->data)
		sp_branch_2->left = sp_branch_1;
	else
		sp_branch_2->right = sp_branch_1;

	size++;
}

template <typename T>
void BSTree<T>::pop(T data)
{
	root = remove(data, root);
	size--;
}

template <typename T>
const typename BSTree<T>::Iterator BSTree<T>::find(T data) const
{
	Iterator it = begin();
	Iterator it_end = end();

	while (it != it_end && *it != data)
		++it;

	return it;
}

template <typename T>
size_t BSTree<T>::height() const
{
	if (root.get() == nullptr)
		return 0;

	size_t left_height = height_branch(root->left);
	size_t right_height = height_branch(root->right);

	return ((left_height > right_height) ? left_height : right_height) + 1;
}

template <typename T>
typename BSTree<T>::Paths BSTree<T>::path(T data) const
{
	Paths paths;
	
	if (root.get() == nullptr)
	{
		paths.push_back(0);
		return paths;
	}
	
	if (root->data == data)
		paths.push_back(0);

	for (auto& element : path(data, root->left, 1))
		paths.push_back(element);
	
	for (auto& element : path(data, root->right, 1))
		paths.push_back(element);

	return paths;
}

template <typename T>
typename BSTree<T>::Iterator BSTree<T>::begin() const
{
	WPBranches branches;
	convert2wvector(root, branches);
	return Iterator(std::move(branches), true);
}

template <typename T>
typename BSTree<T>::Iterator BSTree<T>::end() const
{
	WPBranches branches;
	convert2wvector(root, branches);
	return Iterator(std::move(branches), false);
}

template <typename T>
BSTree<T>& BSTree<T>::operator = (const BSTree<T>& tree)
{
	if (this == &tree)
		return *this;

	WPBranches branches;
	convert2wvector(tree.root, branches);

	for (auto& element : branches)
		push(element.lock()->data);

	return *this;
}

template <typename T>
bool BSTree<T>::operator == (const BSTree<T>& tree) const
{
	if (this == &tree)
		return true;
	
	if (size != tree.size)
		return false;

	Iterator this_it = begin();
	Iterator this_it_end = end();
	Iterator tree_it = tree.begin();

	while (this_it != this_it_end)
		if (*this_it++ != *tree_it++)
			return false;

	return true;
}

template <typename T>
bool BSTree<T>::operator != (const BSTree<T>& tree) const
{
	return !(*this == tree);
}

template <typename T>
bool BSTree<T>::operator < (const BSTree<T>& tree) const
{
	if (this == &tree)
		return false;
	
	Iterator this_it = begin();
	Iterator this_it_end = end();
	
	Iterator tree_it = tree.begin();
	Iterator tree_it_end = tree.end();

	while (this_it != this_it_end && tree_it != tree_it_end)
	{
		const T& this_value = *this_it++;
		const T& tree_value = *tree_it++;
		
		if (this_value != tree_value)
			return this_value < tree_value;
	}

	return size < tree.size;
}

template <typename T>
bool BSTree<T>::operator > (const BSTree<T>& tree) const
{
	return !(*this < tree) && *this != tree;
}

template <typename T>
bool BSTree<T>::operator <= (const BSTree<T>& tree) const
{
	return *this < tree || *this == tree;
}

template <typename T>
bool BSTree<T>::operator >= (const BSTree<T>& tree) const
{
	return *this > tree || *this == tree;
}

template <typename T>
size_t BSTree<T>::height_branch(WPBranch branch) const
{
	if (branch.expired())
		return 0;

	size_t left_height = height_branch(branch.lock()->left);
	size_t right_height = height_branch(branch.lock()->right);

	return ((left_height > right_height) ? left_height : right_height) + 1;
}

template <typename T>
typename BSTree<T>::Paths BSTree<T>::path(T data, WPBranch branch, size_t distance) const
{
	Paths paths;

	if (branch.expired())
	{
		paths.push_back(0);
		return paths;
	}
	
	SPBranch sp_branch = branch.lock();

	if (sp_branch->data == data)
		paths.push_back(distance);

	for (auto& element : path(data, sp_branch->left, distance + 1))
		paths.push_back(element);

	for (auto& element : path(data, sp_branch->right, distance + 1))
		paths.push_back(element);
	
	return paths;
}

template <typename T>
typename BSTree<T>::SPBranch BSTree<T>::remove(T data, WPBranch branch)
{
	throw_if(branch.expired(), "Branch is destroyed!");

	SPBranch sp_branch = branch.lock();
	WPBranch wp_branch;

	if (data < sp_branch->data)
		sp_branch->left = remove(data, sp_branch->left);
	else if (data > sp_branch->data)
		sp_branch->right = remove(data, sp_branch->right);
	else if (sp_branch->left.get() != nullptr && sp_branch->right.get() != nullptr)
	{
		while (wp_branch.lock()->left.get() != nullptr)
			wp_branch = wp_branch.lock()->left;

		sp_branch->data = wp_branch.lock()->data;
		sp_branch->right = remove(sp_branch->data, sp_branch->right);
	}
	else
	{
		wp_branch = branch;

		if (sp_branch->left.get() == nullptr)
			branch = sp_branch->right;
		else if (sp_branch->right.get() == nullptr)
			branch = sp_branch->left;

		wp_branch.lock().reset();
	}

	return branch.lock();
}

template <typename T>
typename BSTree<T>::SPBranch BSTree<T>::make_branch(SPBranches& branches, int start, int end)
{
	if (start > end)
		return SPBranch();

	int mid = (start + end) / 2;
	SPBranch current = branches[mid];

	current->left = make_branch(branches, start, mid - 1);
	current->right = make_branch(branches, mid + 1, end);

	return current;
}

template <typename T>
typename BSTree<T>::SPBranch BSTree<T>::make_tree(SPBranch branch)
{
	SPBranches branches;
	convert2svector(branch, branches);

	return make_branch(branches, 0, branches.size() - 1);
}

template <typename T>
void BSTree<T>::print_recursive(WPBranch branch) const
{
	if (branch.expired())
		return;

	SPBranch sp_branch = branch.lock();
	cout << sp_branch->data << "\n";

	print_recursive(sp_branch->left);
	print_recursive(sp_branch->right);
}

template <typename T>
void BSTree<T>::convert2svector(WPBranch branch, SPBranches& branches) const
{
	if (branch.expired())
		return;

	SPBranch sp_branch = branch.lock();

	convert2svector(sp_branch->left, branches);
	branches.push_back(sp_branch);
	convert2svector(sp_branch->right, branches);
}

template <typename T>
void BSTree<T>::convert2wvector(WPBranch branch, WPBranches& branches) const
{
	if (branch.expired())
		return;

	SPBranch sp_branch = branch.lock();

	convert2wvector(sp_branch->left, branches);
	branches.push_back(sp_branch);
	convert2wvector(sp_branch->right, branches);
}

template <typename T>
void BSTree<T>::throw_if(bool condition, const char* message)
{
	if (condition)
		throw std::runtime_error(message);
}

template <typename T>
std::ostream& operator << (std::ostream& out, const BSTree<T>& tree)
{
	tree.print();
	return out;
}

#endif