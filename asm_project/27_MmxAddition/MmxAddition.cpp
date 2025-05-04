#include<iostream>
#include "MmxVal.h"


enum MmxAddOp :unsigned int {
	paddb,          // packed byte addition with wraparound
	paddsb,         // packed byte addition with signed saturation
	paddusb,        // packed byte addition with unsigned saturation
	padddw,         // packed word addition with wraparound
	padddsw,        // packed word addition with signed saturation
	padddusw,       // packed word addition with unsigned saturation
	paddd,          // packed double word addition with wraparound
};

extern "C" MmxVal MmxAdd(MmxVal a, MmxVal b, MmxAddOp op);
int main(void) {
	
	return 0;

}