### Небольшой отчёт по ДЗ-7.

Выполнил Старцев Евгений, БПИ219.

Корректное завершение программы достигается при помощи команды `signal` и сигнала `SIGINT` - сигнала, получаемого при
завершении программы с помощью Ctrl + C. Но, помимо корректного завершения программы, также необходимо освободить
память. Это достигается с помощью команды `munmap`, принимающая в качестве аргументов указатель на начало области памяти
и её размер.

Всё остальное, в принципе, как и в ДЗ-6. Только средствами POSIX.

Как запустить программу:

Первый терминал:

```
gcc client.c -o client
./client
```

Второй терминал:

```
gcc server.c -o server
./server
```