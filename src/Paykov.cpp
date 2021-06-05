#include <iostream>
#include "HTable.h"
#include "BST.h"

using namespace std;

int main() {
	HTable<string, vector<string>> m;	
	int command;
	while (cin >> command) {
		if (command == 1) /*выдача имен городов, расположенных в одной (указанной) стране;*/ {
			string country;
			cin >> country;
			for (auto i : m["city"]) {
				cout << i << ' ';
			}
			cout << '\n';
		}
		if (command == 2) /*проверку, входит ли указанный город в указанную страну;*/{
			string country;
			cin >> country;
			string city;
			cin >> city;
			bool find = false;
			for (auto i : m["country"]) {
				if (i == city) {
					find = true;
				}
			}			
			if (find)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
}

/*
В результате данного задания были выполнены:
Главные:
1) emplace
2) erase
3) find
4) count
Из бонусов:
5) имитация контейнера (шаблоны)
*/