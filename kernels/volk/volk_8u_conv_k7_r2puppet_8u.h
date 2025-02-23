/* -*- c++ -*- */
/*
 * Copyright 2014 Free Software Foundation, Inc.
 *
 * This file is part of VOLK
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef INCLUDED_volk_8u_conv_k7_r2puppet_8u_H
#define INCLUDED_volk_8u_conv_k7_r2puppet_8u_H

#include <string.h>
#include <volk/volk.h>
#include <volk/volk_8u_x4_conv_k7_r2_8u.h>

typedef union {
    // decision_t is a BIT vector
    unsigned char* t;
    unsigned int* w;
} p_decision_t;

static inline int parity(int x, unsigned char* Partab)
{
    x ^= (x >> 16);
    x ^= (x >> 8);
    return Partab[x];
}

static inline int chainback_viterbi(unsigned char* data,
                                    unsigned int nbits,
                                    unsigned int endstate,
                                    unsigned int tailsize,
                                    unsigned char* decisions)
{
    unsigned char* d;
    int d_ADDSHIFT = 0;
    int d_numstates = (1 << 6);
    int d_decision_t_size = d_numstates / 8;
    unsigned int d_k = 7;
    int d_framebits = nbits;
    /* ADDSHIFT and SUBSHIFT make sure that the thing returned is a byte. */
    d = decisions;
    /* Make room beyond the end of the encoder register so we can
     * accumulate a full byte of decoded data
     */

    endstate = (endstate % d_numstates) << d_ADDSHIFT;

    /* The store into data[] only needs to be done every 8 bits.
     * But this avoids a conditional branch, and the writes will
     * combine in the cache anyway
     */

    d += tailsize * d_decision_t_size; /* Look past tail */
    int retval;
    int dif = tailsize - (d_k - 1);
    // printf("break, %d, %d\n", dif, (nbits+dif)%d_framebits);
    p_decision_t dec;
    while (nbits-- > d_framebits - (d_k - 1)) {
        int k;
        dec.t = &d[nbits * d_decision_t_size];
        k = (dec.w[(endstate >> d_ADDSHIFT) / 32] >> ((endstate >> d_ADDSHIFT) % 32)) & 1;

        endstate = (endstate >> 1) | (k << (d_k - 2 + d_ADDSHIFT));
        // data[((nbits+dif)%nbits)>>3] = endstate>>d_SUBSHIFT;
        // printf("%d, %d\n", k, (nbits+dif)%d_framebits);
        data[((nbits + dif) % d_framebits)] = k;

        retval = endstate;
    }
    nbits += 1;

    while (nbits-- != 0) {
        int k;

        dec.t = &d[nbits * d_decision_t_size];

        k = (dec.w[(endstate >> d_ADDSHIFT) / 32] >> ((endstate >> d_ADDSHIFT) % 32)) & 1;

        endstate = (endstate >> 1) | (k << (d_k - 2 + d_ADDSHIFT));
        data[((nbits + dif) % d_framebits)] = k;
    }
    // printf("%d, %d, %d, %d, %d, %d, %d, %d\n",
    // data[4095],data[4094],data[4093],data[4092],data[4091],data[4090],data[4089],data[4088]);


    return retval >> d_ADDSHIFT;
}


#if LV_HAVE_SSE3

#include <emmintrin.h>
#include <mmintrin.h>
#include <pmmintrin.h>
#include <stdio.h>
#include <xmmintrin.h>

