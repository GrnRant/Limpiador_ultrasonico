#include "sapi.h"
#include "temp.h"



int32_t adc_temp[] = 				{
        								716 ,
                                        707 ,
                                        697 ,
                                        687 ,
                                        677 ,
                                        666 ,
                                        656 ,
                                        646 ,
                                        636 ,
                                        625 ,
                                        615 ,
                                        605 ,
                                        594 ,
                                        584 ,
                                        573 ,
                                        563 ,
                                        553 ,
                                        543 ,
                                        532 ,
                                        522 ,
                                        512 ,
                                        502 ,
                                        492 ,
                                        482 ,
                                        472 ,
                                        463 ,
                                        453 ,
                                        443 ,
                                        434 ,
                                        425 ,
                                        416 ,
                                        407 ,
                                        398 ,
                                        389 ,
                                        380 ,
                                        372 ,
                                        363 ,
                                        355 ,
                                        347 ,
                                        339 ,
                                        331 ,
                                        324 ,
                                        316 ,
                                        309 ,
                                        302 ,
                                        295 ,
                                        288 ,
                                        281 ,
                                        274 ,
                                        268 ,
                                        261 ,
                                        255 ,
                                        249 ,
                                        243 ,
                                        237 ,
                                        231 ,
                                        226 ,
                                        220 ,
                                        215 ,
                                        210 ,
                                        205 ,
										};


int32_t temp[] ={
		0 ,
        1 ,
        2 ,
        3 ,
        4 ,
        5 ,
        6 ,
        7 ,
        8 ,
        9 ,
        10 ,
        11 ,
        12 ,
        13 ,
        14 ,
        15 ,
        16 ,
        17 ,
        18 ,
        19 ,
        20 ,
        21 ,
        22 ,
        23 ,
        24 ,
        25 ,
        26 ,
        27 ,
        28 ,
        29 ,
        30 ,
        31 ,
        32 ,
        33 ,
        34 ,
        35 ,
        36 ,
        37 ,
        38 ,
        39 ,
        40 ,
        41 ,
        42 ,
        43 ,
        44 ,
        45 ,
        46 ,
        47 ,
        48 ,
        49 ,
        50 ,
        51 ,
        52 ,
        53 ,
        54 ,
        55 ,
        56 ,
        57 ,
        58 ,
        59 ,
        60
			};

int32_t calcTemp(int16_t adc_read)
{
	int i;

	for(i = 0; i<(MAX_TEMP+5); i++)
	{
		if(adc_read <= adc_temp[i] && adc_read >= adc_temp[i + 1])
			break;
	}
	return temp[i];
}


















