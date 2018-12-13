#include "skoarpuscle.hpp"

#include "minstrel.hpp"
#include "fairy.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "make_skoarpuscle.hpp"
#include "operators.hpp"

#include <cmath>
#include <random>
#include <chrono>

// --- SkoarpuscleInt ---------------------------------------------------------
auto& get_generator () {
    static std::default_random_engine generator;
    static bool is_initialized (false);

    if (is_initialized == false)
    {
        uint32_t seed (
            static_cast<uint32_t>(
                std::chrono::system_clock::now ().time_since_epoch ().count ()
            )
        );
        generator.seed (seed);
        is_initialized = true;
    }

    return generator;
}

SkoarpusclePtr SkoarpuscleInt::skoar_msg (SkoarString sel, SkoarpusclePtr /*args*/, SkoarMinstrelPtr /*m*/) {

    if (sel == L"random")
    {
        auto v (val);
        
        const bool neg (v < 0);
        if (neg)
            v *= -1;

        if (v <= 1)
            return make_skoarpuscle (0);
        --v;

        auto& generator (get_generator ());
        std::uniform_int_distribution<SkoarInt> distribution (0, v);
        v = distribution (generator);
        if (neg)
            v *= -1;

        return make_skoarpuscle (v);
    }
    else if (sel == L"abs")
        return make_skoarpuscle (abs (val));
    
    return std::make_shared<SkoarpuscleCat> ();
}


// --- SkoarpuscleFloat ---------------------------------------------------------

SkoarpusclePtr SkoarpuscleFloat::skoar_msg (SkoarString sel, SkoarpusclePtr /*args*/, SkoarMinstrelPtr /*m*/) {
    
    if (sel == L"random")
    {
        auto v (val);
        
        const bool neg (v < 0.0);
        if (neg)
            v *= -1.0;

        const SkoarFloat v_minus_epsilon = nexttoward(v, 0.0);

        if (v_minus_epsilon <= 0.0)
            return make_skoarpuscle(0.0);

        auto& generator (get_generator ());
        std::uniform_real_distribution<SkoarFloat> distribution (0.0, v_minus_epsilon);
        v = distribution (generator);
        if (neg)
            v *= -1.0;

        return make_skoarpuscle (v);
    }

    else if (sel == L"sin")
        return make_skoarpuscle (sin (val));
    else if (sel == L"cos")
        return make_skoarpuscle (cos (val));
    else if (sel == L"tan")
        return make_skoarpuscle (tan (val));

    else if (sel == L"asin")
        return make_skoarpuscle (asin (val));
    else if (sel == L"acos")
        return make_skoarpuscle (acos (val));
    else if (sel == L"atan")
        return make_skoarpuscle (atan (val));

    else if (sel == L"sinh")
        return make_skoarpuscle (sinh (val));
    else if (sel == L"cosh")
        return make_skoarpuscle (cosh (val));
    else if (sel == L"tanh")
        return make_skoarpuscle (tanh (val));

    else if (sel == L"asinh")
        return make_skoarpuscle (asinh (val));
    else if (sel == L"acosh")
        return make_skoarpuscle (acosh (val));
    else if (sel == L"atanh")
        return make_skoarpuscle (atanh (val));

    else if (sel == L"abs")
        return make_skoarpuscle (abs (val));
    else if (sel == L"floor")
        return make_skoarpuscle (floor (val));
    else if (sel == L"ceil")
        return make_skoarpuscle (ceil (val));
    else if (sel == L"round")
        return make_skoarpuscle (round (val));
    
    else if (sel == L"exp")
        return make_skoarpuscle (exp (val));
    else if (sel == L"exp2")
        return make_skoarpuscle (exp2 (val));
    else if (sel == L"log")
        return make_skoarpuscle (log (val));
    else if (sel == L"log2")
        return make_skoarpuscle (log2 (val));
    else if (sel == L"log10")
        return make_skoarpuscle (log10 (val));

    else if (sel == L"sqrt")
        return make_skoarpuscle (sqrt (val));
    else if (sel == L"cbrt")
        return make_skoarpuscle (cbrt (val));

    return std::make_shared<SkoarpuscleCat> ();
}