static inline void volk_8u_conv_k7_r2puppet_8u_spiral(unsigned char* syms,
                                                      unsigned char* dec,
                                                      unsigned int framebits)
{


    static int once = 1;
    int d_numstates = (1 << 6);
    int rate = 2;
    static unsigned char* D;
    static unsigned char* Y;
    static unsigned char* X;
    static unsigned int excess = 6;
    static unsigned char* Branchtab;
    static unsigned char Partab[256];

    int d_polys[2] = { 79, 109 };


    if (once) {

        X = (unsigned char*)volk_malloc(2 * d_numstates, volk_get_alignment());
        Y = X + d_numstates;
        Branchtab =
            (unsigned char*)volk_malloc(d_numstates / 2 * rate, volk_get_alignment());
        D = (unsigned char*)volk_malloc((d_numstates / 8) * (framebits + 6),
                                        volk_get_alignment());
        int state, i;
        int cnt, ti;

        /* Initialize parity lookup table */
        for (i = 0; i < 256; i++) {
            cnt = 0;
            ti = i;
            while (ti) {
                if (ti & 1)
                    cnt++;
                ti >>= 1;
            }
            Partab[i] = cnt & 1;
        }
        /*  Initialize the branch table */
        for (state = 0; state < d_numstates / 2; state++) {
            for (i = 0; i < rate; i++) {
                Branchtab[i * d_numstates / 2 + state] =
                    parity((2 * state) & d_polys[i], Partab) ? 255 : 0;
            }
        }

        once = 0;
    }

    // unbias the old_metrics
    memset(X, 31, d_numstates);

    // initialize decisions
    memset(D, 0, (d_numstates / 8) * (framebits + 6));

    volk_8u_x4_conv_k7_r2_8u_spiral(
        Y, X, syms, D, framebits / 2 - excess, excess, Branchtab);

    unsigned int min = X[0];
    int i = 0, state = 0;
    for (i = 0; i < (d_numstates); ++i) {
        if (X[i] < min) {
            min = X[i];
            state = i;
        }
    }

    chainback_viterbi(dec, framebits / 2 - excess, state, excess, D);

    return;
}

#endif /*LV_HAVE_SSE3*/


#if LV_HAVE_NEON

#include "volk/sse2neon.h"

static inline void volk_8u_conv_k7_r2puppet_8u_neonspiral(unsigned char* syms,
                                                          unsigned char* dec,
                                                          unsigned int framebits)
{


    static int once = 1;
    int d_numstates = (1 << 6);
    int rate = 2;
    static unsigned char* D;
    static unsigned char* Y;
    static unsigned char* X;
    static unsigned int excess = 6;
    static unsigned char* Branchtab;
    static unsigned char Partab[256];

    int d_polys[2] = { 79, 109 };


    if (once) {

        X = (unsigned char*)volk_malloc(2 * d_numstates, volk_get_alignment());
        Y = X + d_numstates;
        Branchtab =
            (unsigned char*)volk_malloc(d_numstates / 2 * rate, volk_get_alignment());
        D = (unsigned char*)volk_malloc((d_numstates / 8) * (framebits + 6),
                                        volk_get_alignment());
        int state, i;
        int cnt, ti;

        /* Initialize parity lookup table */
        for (i = 0; i < 256; i++) {
            cnt = 0;
            ti = i;
            while (ti) {
                if (ti & 1)
                    cnt++;
                ti >>= 1;
            }
            Partab[i] = cnt & 1;
        }
        /*  Initialize the branch table */
        for (state = 0; state < d_numstates / 2; state++) {
            for (i = 0; i < rate; i++) {
                Branchtab[i * d_numstates / 2 + state] =
                    parity((2 * state) & d_polys[i], Partab) ? 255 : 0;
            }
        }

        once = 0;
    }

    // unbias the old_metrics
    memset(X, 31, d_numstates);

    // initialize decisions
    memset(D, 0, (d_numstates / 8) * (framebits + 6));

    volk_8u_x4_conv_k7_r2_8u_neonspiral(
        Y, X, syms, D, framebits / 2 - excess, excess, Branchtab);

    unsigned int min = X[0];
    int i = 0, state = 0;
    for (i = 0; i < (d_numstates); ++i) {
        if (X[i] < min) {
            min = X[i];
            state = i;
        }
    }

    chainback_viterbi(dec, framebits / 2 - excess, state, excess, D);

    return;
}

#endif /*LV_HAVE_NEON*/


