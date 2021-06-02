#ifndef CLASS_BSTREE_H
#define CLASS_BSTREE_H

#include <stdexcept>
#include <iostream>
#include <ostream>
#include <initializer_list>

template <typename T>
class BSTree
{
private:
	static void throw_if(bool condition, const char* message)
	{
		if (condition)
			throw std::runtime_error(message);
	}

	struct Branch
	{
		T data;

		Branch* left {nullptr};
		Branch* right {nullptr};

		Branch(T value) : data(value) {}
	};

	Branch* root {nullptr};
	size_t size {0};

	void add_to_branch(T& data, Branch*& branch)
	{
		if (branch == nullptr)
			branch = new Branch(data);
		else
			add_to_branch(data, (data < branch->data) ? branch->left : branch->right);
	}

	void print_recursive(Branch* branch) const
	{
		if (branch == nullptr)
			return;
		
		std::cout << branch->data << "\n";

		print_recursive(branch->left);
		print_recursive(branch->right);
	}

	void clear_branch(Branch*& branch)
	{
		if (branch == nullptr)
			return;

		clear_branch(branch->left);
		clear_branch(branch->right);

		delete branch;
		branch = nullptr;
	}

public:
	class Iterator;
	friend class Iterator;
	
	BSTree() = default;

	BSTree(const std::initializer_list<T>& list)
	{
		for (auto& element : list)
			push(element);
	}

	~BSTree() { clear(); }
	
	void push(T data)
	{
		add_to_branch(data, root);
		size++;
	}

	void pop()
	{
		
	}

	Iterator begin() const { return Iterator(root, this); }

	Iterator end() const { return Iterator(nullptr, this); }
	
	Iterator find() const
	{
		
	}

	size_t count() const { return size; }

	bool empty() const { return size == 0; }
	
	size_t height() const
	{
		
	}

	size_t path() const
	{
		
	}

	void print() const { print_recursive(root); }

	bool balance()
	{
		
	}

	void clear() { clear_branch(root); }
	
	bool operator == (const BSTree<T>& tree) const
	{
		return false;
	}
	
	bool operator != (const BSTree<T>& tree) const
	{
		return false;
	}

	bool operator < (const BSTree<T>& tree) const
	{
		return false;
	}
	
	bool operator > (const BSTree<T>& tree) const
	{
		return false;
	}
	
	bool operator <= (const BSTree<T>& tree) const
	{
		return false;
	}
	
	bool operator >= (const BSTree<T>& tree) const
	{
		return false;
	}

	class Iterator
	{
	private:
		friend class BSTree<T>;
		
		Branch* current_branch {nullptr};
		const BSTree<T>* current_tree {nullptr};
		
		Iterator(Branch* branch, const BSTree<T>* tree) : current_branch(branch), current_tree(tree) {}

		void has_errors_control() const
		{
			throw_if(current_tree == nullptr, "The iterator is not bound to a tree!");
			throw_if(current_tree->size == 0, "The iterated tree is empty!");
			throw_if(current_branch == nullptr, "Trying to work with empty pointer!");
		}
	
	public:
		Iterator() = default;

		Iterator& operator ++ ()
		{
			has_errors_control();
			return Iterator();
		}

		Iterator operator ++ (int)
		{
			has_errors_control();
			return Iterator();
		}

		T& operator * ()
		{
			has_errors_control();
			return current_branch->data;
		}

		bool operator == (const Iterator& it) const { return current_branch == it.current_branch; }
		bool operator != (const Iterator& it) const { return current_branch != it.current_branch; }
	};
};

#endif