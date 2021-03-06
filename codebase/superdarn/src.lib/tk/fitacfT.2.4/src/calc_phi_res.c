/* calc_phi_res.c
   ==============
   Author: R.J.Barnes & K.Baker
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



/*
  2003/09/04 Kile Baker
  changed the return type of this function from void to int
  the function now checks to see if all the phases turned out
  to be 0.  If so, it returns -1, otherwise it returns 0.

  The return code of -1 indicates that you can't really do a fit
  because all the phases were exactly 0.  This can happen when
  the power is low and we are reprocessing DAT files that have lost
  some precision.
*/

#include <math.h>
#include "rmath.h"



int calc_phi_res(struct complex *acf,int *badlag,
				  double *phi_res,int mplgs) {
  int i, nzc;
  for (i=0, nzc=0; i< mplgs; ++i)
	{ 
		phi_res[i] = ((badlag[i]) ? 0.0 : atan2(acf[i].y, acf[i].x));
		if (phi_res[i] != 0.0)
			nzc++;

  }
  if (nzc > 0) return 0;
  else return -1;
}
