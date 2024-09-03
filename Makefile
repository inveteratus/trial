
CC		=	gcc
CFLAGS		=	-W -Wall -Werror -O3

LD		=	$(CC)
LDFLAGS		=	
LDLIBS		=	-lgmp -lm

RM		=	rm -f

#################

TRIAL		=	trial
TRIAL_O		=	main.o \
			primegen.o \
			primegen_init.o \
			primegen_next.o \
			primegen_skip.o

#################

all		:	$(TRIAL)

build		:	distclean all

clean		:
	-$(RM) $(TRIAL_O)

distclean	:	clean
	-$(RM) $(TRIAL)

#################

$(TRIAL)	:	$(TRIAL_O)
	$(LD) $(LDFLAGS) -o $(TRIAL) $(TRIAL_O) $(LDLIBS)

#################

INT64_H		:	int64.h
PRIMEGEN_H	:	primegen.h $(UINT32_H) $(UINT64_H)
PRIMEGEN_IMPL_H	:	primegen_impl.h
UINT32_H	:	uint32.h
UINT64_H	:	uint64.h

#################

main.o		:	main.c $(PRIMEGEN_H)
primegen.o	:	primegen.c $(PRIMEGEN_H) $(PRIMEGEN_IMPL_H) $(INT64_H)
primegen_init.o	:	primegen_init.c $(PRIMEGEN_H) $(PRIMEGEN_IMPL_H)
primegem_next.o	:	primegen_next.c $(PRIMEGEN_H) $(PRIMEGEN_IMPL_H)
primegen_skip.o	:	primegen_skip.o $(PRIMEGEN_H) $(PRIMEGEN_IMPL_H)
