OBJS=main.o\
	config.o
TARGET=tjvm
LIBS= -lboost_program_options

$(TARGET):$(OBJS)
	g++ $(OBJS) -o $(TARGET) $(LIBS)
*.o:

.PHONY:clean
clean:
	rm -rf *.o
	rm -rf $(TARGET)
