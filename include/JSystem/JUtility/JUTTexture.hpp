#ifndef JUT_TEXTURE_HPP
#define JUT_TEXTURE_HPP

#include <JSystem/ResTIMG.hpp>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <types.h>

class JUTPalette;

class JUTTexture {
public:
	JUTTexture()
	{
		setCaptureFlag(false);
		mEmbPalette = nullptr;
		mTexInfo    = nullptr;
	}

	JUTTexture(const ResTIMG* p_timg)
	{
		mEmbPalette = nullptr;
		storeTIMG(p_timg);
		unk50 = 0;
	}

	JUTTexture(const ResTIMG* p_timg, u32 param_2)
	    : unk50(param_2)
	{
		mEmbPalette = nullptr;
		storeTIMG(p_timg);
	}

	JUTTexture(int, int, GXTexFmt);

	~JUTTexture();
	void storeTIMG(ResTIMG const*);
	void attachPalette(JUTPalette*);
	void initTexObj(GXTlut);
	void initTexObj();
	void load(GXTexMapID);

	const ResTIMG* getTexInfo() const { return mTexInfo; }
	u8 getFormat() const { return mFormat; }
	s32 getTransparency() { return mAlphaEnabled; }
	s32 getWidth() const { return mWidth; }
	s32 getHeight() const { return mHeight; }
	void setCaptureFlag(bool flag) { mFlags &= 2 | flag; }
	u8 getCaptureFlag() const { return mFlags & 1; }
	u8 getEmbPaletteDelFlag() const { return mFlags & 2; }
	void setEmbPaletteDelFlag(bool flag)
	{
		mFlags = (mFlags & 1) | (flag << 1);
	}
	u8 getTlutName() const { return mTlutName; }
	bool operator==(const JUTTexture& other)
	{
		return mTexInfo == other.mTexInfo && field_0x2c == other.field_0x2c
		       && mWrapS == other.mWrapS && mWrapT == other.mWrapT
		       && mMinFilter == other.mMinFilter
		       && mMagFilter == other.mMagFilter && mMinLOD == other.mMinLOD
		       && mMinLOD == other.mMinLOD && mLODBias == other.mLODBias;
	}
	bool operator!=(const JUTTexture& other) { return !operator==(other); }

public:
	/* 0x00 */ GXTexObj mTexObj;
	/* 0x20 */ const ResTIMG* mTexInfo;
	/* 0x24 */ void* mTexData;
	/* 0x28 */ JUTPalette* mEmbPalette;
	/* 0x2C */ JUTPalette* field_0x2c;
	/* 0x30 */ u32 mTlutName;
	/* 0x34 */ u32 mFormat;
	/* 0x38 */ u32 mAlphaEnabled;
	/* 0x3C */ u16 mWidth;
	/* 0x3E */ u16 mHeight;
	/* 0x40 */ u8 mWrapS;
	/* 0x41 */ u8 mWrapT;
	/* 0x42 */ u8 mMinFilter;
	/* 0x43 */ u8 mMagFilter;
	/* 0x44 */ u16 mMinLOD;
	/* 0x46 */ u16 mMaxLOD;
	/* 0x48 */ s16 mLODBias;
	/* 0x4B */ u8 mFlags;
	/* 0x4C */ void* field_0x4c;
	/* 0x50 */ u8 unk50;
};

#endif
