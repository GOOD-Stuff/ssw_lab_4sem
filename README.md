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
## Компиляция кода на WSL
Сначала надо установить ПО
```bash
$ sudo apt-get update
$ sudo apt-get install make
$ sudo apt-get install cmake
```

Для начального запуска проекта надо выполнить команды из корневой папки:
```bash
$ mkdir build
$ cd build
$ /usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/home/linuxbrew/.linuxbrew/bin/gcc-5 -DCMAKE_CXX_COMPILER:FILEPATH=/home/linuxbrew/.linuxbrew/bin/g++-5 -H.. -B. -G "Unix Makefiles"
$ make
$ ./lab_01
```
Далее для генерации кода надо будет вызывать только команду `make` в этой папке, она сгенерирует двоичный файл, который можно запустить через `./lab_01`
