all: mapcsv2input_debug
	
mapcart2pol:
	g++ -I ${BOOST_ROOT} src/CartesianToPolarConverter.cpp src/CircularSegment.cpp src/GnuplotScriptGenerator.cpp src/MapCartesianToPolar.cpp src/NumericRangeManipulator.cpp src/StringManipulator.cpp -o bin/MapCartesianToPolar -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a
	
mapcart2pol_debug:
	g++ -g -I ${BOOST_ROOT} src/CartesianToPolarConverter.cpp src/CircularSegment.cpp src/GnuplotScriptGenerator.cpp src/MapCartesianToPolar.cpp src/NumericRangeManipulator.cpp src/StringManipulator.cpp -o bin/MapCartesianToPolar -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

mapcsv2input:
	g++ -I ${BOOST_ROOT} src/CsvToInputFilesConverter.cpp src/LexicographicNumberIterator.cpp src/MapCsvToInputFiles.cpp src/StringManipulator.cpp -o bin/MapCsvToInputFiles -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

mapcsv2input_debug:
	g++ -g -I ${BOOST_ROOT} src/CsvToInputFilesConverter.cpp src/LexicographicNumberIterator.cpp src/MapCsvToInputFiles.cpp src/StringManipulator.cpp -o bin/MapCsvToInputFiles -Wall ${BOOST_LIBS}/program_options/build/gcc-4.6/release/link-static/threading-multi/libboost_program_options.a

clean:
	rm -f bin/MapCartesianToPolar	
