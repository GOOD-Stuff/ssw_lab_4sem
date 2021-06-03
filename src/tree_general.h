#ifndef TREE__GENERAL
#define TREE__GENERAL
#include <iostream>
template <typename T>
struct tree_g
{
	T data;
	tree_g<T>* son;
	tree_g<T>* brother;
	tree_g()
	{
		this->data = 0;
		this->son = nullptr;
		this->brother = nullptr;

	}
	tree_g(T data)
	{
		this->data = data;
		this->son = nullptr;
		this->brother = nullptr;
	}
};

template <typename T>
class tree_general
{
private://����
	tree_g<T>* unit;

private://������
	void delete_tree(tree_g<T>* unit)
	{
		if (unit == nullptr)
			return;
		delete_tree(unit->son);
		delete_tree(unit->brother);
		delete unit;
	}
	void push(tree_g<T>* unit, T node, T data)
	{
		//����� ����
		if (unit == nullptr)
		{
			this->unit = new tree_g<T>(data);
			return;
		}
		unit = find_element(unit, node);
		//��������� � ���� ����� ����
		if (unit->son == 0) {
			unit->son = new tree_g<T>(data);
			return;
		}
		unit = unit->son;
		//����� ���������� ����� ����� ����
		while(unit->brother != nullptr)
			unit = unit->brother;
		//���������� �������� � ������ ���������� �����
		unit->brother = new tree_g<T>(data);
		return;
		std::cout << unit->data << std::endl;
	}
	T pop(tree_g<T>* unit, T element)
	{
		T data_element = 0;
		tree_g<T>* local_element;
		tree_g<T>* before_local;
		tree_g<T>* local;
		//���������� �� �������
		local_element = find_element(unit, element);
		before_local = find_unit_before_son(unit, local_element);
		//����� ���� ������ �� ���� ������: ��� ��� ����
		if (before_local == 0)
		{
			before_local = find_unit_before_brother(unit, local_element);
			if (before_local == 0)
			{
				//��������� ������ �������� ������ ������?
				if (local_element == unit)
				{
					this->unit = unit->son;
					data_element = local_element->data;
					delete local_element;
					return data_element;
				}
			}
			else 
			{
				//���� �� ������� � ���������� ��������?
				if (local_element->son != 0)
				{//��
					//���� �� ��� � ����������� ��������?
					if (before_local->son != 0)
					{//��
						local = before_local->son;
						//������� ���������� ����� ����� ����
						while (local->brother == 0) {
							local = local->brother;
						}
						local->brother = local_element->son;
					}
					else
					{//���
						before_local->son = local_element->son;
					}
				}
				//���� �� ���� � ���������� ��������
				if (local_element->brother != 0)
				{
					before_local->brother = local_element->brother;
				}
				else
				{
					before_local->brother = nullptr;
				}
				local_element->son = nullptr;
				local_element->brother = nullptr;
				data_element = local_element->data;
				delete local_element;
			}
		}
		else
		{
			//���� �� ���� � ���������� ��������
			if (local_element->brother != 0)
			{//��
				//���� �� ��� � ���������� ��������
				if (local_element->son != 0)
				{//��
					local = local_element->brother;
					//���� �� ��� � ����� ���������� ��������
					if (local->son != 0)
					{//��
						local = local->son;
						while (local->brother != 0)
							local = local->brother;
						local->brother = local_element->son;
					}
					else
					{//���
						local->son = local_element->son;
					}
				}
				before_local->son = local_element->brother;
			}
			else
			{//���
				//���� �� ��� � ���������� ��������
				if (local_element->son != 0)
				{
					before_local->son = local_element->son;
				}
				else
				{
					before_local->son = nullptr;
				}
			}
		//�������� ��������
		local_element->son = nullptr;
		local_element->brother = nullptr;
		data_element = local_element->data;
		delete local_element;
		}
		return data_element;

	}

