#ifndef J3DSTRUCT_H
#define J3DSTRUCT_H

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class J3DLightInfo {
public:
	J3DLightInfo& operator=(const J3DLightInfo& other)
	{
		mLightPosition.x = other.mLightPosition.x;
		mLightPosition.y = other.mLightPosition.y;
		mLightPosition.z = other.mLightPosition.z;

		mLightDirection.x = other.mLightDirection.x;
		mLightDirection.y = other.mLightDirection.y;
		mLightDirection.z = other.mLightDirection.z;

		mColor.r = other.mColor.r;
		mColor.g = other.mColor.g;
		mColor.b = other.mColor.b;
		mColor.a = other.mColor.a;

		mCosAtten.x = other.mCosAtten.x;
		mCosAtten.y = other.mCosAtten.y;
		mCosAtten.z = other.mCosAtten.z;

		mDistAtten.x = other.mDistAtten.x;
		mDistAtten.y = other.mDistAtten.y;
		mDistAtten.z = other.mDistAtten.z;

		return *this;
	}

	/* 0x00 */ Vec mLightPosition;
	/* 0x0C */ Vec mLightDirection;
	/* 0x18 */ GXColor mColor;
	/* 0x1C */ Vec mCosAtten;
	/* 0x28 */ Vec mDistAtten;
}; // Size = 0x34

struct J3DTextureSRTInfo {
	J3DTextureSRTInfo& operator=(const J3DTextureSRTInfo& other)
	{
		mScaleX       = other.mScaleX;
		mScaleY       = other.mScaleY;
		mRotation     = other.mRotation;
		mTranslationX = other.mTranslationX;
		mTranslationY = other.mTranslationY;
		return *this;
	}

	/* 0x00 */ f32 mScaleX;
	/* 0x04 */ f32 mScaleY;
	/* 0x08 */ s16 mRotation;
	/* 0x0C */ f32 mTranslationX;
	/* 0x10 */ f32 mTranslationY;
}; // Size: 0x14

enum J3DTexMtxMode {
	J3DTexMtxMode_None,
	J3DTexMtxMode_EnvmapBasic,
	J3DTexMtxMode_ProjmapBasic,
	J3DTexMtxMode_ViewProjmapBasic,
	J3DTexMtxMode_Unknown4,
	J3DTexMtxMode_Unknown5,
	J3DTexMtxMode_EnvmapOld,
	J3DTexMtxMode_Envmap,
	J3DTexMtxMode_Projmap,
	J3DTexMtxMode_ViewProjmap,
	J3DTexMtxMode_EnvmapOldEffectMtx,
	J3DTexMtxMode_EnvmapEffectMtx,
};

struct J3DTexMtxInfo {
	J3DTexMtxInfo& operator=(const J3DTexMtxInfo& other)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mEffectMtx[i][j] = other.mEffectMtx[i][j];
			}
		}
		mCenter.x   = other.mCenter.x;
		mCenter.y   = other.mCenter.y;
		mCenter.z   = other.mCenter.z;
		mProjection = other.mProjection;
		mInfo       = other.mInfo;
		mSRT        = other.mSRT;
		return *this;
	}
	void setEffectMtx(Mtx m)
	{
		mEffectMtx[0][0] = m[0][0];
		mEffectMtx[0][1] = m[0][1];
		mEffectMtx[0][2] = m[0][2];
		mEffectMtx[0][3] = m[0][3];

		mEffectMtx[1][0] = m[1][0];
		mEffectMtx[1][1] = m[1][1];
		mEffectMtx[1][2] = m[1][2];
		mEffectMtx[1][3] = m[1][3];

		mEffectMtx[2][0] = m[2][0];
		mEffectMtx[2][1] = m[2][1];
		mEffectMtx[2][2] = m[2][2];
		mEffectMtx[2][3] = m[2][3];

		mEffectMtx[3][0] = 0.0f;
		mEffectMtx[3][1] = 0.0f;
		mEffectMtx[3][2] = 0.0f;
		mEffectMtx[3][3] = 1.0f;
	}

	/* 0x00 */ u8 mProjection;
	/* 0x01 */ u8 mInfo;
	/* 0x02 */ u8 padding[2];
	/* 0x04 */ Vec mCenter;
	/* 0x10 */ J3DTextureSRTInfo mSRT;
	/* 0x24 */ Mtx44 mEffectMtx;
}; // Size: 0x64

