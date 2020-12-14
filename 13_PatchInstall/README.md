## Чтобы собрать нужно выполнить:
```
autoreconf -fisv
./configure
make
```

## Чтобы запустить английский вариант:
```
make run_english
```

## Чтобы запустить русский вариант:
```
make run_russian
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
