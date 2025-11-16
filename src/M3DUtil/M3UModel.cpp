#include <M3DUtil/M3UModel.hpp>
#include <JSystem/J3D/J3DGraphAnimator/J3DModel.hpp>
#include <JSystem/J3D/J3DGraphAnimator/J3DJoint.hpp>
#include <JSystem/J3D/J3DGraphAnimator/J3DAnimation.hpp>
#include <JSystem/J3D/J3DGraphLoader/J3DModelLoader.hpp>

//98.26%
J3DMtxCalc* M3UModelCommon::getMtxCalc(const M3UMtxCalcSetInfo& info) {
	J3DMtxCalc** ptr;

	switch (info.type) {
		case 0:
			ptr = (J3DMtxCalc**)((int)unk10 + (u8)info.index * 0x70);
			if (ptr == 0) break;
			return *ptr;
		case 1:
			ptr = (J3DMtxCalc**)((int)unk14 + (u8)info.index * 0x70);
			if (ptr == 0) break;
			return *ptr;
		default:
			return 0;
	}
}

//87.41%
void M3UModel::changeMtxCalcAnmTransform(int param_1, u8 param_2) {
	u8* ptr = &texPatternInfo[param_1 * 2];
	*ptr = param_2;

	int value = *(s16*)((u32)common->texPattern[param_2] + 2);

	J3DFrameCtrl* ctrl = &frameControls[ptr[1]];
	*(s16*)((u32)ctrl + 8) = value;
	*(f32*)((u32)ctrl + 0x10) = 0.0f;
}

void M3UModel::changeAnmTexPattern(int param_1, u8 param_2)
{
	u8* ptr = &texPatternInfo[param_1 * 2];
	ptr[0]  = param_2;

	J3DFrameCtrl& ctrl = frameControls[ptr[1]];
	ctrl.mEndFrame     = common->texPattern[param_2]->getFrameMax();
	ctrl.mCurrentFrame = 0.0f;
}

void M3UModel::updateInMotion()
{
	int offset = 0;
	for (int i = 0; i < motionCount; i++) {
		u16* entry = (u16*)((u32)motionInfo + offset);

		J3DFrameCtrl* frameCtrl = &frameControls[*((u8*)entry + 5)];
		J3DAnmBase* matAnm = ((J3DAnmBase**)common->anmData)[*((u8*)entry + 4)];

		frameCtrl->update();

		J3DJoint* joint = jModel->mModelData->mJointNodePointer[*entry];

		if (*((u8*)entry + 3) == 0xFF) {
			joint->setMtxCalc(nullptr);
		} else {
			matAnm->mFrame = frameCtrl->mCurrentFrame;

			switch (*((u8*)entry + 2)) {
				case 1:
					*(J3DAnmBase**)((u32)common->unk14 + *((u8*)entry) * 0x70 + 0x58) = matAnm;
					break;
				case 0:
					*(J3DAnmBase**)((u32)common->unk10 + *((u8*)entry) * 0x70 + 0x58) = matAnm;
					break;
			}

			joint->setMtxCalc(common->getMtxCalc(*(M3UMtxCalcSetInfo*)entry));
		}

		offset += 6;
		
	}
}

void M3UModel::updateInTexPatternAnm()
{
	if (texPatternInfo)
		frameControls[texPatternInfo[1]].update();
}

void M3UModel::updateIn()
{
	updateInMotion();
	updateInTexPatternAnm();
}

void M3UModel::updateOut()
{
	for (int i = 0; i < motionCount; i++) {
		M3UMotionInfo* entry = &motionInfo[i];
		J3DJoint** joints = jModel->mModelData->mJointNodePointer;
		J3DJoint* joint = joints[entry->jointNo];
		joint->setMtxCalc(nullptr);
	}
}

//67.74, make this better
void M3UModel::entryIn()
{
	u8* ptr = texPatternInfo;
	if (ptr != nullptr) {
		if (ptr[1] != 0xFF) {
			u8 index1 = ptr[1];
			J3DAnmTexPattern* pattern = common->texPattern[ptr[0]];
			pattern->mFrame = frameControls[index1].mCurrentFrame;
			jModel->mModelData->setTexNoAnimator(pattern, common->texNoAnm[ptr[0]]);
		}
	}
}

void M3UModel::entryOut()
{
	if (texPatternInfo != nullptr && texPatternInfo[0] != 0xFF) { 
		J3DAnmTexPattern* anim = common->texPattern[texPatternInfo[0]];
		jModel->mModelData->removeTexNoAnimator(anim);
	}
}

void M3UModel::perform(u32 flags, JDrama::TGraphics* graphics)
{
	if (flags & 0x2) {
		updateIn();
		jModel->calc();
		updateOut();
	}

	if (flags & 0x4) {
		jModel->viewCalc();
	}

	if (flags & 0x200) {
		entryIn();
		jModel->entry();
		entryOut();
	}
}
