#include "meditation.hpp"
#include "noad.hpp"
#include "skoarpion.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"

// --- SkoarpuscleMeditation ---------------------------------------------
SkoarpuscleMeditation::SkoarpuscleMeditation(Skoar* skoar, SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Meditation");
#endif
    auto med_root (SkoarNoad::NewArtificial (L"meditation"));

    for (auto& x : noad->children)
        med_root->add_noad (x);
    noad->children.clear (); 

    skoarpion = Skoarpion::NewFromSubtree (skoar, med_root);

}

SkoarpuscleMeditation::SkoarpuscleMeditation (SkoarpionPtr p) :
    skoarpion (p)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Meditation");
#endif
}

SkoarpuscleMeditation::~SkoarpuscleMeditation ()
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Goto");
#endif
    clear ();
}

void SkoarpuscleMeditation::clear ()
{
    skoarpion = nullptr;
}

SkoarpusclePtr SkoarpuscleMeditation::duplicate ()
{
    return std::make_shared<SkoarpuscleMeditation>(skoarpion);
}

void SkoarpuscleMeditation::on_enter (SkoarMinstrelPtr m)
{
    m->fairy->impress (duplicate ());
}


void SkoarpuscleMeditation::run (SkoarMinstrelPtr m) {
    auto impression = m->fairy->impression;
    m->koar->do_skoarpion (skoarpion, m, SkoarKoar::EExecStyle::MEDITATION, impression);
}

SkoarpusclePtr SkoarpuscleMeditation::skoar_msg (SkoarString /*sel*/, SkoarpusclePtr /*args*/, SkoarMinstrelPtr /*m*/) {
    //args = msg->get_msg_arr(minstrel);
    return nullptr;
}



// --- SkoarpuscleMeditationMsg ------------------------------------------
SkoarpuscleMeditationMsg::SkoarpuscleMeditationMsg(Skoar* /*skoar*/, SkoarNoadPtr /*noad*/) {

}

