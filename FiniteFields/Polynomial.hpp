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
                _coefficients{coefficients} {}

        constexpr explicit Polynomial(std::vector<T> &&coefficients) :
                _coefficients{coefficients} {}

        Polynomial(const Polynomial<T> &other) = default;

    private:
        std::pair<Polynomial<T>, Polynomial<T>> divmod(const Polynomial<T> &other) const;
        Polynomial<T> strip();

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
    bool Polynomial<T>::operator==(const Polynomial &other) const {
        return AsVector() == other.AsVector();
    }

    template<class T>
    std::pair<Polynomial<T>, Polynomial<T>> Polynomial<T>::divmod(const Polynomial<T> &other) const {
        if (degree() < other.degree())
            return std::make_pair(Polynomial<T>({0}), Polynomial<T>(*this));

        size_t dN = degree(), dD = other.degree(), dd, dq = dN - dD, dr = dN - dD;

        std::vector<T> result(_coefficients);

        std::vector<T> q(degree() - other.degree() + 1, 0);
        std::vector<T> r(degree() - other.degree() + 1, 0);
        std::vector<T> d(degree() + 1, 0);

        d.assign(dN + 1, 0);
        q.assign(dq + 1, 0);
        r.assign(dr + 1, 0);

        while (dN >= dD) {
            d.assign(d.size(), 0);
            for (size_t i = 0; i <= dD; i++)
                d[i + dN - dD] = other[i];
            dd = dN;
            q[dN - dD] = GetEl(dN) / (d[dd]);
            for (size_t i = 0; i < dq + 1; i++)
                d[i] = d[i] * q[dN - dD];
            for (size_t i = 0; i < dN + 1; i++)
                result[i] = result[i] - d[i];
            dN--;
        }
        for (size_t i = 0; i <= dN; i++)
            r[i] = result[i];
        return std::make_pair(Polynomial<T>(q).strip(), Polynomial<T>(r).strip());
    }

    template<class T>
    Polynomial<T> Polynomial<T>::strip() {
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
        return Polynomial<T>(result).strip();
    }

    template<class T>
    Polynomial<T> Polynomial<T>::operator*(const T &other) const {
        std::vector<T> result(_coefficients);
        for (auto &it: result) {
            it = it * other;
        }
        return Polynomial<T>(result).strip();
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
        return Polynomial(result).strip();
    }

    template<class T>
    std::ostream &operator<<(std::ostream &os, Polynomial<T> p) {
        for (auto e: p) os << e << ' ';
        return os;
    }

}

#endif //FINITEFIELDS_POLYNOMIAL_H
