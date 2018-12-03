#include "minstrel.hpp"

// --- SkoarMinstrel -------------------------------------
SkoarMinstrel::SkoarMinstrel (
    SkoarString minstrel_name,
    SkoarKoarPtr koar,
    Skoar* const skoar,
    const SpellOfHappening& spell)
    :
    t0 (0.0),
    tAccumulated (0.0),
    name(minstrel_name),
    skoar(skoar),
    koar(koar),
    fairy(nullptr),
    all_voice(skoar->all_voice),
    happenSpell(spell),
    isDebugging(false)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocMinstrel(name);
#endif

    // some defaults
    auto& k (*koar);
    k.put (L"octave", make_skoarpuscle(5));
    k.put (L"bps", make_skoarpuscle (2.0));
    k.put (L"bpm", make_skoarpuscle(120.0));
    k.put (L"amp", make_skoarpuscle(0.2));
    k.put (L"legato", make_skoarpuscle(1.0));
    k.put (L"stretch", make_skoarpuscle(1.0));
     
    k.put (L"num_impression", make_skoarpuscle(0.0));
    k.put (L"sym_impression", make_skoarpuscle(SkoarString(L"lin")));
    k.put (L"dyn_impression", make_skoarpuscle(nullptr));

    //controls = make_shared<SkoarControls>(name);
}

SkoarMinstrel::~SkoarMinstrel() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocMinstrel(name);
#endif
    clear ();
}

void SkoarMinstrel::clear () {
    if (fairy != nullptr)
        fairy->fly_away ();
    fairy = nullptr;
    koar = nullptr;
    all_voice = nullptr;
    f = nullptr;
}

SkoarMinstrelPtr SkoarMinstrel::New(
    SkoarString name, 
    SkoarKoarPtr koar, 
    Skoar* const skoar,
    const SpellOfHappening& spell) 
{
    auto m = make_shared<SkoarMinstrel>(name, koar, skoar, spell);
    m->fairy = make_shared<SkoarFairy>(L"$" + name, m);
    SkoarMinstrel::ready_stream (m);
    return m;
}

SkoarMinstrelPtr SkoarMinstrel::NewForSkoarpion (
    SkoarString name, 
    SkoarKoarPtr koar, 
    Skoar* const skoar, 
    SkoarpionPtr skoarpion, 
    const SpellOfHappening& spell)
{
    auto m = make_shared<SkoarMinstrel> (name, koar, skoar, spell);
    m->fairy = make_shared<SkoarFairy> (L"$" + name, m);
    SkoarMinstrel::ready_skoarpion (m, skoarpion);
    return m;
}


SkoarMinstrelPtr SkoarMinstrel::NewDebugging(
    SkoarString name, 
    SkoarKoarPtr koar,
    Skoar* const skoar,
    const SpellOfHappening& spell, 
    const MinstrelDebugConfig& config) 
{
    auto m = make_shared<DebuggingMinstrel>(name, koar, skoar, spell, config);
    m->fairy = make_shared<SkoarFairy>(L"$" + name, m);
    SkoarMinstrel::ready_stream (m);
    return m;
}


SkoarMinstrelPtr SkoarMinstrel::NewDebuggingForSkoarpion (
    SkoarString name,
    SkoarKoarPtr koar,
    Skoar* const skoar,
    SkoarpionPtr skoarpion,
    const SpellOfHappening& spell,
    const MinstrelDebugConfig& config)
{
    auto m = make_shared<DebuggingMinstrel> (name, koar, skoar, spell, config);
    m->fairy = make_shared<SkoarFairy> (L"$" + name, m);
    SkoarMinstrel::ready_skoarpion (m, skoarpion);
    return m;
}


void SkoarMinstrel::start() {
    if (musicker != nullptr)
        t0 = musicker->getTime ();
    tAccumulated = t0;

    skoar->one_more_running ();
    f();
}

void SkoarMinstrel::ready_stream(SkoarMinstrelPtr m) {
    
    if (m->skoar == nullptr)
        return;

    auto tree = m->skoar->tree;
    if (tree == nullptr)
        return;

    auto x = tree->next_skoarpuscle();
    if (is_skoarpuscle<SkoarpuscleSkoarpion>(x))
        ready_skoarpion (m, skoarpuscle_ptr<SkoarpuscleSkoarpion> (x)->val);
}


void SkoarMinstrel::ready_skoarpion (SkoarMinstrelPtr m, SkoarpionPtr skoarpion) {
    m->f = [=]() {
        auto running = true;

        while (running)
        {
            try
            {
                m->koar->do_skoarpion (skoarpion, m, SkoarKoar::EExecStyle::NORMAL, nullptr);
                throw SkoarNav (SkoarNav::DONE);
            }
            catch (SkoarNav &nav_result)
            {
                switch (nav_result.code)
                {

                case SkoarNav::DONE:
                    running = false;
                    break;

                case SkoarNav::CODA:
                    throw SkoarError (L"Unhandled Coda");
                    break;

                case SkoarNav::COLON:
                    // do nothing, will enter skoarpion again
                    break;

                };

            }
        }

        // todo: uncomment when lute exists
        //if (m->fairy->lute != nullptr) {
        //    m->fairy->lute->flush_everything();
        //}

        m->done ();
    };
}

void SkoarMinstrel::done () {
    skoar->one_less_running ();
    exiting ();
}
void SkoarMinstrel::reset_colons() {
    fairy->forget_that_you_have_seen(ESkoarpuscle::Bars);
    //koar->state_put(L"colons_burned", make_shared<SkoarDic>());
}

