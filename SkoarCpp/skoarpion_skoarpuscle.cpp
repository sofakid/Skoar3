#include "skoarpion_skoarpuscle.hpp"

// --- SkoarpuscleSkoarpion ------------------------------------------------
SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(Skoarpion *s) {
    val = s;
    on_enter = [this](SkoarMinstrel *m) {
        this->on_enter_method(m);
    };
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(Skoarpion *s, SkoarNoadPtr) {
    val = s;
    on_enter = [this](SkoarMinstrel *m) {
        this->on_enter_method(m);
    };
}


Skoarpuscle *SkoarpuscleSkoarpion::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {
    //msg_arr = msg->get_msg_arr(minstrel);
    return this;
}

void SkoarpuscleSkoarpion::on_enter_method(SkoarMinstrel *m) {
    Skoarpion* skrp = val.extract<Skoarpion*>();
    auto name = SkoarString(L"derp");// skrp->name;
    if (name.size() > 0) {
        //m->koar[name] = this;
    }

    if (msg_arr.empty() == false) {
        //m->koar.do_skoarpion(skrp, m, msg_arr, nullptr);
    }
}

// --- SkoarpuscleSkoarpionSig ----------------------------------------------
SkoarpuscleSkoarpionSig::SkoarpuscleSkoarpionSig(SkoarNoadPtr noad) {

}


// --- SkoarpuscleArgExpr ----------------------------------------------
SkoarpuscleArgExpr::SkoarpuscleArgExpr() {

}


// --- SkoarpuscleArgList ----------------------------------------------
SkoarpuscleArgList::SkoarpuscleArgList(SkoarNoadPtr) {

}


// --- SkoarpuscleProjection ----------------------------------------------
SkoarpuscleProjection::SkoarpuscleProjection(SkoarProjection *) {

}