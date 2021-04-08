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

Для запуска программы надо создать папку build и перейти в неё, выполнить команду:
```bash
$ /usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/home/linuxbrew/.linuxbrew/bin/gcc-5 -DCMAKE_CXX_COMPILER:FILEPATH=/home/linuxbrew/.linuxbrew/bin/g++-5 -H.. -B. -G "Unix Makefiles"
```
Далее для генерации кода надо будет вызывать только команду `make` в этой папке, она сгенерирует двоичный файл, который можно запустить через `./lab_01`
