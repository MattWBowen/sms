#ifndef M3DUTIL_M3U_MODEL_HPP
#define M3DUTIL_M3U_MODEL_HPP

#include <JSystem/JDrama/JDRGraphics.hpp>

struct M3UMtxCalcSetInfo {
	/* 0x0 */ u8 unk0;
	/* 0x1 */ u8 unk1;
	/* 0x2 */ u8 type;  
	/* 0x3 */ u8 index; 
};

class J3DModel;
class J3DFrameCtrl;
class J3DAnmTexPattern;
class J3DTexNoAnm;
class J3DMtxCalc;

class M3UModelCommon {
public:
	virtual J3DMtxCalc* getMtxCalc(const M3UMtxCalcSetInfo&);

public:
	/* 0x4 */ void* anmData; // TODO: what is this?
	/* 0x8 */ J3DAnmTexPattern** texPattern;
	/* 0xC */ J3DTexNoAnm** texNoAnm;
	/* 0x10 */ void* unk10;
	/* 0x14 */ void* unk14; 
};

class M3UModel {
public:
	virtual void changeMtxCalcAnmTransform(int, u8);
	virtual void changeAnmTexPattern(int, u8);
	virtual void setMtxCalc(const M3UMtxCalcSetInfo&) { }
	virtual void updateIn();
	virtual void updateOut();
	virtual void entryIn();
	virtual void entryOut();

	void perform(u32, JDrama::TGraphics*);
	void entryOutTexPatternAnm();
	void entryInTexPatternAnm();
	void updateInTexPatternAnm();
	void updateInMotion();

public:
	/* 0x4 */ M3UModelCommon* common;
	/* 0x8 */ J3DModel* jModel;
	/* 0xC */ J3DFrameCtrl* frameControls;
	/* 0x10 */ u16 motionCount;
	/* 0x14 */ void* unk14; // TODO: what is this? //todo: MotionInfo
	/* 0x18 */ u32 unk18;
	/* 0x1C */ u8* texPatternInfo;
};

#endif
