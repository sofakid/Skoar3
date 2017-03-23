#include "minstrel.hpp"


// --- SkoarMinstrel -------------------------------------

SkoarMinstrel::SkoarMinstrel(SkoarString name, SkoarKoarPtr koar, Skoar* skoar) :
    skoar(skoar),
    koar(koar),
    fairy(nullptr),
    event_stream(nullptr),
    all_voice(skoar->all_voice)
{
    // some defaults
    koar->put(L"octave", make_skoarpuscle(5));
    koar->put(L"tempo", make_skoarpuscle(1));
    koar->put(L"amp", make_skoarpuscle(0.2));
    koar->put(L"legato", make_skoarpuscle(1));
    koar->put(L"stretch", make_skoarpuscle(1));

    koar->put(L"num_impression", make_skoarpuscle(0));
    koar->put(L"sym_impression", make_skoarpuscle(L"lin"));
    koar->put(L"dyn_impression", make_skoarpuscle(nullptr));

    //controls = make_shared<SkoarControls>(name);
}

SkoarMinstrel::~SkoarMinstrel() {
    //event_stream->destroy();
    event_stream = nullptr;
    fairy->fly_away();
    fairy = nullptr;
    koar = nullptr;
    all_voice = nullptr;
    skoar = nullptr;
}

SkoarMinstrelPtr SkoarMinstrel::New(SkoarString name, SkoarKoarPtr koar, Skoar* skoar) {
    auto m = make_shared<SkoarMinstrel>(name, koar, skoar);
    m->fairy = make_shared<SkoarFairy>(L"$" + name, m);
    SkoarMinstrel::EventStream(m);
    return m;
}

void SkoarMinstrel::EventStream(SkoarMinstrelPtr m) {
    auto x = m->skoar->tree->next_skoarpuscle();
    auto skoarpion = skoarpuscle_ptr<SkoarpuscleSkoarpion>(x)->val;

    auto f_event_stream = [=]() {
        auto running = false;

        while (running) {
            try {
                m->koar->do_skoarpion(skoarpion, m, SkoarKoar::EExecStyle::NORMAL, nullptr);

                throw SkoarNav(SkoarNav::DONE);
            }
            catch (SkoarNav &nav_result) {
                switch (nav_result.code) {

                case SkoarNav::DONE:
                    running = false;
                    break;

                case SkoarNav::CODA:
                    throw SkoarError(L"Unhandled Coda");
                    break;

                case SkoarNav::DA_CAPO:
                    // do nothing, will enter skoarpion again
                    break;

                case SkoarNav::SEGNO:
                    throw SkoarError(L"Unhandled Segno");
                    break;

                case SkoarNav::COLON:
                    // do nothing, will enter skoarpion again
                    break;

                case SkoarNav::FINE:
                    running = false;
                    break;
                };

            }
        }

        // todo: uncomment when lute exists
        //if (m->fairy->lute != nullptr) {
        //    m->fairy->lute->flush_everything();
        //}

        m->skoar->one_less_running();
    };
}

SkoarEventPtr SkoarMinstrel::nextEvent() {
    return nullptr;
}

SkoarEventStreamPtr SkoarMinstrel::pfunk() {
    return nullptr;
}

void SkoarMinstrel::reset_colons() {

}



// --- Skoarchestra ----------------------------------------

Skoarchestra::Skoarchestra(Skoar*) {

}

Skoarchestra::~Skoarchestra() {

}

SkoarEventStreamPtr Skoarchestra::eventStream() {
    return nullptr;
}

SkoarEventStreamPtr Skoarchestra::pfunk() {
    return nullptr;
}