void SkoarMinstrel::happen(SkoarEventPtr p) {
    bool isRest = is_skoarpuscle<SkoarpuscleTrue> (p->at (L"isRest"));
    if (musicker != nullptr)
    {
        musicker->config (p);
        if (!isRest)
            musicker->noteOn ();
    }

    happenSpell (p);
    
    if (musicker != nullptr)
    {
        auto bps = skoarpuscle_ptr<SkoarpuscleFloat> (p->at (L"bps"))->val;
        auto dur = skoarpuscle_ptr<SkoarpuscleFloat> (p->at (L"dur"))->val;

        if (bps < 0.f)
            bps *= -1.f;
        if (bps == 0.f)
            bps = 120.f;

        if (dur < 0.f)
            dur *= -1.f;

        SkoarFloat exactDur = (1000.0 / bps) * dur;
        tAccumulated += exactDur;
        SkoarFloat tNow = musicker->getTime ();

        SkoarFloat fSleepFor = tAccumulated - tNow;

        if (fSleepFor > 0.0)
        {
            uint64_t sleepFor = static_cast<uint64_t> (fSleepFor);
            if (sleepFor > INT_MAX)
                sleepFor = INT_MAX - 1;

            musicker->sleep (static_cast<int>(sleepFor));
        }
    
        if (!isRest)
            musicker->noteOff ();
    }
}


void SkoarMinstrel::before_entering_noad(SkoarMinstrelPtr, SkoarNoadite*) {
}

void SkoarMinstrel::after_entering_noad(SkoarMinstrelPtr, SkoarNoadite*) {
}

void SkoarMinstrel::before_entering_skoarpuscle(SkoarMinstrelPtr, SkoarpusclePtr) {
}

void SkoarMinstrel::after_entering_skoarpuscle(SkoarMinstrelPtr, SkoarpusclePtr) {
}

void SkoarMinstrel::before_entering_skoarpion(SkoarMinstrelPtr, SkoarpionPtr) {
}

void SkoarMinstrel::after_entering_skoarpion(SkoarMinstrelPtr, SkoarpionPtr) {
}

void SkoarMinstrel::exiting () {
    clear ();
}



// --- MinstrelDebugConfig -------------------------------------
MinstrelDebugConfig::MinstrelDebugConfig(
    const SpellOfDebuggingNoads& before_entering_noad_spell,
    const SpellOfDebuggingNoads& after_entering_noad_spell,
    const SpellOfDebuggingSkoarpuscles& before_entering_skoarpuscle_spell,
    const SpellOfDebuggingSkoarpuscles& after_entering_skoarpuscle_spell,
    const SpellOfDebuggingSkoarpions& before_entering_skoarpion_spell,
    const SpellOfDebuggingSkoarpions& after_entering_skoarpion_spell,
    const SpellOfDebuggingExiting& exiting_spell
) :
    before_entering_noad(before_entering_noad_spell),
    after_entering_noad(after_entering_noad_spell),
    before_entering_skoarpuscle(before_entering_skoarpuscle_spell),
    after_entering_skoarpuscle(after_entering_skoarpuscle_spell),
    before_entering_skoarpion(before_entering_skoarpion_spell),
    after_entering_skoarpion(after_entering_skoarpion_spell),
    exiting(exiting_spell)
{
}

// --- DebuggingMinstrel -------------------------------------
DebuggingMinstrel::DebuggingMinstrel(
    SkoarString minstrel_name,
    SkoarKoarPtr koar,
    Skoar* skoar,
    const SpellOfHappening& spell,
    const MinstrelDebugConfig& config)
    :
    SkoarMinstrel(minstrel_name, koar, skoar, spell),
    
    before_entering_noad_spell(config.before_entering_noad),
    after_entering_noad_spell(config.after_entering_noad),

    before_entering_skoarpuscle_spell(config.before_entering_skoarpuscle),
    after_entering_skoarpuscle_spell(config.after_entering_skoarpuscle),
    
    before_entering_skoarpion_spell(config.before_entering_skoarpion),
    after_entering_skoarpion_spell(config.after_entering_skoarpion),

    exiting_spell(config.exiting)
{
}

DebuggingMinstrel::~DebuggingMinstrel() {
}


void DebuggingMinstrel::before_entering_noad(SkoarMinstrelPtr m, SkoarNoadite* noad) {
    before_entering_noad_spell(m, noad);
}

void DebuggingMinstrel::after_entering_noad(SkoarMinstrelPtr m, SkoarNoadite* noad) {
    after_entering_noad_spell(m, noad);
}

void DebuggingMinstrel::before_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle) {
    before_entering_skoarpuscle_spell(m, skoarpuscle);
}

void DebuggingMinstrel::after_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle) {
    after_entering_skoarpuscle_spell(m, skoarpuscle);
}

void DebuggingMinstrel::before_entering_skoarpion(SkoarMinstrelPtr m, SkoarpionPtr skoarpion) {
    before_entering_skoarpion_spell(m, skoarpion);
}

void DebuggingMinstrel::after_entering_skoarpion(SkoarMinstrelPtr m, SkoarpionPtr skoarpion) {
    after_entering_skoarpion_spell(m, skoarpion);
}

void DebuggingMinstrel::exiting () {
    exiting_spell ();
}


// --- Skoarchestra ----------------------------------------
Skoarchestra::Skoarchestra (Skoar* skoar, const SpellOfHappening& spell) :
    happenSpell (spell)
{
    if (skoar->voices.size () == 1)
    {
        minstrels.push_back (SkoarMinstrel::New (L"all", skoar->all_voice, skoar, happenSpell));
    }
    else
    {
        for (auto kv : skoar->voices)
        {
            auto v = kv.second;
            minstrels.push_back (SkoarMinstrel::New (v->name, v, skoar, happenSpell));
        }
    }

    //minstrels.push_back(skoar->skoarsfjord->troll);
    //skoar->running = minstrels.size();
}