// --- SkoarpuscleList ---------------------------------------------------------

SkoarpusclePtr SkoarpuscleList::skoar_msg (SkoarString sel, SkoarpusclePtr args_sp, SkoarMinstrelPtr m) {
    auto& v (*val);
    auto& fairy (*m->fairy);
    SkoarpuscleList* args (nullptr);

    if (is_skoarpuscle<SkoarpuscleList> (args_sp))
        args = skoarpuscle_ptr<SkoarpuscleList> (args_sp);

    if (sel == L"size")
        return make_skoarpuscle (static_cast<SkoarInt>(val->size()));
    
    
    else if (sel == L"at")
    {
        if (args->val->size () == 1)
        {
            auto arg (args->val->front ());
            if (is_skoarpuscle<SkoarpuscleInt> (arg))
            {
                const SkoarInt n (static_cast<SkoarInt>(v.size ()));
                const SkoarInt i (abs (skoarpuscle_ptr<SkoarpuscleInt>(arg)->val) % n);

                return make_skoarpuscle(v[i]);
            }
        }
        return make_skoarpuscle (nullptr);
    }


    else if (sel == L"random")
    {
        SkoarInt n (static_cast<SkoarInt>(v.size ()));
        if (n == 0)
            return make_skoarpuscle (nullptr);
        if (n == 1)
            return make_skoarpuscle (v[0]);
        --n;

        auto& generator (get_generator ());
        std::uniform_int_distribution<SkoarInt> distribution (0, n);
        const SkoarInt i (distribution (generator));
        return make_skoarpuscle (v[i]);
    }


    else if (sel == L"shuffle")
    {
        auto& generator (get_generator ());
        auto x (duplicate_shallow ());
        auto& vec (skoarpuscle_ptr<SkoarpuscleList> (x)->val);
        shuffle (vec->begin (), vec->end (), generator);
        return x;
    }


    else if (sel == L"fill")
    {
        if (args == nullptr)
            return make_skoarpuscle (nullptr);

        auto& argsval (*(args->val));
        if (argsval.size () != 2)
            return make_skoarpuscle (nullptr);

        auto& arg0 (argsval[0]);
        auto& arg1 (argsval[1]);
        if (is_skoarpuscle<SkoarpuscleInt> (arg0) && is_skoarpuscle<SkoarpuscleSkoarpion> (arg1))
        {
            const auto& n (skoarpuscle_ptr<SkoarpuscleInt> (arg0)->val);
            auto& skoarpion (skoarpuscle_ptr<SkoarpuscleSkoarpion> (arg1)->val);
            ListOfSkoarpuscles new_list (static_cast<size_t>(n));

            for (SkoarInt i (0); i < n; ++i)
            {
                auto el_i (make_skoarpuscle(i));
                ListOfSkoarpuscles args_list { el_i };

                m->koar->do_skoarpion (skoarpion, m, SkoarKoar::EExecStyle::NORMAL, make_skoarpuscle (args_list));
                new_list[i] = fairy.impression;
            }
            return make_skoarpuscle (new_list);

        }
        return make_skoarpuscle (nullptr);
    }
    

    else if (sel == L"map")
    {
        if (args == nullptr)
            return make_skoarpuscle (nullptr);

        auto& argsval (args->val);
        if (argsval->size () == 0)
            return make_skoarpuscle (nullptr);

        auto& arg0 (argsval->front ());
        if (is_skoarpuscle<SkoarpuscleSkoarpion> (arg0))
        {
            auto& skoarpion (skoarpuscle_ptr<SkoarpuscleSkoarpion> (arg0)->val);
            ListOfSkoarpuscles new_list (v.size());
            size_t i (0U);
            for (auto& el : v)
            {
                ListOfSkoarpuscles args_list { el };
                m->koar->do_skoarpion (skoarpion, m, SkoarKoar::EExecStyle::NORMAL, make_skoarpuscle (args_list));
                new_list[i++] = fairy.impression;
            }
            return make_skoarpuscle (new_list);
        }
        return make_skoarpuscle (nullptr);
    }


    else if (sel == L"filter")
    {
        if (args == nullptr)
            return make_skoarpuscle (nullptr);

        auto& argsval (args->val);
        if (argsval->size () == 0)
            return make_skoarpuscle (nullptr);

        auto& arg0 (argsval->front ());
        if (is_skoarpuscle<SkoarpuscleSkoarpion> (arg0))
        {
            auto& skoarpion (skoarpuscle_ptr<SkoarpuscleSkoarpion> (arg0)->val);
            ListOfSkoarpuscles new_list (v.size());
            size_t i (0U);
            for (auto& el : v)
            {
                ListOfSkoarpuscles args_list { el };
                m->koar->do_skoarpion (skoarpion, m, SkoarKoar::EExecStyle::NORMAL, make_skoarpuscle (args_list));
                
                auto result = fairy.impression;
                if (result->kind == ESkoarpuscle::True)
                    new_list[i++] = el;
            }
            new_list.resize (i);

            return make_skoarpuscle (new_list);
        }
        return make_skoarpuscle (nullptr);
    }


    else if (sel == L"reduce")
    {
        if (args == nullptr)
            return make_skoarpuscle (nullptr);

        auto& argsval (args->val);
        if (argsval->size () == 0)
            return make_skoarpuscle (nullptr);

        auto& arg0 (argsval->front ());
        if (is_skoarpuscle<SkoarpuscleSkoarpion> (arg0))
        {
            auto& skoarpion (skoarpuscle_ptr<SkoarpuscleSkoarpion> (arg0)->val);

            if (v.size () == 0)
                return make_skoarpuscle (nullptr);

            auto iter (v.cbegin ());
            auto end (v.cend ());
            auto x (*iter++);
            for (; iter != end; ++iter)
            {
                ListOfSkoarpuscles args_list { x, *iter };
                m->koar->do_skoarpion (skoarpion, m, SkoarKoar::EExecStyle::NORMAL, make_skoarpuscle (args_list));
                x = fairy.impression;
            }
            if (x == nullptr)
                return make_skoarpuscle (nullptr);

            return x;
        }
        return make_skoarpuscle (nullptr);
    }


    else if (sel == L"each")
    {
        if (args == nullptr)
            return make_skoarpuscle (nullptr);

        auto& argsval (args->val);
        if (argsval->size () == 0)
            return make_skoarpuscle (nullptr);

        auto& arg0 (argsval->front ());
        if (is_skoarpuscle<SkoarpuscleSkoarpion> (arg0))
        {
            auto& skoarpion (skoarpuscle_ptr<SkoarpuscleSkoarpion> (arg0)->val);
            for (auto& el : v)
            {
                ListOfSkoarpuscles args_list { el };
                m->koar->do_skoarpion (skoarpion, m, SkoarKoar::EExecStyle::NORMAL, make_skoarpuscle (args_list));
            }

        }
        return make_skoarpuscle (val);
    }

    return make_skoarpuscle (nullptr);

}


SkoarpusclePtr SkoarpuscleString::skoar_msg (SkoarString sel, SkoarpusclePtr args, SkoarMinstrelPtr m) {

    //if (sel == L"sample") {
    //    return make_shared<SkoarpuscleSample>(val);
    //}
    return std::make_shared<SkoarpuscleCat> ();
}

SkoarpusclePtr SkoarpuscleSymbol::skoar_msg (SkoarString sel, SkoarpusclePtr args, SkoarMinstrelPtr m) {

    /* this was how we called underlying SC class methods..
    don't know what I want to do with this anymore. */

    return std::make_shared<SkoarpuscleCat> ();
}


