subsystem:
	cd relatorio_fase4/ && $(MAKE)
	mv relatorio_fase4/CG4-GRUPO03.pdf ./
	cd ..
	zip -r Engine.zip Engine/ -x \*.git\* -x \*.settings/\*
	zip -r Generator.zip Generator/ -x \*.git\* -x \*.settings/\*
	zip -r FASE_4_Bruno_Pereira.zip CG4-GRUPO03.pdf Engine.zip Generator.zip
	rm Engine.zip Generator.zip
	mv FASE_4_Bruno_Pereira.zip ~/Área\ de\ Trabalho/
