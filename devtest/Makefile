CC = $(CC)
CFLAGS += -Wall  -fPIC

MYLDLIBS = 

obj = dev_so.o led_test.o dev_so_common.o dev_button_test.o dev_phy_test.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	
devtest: $(obj)
	$(CC) $(LDFLAGS) $(MYLDLIBS) -o $@ $^ $(LDLIBS) 
	
clean:
	rm -f *.o devtest