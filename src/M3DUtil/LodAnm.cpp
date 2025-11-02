#include <M3DUtil/LodAnm.hpp>
#include <M3DUtil/MActor.hpp>
#include <M3DUtil/MActorData.hpp>

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

int TLodAnm::setBckAnm_(int param_1) {
    if (param_1 < 0) {
        (*(MActor**)((char*)mActor + 0x74))->setBckFromIndex(-1);
        return 1;
    }

    int changed = 0;
    int currentAnmIdx = (*(MActor**)((char*)mActor + 0x74))->getCurAnmIdx(0);
    int anmIdx;
    if (mIndex == 0) {
        anmIdx = param_1;
    } else {
        anmIdx = *(int*)((char*)mIndex + (param_1 << 4) + (mParam3 << 2));
    }

    int* remapPtr = mField18;
    if (remapPtr != nullptr) {
        while (*remapPtr >= 0) {
            if (anmIdx == *remapPtr) {
                anmIdx = remapPtr[1];
                break;
            }
            remapPtr += 2;
        }
    }

    if (currentAnmIdx != anmIdx) {
        (*(MActor**)((char*)mActor + 0x74))->setBckFromIndex(anmIdx);
        changed = 1;
    }

    return changed;
}

int TLodAnm::setBtpAnm_(int param_1) {
    if (param_1 < 0) {
        (*(MActor**)((char*)mActor + 0x74))->setBtpFromIndex(-1);
        return 1;
    }

    int changed = 0;
    int currentAnmIdx = (*(MActor**)((char*)mActor + 0x74))->getCurAnmIdx(3);
    char* basePtr = (char*)mIndex;
    basePtr += (param_1 << 4);
    basePtr += (mParam3 << 2);
    int anmIdx = *(int*)(basePtr + 8);

    if (mField1C != nullptr) {
        int* remapPtr = mField1C;
        while (*remapPtr >= 0) {
            if (anmIdx == *remapPtr) {
                anmIdx = remapPtr[1];
                break;
            }
            remapPtr += 2;
        }
    }

    if (currentAnmIdx != anmIdx) {
        (*(MActor**)((char*)mActor + 0x74))->setBtpFromIndex(anmIdx);
        changed = 1;
    }

    return changed;
}
int TLodAnm::setBckAndBtpAnm(int param_1) {
    int result = setBckAnm_(param_1);
    if (mIndex != 0) {
        setBtpAnm_(param_1);
    }
    mField14 = param_1;
    return result;
}