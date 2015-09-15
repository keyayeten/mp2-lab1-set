# Методы программирования 2:
# Множества на основе битовых полей

[![Build Status](https://travis-ci.org/UNN-VMK-Software/mp2-lab1-bitfield.svg)](https://travis-ci.org/UNN-VMK-Software/mp2-lab1-bitfield)

<!-- TODO

  -

  - Optional
    -

-->

Используемые инструменты:
  
  - Система контроля версий [Git](https://git-scm.com/book/en/v2).
  - Библиотека автоматического тестирования 
    [Google Test Framework](https://code.google.com/p/googletest).
  - Среда разработки Microsoft Visual Studio (> 2008).
  - Опционально утилита [CMake](http://www.cmake.org) для сборки
    исходных кодов.

## Общая структура проекта

Структура проекта:

  - `gtest` - библиотека Google Test.
  - `include` - директория для размещения заголовочных файлов.
  - `samples` - директория для размещения демо-приложений.
  - `src` - директория с файлами решений и проектов для VS 2008
    (директория vc9) и VS2010 (vc10).
  - `src` - директория с исходными кодами.
  - `test` - директория с тестами.
  - `.gitignore` - перечень файлов, игнорируемых Git.  
  - `README.md` - информация о проекте, которую вы сейчас читаете.
  - `CMakeLists.txt` - корневой файл для сборки проекта с помощью CMake.  
  - `.travis.yml` - конфигурационный файл для системы автоматического
    тестирования Travis-CI.

В решении содержатся следующие модули:
  - Модуль `tbitfield` (`./include/tbitfield.h`, `./src/tbitfield.cpp`),
    содержащий реализацию класса битового поля. Предполагается, что
    в ходе выполнения работы реализуются методы класса (в файле `./src/tbitfield.cpp`),
    при этом заголовочный файл (`./include/tbitfield.h`) с объявлениями
    должен оставаться неизменным.
  - Модуль `tset` (`./include/tset.h`, `./src/tset.cpp`), содержащий
    реализацию класса множества. При выполнении работы так же, как и в случае
    класса битового поля, разрабатывается только реализация методов класса.
  - Тесты для классов битовое поле и множество (`./test/test_tbitfield.cpp`,
    `test_tset.cpp`).
  - Пример использования для решения задачи "Решето Эратосфена"
    (`./samples/sample_prime_numbers.cpp`).
  
## Цели и задачи

__Цель данной работы__ - разработка структуры данных для хранения множеств
с использованием битовых полей, а также освоение таких инструментов разработки
программного обеспечения, как система контроля версий
[Git](https://git-scm.com/book/en/v2) и фрэймворк для разработки
тестов [Google Test Framework](https://code.google.com/p/googletest).

Предполагается, что перед выполнением работы студент получает данный
шаблон проекта, содержащий интерфесы классов битового поля и множества,
набор тестов для каждого из указанных классов, пример использования
класса битового поля и множества для решения задачи "Решето Эратосфена".

Выполнение работы предполагает решение следующих задач:
  1. Реализация заданного интерфейса класса битового поля `TBitField`.
  1. Реализация заданного интерфейса класса множества `TSet`.
  1. Обеспечение работоспособности тестов.

## Инструкция по выполнению работы

## Общие инструкции по работе с Git

В данном разделе описана типичная последовательность действий, которую 
необходимо выполнить перед тем, как начать работать с проектом. Далее 
для определенности используется репозиторий mp2-lab1-bitfield.

  1. Создать аккаунт на [github.com](https://github.com), если такой
     отсутствует. Для определенности обозначим аккаунт `github-account`.

  1. Сделать fork репозитория
     <https://github.com/UNN-VMK-Software/mp2-lab1-bitfield> (в
     терминологии Git upstream-репозиторий) к себе в личный профиль с названием
     github-account. В результате будет создана копия репозитория с названием
     <https://github.com/github-account/mp2-lab1-bitfield>
     (origin-репозиторий).

  1. Клонировать [origin][origin] репозиторий к себе на локальный компьютер,
     воспользовавшись следующей командой:

  ```
  $ git clone https://github.com/github-account/mp2-lab1-bitfield
  ```

  1. Перейти в директорию mp2-lab1-bitfield:

  ```
  $ cd ./mp2-lab1-bitfield
  ```

  1. Настроить имя пользователя, из под которого будут выполняться все операции
     с репозиторием Git:

  ```
  $ git config --local user.name "github-account"
  ```

Чтобы обеспечить возможность удаленной проверки работы (включая автоматический
запуск и проверку корректности тестов), необходимо создать Pull Request
в upstream-репозиторий:
  1. Открыть в браузере <https://github.com/github-account/mp2-lab1-bitfield>.
  2. Нажать кнопку Pull Request в строке над исходными кодами, содержащей
     информацию о последних коммитах.

При работе с файлами в ветке необходимо управлять изменениями. Далее приведен
перечень основных команд в предположении, что текущей рабочей веткой 
является `master`.

  1. Получить список текущих изменений:
  
  ```
  $ git status
  ```
  
  1. Пометить файл как добавленный в текущую ветку репозитория (файл будет
     добавлен после выполнения команды `commit`):
  
  ```
  $ git add [<file_name>]
  # <file_name> - название файла для добавления в commit
    если вместо имени указан символ *, то будут добавлены все новые файлы, 
    расширение которых не указано в .gitignore
  ```

  1. Добавить изменения в текущую ветку локального репозитория:

  ```  
  $ git commit [-m "<message_to_commit>"] [-a]
  # [-a] - автоматически добавляет изменения для существующих на сервере файлов
    без выполнения команды git add
  # [--amend] - перезаписывает последний коммит (используется, если не забыты
    изменения)
  ```

  1. Разместить изменения, которые были добавлены в локальный репозиторий 
     с помощью команды `push`:

  ```
  $ git push origin/master
  ```

  1. Удалить файлы или директории (!без опции -f для файлов, состояния 
     которых совпадают с состоянием на сервере):

  ```
  $ git rm [-f] [--cached]
  # [-f] - принудительное удаление (файла с измененным состоянием)
  # [--cached] - удаление файлов на сервере, но не в локальной директории
  ```

  1. Переименовать файлы (или 3 команды: `mv`, `git rm`, `git add`):

  ```
  $ git mv <file_from> <file_to>
  ```

<!-- LINKS -->

[origin]: https://github.com/github-account/mp2-lab1-bitfield
