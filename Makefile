CC=g++
#CC=/opt/intel/bin/icpc
BIN=bin/
TEST=test/
BUILD=build/
SRC=src/
CONF=conf/
#CCFLAGS=-c -Wall  -g -fopenmp 
#CCFLAGS=-c -Wall  -g -fopenmp -pg
#CCFLAGS=-c -Wall  -O3 -fopenmp -mfpmath=sse -march=native
CCFLAGS=-c -Wall  -Ofast -fopenmp -mfpmath=sse -march=native
CPPUNITLINKS=-lcppunit
MAINLINKS=-lgomp


#
#	Main Binary
#
Thoth: $(BIN)Thoth

$(BIN)Thoth: $(BUILD)Thoth.o
	$(CC) $(BUILD)*.o $(MAINLINKS) -o $(BIN)Thoth

$(BUILD)Thoth.o: source-files checkconfigcopied
	rm -f $(BUILD)profiler.o $(BUILD)TestRunner.o 
	$(CC) $(CCFLAGS) $(SRC)Thoth.cpp -o $(BUILD)Thoth.o



#
#	Profiler
#
profiler: $(BIN)profiler

$(BIN)profiler: $(BUILD)profiler.o
	$(CC) $(BUILD)*.o $(MAINLINKS) -o $(BIN)profiler
	
$(BUILD)profiler.o: source-files
	rm -f $(BUILD)Thoth.o $(BUILD)test_cases.o $(BUILD)TestRunner.o
	$(CC) $(CCFLAGS) $(SRC)profiler.cpp -o $(BUILD)profiler.o


#
#	Test Suite
#
test: $(BIN)test_cases

$(BIN)test_cases: $(BUILD)TestRunner.o
	rm -f $(BUILD)Thoth.o $(BUILD)profiler.o
	$(CC) $(BUILD)*.o $(CPPUNITLINKS) $(MAINLINKS) -o $(BIN)test_cases

$(BUILD)TestRunner.o: source-files
	$(CC) $(CCFLAGS) $(TEST)TestRunner.cpp -o $(BUILD)TestRunner.o


#
#	SOURCE FILES
#

pop-mem: $(BUILD)PopulationMember.o

source-files: $(BUILD)Settings.o $(BUILD)Function.o $(BUILD)Node.o $(BUILD)NodeManager.o $(BUILD)RNG.o $(BUILD)FitnessCases.o $(BUILD)PopulationMember.o $(BUILD)Optimiser.o $(BUILD)EvolutionManager.o $(BUILD)GlobalManager.o 

$(BUILD)GlobalManager.o:  $(BUILD)ArgParser.o $(BUILD)JsonConfigLoader.o $(BUILD)PopulationManager.o
	$(CC) $(CCFLAGS) $(SRC)GlobalManager.cpp -o $(BUILD)GlobalManager.o

$(BUILD)EvolutionManager.o:
	$(CC) $(CCFLAGS) $(SRC)EvolutionManager.cpp -o $(BUILD)EvolutionManager.o

$(BUILD)Optimiser.o: $(BUILD)PopulationManager.o
	$(CC) $(CCFLAGS) $(SRC)Optimiser.cpp -o $(BUILD)Optimiser.o

$(BUILD)PopulationManager.o: $(BUILD)PopulationMember.o $(BUILD)TvectorPM.o
	$(CC) $(CCFLAGS) $(SRC)PopulationManager.cpp -o $(BUILD)PopulationManager.o

$(BUILD)TvectorPM.o: $(BUILD)PopulationMember.o
	$(CC) $(CCFLAGS) $(SRC)TvectorPM.cpp -o $(BUILD)TvectorPM.o

$(BUILD)PopulationMember.o: $(BUILD)NodeManager.o
	$(CC) $(CCFLAGS) $(SRC)PopulationMember.cpp -o $(BUILD)PopulationMember.o

$(BUILD)NodeManager.o: $(BUILD)Node.o
	$(CC) $(CCFLAGS) $(SRC)NodeManager.cpp -o $(BUILD)NodeManager.o

$(BUILD)Node.o: $(BUILD)Function.o
	$(CC) $(CCFLAGS) $(SRC)Node.cpp -o $(BUILD)Node.o

$(BUILD)Function.o:
	$(CC) $(CCFLAGS) $(SRC)Function.cpp -o $(BUILD)Function.o
	
$(BUILD)Settings.o: 
	$(CC) $(CCFLAGS) $(SRC)Settings.cpp -o $(BUILD)Settings.o

$(BUILD)FitnessCases.o: $(BUILD)ConstantPool.o
	$(CC) $(CCFLAGS) $(SRC)FitnessCases.cpp -o $(BUILD)FitnessCases.o

$(BUILD)ConstantPool.o:
	$(CC) $(CCFLAGS) $(SRC)ConstantPool.cpp -o $(BUILD)ConstantPool.o

$(BUILD)RNG.o:
	$(CC) $(CCFLAGS) $(SRC)RNG.cpp -o $(BUILD)RNG.o

$(BUILD)ArgParser.o:
	$(CC) $(CCFLAGS) $(SRC)ArgParser.cpp -o $(BUILD)ArgParser.o

$(BUILD)JsonConfigLoader.o: $(BUILD)jsoncpp.o
	$(CC) $(CCFLAGS) $(SRC)JsonConfigLoader.cpp -o $(BUILD)JsonConfigLoader.o

$(BUILD)jsoncpp.o:
	$(CC) $(CCFLAGS) $(SRC)jsoncpp.cpp -o $(BUILD)jsoncpp.o


clean:
	rm -rf test/*.o
	rm -rf src/*.o
	rm -rf build/*
	rm -rf test/*~
	rm -rf src/*~
	rm -rf build/*~
	rm -f *~

# Might be a better way of copying in the config than this
checkconfigcopied: $(CONF)config.json

$(CONF)config.json:
	cp $(CONF)config.json.orig $(CONF)config.json
