CC=gcc 
CFLAGS =  -m64 -march=core-avx2 -O3 -fomit-frame-pointer	
OBJS += fe.o key_exchange.o seed.o sc.o keypair.o sha512.o ge.o verify.o add_scalar.o sign.o
OBJS += fe4x_mul.o
OBJS += fe4x_sub.o
OBJS += fe4x_add.o
OBJS += fe4x_sq.o
OBJS += fe4x_neg.o
OBJS += fe4x_copy.o
OBJS += fe4x_cmov.o
OBJS += fe4x_cswap.o
OBJS += fe4x_neg.o
test: test.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	-rm -f *.o test                            
