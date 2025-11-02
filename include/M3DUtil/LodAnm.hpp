#ifndef M3DUTIL_LOD_ANM_HPP
#define M3DUTIL_LOD_ANM_HPP

class TLiveActor;
struct TLodAnmIndex {
	int index;
	int data[3];
}; 


class TLodAnm {
public:
    TLodAnm(TLiveActor* param_1, const TLodAnmIndex* param_2, int param_3, float param_4);

    void execChangeLod();
    int setBckAndBtpAnm(int);
   
    
    //was void, int for testing
    int setBtpAnm_(int);
    int setBckAnm_(int);

    /* 0x0 */ TLiveActor* mActor;     
    /* 0x04 */const TLodAnmIndex* mIndex;     
    
	/* 0x08 */int mParam3;                    
    /* 0x0c */float mParam4;                 
    /* 0x10 */int mField10;
    /* 0x14 */int mField14;
    /* 0x18 */int* mField18;
    /* 0x1c */int* mField1C;             
};
#endif