//#if LV_HAVE_AVX2
//
//#include <immintrin.h>
//#include <stdio.h>
//
// static inline void volk_8u_conv_k7_r2puppet_8u_avx2(unsigned char* syms,
//                                                    unsigned char* dec,
//                                                    unsigned int framebits)
//{
//
//
//    static int once = 1;
//    int d_numstates = (1 << 6);
//    int rate = 2;
//    static unsigned char* D;
//    static unsigned char* Y;
//    static unsigned char* X;
//    static unsigned int excess = 6;
//    static unsigned char* Branchtab;
//    static unsigned char Partab[256];
//
//    int d_polys[2] = { 79, 109 };
//
//
//    if (once) {
//
//        X = (unsigned char*)volk_malloc(2 * d_numstates, volk_get_alignment());
//        Y = X + d_numstates;
//        Branchtab =
//            (unsigned char*)volk_malloc(d_numstates / 2 * rate, volk_get_alignment());
//        D = (unsigned char*)volk_malloc((d_numstates / 8) * (framebits + 6),
//                                        volk_get_alignment());
//        int state, i;
//        int cnt, ti;
//
//        /* Initialize parity lookup table */
//        for (i = 0; i < 256; i++) {
//            cnt = 0;
//            ti = i;
//            while (ti) {
//                if (ti & 1)
//                    cnt++;
//                ti >>= 1;
//            }
//            Partab[i] = cnt & 1;
//        }
//        /*  Initialize the branch table */
//        for (state = 0; state < d_numstates / 2; state++) {
//            for (i = 0; i < rate; i++) {
//                Branchtab[i * d_numstates / 2 + state] =
//                    parity((2 * state) & d_polys[i], Partab) ? 255 : 0;
//            }
//        }
//
//        once = 0;
//    }
//
//    // unbias the old_metrics
//    memset(X, 31, d_numstates);
//
//    // initialize decisions
//    memset(D, 0, (d_numstates / 8) * (framebits + 6));
//
//    volk_8u_x4_conv_k7_r2_8u_avx2(
//        Y, X, syms, D, framebits / 2 - excess, excess, Branchtab);
//
//    unsigned int min = X[0];
//    int i = 0, state = 0;
//    for (i = 0; i < (d_numstates); ++i) {
//        if (X[i] < min) {
//            min = X[i];
//            state = i;
//        }
//    }
//
//    chainback_viterbi(dec, framebits / 2 - excess, state, excess, D);
//
//    return;
//}
//
//#endif /*LV_HAVE_AVX2*/


#if LV_HAVE_GENERIC


static inline void volk_8u_conv_k7_r2puppet_8u_generic(unsigned char* syms,
                                                       unsigned char* dec,
                                                       unsigned int framebits)
{


    static int once = 1;
    int d_numstates = (1 << 6);
    int rate = 2;
    static unsigned char* Y;
    static unsigned char* X;
    static unsigned char* D;
    static unsigned int excess = 6;
    static unsigned char* Branchtab;
    static unsigned char Partab[256];

    int d_polys[2] = { 79, 109 };


    if (once) {

        X = (unsigned char*)volk_malloc(2 * d_numstates, volk_get_alignment());
        Y = X + d_numstates;
        Branchtab =
            (unsigned char*)volk_malloc(d_numstates / 2 * rate, volk_get_alignment());
        D = (unsigned char*)volk_malloc((d_numstates / 8) * (framebits + 6),
                                        volk_get_alignment());

        int state, i;
        int cnt, ti;

        /* Initialize parity lookup table */
        for (i = 0; i < 256; i++) {
            cnt = 0;
            ti = i;
            while (ti) {
                if (ti & 1)
                    cnt++;
                ti >>= 1;
            }
            Partab[i] = cnt & 1;
        }
        /*  Initialize the branch table */
        for (state = 0; state < d_numstates / 2; state++) {
            for (i = 0; i < rate; i++) {
                Branchtab[i * d_numstates / 2 + state] =
                    parity((2 * state) & d_polys[i], Partab) ? 255 : 0;
            }
        }

        once = 0;
    }

    // unbias the old_metrics
    memset(X, 31, d_numstates);

    // initialize decisions
    memset(D, 0, (d_numstates / 8) * (framebits + 6));

    volk_8u_x4_conv_k7_r2_8u_generic(
        Y, X, syms, D, framebits / 2 - excess, excess, Branchtab);

    unsigned int min = X[0];
    int i = 0, state = 0;
    for (i = 0; i < (d_numstates); ++i) {
        if (X[i] < min) {
            min = X[i];
            state = i;
        }
    }

    chainback_viterbi(dec, framebits / 2 - excess, state, excess, D);

    return;
}

#endif /* LV_HAVE_GENERIC */

#endif /*INCLUDED_volk_8u_conv_k7_r2puppet_8u_H*/
