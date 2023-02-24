//
// Created by Mikhail Kiselyov on 21.02.2023.
//

#ifndef FINITEFIELDS_PRIMEFIELDELEMENT_H
#define FINITEFIELDS_PRIMEFIELDELEMENT_H

#include <iostream>

namespace FiniteFields {

    template<size_t p>
    class PrimeFieldElement {
    private:
        int _val;

    public:
        PrimeFieldElement(int val) : _val{normalize(val)} {
            std::vector<bool> erathosphene(p + 2, true);
            erathosphene[0] = false;
            erathosphene[1] = false;
            for (size_t i = 2; i * i <= p; i++)
                if (erathosphene[i])
                    for (size_t j = i * i; j <= p; j += i)
                        erathosphene[j] = false;

            if (!erathosphene[p])
                throw std::invalid_argument("Parameter p has to be prime.");
        }

    private:
        [[nodiscard]] int normalize(int x) const {
            int r = p;
            return x >= 0 ? x % r : r + x % r; // SUPER WEIRD error occurs when `p` is used instead of `r`
        }

    public:
        [[nodiscard]] size_t GetVal() const { return _val; }
        void SetVal(size_t newVal) { _val = normalize(newVal); }

        bool operator==(const PrimeFieldElement<p> &other) const { return _val == other.GetVal(); }
        PrimeFieldElement<p> pow(size_t power) const;
        PrimeFieldElement<p> inv() const;
        PrimeFieldElement<p> operator*(const PrimeFieldElement<p> &other) const;
        PrimeFieldElement<p> operator*=(const PrimeFieldElement<p> &other) const { this = this * other; }
        PrimeFieldElement<p> operator+(const PrimeFieldElement<p> &other) const;
        PrimeFieldElement<p> operator+=(const PrimeFieldElement<p> &other) const { this = this + other; }
        PrimeFieldElement<p> operator-(const PrimeFieldElement<p> &other) const;
        PrimeFieldElement<p> operator-=(const PrimeFieldElement<p> &other) const { this = this - other; }
        PrimeFieldElement<p> operator/(const PrimeFieldElement<p> &other) const;
        PrimeFieldElement<p> operator/=(const PrimeFieldElement<p> &other) const { this = this / other; }
        PrimeFieldElement<p> operator-() const;
    };

    template<size_t p>
    PrimeFieldElement<p> PrimeFieldElement<p>::operator/(const PrimeFieldElement<p> &other) const {
        return *this * other.inv();
    }

    template<size_t p>
    PrimeFieldElement<p> PrimeFieldElement<p>::inv() const {
        return pow(p - 2);
    }

    template<size_t p>
    PrimeFieldElement<p> PrimeFieldElement<p>::pow(size_t power) const {
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
        return PrimeFieldElement<p>(res);
    }

    template<size_t p>
    PrimeFieldElement<p> PrimeFieldElement<p>::operator-() const {
        return PrimeFieldElement<p>(-_val);
    }

    template<size_t p>
    PrimeFieldElement<p> PrimeFieldElement<p>::operator-(const PrimeFieldElement<p> &other) const {
        return PrimeFieldElement<p>(_val - other.GetVal());
    }

    template<size_t p>
    PrimeFieldElement<p> PrimeFieldElement<p>::operator+(const PrimeFieldElement<p> &other) const {
        return PrimeFieldElement<p>(_val + other.GetVal());
    }

    template<size_t p>
    PrimeFieldElement<p> PrimeFieldElement<p>::operator*(const PrimeFieldElement<p> &other) const {
        return PrimeFieldElement<p>(_val * other.GetVal());
    }

    template<size_t p>
    std::ostream &operator<<(std::ostream &os, PrimeFieldElement<p> ffe) {
        os << ffe.GetVal()<<"+("<<p<<')';
        return os;
    }

} // FiniteFields

#endif //FINITEFIELDS_PRIMEFIELDELEMENT_H
