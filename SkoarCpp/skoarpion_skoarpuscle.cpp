#include "noad.hpp"
#include "skoarpion.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "all_skoarpuscles.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"


// --- SkoarpuscleSkoarpion ------------------------------------------------
SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(const SkoarpuscleSkoarpion *that) :
    val (that->val),
    args (that->args),
    capture_names (that->capture_names),
    expoart_names (that->expoart_names)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Skoarpion");
#endif

    for (auto& name : capture_names)
        captures.push_back (std::make_shared<SkoarpuscleCapture>(name));

}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpionPtr s) :
    val (s),
    args (nullptr),
    capture_names (s->capture_list),
    expoart_names (s->expoart_list)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Skoarpion");
#endif
    for (auto& name : capture_names)
        captures.push_back (std::make_shared<SkoarpuscleCapture> (name));
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpionPtr s, SkoarNoadPtr) :
    val (s),
    args (nullptr),
    capture_names (s->capture_list),
    expoart_names (s->expoart_list)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Skoarpion");
#endif
    for (auto& name : capture_names)
        captures.push_back (std::make_shared<SkoarpuscleCapture> (name));
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpusclePtr s, SkoarpusclePtr args) :
    val (skoarpuscle_ptr<SkoarpuscleSkoarpion>(s)->val),
    args (args),
    capture_names (skoarpuscle_ptr<SkoarpuscleSkoarpion> (s)->capture_names),
    expoart_names (skoarpuscle_ptr<SkoarpuscleSkoarpion> (s)->expoart_names)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Skoarpion");
#endif
    for (auto& name : capture_names)
        captures.push_back (std::make_shared<SkoarpuscleCapture> (name));
}

SkoarpuscleSkoarpion::~SkoarpuscleSkoarpion(){
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"Skoarpion");
#endif
    clear ();
}

void SkoarpuscleSkoarpion::clear ()
{
    val = nullptr;
    args = nullptr;
}


void SkoarpuscleSkoarpion::on_enter(SkoarMinstrelPtr m) {
    auto skrpskrp (std::make_shared<SkoarpuscleSkoarpion> (this));
    skrpskrp->bind_captures (m);
    m->fairy->impress (skrpskrp);

}

void SkoarpuscleSkoarpion::run(SkoarMinstrelPtr m) {
    auto impression = m->fairy->impression;
    m->koar->do_skoarpion(val, m, SkoarKoar::EExecStyle::NORMAL, impression, &captures, &expoart_names);
}

void SkoarpuscleSkoarpion::asString(std::wostream &out) { 
    out << L"Skoarpion :: " << val->name;
}

void SkoarpuscleSkoarpion::bind_captures (SkoarMinstrelPtr m)
{
    for (auto& x: captures) 
        SkoarpuscleCapture::Capture (x, m);
}

// --- SkoarpuscleArgExpr ----------------------------------------------
SkoarpuscleArgExpr::SkoarpuscleArgExpr(SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"ArgExpr");
#endif
    auto x = noad->next_skoarpuscle();

    if (is_skoarpuscle<SkoarpuscleSymbolColon>(x)) 
        name = skoarpuscle_ptr<SkoarpuscleSymbolColon>(x)->val;
    
    if (is_skoarpuscle<SkoarpuscleSymbolName> (x))
        name = skoarpuscle_ptr<SkoarpuscleSymbolName> (x)->val;

    if (noad->children.size() > 1) 
        SkoarNoad::inorder (noad->children[1], [&](SkoarNoadPtr x) {
            if (x->on_enter != nullptr || x->skoarpuscle != nullptr)
                expr.emplace_back (x);
        });
}

SkoarpuscleArgExpr::~SkoarpuscleArgExpr() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"ArgExpr");
#endif
    clear ();
}

void SkoarpuscleArgExpr::clear ()
{
    expr.clear ();
    name = L"";
}

void SkoarpuscleArgExpr::asString(std::wostream &out) {
    out << "ArgExpr" << " :: " << name;
    //if (is_skoarpuscle<SkoarpuscleExpr>(expr)) {
    //    out << " :: ";
    //    skoarpuscle_ptr<SkoarpuscleExpr>(expr)->asString(out);
    //}
}

