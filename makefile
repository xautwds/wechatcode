main: test.o MysqlDB.o
	g++ -o main test.o MysqlDB.o -l mysqlclient -l pthread
test.o: test.cpp
	g++ -c test.cpp 

MysqlDB.o: MysqlDB.cpp MysqlDB.h
	g++ -c MysqlDB.cpp

clean:
	rm MysqlDB.o  test.o main


#server: server.o Socket.o Libevent.o
#	g++ -o server server.o Socket.o Libevent.o -l event
#
#server.o: server.cpp
#	g++ -c server.cpp
#Socket.o: Socket.cpp Socket.h
#	g++ -c Socket.cpp 
#Libevent.o: Libevent.cpp Libevent.h
#	g++ -c Libevent.cpp 
#clean:
#	rm server Socket.o Libevent.o server.o


#test: test.o Redis.o
#	g++ -o test test.o Redis.o -l hiredis
#test.o: test.cpp
#	g++ -c test.cpp
#Redis.o: Redis.cpp Redis.h
#	g++ -c Redis.cpp 

#clean :
#	rm test test.o Redis.o
