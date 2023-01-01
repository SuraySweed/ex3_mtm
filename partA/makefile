progA: date_wrap.o libdate exceptions.o test_partA.o
	g++ -std=c++11 -Wall -pedantic-errors -Werror -DNDEBUG date_wrap.o exceptions.o test_partA.o -o progA


date_wrap.o: date_wrap.cpp date_wrap.h date.h exceptions.h
	g++ -std=c++11 -Wall -pedantic-errors -Werror -DNDEBUG -cpp date_wrap.cpp

exceptions.o: exceptions.cpp exceptions.h
	g++ -std=c++11 -Wall -pedantic-errors -Werror -DNDEBUG -cpp exceptions.cpp

test_partA.o: test_partA.cpp date_wrap.h exceptions.h
	g++ -std=c++11 -Wall -pedantic-errors -Werror -DNDEBUG -cpp test_partA.cpp

clean:
	rm -f *.o progA


