// Author: Aime' Fournier
// E-mail: fournier@ucar.edu

#include <stdio.h>
#include "qf.h"		// for pqf ...
#include "real.h"

// See 2009/8/4 e-mail from john@michalakes.us
#ifndef CRAY
#   ifdef NOUNDERSCORE
#      define DWTAI_W dwtai_w
#   else
#      ifdef F2CSTYLE
#         define DWTAI_W dwtai_w__
#      else
#         define DWTAI_W dwtai_w_
#      endif
#   endif
#endif

void DWTAI_W (char *nam,// in: filter name
           int *ran,	// in: filter length
           real *u,	// in/out: data & transform
           real *s,	// scratch space
           int *iv,	// v-space lengths
           int *ia,	// w-space starts
           int *lm) {	// maximum level
  pqf *g,*h;		// wavelet hpf & lpf
  static int call1=1;

//printf("dwtai_w::dwtai_w(%s,%2d,{%6.3f,...},{%6.3f,...},{%2d,...},{%2d,...},%2d)\n",nam,*ran,*u,*s,*iv,*ia,*lm);
  if( *ran ) {
     h=qf(nam,*ran,0);	// assign h
     g=qf(nam,*ran,1);	// assign g
//   PrintFilter(nam,*ran,0,h);
//   PrintFilter(nam,*ran,1,g);

     dwtai(u,s,iv,ia,*lm,h,g);

     free(g->fp);free(g);free(h->fp);free(h);
  }else{
     if( call1 ) {
        printf(" dwtai_w: abort because *ran==0.\n");
        call1=0;
        abort();
     }
  }
}
