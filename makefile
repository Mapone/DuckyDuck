CXX=g++
CXXFLAGS=-std=c++11 -W -Wall -g
CXXLINK= -LSFML-2.3.2/lib -lsfml-graphics -lsfml-window -lsfml-system

DIR_SRC=src/
DIR_INC=inc/
DIR_BIN=bin/
DIR_RUN=resources/

#Va chercher tous les .cpp présents dans DIR_INC
SRC=$(shell find $(DIR_SRC) -name "*.cpp" -exec basename {} \;)

#Genere tous les noms de .o en fonction de SRC
OBJ=$(SRC:%.cpp=$(DIR_BIN)%.o)

#Genere la liste des .d en fonction de OBJ
DEP=$(OBJ:.o=.d)
EXE=$(DIR_BIN)DuckyDuck

#Genere l'executable, qui dépend de tous les .o
$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(CXXLINK)

# Genere les .o
# -MMD pour generer les makefiles
# Crée DIR_BIN si celui-ci n'existe pas
$(DIR_BIN)%.o: $(DIR_SRC)%.cpp | $(DIR_BIN)
	$(CXX) $(CXXFLAGS) -I$(DIR_INC) -MMD -c -o $@ -ISFML-2.3.2/include $<

run: $(EXE)
	cd $(DIR_RUN) && ../$<

#Inclus les makefiles générés pour chaque cpp 
-include $(DEP)

$(DIR_BIN):
	@mkdir $@

clean:
	@rm -rf $(DIR_BIN)

debug: $(EXE)
	@cd $(DIR_RUN) && gdb ../$<

# Cibles qui ne sont pas des noms de fichiers
.PHONY: clean run debug
