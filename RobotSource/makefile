src = $(wildcard *.c)
obj = $(src:.c=.o)

myprog: $(obj)
    $(CC) -o $@ $^

.PHONY: clean
clean:
    rm -f $(obj) myprog  
