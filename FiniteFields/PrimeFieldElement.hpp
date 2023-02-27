//
// Created by Mikhail Kiselyov on 21.02.2023.
//

#ifndef FINITEFIELDS_PRIMEFIELDELEMENT_H
#define FINITEFIELDS_PRIMEFIELDELEMENT_H

#include <iostream>
#include "PrimeField.h"

namespace FiniteFields {

    template<PrimeField pf>
    class PrimeFieldElement{
        int _val;

    private:
        [[nodiscard]] int normalize(int x) const {
            int p = pf.p;
            return x >= 0 ? x % p : p + x % p;
        }
    public:
        PrimeFieldElement(int val);
        PrimeFieldElement(const PrimeFieldElement& other);

        [[nodiscard]] size_t GetVal() const { return _val; }
        void SetVal(size_t newVal) { _val = normalize(newVal); }

        PrimeFieldElement<pf> &operator=(const PrimeFieldElement<pf> &other) { _val = other.GetVal(); return *this; }
        bool operator==(const PrimeFieldElement<pf> &other) const { return _val == other.GetVal(); }
        PrimeFieldElement<pf> pow(size_t power) const;
        PrimeFieldElement<pf> inv() const;
        PrimeFieldElement<pf> operator*(const PrimeFieldElement<pf> &other) const;
        PrimeFieldElement<pf> operator+(const PrimeFieldElement<pf> &other) const;
        PrimeFieldElement<pf> operator-(const PrimeFieldElement<pf> &other) const;
        PrimeFieldElement<pf> operator/(const PrimeFieldElement<pf> &other) const;
        PrimeFieldElement<pf> operator-() const;
//        PrimeFieldElement<pf> &operator*=(const PrimeFieldElement<pf> &other) const { this->_val *= other; return *this; }
//        PrimeFieldElement<pf> &operator+=(const PrimeFieldElement<pf> &other) const { *this = *this + other; return *this; }
//        PrimeFieldElement<pf> &operator-=(const PrimeFieldElement<pf> &other) const { *this = *this - other; return *this; }
//        PrimeFieldElement<pf> &operator/=(const PrimeFieldElement<pf> &other) const { *this = *this / other; return *this; }


    };

    template<PrimeField pf>
    PrimeFieldElement<pf>::PrimeFieldElement(const PrimeFieldElement &other) {
        _val = other.GetVal();
    }

    template<PrimeField pf>
    PrimeFieldElement<pf>::PrimeFieldElement(int val) : _val(normalize(val)){
        std::vector<bool> erathosphene(pf.p + 2, true);
        erathosphene[0] = false;
        erathosphene[1] = false;
        for (size_t i = 2; i * i <= pf.p; i++)
            if (erathosphene[i])
                for (size_t j = i * i; j <= pf.p; j += i)
                    erathosphene[j] = false;

        if (!erathosphene[pf.p])
            throw std::invalid_argument("Parameter p has to be prime.");
    }


    template<PrimeField pf>
    PrimeFieldElement<pf> PrimeFieldElement<pf>::operator/(const PrimeFieldElement<pf> &other) const {
        return *this * other.inv();
    }

    template<PrimeField pf>
    PrimeFieldElement<pf> PrimeFieldElement<pf>::inv() const {
        return pow(pf.p - 2);
    }

    template<PrimeField pf>
    PrimeFieldElement<pf> PrimeFieldElement<pf>::pow(size_t power) const {
        size_t base = _val;
        size_t res = 1;
        while (power) {
            if (power % 2 == 0) {
                base = normalize(base * base);
                power /= 2;
            } else {
                res = normalize(res * base);
                power--;
            }
        }
        return PrimeFieldElement<pf>(res);
    }

    template<PrimeField pf>
    PrimeFieldElement<pf> PrimeFieldElement<pf>::operator-() const {
        return PrimeFieldElement<pf>(-_val);
    }

    template<PrimeField pf>
    PrimeFieldElement<pf> PrimeFieldElement<pf>::operator-(const PrimeFieldElement<pf> &other) const {
        return PrimeFieldElement<pf>(_val - other.GetVal());
    }

    template<PrimeField pf>
    PrimeFieldElement<pf> PrimeFieldElement<pf>::operator+(const PrimeFieldElement<pf> &other) const {
        return PrimeFieldElement<pf>(_val + other.GetVal());
    }

    template<PrimeField pf>
    PrimeFieldElement<pf> PrimeFieldElement<pf>::operator*(const PrimeFieldElement<pf> &other) const {
        return PrimeFieldElement<pf>(_val * other.GetVal());
    }

    template<PrimeField pf>
    std::ostream &operator<<(std::ostream &os, PrimeFieldElement<pf> pfe) {
        os << pfe.GetVal()<<"+("<<pf.p<<')';
        return os;
    }

} // FiniteFields

#endif //FINITEFIELDS_PRIMEFIELDELEMENT_H
