#include <M3DUtil/LodAnm.hpp>

//bad: slwi r0, r0, 2      good: //slwi r0, r0, 4     me: 
TLodAnm::TLodAnm(TLiveActor* param_1, const TLodAnmIndex* param_2, int param_3, float param_4) {
    mActor = param_1;
    mIndex = param_2;
    mParam3 = param_3;
    mParam4 = param_4;

    mField10 = 0;
    mField14 = -1;
    mField18 = 0;
    mField1C = 0;
    
    if (param_2 != 0) {

        while (param_2[mField10].index >= -1) {
            mField10++;
        }
    }
} 

void TLodAnm::setBckAnm_(int) { }

void TLodAnm::setBtpAnm_(int param_1) { }
void TLodAnm::setBckAndBtpAnm(int param_1) 
{ 
    //TODO

    setBckAnm_(param_1);
    if (mIndex != 0)
    {
        setBtpAnm_(param_1);
    }
}