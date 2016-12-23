#include "../SPPoint.h"
#include "unit_test_util.h"
#include <stdbool.h>


//Checks if copy Works
bool pointBasicCopyTest() {
	double data[2] = { 1.0, 1.0 };
	int dim = 2;
	int index = 1;
	SPPoint* p = spPointCreate(data, dim, index);
	SPPoint* q = spPointCopy(p);
	ASSERT_TRUE(spPointGetIndex(p) == spPointGetIndex(q));
	ASSERT_TRUE(spPointGetDimension(p) == spPointGetDimension(q));
	for (int i = 0; i < spPointGetDimension(p); i++) {
		ASSERT_TRUE(spPointGetAxisCoor(p, i) == spPointGetAxisCoor(q, i));
	}
	spPointDestroy(p);
	spPointDestroy(q);
	return true;
}
bool pointBasicL2Distance() {
	double data1[2] = { 1.0, 1.0 };
	double data2[2] = { 1.0, 0.0 };
	int dim1 = 2;
	int dim2 = 2;
	int index1 = 1;
	int index2 = 1;
	SPPoint* p = spPointCreate(data1, dim1, index1);
	SPPoint* q = spPointCreate(data2, dim2, index2);
	ASSERT_TRUE(spPointL2SquaredDistance(p,p) == 0.0);
	ASSERT_TRUE(spPointL2SquaredDistance(q,q) == 0.0);
	ASSERT_TRUE(spPointL2SquaredDistance(p,q) == 1.0);
	spPointDestroy(p);
	spPointDestroy(q);
	return true;
}
double norm(SPPoint* point){
        int dim =spPointGetDimension(point);
        double Norm=0;
        int i = 0;
        for(; i < dim ; i++)
            Norm += spPointGetAxisCoor(point , i) * spPointGetAxisCoor(point , i);
        return Norm;
}

bool pointBasicAxisTest(){
    double dims[3] = {5,2,8};
    double data2[2] = {1,3};
    double data5[5] = {0,3,6,-12,0};
    double data8[8] = {1,0.5,3,6,0.5,0.5,0.5,9};
    SPPoint* dimensions = spPointCreate(dims , 3 , 42);
    ASSERT_TRUE(spPointGetIndex(dimensions)==42);
    SPPoint* dim2 = spPointCreate(data2,2,0);
    SPPoint* dim8 = spPointCreate(data8,8,0);
    SPPoint* dim5 = spPointCreate(data5,5,0);
    ASSERT_TRUE(spPointGetAxisCoor(dimensions , (int)norm(dim2)%3) == 2);
    ASSERT_TRUE(spPointGetAxisCoor(dimensions , (int)norm(dim8)%3) == 8);
    ASSERT_TRUE(spPointGetAxisCoor(dimensions , (int)norm(dim5)%3) == 5);
    spPointDestroy(dimensions);
    spPointDestroy(dim2);
    spPointDestroy(dim5);
    spPointDestroy(dim8);
    return true;

}

int main() {
    RUN_TEST(pointBasicCopyTest);
	RUN_TEST(pointBasicL2Distance);
	RUN_TEST(pointBasicAxisTest);
	return 0;
}
