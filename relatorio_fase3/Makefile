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
	mv main.pdf CG3-GRUPO03.pdf
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



compress:  
	@echo "Preparar ficheiro Zip para entrega...."
	zip -r FASE_2.zip CG2-GRUPO03.pdf Engine.zip Generator.zip