struct J3DIndTexMtxInfo {
	J3DIndTexMtxInfo& operator=(const J3DIndTexMtxInfo& other)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				mOffsetMtx[i][j] = other.mOffsetMtx[i][j];
			}
		}
		mScaleExp = other.mScaleExp;
		return *this;
	}

	/* 0x00 */ f32 mOffsetMtx[2][3];
	/* 0x18 */ s8 mScaleExp;
}; // Size: 0x1C

struct J3DFogInfo {
	J3DFogInfo& operator=(const J3DFogInfo& other)
	{
		mType      = other.mType;
		mAdjEnable = other.mAdjEnable;
		mCenter    = other.mCenter;
		mStartZ    = other.mStartZ;
		mEndZ      = other.mEndZ;
		mNearZ     = other.mNearZ;
		mFarZ      = other.mFarZ;
		mColor.r   = other.mColor.r;
		mColor.g   = other.mColor.g;
		mColor.b   = other.mColor.b;
		mColor.a   = other.mColor.a;
		for (int i = 0; i < 10; i++) {
			mFogAdjTable[i] = other.mFogAdjTable[i];
		}
		return *this;
	}

	/* 0x00 */ u8 mType;
	/* 0x01 */ u8 mAdjEnable;
	/* 0x02 */ u16 mCenter;
	/* 0x04 */ f32 mStartZ;
	/* 0x08 */ f32 mEndZ;
	/* 0x0C */ f32 mNearZ;
	/* 0x10 */ f32 mFarZ;
	/* 0x14 */ GXColor mColor;
	/* 0x18 */ u16 mFogAdjTable[10];
}; // Size: 0x2C

struct J3DNBTScaleInfo {
	/* 0x0 */ u8 mbHasScale;
	/* 0x4 */ Vec mScale;

	J3DNBTScaleInfo& operator=(const J3DNBTScaleInfo& other)
	{
		mbHasScale = other.mbHasScale;
		mScale.x   = other.mScale.x;
		mScale.y   = other.mScale.y;
		mScale.z   = other.mScale.z;
		return *this;
	}
}; // Size: 0x10

struct J3DIndTexOrderInfo {
	J3DIndTexOrderInfo& operator=(const J3DIndTexOrderInfo& other)
	{
		mCoord = other.mCoord;
		mMap   = other.mMap;
		return *this;
	}

	/* 0x0 */ u8 mCoord;
	/* 0x1 */ u8 mMap;
	/* 0x2 */ u8 field_0x2;
	/* 0x3 */ u8 field_0x3;
};

struct J3DTevSwapModeInfo {
	/* 0x0 */ u8 mRasSel __attribute__((aligned(4)));
	/* 0x1 */ u8 mTexSel;
};

struct J3DTevSwapModeTableInfo {
	/* 0x0 */ u8 field_0x0;
	/* 0x1 */ u8 field_0x1;
	/* 0x2 */ u8 field_0x2;
	/* 0x3 */ u8 field_0x3;
};

struct J3DTevStageInfo {
	/* 0x0 */ u8 field_0x0;
	/* 0x1 */ u8 field_0x1;
	/* 0x2 */ u8 field_0x2;
	/* 0x3 */ u8 field_0x3;
	/* 0x4 */ u8 field_0x4;
	/* 0x5 */ u8 field_0x5;
	/* 0x6 */ u8 field_0x6;
	/* 0x7 */ u8 field_0x7;
	/* 0x8 */ u8 field_0x8;
	/* 0x9 */ u8 field_0x9;
	/* 0xA */ u8 field_0xa;
	/* 0xB */ u8 field_0xb;
	/* 0xC */ u8 field_0xc;
	/* 0xD */ u8 field_0xd;
	/* 0xE */ u8 field_0xe;
	/* 0xF */ u8 field_0xf;
	/* 0x10 */ u8 field_0x10;
	/* 0x11 */ u8 field_0x11;
	/* 0x12 */ u8 field_0x12;
	/* 0x13 */ u8 field_0x13;
};

