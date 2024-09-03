
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "primegen.h"

void main_loop(primegen pg, mpz_t number)
{
    mpz_t square;
    uint64 prime;

    mpz_init(square);

    do {
        prime = primegen_next(&pg);
        // compare the two
        if (mpz_cmp_ui(number, prime) == 0) {
            gmp_printf("trial: %Zd is prime\n", number);
            mpz_clear(square);
            return;
        }

        if (mpz_divisible_ui_p(number, prime)) {
            mpz_t factor;

            mpz_init(factor);
            mpz_divexact_ui(factor, number, prime);

            gmp_printf("trial: %Zd is composite (%lu x %Zd)\n", number, prime, factor);
            mpz_clear(factor);

            return;
        }

        // check to see if prime * prime > number
        mpz_ui_pow_ui(square, prime, 2);
        if (mpz_cmp(square, number) > 0) {
            gmp_printf("trial: %Zd is prime\n", number);
            mpz_clear(square);
        }
    }
    while (prime < 3162277660);

    switch (mpz_probab_prime_p(number, 25)) {
        case 2:
            gmp_printf("trial: %Zd is prime\n", number);
            break;
        case 1:
            gmp_printf("trial: %Zd is probably prime\n", number);
            break;
        case 0:
            gmp_printf("trial: %Zd is composite\n", number);
            break;
    }

    mpz_clear(square);
}

int main(int argc, char *argv[])
{
    mpz_t number;
    primegen pg;

    primegen_init(&pg);

    if (argc == 3) {
        uint64 from = strtoul(argv[2], NULL, 10);

        if (from > 1) {
            primegen_skipto(&pg, from);
        }
    }
    else if (argc != 2) {
        fprintf(stderr, "usage: trial <number> [<from>]\n");
        return EXIT_FAILURE;
    }

    if (mpz_init_set_str(number, argv[1], 10) == -1) {
        fprintf(stderr, "trial: invalid number\n");
        return EXIT_FAILURE;
    }

    if (mpz_cmp_ui(number, 2) < 0) {
        fprintf(stderr, "trial: number too small\n");
        return EXIT_FAILURE;
    }

    main_loop(pg, number);

    mpz_clear(number);

    return EXIT_SUCCESS;
}
