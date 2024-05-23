#include "lowpass.h"


static void setCoef(lowpass_filter *lp){
	  float alpha = lp->omega0 * lp->dt;
		lp->a[0] = -(alpha - 2.0) / (alpha + 2.0);
		lp->b[0] = alpha / (alpha + 2.0);
    lp->b[1] = alpha / (alpha + 2.0);	

}


void lowpass_init(lowpass_filter *lp , float f0, float fs){
	lp->omega0 = 2 * PI * f0;
	lp ->dt = 1 /fs;
	for(int i = 0; i < 2; i++){
		lp->x[i] = 0;
		lp->y[i] = 0;
	}
	
	
	setCoef(lp);
	
}
float filt(lowpass_filter * lp, float xn){
	  lp->y[0] = 0;
    lp->x[0] = xn;
	
    lp->y[0] += lp->a[0] * lp->y[1] + lp->b[0] * lp->x[0];
    
    lp->y[0] += lp->b[1] * lp->x[1];
	
		for(int k = 1; k > 0; k--){
        lp->y[k] = lp->y[k-1];
        lp->x[k] = lp->x[k-1];
      }
  
      // Return the filtered value    
      return lp->y[0];
}



