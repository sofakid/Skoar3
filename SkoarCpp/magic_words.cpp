#include "magic_words.hpp"
#include "skoarpuscle.hpp"
#include "minstrel.hpp"


bool handle_magic_words (SkoarString word, SkoarpusclePtr v, SkoarMinstrelPtr m)
{
    auto& koar (*m->koar);

    if (word == L"bpm")
    {
        auto& bpm (v);

        if (is_skoarpuscle<SkoarpuscleInt> (bpm))
        {
            auto x = skoarpuscle_ptr<SkoarpuscleInt> (bpm)->val;
            bpm = make_skoarpuscle (static_cast<float>(x));
        }

        if (!is_skoarpuscle<SkoarpuscleFloat> (bpm))
            bpm = make_skoarpuscle (120.0);

        auto x = skoarpuscle_ptr<SkoarpuscleFloat> (bpm)->val;
        if (x <= 0.0 || isnan (x))
        {
            x = 120.0;
            bpm = make_skoarpuscle (x);
        }

        auto bps = x / 60.0;
        koar.put (L"bpm", bpm);
        koar.put (L"bps", make_skoarpuscle (bps));

        return true;

    }

    if (word == L"bps")
    {
        auto& bps (v);

        if (is_skoarpuscle<SkoarpuscleInt> (bps))
        {
            auto x = skoarpuscle_ptr<SkoarpuscleInt> (bps)->val;
            bps = make_skoarpuscle (static_cast<float>(x));
        }

        if (!is_skoarpuscle<SkoarpuscleFloat> (bps))
            bps = make_skoarpuscle (2.0);

        auto x = skoarpuscle_ptr<SkoarpuscleFloat> (bps)->val;
        if (x <= 0.0 || isnan (x))
        {
            x = 2.0;
            bps = make_skoarpuscle (x);
        }

        auto bpm = x * 60.0;
        koar.put (L"bpm", make_skoarpuscle (bpm));
        koar.put (L"bps", bps);

        return true;

    }
    return false;

}