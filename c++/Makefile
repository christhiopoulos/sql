# paths
MODULES = ../../modules
INCLUDE = ../../include

# Compile options. Το -I<dir> χρειάζεται για να βρει ο gcc τα αρχεία .h
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o, εκτελέσιμο πρόγραμμα και παράμετροι
OBJS = Course.o main.o Person.o Professor.o Secretary.o Semester.o Student.o
EXEC = sec 
ARGS =

$(EXEC): $(OBJS)
	g++ $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)


