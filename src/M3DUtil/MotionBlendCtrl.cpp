#include <M3DUtil/MotionBlendCtrl.hpp>
#include <M3DUtil/M3UJoint.hpp>
#include <Camera/cameralib.hpp>


TMotionBlendCtrl::TMotionBlendCtrl(bool param_1, int param_2)
{
    unk0 = 1;

    if (param_2 <= 0) {
        unk4 = 1.0f;
    } else {
        int frameCount = CLBPalFrame(param_2);
        unk4 = 1.0f / (f32)frameCount;
    }

    unk8 = new M3UMtxCalcSIAnmBlendQuat(param_1);
}

TMotionBlendCtrl::TMotionBlendCtrl(bool param_1) 
{ 
    M3UMtxCalcSIAnmBlendQuat *this_00;
    unk0 = 0;
    unk4 = 0.0f; //@1694

    this_00 = new M3UMtxCalcSIAnmBlendQuat(param_1);
    
    unk8 = this_00;
}

void TMotionBlendCtrl::execSimpleMotionBlend()
{
    if ((unk0 & 1) == 0)
        return;

    float diff = unk8->unk50 - unk4;

    if (diff <= 0) {
        diff = 0;
    } else {
        if (unk8->unk58 != 0) {
            *(float*)((u8*)unk8->unk58 + 4) = unk8->unk60;
        }
    }

    unk8->unk50 = diff;
}

float TMotionBlendCtrl::getMotionBlendRatio() const 
{
    return unk8->unk50;
}

void TMotionBlendCtrl::setMotionBlendRatio(float ratio) 
{
    unk8->unk50 = ratio;
}

void TMotionBlendCtrl::keepCurAnm(J3DAnmTransform* transform, float blendFrame) 
{ 
    unk8->unk60 = blendFrame;
    unk8->unk58 = transform;
}

//93.33%
void TMotionBlendCtrl::setNewAnm(J3DAnmTransform* anm) 
{ 
    unk8->unk54 = anm;
    if (unk0 == 0)
        return;
    
    unk8->unk50=1.0f; //@1661
}

J3DAnmTransform* TMotionBlendCtrl::getOldMotionBlendAnmPtr() const
{
    return unk8->unk58;
}

void TMotionBlendCtrl::setOldMotionBlendAnmPtr(J3DAnmTransform* transform) 
{ 
    unk8->unk58 = transform;
}

float TMotionBlendCtrl::getOldMotionBlendFrame() const
{
    return unk8->unk60;
}
