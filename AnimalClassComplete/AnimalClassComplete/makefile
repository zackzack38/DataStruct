AnimalDrive: cat.o dog.o animal.o animaldriver.o
	g++ cat.o dog.o animal.o animaldriver.o -o AnimalDrive

cat.o: cat.cpp cat.h
	g++ -c cat.cpp cat.h -std=c++17

dog.o: dog.cpp dog.h
	g++ -c dog.cpp dog.h -std=c++17

animal.o: animal.cpp animal.h
	g++ -c animal.cpp animal.h -std=c++17

animaldriver.o: animaldriver.cpp
	g++ -c animaldriver.cpp -std=c++17

clean:
	rm *.o *.gch AnimalDrive
