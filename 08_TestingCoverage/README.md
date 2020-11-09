## Чтобы собрать нужно выполнить:
```
autoreconf -fisv
./configure
make
```

## Чтобы прогнать тесты:
```
make check
```

## Для проверки покрытия:
```
autoreconf -fisv
./configure --enable-gcov
make check
cd src
gcov .libs/libbuf
cat ./libbuf.c.gcov
cd ..
```

## Для очистки:
```
make gitclean
```
