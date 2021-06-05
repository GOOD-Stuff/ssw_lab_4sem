// Copyright by (c) Paykov
#pragma once
#include <xhash>
#include <vector>	 

// Реализована как классическая unordered_map

template<class Key, class Type>
class HTable {
private:
	std::vector<std::vector<std::pair<Key, Type>>> htable;
	std::size_t size = 0;	 
	unsigned long long get_hash(const Key& x) const {
		return std::hash<Key>{}(x) % htable.size();
	}
	
public:
	HTable() {
		this->htable.resize(1e5);
	}
	
	// Находим
	bool find(const Key& x) {
		auto iter = htable[get_hash(x)].begin();
		auto end = htable[get_hash(x)].end();
		while (iter != end) {
			if ((*iter).first == x) {
				return true;
			}
		}
		return false;
	}

	// Возвращаем 
	Type& operator [](const Key& x) {
		auto iter = htable[get_hash(x)].begin();
		auto end = htable[get_hash(x)].end();
		while (iter != end) {
			if ((*iter).first == x) {
				return (*iter).second;
			}
		}
		Type ret{};
		return ret;
	}

	// Заменяем
	void emplace(const Key& x, const Type& k) {
		if (find(x)) {
			auto iter = htable[get_hash(x)].begin();
			auto end = htable[get_hash(x)].end();
			while (iter != end) {
				if ((*iter).first == x) {
					(*iter).second = k;
					break;
				}
			}
		} else {
			htable[get_hash(x)].emplace_back(x, k);
			size++;
		}
	}

	// Удаляем
	void erase(const Key& k) {
		if (find(k)) {
			auto iter = htable[get_hash(k)].begin();
			auto end = htable[get_hash(k)].end();
			while (iter != end) {
				if ((*iter).first == k) {
					htable[get_hash(k)].erase(iter);
					size--;
					break;
				}
			}
		}
	}


	int count() const {
		return this->size;
	}
};