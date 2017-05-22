SHELL := /bin/bash

LATEX=pdflatex
LATEXOPT=--shell-escape
LATEXMK=latexmk
LATEXMKOPT=-pdf
LATEXMKBIBTEX=-bibtex

all: relatorio 

cleanaux: 	
	rm -rf *.bbl
	rm -rf *.blg
	rm -rf *.lof
	rm -rf *.out
	rm -rf *.aux
	rm -rf *.toc
	rm -rf *.loa
	rm -rf *.log
	rm -rf *.fls
	rm -rf *.fdb_latexmk
	rm -fr _minted-main

clean: cleanaux
	rm -rf *.pdf

relatorio: clean relatorio.pdf cleanaux
#	xreader relatorio.pdf &> /dev/null &


relatorio.pdf:  main.tex 
	$(LATEXMK) $(LATEXMKBIBTEX) $(LATEXMKOPT) \
	$(LATEXMKBIBTEX) $(CONTINUOUS) \
	-pdflatex="$(LATEX) $(LATEXOPT) %O %S" \
	main.tex
	mv main.pdf CG4-GRUPO03.pdf
	rm -rf *.bbl
	rm -rf *.blg
	rm -rf *.lof
	rm -rf *.out
	rm -rf *.aux
	rm -rf *.toc
	rm -rf *.loa
	rm -rf *.log
	rm -rf *.fls
	rm -rf *.fdb_latexmk
	rm -fr _minted-main







