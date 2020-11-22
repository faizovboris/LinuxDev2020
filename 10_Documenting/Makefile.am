bin_PROGRAMS=guesser
guesser_SOURCES = main.c roman.c
pkgdata_DATA=update_pot_po ru/LC_MESSAGES/guesser.mo

@DX_RULES@

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

run_english_integer: guesser
	./guesser

run_russian_integer: guesser
	LANGUAGE=ru_RU ./guesser

run_english_roman: guesser
	./guesser -r

run_russian_roman: guesser
	LANGUAGE=ru_RU ./guesser -r

doxygen:
	make doxygen-doc

manfile: guesser
	help2man ./guesser > guesser.man.1
	man ./guesser.man.1

all-local:	doxygen-doc

gitclean: maintainer-clean
	git clean -fd
	rm *~
	rm guesse
