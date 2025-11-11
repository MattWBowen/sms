#include <M3DUtil/MotionBlendCtrl.hpp>
#include <M3DUtil/M3UJoint.hpp>

TMotionBlendCtrl::TMotionBlendCtrl(bool, int) { }

TMotionBlendCtrl::TMotionBlendCtrl(bool) { }

void TMotionBlendCtrl::execSimpleMotionBlend() { }

float TMotionBlendCtrl::getMotionBlendRatio() const {
    return unk8->unk50;
}

void TMotionBlendCtrl::setMotionBlendRatio(float ratio) {
    unk8->unk50 = ratio;
}

void TMotionBlendCtrl::keepCurAnm(J3DAnmTransform*, float) { }

void TMotionBlendCtrl::setNewAnm(J3DAnmTransform*) { }

J3DAnmTransform* TMotionBlendCtrl::getOldMotionBlendAnmPtr() const { }

void TMotionBlendCtrl::setOldMotionBlendAnmPtr(J3DAnmTransform*) { }

float TMotionBlendCtrl::getOldMotionBlendFrame() const { }
