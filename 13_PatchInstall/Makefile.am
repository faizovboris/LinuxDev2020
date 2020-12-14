bin_PROGRAMS=guesser
guesser_SOURCES =main.c
pkgdata_DATA=ru/LC_MESSAGES/guesser.mo
AM_CFLAGS = -D LOCALEDIR='"$(localedir)"'
pkgdatadir = $(localedir)/ru/LC_MESSAGES

init_pot_po:	guesser.pot
	msginit -i guesser.pot -o guesser_ru.po -l ru

ru/LC_MESSAGES/guesser.mo: guesser_ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

guesser_ru.po:	guesser.pot
	msgmerge -U $@ $<

guesser.pot:	main.c
	xgettext -k_ -c main.c -o guesser.new.pot
	msgmerge -U guesser.pot guesser.new.pot
	rm guesser.new.pot

update_pot_po: guesser.pot guesser_ru.po

run_english: guesser
	${bindir}/guesser

run_russian: guesser
	LANGUAGE=ru_RU ${bindir}/guesser

gitclean:
	git clean -fd
	rm -rf *~
