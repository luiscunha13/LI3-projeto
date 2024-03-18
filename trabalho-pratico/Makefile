CC=gcc

CFLAGS=-O3 -march=native -Wall -g -Iincludes `pkg-config --cflags glib-2.0` 

LDFLAGS=`pkg-config --libs glib-2.0` -lm -lncurses



all: programa-principal programa-testes

programa-principal: src/main.o src/airport.o src/catalog.o src/date.o src/dayinfo.o src/flight.o src/flights.o src/func.o src/hotel.o src/parsing.o src/passengers.o src/query1.o src/query2.o src/query3.o src/query4.o src/query5.o src/query6.o src/query7.o src/query8.o src/query9.o src/query10.o src/reservation.o src/reservations.o src/seat.o src/user.o src/users.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ 

programa-testes: src/main_testes.o src/airport.o src/catalog.o src/date.o src/dayinfo.o src/flight.o src/flights.o src/func.o src/hotel.o src/parsing.o src/passengers.o src/query1.o src/query2.o src/query3.o src/query4.o src/query5.o src/query6.o src/query7.o src/query8.o src/query9.o src/query10.o src/reservation.o src/reservations.o src/seat.o src/user.o src/users.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ 

main.o: src/main.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@  -c main.c

main_testes.o : src/main_testes.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@  -c main_testes.c

airport.o: src/airport.c include/airport.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ airport.c

catalog.o: src/catalog.c include/catalog.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ catalog.c

dayinfo.o: src/dayinfo.c include/dayinfo.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ dayinfo.c

date.o: src/date.c include/date.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ date.c

flight.o: src/flight.c include/flight.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ flight.c

flights.o: src/flights.c include/flights.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ flights.c

func.o: src/func.c include/func.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ func.c

hotel.o: src/hotel.c include/hotel.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ hotel.c

parsing.o: src/parsing.c include/parsing.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ parsing.c

query1.o: src/query1.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query1.c

query2.o: src/query2.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query2.c

query3.o: src/query3.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query3.c

query4.o: src/query4.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query4.c

query5.o: src/query5.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query5.c

query6.o: src/query6.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query6.c

query7.o: src/query7.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query7.c

query8.o: src/query8.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query8.c

query9.o: src/query9.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query9.c

query10.o: src/query10.c include/queries.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ query10.c

seat.o: src/seat.c include/seat.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ seat.c

reservation.o: src/reservation.c include/reservation.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ reservation.c

reservations.o: src/reservations.c include/reservations.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ reservations.c

user.o: src/user.c include/user.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ user.c

users.o: src/users.c include/users.h
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ users.c


clean:
	rm -f programa-principal src/*.o Resultados/*.csv Resultados/*.txt
	rm -f programa-testes src/*.o Resultados/*.csv Resultados/*.txt