struct J3DIndTevStageInfo {
	J3DIndTevStageInfo& operator=(const J3DIndTevStageInfo& other)
	{
		mIndStage  = other.mIndStage;
		mIndFormat = other.mIndFormat;
		mBiasSel   = other.mBiasSel;
		mMtxSel    = other.mMtxSel;
		mWrapS     = other.mWrapS;
		mWrapT     = other.mWrapT;
		mPrev      = other.mPrev;
		mLod       = other.mLod;
		mAlphaSel  = other.mAlphaSel;
		return *this;
	}

	/* 0x0 */ u8 mIndStage;
	/* 0x1 */ u8 mIndFormat;
	/* 0x2 */ u8 mBiasSel;
	/* 0x3 */ u8 mMtxSel;
	/* 0x4 */ u8 mWrapS;
	/* 0x5 */ u8 mWrapT;
	/* 0x6 */ u8 mPrev;
	/* 0x7 */ u8 mLod;
	/* 0x8 */ u8 mAlphaSel;
	/* 0x9 */ u8 unk9; // TODO: are these really here? tww used alignment...
	/* 0xA */ u8 unkA;
	/* 0xB */ u8 unkB;
};

struct J3DTexCoordInfo {
	J3DTexCoordInfo& operator=(const J3DTexCoordInfo& other)
	{
		mTexGenType = other.mTexGenType;
		mTexGenSrc  = other.mTexGenSrc;
		mTexGenMtx  = other.mTexGenMtx;
		return *this;
	}

	/* 0x0 */ u8 mTexGenType __attribute__((aligned(4)));
	/* 0x1 */ u8 mTexGenSrc;
	/* 0x2 */ u8 mTexGenMtx;
};

struct J3DIndTexCoordScaleInfo {
	J3DIndTexCoordScaleInfo& operator=(const J3DIndTexCoordScaleInfo& other)
	{
		mScaleS = other.mScaleS;
		mScaleT = other.mScaleT;
		return *this;
	}

	/* 0x0 */ u8 mScaleS;
	/* 0x1 */ u8 mScaleT;
	/* 0x2 */ u8 field_0x2;
	/* 0x3 */ u8 field_0x3;
};

struct J3DBlendInfo {
	J3DBlendInfo& operator=(const J3DBlendInfo& other)
	{
		mBlendMode = other.mBlendMode;
		mSrcFactor = other.mSrcFactor;
		mDstFactor = other.mDstFactor;
		mLogicOp   = other.mLogicOp;
		return *this;
	}

	/* 0x0 */ u8 mBlendMode;
	/* 0x1 */ u8 mSrcFactor;
	/* 0x2 */ u8 mDstFactor;
	/* 0x3 */ u8 mLogicOp;
};

struct J3DTevOrderInfo {
	J3DTevOrderInfo& operator=(const J3DTevOrderInfo& other)
	{
		mTexCoord  = other.mTexCoord;
		mTexMap    = other.mTexMap;
		mColorChan = other.mColorChan;
		return *this;
	}

	/* 0x0 */ u8 mTexCoord __attribute__((aligned(2)));
	/* 0x1 */ u8 mTexMap;
	/* 0x2 */ u8 mColorChan;
};

struct J3DColorChanInfo {
	/* 0x0 */ u8 mEnable;
	/* 0x1 */ u8 mMatSrc;
	/* 0x2 */ u8 mLightMask;
	/* 0x3 */ u8 mDiffuseFn;
	/* 0x4 */ u8 mAttnFn;
	/* 0x5 */ u8 mAmbSrc;
	/* 0x6 */ u8 field_0x6;
	/* 0x7 */ u8 field_0x7;
};

struct J3DZModeInfo {
	/* 0x00 */ u8 mCompareEnable;
	/* 0x01 */ u8 mFunc;
	/* 0x02 */ u8 mUpdateEnable;
	/* 0x03 */ u8 pad;
};

struct J3DAlphaCompInfo {
	/* 0x0 */ u8 mComp0;
	/* 0x1 */ u8 mRef0;
	/* 0x2 */ u8 mOp;
	/* 0x3 */ u8 mComp1;
	/* 0x4 */ u8 mRef1;

	/* 0x5 */ u8 field_0x5;
	/* 0x6 */ u8 field_0x6;
	/* 0x7 */ u8 field_0x7;
};

#endif /* J3DSTRUCT_H */
