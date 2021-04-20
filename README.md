![state](https://github.com/michael2021-vlsu/ssw_lab_4sem/actions/workflows/c-cpp.yml/badge.svg)

## lab_01

Реализация таких линейных структур данных как: стек, очередь, вектор.

Данные структуры должны поддерживать следующие операции/свойства:

- push - вставка элемента в структуру;
- pop - выталкивание элемента из структуры;
- peek - возврат вершины структуры (верхнего элемента);
- count - возврат количества элементов в структуре;
- at - метод произвольного доступа к элементу, реализуется только для структуры *вектор*;
- динамический размер - размер структуры должен увеличиваться при необходимости;
- операторы сравнения (>, <, !=, etc) - объекты структур должны поддерживать операции **лексикографического** сравнения;
- не должны содержать в себе STL контейнеров (`std::stack, std::queue, std::vector`).

Бонусы (не обязательно к выполнению):

- шаблонный интерфейс - структура является по своей сути контейнером, может содержать элементы любого типа (`my_structure<int> int_obj; my_structure<float> float_obj`).

------------------------------

### Что Вы должны сделать:

Ниже представлен список **индивидуальных** заданий:

- вариант 1: 
  - реализация обмена (*swap*) данными между структурами; 
  - определение "горной" последовательности;[1]
- вариант 2: 
  - отсортированная конкатенация данных между структурами одного типа;[2]
  - вычисление среднего арифметического;
- вариант 3:  
  - исключение из структуры элементов подпадающих в заданный диапазон;
  - реализация смены порядка элементов в структуре на обратный (*reverse*);
- вариант 4:  
  - вычисление суммы всех элементов;
  - конкатенация данных внутри структуры.[3]

##### [1]: Если данные в структуре удовлетворяют следующим условиям:
- кол-во эл-ов >= 3;
- есть индекс i: *0 < i < struct.size() - 1*, так что:
	- *struct[0] < struct[1] < ... < struct[i - 1] < struct[i]*
	- *struct[i] > struct[i + 1] > ... > struct[struct.size() - 1]*

то вызов метода `isMount()` должен вернуть `true`, в противном случае `false`.

##### [2]: например: имеются два вектора v1 {0, 1, 5} и v2 {1, 4, 5}. Результат конкатенации вернёт вектор {0, 1, 1, 4, 5, 5};

##### [3]: К примеру: структура содержит следующий перечень элементов { 1, 2, 5, 40, 3 }, соответственно их конкатенация выдаст число 125403. Все отрицательные числа берутся по модулю, не реализуется для структуры - стек.

-----------------

Ваши **структуры должны** поддерживать реализации индивидуальных заданий (если не было указано иное). К примеру: *стек, очередь и вектор, для варианта 1 должны поддерживать такие методы как `swap` и `isMount` предоставляя ожидаемый функционал (обмен и "переворот" данных).* 

### Сборка

Все представленные ниже инструкции используются для _*nix_ семейства ОС.  Для пользователей ОС Windows может понадобиться использование других инструкций (либо вы можете использовать *Cygwin* или *MinGW*).

Для сборки с помощью `make` (Makefile):

```bash
$ cd <to repo path>/lab_01
$ make
```

Для сборки с помощью `cmake` (CMakeLists.txt):

```bash
$ cd <to repo path>/lab_01
$ cmake .
$ make
```

### Отчёт

В отчёте должно содержаться:

- перечисление **выполненых** заданий;
- листинг (код) программы;
- тестирование программы;
- сравнение производительности основных операций между вашими структурами и STL контейнерами;
- вывод скомпилированной программы;
- вывод по проделанной работе.