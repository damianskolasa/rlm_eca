VERS = 2.1.11

CFLAGS  =  -DNDEBUG -Wall -I/opt/include \
           -I/HOME/damiank/freeradius-server-$(VERS)/src

LIBS    =  -lc -L/usr/local/msql3/lib -lmsql

ALL:    rlm_xxx.o rlm_xxx-$(VERS).so

rlm_xxx.o:     rlm_xxx.c
        cc -g -fPIC -DPIC -c $(CFLAGS) rlm_xxx.c

rlm_xxx-$(VERS).so:    rlm_xxx.o
        cc -g -shared -Wl,-soname,rlm_xxx-$(VERS).so \
           -o rlm_xxx-$(VERS).so rlm_xxx.o $(LIBS)

install:        ALL
        install rlm_xxx-$(VERS).so /usr/local/lib/freeradius-$(VERS)
        ln -fs rlm_xxx-$(VERS).so /usr/local/lib/freeradius-$(VERS)/rlm_xxx.so

clean:
        rm rlm_xxx*.o rlm_xxx*.so