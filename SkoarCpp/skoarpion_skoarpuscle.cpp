#include "skoarpion.hpp"
#include "skoarpion_skoarpuscle.hpp"

// --- SkoarpuscleSkoarpion ------------------------------------------------
SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpionPtr s) {
    val = s;
    on_enter = [this](SkoarMinstrelPtr m) {
        this->on_enter_method(m);
    };
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpionPtr s, SkoarNoadPtr) {
    val = s;
    on_enter = [this](SkoarMinstrelPtr m) {
        this->on_enter_method(m);
    };
}


Skoarpuscle *SkoarpuscleSkoarpion::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
    //msg_arr = msg->get_msg_arr(minstrel);
    return this;
}

void SkoarpuscleSkoarpion::on_enter_method(SkoarMinstrelPtr m) {
    SkoarpionPtr skrp = val.extract<SkoarpionPtr>();
    auto name = skrp->name;
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
SkoarpuscleProjection::SkoarpuscleProjection(SkoarProjectionPtr) {

}

// --- SkoarpuscleProjections ----------------------------------------------
SkoarpuscleProjections::SkoarpuscleProjections(ListOfSkoarProjectionsPtr) {

}