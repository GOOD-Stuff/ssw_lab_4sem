## lab_01

После клонирования репозитория надо создать файл src/lab_01.cpp с кодом:

```C++
#include <iostream>
#include "vector/vector.h"
#include "stack/stack.h"
#include "queue/queue.h"

int main(int argc, char** argv)
{
	return 0;
}
```

Для запуска программы надо создать папку build и перейти в неё, выполнить команду `cmake .`, далее для генерации кода надо будет вызывать только команду `make`, она сгенерирует двоичный файл, который можно запустить через `./lab_01`
