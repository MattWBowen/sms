#ifndef J2D_PANE_HPP
#define J2D_PANE_HPP

#include <JSystem/JSupport/JSUList.hpp>
#include <JSystem/JUtility/JUTRect.hpp>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx.h>

class J2DAnmBase;
class J2DAnmColor;
class J2DAnmTransform;
class J2DAnmTevRegKey;
class J2DAnmTextureSRTKey;
class J2DAnmVisibilityFull;
class J2DAnmVtxColor;
class J2DGrafContext;
class J2DScreen;
class J2DAnmTexPattern;
class JKRArchive;
class JSURandomInputStream;
struct ResFONT;
struct ResTIMG;

enum J2DRotateAxis {
	/* 0x78 */ ROTATE_X = 'x',
	/* 0x79 */ ROTATE_Y = 'y',
	/* 0x7A */ ROTATE_Z = 'z'
};

enum J2DBasePosition {
	J2DBasePosition_0,
	J2DBasePosition_1,
	J2DBasePosition_2,
	J2DBasePosition_3,
	J2DBasePosition_4,
	J2DBasePosition_5,
};

class J2DPane {
public:
	J2DPane();
	J2DPane(J2DPane*, u16, bool, u32, const JUTRect&);
	J2DPane(u32, const JUTRect&);
	J2DPane(u16, u32, const JUTRect&);
	J2DPane(J2DPane*, JSURandomInputStream*, bool);

	void draw(int, int, const J2DGrafContext*, bool);
	void clip(const JUTRect&);
	void gather(J2DPane**, u32, u32, int, int&);
	void setCullBack(GXCullMode);
	void setBasePosition(J2DBasePosition);
	J2DPane* getFirstChildPane();
	J2DPane* getNextChildPane();
	J2DPane* getParentPane();

	virtual ~J2DPane();

	virtual void move(int x, int y) { mBounds.move(x, y); }
	virtual void add(int x, int y) { mBounds.add(x, y); }
	virtual void resize(int w, int h) { mBounds.resize(w, h); }
	virtual bool setConnectParent(bool connected)
	{
		mConnected = false;
		return false;
	}
	virtual void drawSelf(int x, int y) { }
	virtual void drawSelf(int x, int y, Mtx* mtx) { }
	virtual J2DPane* search(u32 tag);
	virtual void makeMatrix(int, int);

	int getHeight() const { return mBounds.getHeight(); }
	int getWidth() const { return mBounds.getWidth(); }
	JSUTree<J2DPane>* getFirstChild() { return mPaneTree.getFirstChild(); }
	JSUTree<J2DPane>* getEndChild() { return mPaneTree.getEndChild(); }
	const JSUTree<J2DPane>* getPaneTree() { return &mPaneTree; }
	u8 getAlpha() const { return mAlpha; }
	void setAlpha(u8 alpha) { mAlpha = alpha; }

	f32 getRotOffsetX() const { return mRotateOffsetX; }

	f32 getRotOffsetY() const { return mRotateOffsetY; }

	MtxPtr getGlbMtx() { return mGlobalMtx; }

	void setMtx(Mtx m) { MTXCopy(m, mPositionMtx); }

	u32 getKind() const { return mKind; }
	u16 getTag() const { return mInfoTag; }

	bool isVisible() const { return mVisible; }

	void show() { mVisible = true; }
	void hide() { mVisible = false; }

	bool isConnectParent() const { return mConnected; }

	void setUserInfo(u64 info) { mUserInfoTag = info; }
	const Mtx* getMtx() const { return &mPositionMtx; }

	// fabricated
	const JUTRect& getBounds() const { return mBounds; }

public:
	/* 0x4 */ u16 mInfoTag;
	/* 0x8 */ u32 mKind;
	/* 0xC */ bool mVisible;
	/* 0x10 */ u32 mUserInfoTag;
	/* 0x14 */ JUTRect mBounds;
	/* 0x24 */ JUTRect mGlobalBounds;
	/* 0x34 */ JUTRect mClipRect;
	/* 0x44 */ JUTRect mScissorBounds;
	/* 0x54 */ Mtx mPositionMtx;
	/* 0x84 */ Mtx mGlobalMtx;
	/* 0xB4 */ int mRotateOffsetX;
	/* 0xB8 */ int mRotateOffsetY;
	/* 0xBC */ char mRotAxis;
	/* 0xC0 */ f32 mRotation;
	/* 0xC4 */ J2DBasePosition mBasePosition;
	/* 0xC8 */ GXCullMode mCullMode;
	/* 0xCC */ u8 mAlpha;
	/* 0xCD */ u8 mColorAlpha;
	/* 0xCE */ bool mIsInfluencedAlpha;
	/* 0xCF */ bool mConnected;
	/* 0xD0 */ JSUTree<J2DPane> mPaneTree;
};

#endif
