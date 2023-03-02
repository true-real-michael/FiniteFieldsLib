//
// Created by Mikhail Kiselyov on 21.02.2023.
//

#ifndef FINITEFIELDS_POLYNOMIAL_H
#define FINITEFIELDS_POLYNOMIAL_H

#include <vector>

namespace FiniteFields {

    template<class T>
    class Polynomial {
    private:
        std::vector<T> _coefficients;

    public:
        constexpr explicit Polynomial(const std::vector<T> &coefficients) :
                _coefficients{coefficients} { stripCoefficients(); }

        constexpr explicit Polynomial(std::vector<T> &&coefficients) :
                _coefficients{coefficients} { stripCoefficients(); }

        Polynomial(const Polynomial<T> &other) = default;

    private:
        std::pair<Polynomial<T>, Polynomial<T>> divmod(const Polynomial<T> &other) const;
        void stripCoefficients();
        Polynomial<T> stripped();

    public:
        [[nodiscard]] size_t degree() const { return _coefficients.size(); }
        std::vector<T> AsVector() const { return std::vector<T>(_coefficients); }

        T GetEl(const size_t index) const { return _coefficients[index]; }
        T operator[](const size_t index) const { return _coefficients[index]; }
        T &operator[](const size_t index) { return _coefficients[index]; }

        bool operator==(const Polynomial &other) const;

        Polynomial<T> operator+(const Polynomial &other) const;
        Polynomial<T> operator*(const T &other) const;
        Polynomial<T> operator*(const Polynomial &other) const;
        Polynomial<T> operator/(const Polynomial &other) const { return divmod(other).first; }
        Polynomial<T> operator%(const Polynomial &other) const { return divmod(other).second; }

        friend std::ostream &operator<<(std::ostream &os, const Polynomial<T> &poly) {
            for (auto e: poly._coefficients)
                os << e << ' ';
            return os;
        }
    };

    template<class T>
    void Polynomial<T>::stripCoefficients() {
        while(_coefficients.size() > 1 && *_coefficients.rbegin() == 0)
            _coefficients.pop_back();
    }

    template<class T>
    bool Polynomial<T>::operator==(const Polynomial &other) const {
        if (degree() != other.degree())
            return false;
        for (size_t i = 0; i < degree(); i++)
            if (_coefficients[i] != other.GetEl(i))
                return false;
        return true;
    }


    template<class T>
    size_t vecDegree(std::vector<T> &vec) {
        while (!vec.empty() && *vec.rbegin() == 0)
            vec.pop_back();
        if (vec.empty())
            vec.emplace_back(0);
        return vec.size() - 1;
    }


    template<class T>
    std::pair<Polynomial<T>, Polynomial<T>> Polynomial<T>::divmod(const Polynomial<T> &otherP) const {
        std::vector<T> tthis(AsVector());
        std::vector<T> other(otherP.AsVector());
        size_t degOther = vecDegree(other);
        size_t degThis = vecDegree(tthis);

        if (degree() < otherP.degree())
            return std::make_pair(Polynomial<T>({0}), Polynomial<T>(tthis));

        std::vector<T> remainder(tthis);
        std::vector<T> quotient(degThis, 0);
        while (degThis >= degOther) {
            std::vector<T> d(degThis+1, 0);
            for (int i = 0; i <= degThis; i++)
                d[degThis - degOther + i] = other[i];

            T mult = *remainder.rbegin() / *d.rbegin();
            quotient[degThis - degOther] = mult;

            for (int i = 0; i <= degThis; i++)
                d[i] = d[i] * mult;

            for (int i = 0; i <= degThis; i++) {
                remainder[i] = remainder[i] - d[i];
            }
            degThis = vecDegree(remainder);
        }
        return {Polynomial<T>(quotient), Polynomial<T>(remainder)};
    }

    template<class T>
    Polynomial<T> Polynomial<T>::stripped() {
        std::vector<T> result(_coefficients);
        while (result.size() > 1 && *result.rbegin() == T(0)) {
            result.pop_back();
        }
        return Polynomial<T>(result);
    }

    template<class T>
    Polynomial<T> Polynomial<T>::operator*(const Polynomial &other) const {
        std::vector<T> result(degree() * other.degree(), 0);  // WARN: potential substitution error
        for (size_t iThis = 0; iThis < degree(); iThis++) {
            for (size_t iOther = 0; iOther < other.degree(); iOther++) {
                result[iThis + iOther] = result[iThis + iOther] + _coefficients[iThis] * other[iOther];  // WARN: potential substitution error
            }
        }
        return Polynomial<T>(result).stripped();
    }

    template<class T>
    Polynomial<T> Polynomial<T>::operator*(const T &other) const {
        std::vector<T> result(_coefficients);
        for (auto &it: result) {
            it = it * other;
        }
        return Polynomial<T>(result).stripped();
    }

    template<class T>
    Polynomial<T> Polynomial<T>::operator+(const Polynomial &other) const {
        size_t size1 = degree(), size2 = other.degree();
        size_t resSize = std::max(size1, size2);
        std::vector<T> result(resSize, 0);
        for (size_t i = 0; i < resSize; i++) {
            if (i < size1)
                result[i] = result[i] + _coefficients[i];
            if (i < size2)
                result[i] = result[i] + other[i];
        }
        return Polynomial(result).stripped();
    }

    template<class T>
    std::ostream &operator<<(std::ostream &os, Polynomial<T> p) {
        for (auto e: p) os << e << ' ';
        return os;
    }

}

#endif //FINITEFIELDS_POLYNOMIAL_H
