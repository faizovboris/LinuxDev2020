## Чтобы собрать нужно выполнить:
```
autoreconf -fisv
./configure
make
```

## Чтобы запустить английский вариант с обычными цифрами:
```
make run_english_integer
```

## Чтобы запустить русский вариант с обычными цифрами:
```
make run_russian_integer
```

## Чтобы запустить английский вариант с римскими цифрами:
```
make run_english_roman
```

## Чтобы запустить русский вариант с римскими цифрами:
```
make run_russian_roman
```

## Чтобы сгенерировать man-файл:
```
make manfile
```

## Чтобы сгенерировать doxygen-мануал:
```
make doxygen
```

## Чтобы изменить переводы нужно выполнить:
```
make update_pot_po
# Отредактировать guesser_ru.po
make ru/LC_MESSAGES/guesser.mo
```

## Для очистки:
```
make gitclean
```