	tree_g<T>* find_unit_before_brother(tree_g<T>* unit, tree_g<T>* element)
	{
		tree_g<T>* local = nullptr;
		if (unit == nullptr)
			return 0;
		if (unit->brother == element)
			return unit;
		local = find_unit_before_brother(unit->son, element);
		if (local != 0)
			return local;
		local = find_unit_before_brother(unit->brother, element);
		if (local != 0)
			return local;
		return local;

	}
	tree_g<T>* find_unit_before_son(tree_g<T>* unit, tree_g<T>* element)
	{
		tree_g<T>* local = nullptr;
		if (unit == nullptr)
			return 0;
		if (unit->son == element)
			return unit;
		local = find_unit_before_son(unit->son, element);
		if (local != 0)
			return local;
		local = find_unit_before_son(unit->brother, element);
		if (local != 0)
			return local;
		return local;

	}
	tree_g<T>* find_element(tree_g<T>* unit, T element)
	{
		tree_g<T>* local = nullptr;
		if (unit == nullptr)
			return 0;
		if (unit->data == element)
			return unit;
		local = find_element(unit->son, element);
		if (local != 0)
		{
			return local;
		}
		local = find_element(unit->brother, element);
		if (local != 0)
		{
			return local;
		}
		if(local == 0 && unit==this->unit)
			throw std::underflow_error("Element is not found");
		return local;
	}
	int count(tree_g<T>* unit)
	{
		int sum = 0;
		if (unit == nullptr)
			return 0;
		sum = sum + count(unit->son);
		sum = sum + count(unit->brother);
		sum++;
		return sum;
	}
	int height(tree_g<T>* unit)
	{
		if (unit == 0)
			return 0;
		int height_max = 0;
		for (tree_g<T>* unit_local = unit->son; unit_local; unit_local = unit_local->brother)
		{
			int height_local = height(unit_local);
			if (height_local > height_max)
				height_max = height_local;
		}
		return ++height_max;
	}
	T path(tree_g<T>* unit, T node)
	{
		if (unit == nullptr)
			return 0;
		int local = 0;
		if (unit->data == node)
			return 1;
		local = path(unit->son, node);
		if (local != 0)
		{
			++local;
			return local;
		}
		local = path(unit->brother, node);
		if (local != 0)
		{
			return local;
		}
		if (local == 0 && unit == this->unit)
			throw std::underflow_error("Element is not found");
		return local;

	}
	void print(tree_g<T>* unit, int count_scape)
	{
		if (unit == 0)
			return;
		for (int i = 0; i < count_scape; i++)
			std::cout << " ";
		std::cout << unit->data << std::endl;
		if (unit->son != 0)
		{
			++count_scape;
			print(unit->son, count_scape);
			--count_scape;
		}
		if (unit->brother != 0)
		{
			print(unit->brother, count_scape);
		}
		
	}
public:
	tree_general()
	{
		unit = nullptr;
	}
	~tree_general()
	{
		delete_tree(unit);
	}
	void push(T node, T data)
	{
		push(unit, node, data);
	}
	T pop(T element)
	{
		return pop(unit, element);
	}
	int count()
	{
		return count(unit);
	}
	tree_g<T>* find(T element)
	{
		return find_element(unit, element);
	}
	int height()
	{
		return height(unit);
	}
	void print()
	{
		print(unit, 0);
	}
	T path(T node)
	{
		return path(unit, node);
	}


	bool operator<(tree_general<T>& second_tree)
	{
		if (this == &second_tree)
			return false;

		return (count() < second_tree.count());
	}
	bool operator>(tree_general<T>& second_tree)
	{
		return (second_tree < *this);
	}
	bool operator==(tree_general<T>& second_tree)
	{
		if (this == &second_tree)
			return true;
		return (count() == second_tree.count());
	}
	bool operator!=(tree_general<T>& second_tree)
	{
		return !(*this == second_tree);
	}
	bool operator<=(tree_general<T>& second_tree)
	{
		return ((*this < second_tree) || (*this == second_tree));
	}
	bool operator>=(tree_general<T>& second_tree)
	{
		return ((*this > second_tree) || (*this == second_tree));
	}

};
#endif