SkoarpusclePtr SkoarpuscleArgExpr::flatten (SkoarMinstrelPtr m)
{
    auto& fairy (*m->fairy);
    fairy.push ();
        
    fairy.impress (nullptr);
    for (auto &noadite : expr)
        noadite.enter_noad (m);

    auto result = fairy.impression;

    if (is_skoarpuscle<SkoarpusclePair> (result))
        result = skoarpuscle_ptr<SkoarpusclePair> (result)->val.second;

    fairy.pop ();
    return result;
}

// --- SkoarpuscleArgList ----------------------------------------------
SkoarpuscleArgList::SkoarpuscleArgList(SkoarNoadPtr noad) :
    noad(noad)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"ArgList");
#endif
    
    for (auto& x : noad->collect_skoarpuscles ()) {
        if (is_skoarpuscle<SkoarpuscleArgExpr>(x)) {
            auto p = skoarpuscle_ptr<SkoarpuscleArgExpr>(x);
            args_dict[p->name] = x;
            args_names.push_back(p->name);
        }
    }
}

SkoarpuscleArgList::~SkoarpuscleArgList() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"ArgList");
#endif
    clear();
}

void SkoarpuscleArgList::clear ()
{
    for (auto& entry : args_dict)
    {
        auto &x = entry.second;
        if (is_skoarpuscle<SkoarpuscleArgExpr> (x))
            skoarpuscle_ptr<SkoarpuscleArgExpr> (x)->clear ();

    }
    
    args_dict.clear ();
    args_names.clear ();

    if (noad != nullptr)
    {
        auto p = noad;
        noad = nullptr;
        p->clear ();
    }
}

void SkoarpuscleArgList::on_enter(SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);
    fairy.push_noating();
    fairy.push();
}

void SkoarpuscleArgList::asString(std::wostream &out) {
    out << "ArgList";
    for (auto x : args_names)
        out << " :: " << x ;
}

// --- SkoarpuscleProjections ----------------------------------------------
SkoarpuscleProjections::SkoarpuscleProjections (ListOfSkoarpionProjectionsPtr lospp) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Projections");
#endif
    if (lospp != nullptr && lospp->size() > 0)
        for (auto x : *lospp)
            if (x != nullptr)
                // todo: there will be dups, what's up?
                mapp[x->name] = x;
}

SkoarpuscleProjections::~SkoarpuscleProjections () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Projections");
#endif
    clear ();
}

void SkoarpuscleProjections::clear ()
{
    mapp.clear ();
}

void SkoarpuscleProjections::asString (std::wostream &out) {
    out << "Projections";
}


// --- SkoarpuscleCapture ----------------------------------------------

SkoarpuscleCapture::SkoarpuscleCapture (const SkoarString& name) :
    name (name),
    val (nullptr)
{
#if SKOAR_DEBUG_MEMORY
        SkoarMemories::o ().allocSkoarpuscle (L"Capture");
#endif 
}
SkoarpuscleCapture::~SkoarpuscleCapture () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Capture");
#endif
}

void SkoarpuscleCapture::Capture (SkoarpusclePtr& cap_p, SkoarMinstrelPtr m)
{
    auto& cap (*skoarpuscle_ptr<SkoarpuscleCapture> (cap_p));
    auto dic_p (m->koar->find_stack_level_for_var (cap.name));

    if (dic_p == nullptr)
        throw SkoarRuntimeException (L"Capture failed.", cap_p);

    auto& dic (*dic_p);
    auto x = dic.at (cap.name);
    if (is_skoarpuscle<SkoarpuscleCapture> (x))
        cap_p = x;
    else
    {
        cap.val = x;
        dic.put (cap.name, cap_p);
    }
}

void SkoarpuscleCapture::asString (std::wostream & out)
{
    out << L"Capture :: " << name << L" :: ";
    if (val == nullptr)
        out << L"nullptr";
    else
        val->asString (out);
}
