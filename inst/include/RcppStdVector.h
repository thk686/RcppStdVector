#ifndef __RCPPSTDVECTOR_H__
#define __RCPPSTDVECTOR_H__

#include <RcppCommon.h>

namespace RcppStdVector {

template <int RTYPE> struct ctype {};
template <> struct ctype<REALSXP> {
  using type = double;
};
template <> struct ctype<INTSXP> {
  using type = int;
};
template <> struct ctype<LGLSXP> {
  using type = int;
};
template <> struct ctype<VECSXP> {
  using type = SEXP;
};
template <> struct ctype<STRSXP> {
  using type = SEXP;
};

template <int RTYPE>
using value_t = typename ctype<RTYPE>::type;

template <int RTYPE>
struct Rallocator {
  SEXP s;
  int count = 0;
  using value_type = value_t<RTYPE>;
  value_type* allocate(std::size_t n) {
    s = Rf_allocVector(RTYPE, n);
    PROTECT(s); ++count;
    return static_cast<value_type*>(DATAPTR(s));
  }
  void deallocate(value_type* p, std::size_t n) {
    if (count > 0) {
      UNPROTECT(count);
      count = 0;
    }
  }
};

template <int RTYPE>
struct RInplaceAlloc {
  SEXP s;
  RInplaceAlloc() = delete;
  RInplaceAlloc(SEXP t) : s(t) {}
  using value_type = value_t<RTYPE>;
  value_type* allocate(std::size_t n) {
    if (n != Rf_xlength(s))
      Rcpp::stop("Cannot resize inplace vector");
    return static_cast<value_type*>(DATAPTR(s));
  }
  void deallocate(value_type* p, std::size_t n) {}
  void construct(value_type* p) {
    new (static_cast<void*>(p)) value_type;
  }
};

template <int RTYPE>
using std_vec_t = std::vector<value_t<RTYPE>, Rallocator<RTYPE>>;

using std_vec_real = std_vec_t<REALSXP>;
using std_vec_int = std_vec_t<INTSXP>;
using std_vec_lgl = std_vec_t<LGLSXP>;
using std_vec_sxp = std_vec_t<VECSXP>;
using std_vec_chr = std_vec_t<STRSXP>;

template <int RTYPE>
using std_ivec_t = std::vector<value_t<RTYPE>, RInplaceAlloc<RTYPE>>;

using std_ivec_real = std_ivec_t<REALSXP>;
using std_ivec_int = std_ivec_t<INTSXP>;
using std_ivec_lgl = std_ivec_t<LGLSXP>;
using std_ivec_sxp = std_ivec_t<VECSXP>;
using std_ivec_chr = std_ivec_t<STRSXP>;

template <typename T>
SEXP get_sexp(const T& x) {
  auto s = x.get_allocator().s;
  if (x.size() < x.capacity()) {
    SET_GROWABLE_BIT(s);
    SET_TRUELENGTH(s, x.capacity());
    SETLENGTH(s, x.size());
  }
  return s;
}

template <int RTYPE>
value_t<RTYPE>* begin(SEXP x) {
  return static_cast<value_t<RTYPE>*>(DATAPTR(x));
}

template <int RTYPE>
value_t<RTYPE>* end(SEXP x) {
  return static_cast<value_t<RTYPE>*>(DATAPTR(x)) + Rf_xlength(x);
}

template <int RTYPE>
std_vec_t<RTYPE>
from_sexp(SEXP s) {
  if (TYPEOF(s) != RTYPE) Rcpp::stop("Invalid type");
  return std_vec_t<RTYPE>(begin<RTYPE>(s), end<RTYPE>(s));
}

template <int RTYPE>
std_ivec_t<RTYPE>
from_sexp_inp(SEXP s) {
  if (TYPEOF(s) != RTYPE) Rcpp::stop("Invalid type");
  return std_ivec_t<RTYPE>(Rf_xlength(s), RInplaceAlloc<RTYPE>(s));
}

}; // namespace RcppStdVector

namespace Rcpp
{

template<>
inline SEXP
wrap<RcppStdVector::std_vec_real>(const RcppStdVector::std_vec_real& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_vec_real
as<RcppStdVector::std_vec_real>(SEXP s) {
  return RcppStdVector::from_sexp<REALSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_vec_int>(const RcppStdVector::std_vec_int& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_vec_int
as<RcppStdVector::std_vec_int>(SEXP s) {
  return RcppStdVector::from_sexp<INTSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_vec_lgl>(const RcppStdVector::std_vec_lgl& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_vec_lgl
as<RcppStdVector::std_vec_lgl>(SEXP s) {
  return RcppStdVector::from_sexp<LGLSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_vec_sxp>(const RcppStdVector::std_vec_sxp& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_vec_sxp
as<RcppStdVector::std_vec_sxp>(SEXP s) {
  return RcppStdVector::from_sexp<VECSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_vec_chr>(const RcppStdVector::std_vec_chr& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_vec_chr
as<RcppStdVector::std_vec_chr>(SEXP s) {
  return RcppStdVector::from_sexp<STRSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_ivec_real>(const RcppStdVector::std_ivec_real& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_ivec_real
as<RcppStdVector::std_ivec_real>(SEXP s) {
  return RcppStdVector::from_sexp_inp<REALSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_ivec_int>(const RcppStdVector::std_ivec_int& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_ivec_int
as<RcppStdVector::std_ivec_int>(SEXP s) {
  return RcppStdVector::from_sexp_inp<INTSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_ivec_lgl>(const RcppStdVector::std_ivec_lgl& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_ivec_lgl
as<RcppStdVector::std_ivec_lgl>(SEXP s) {
  return RcppStdVector::from_sexp_inp<LGLSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_ivec_sxp>(const RcppStdVector::std_ivec_sxp& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_ivec_sxp
as<RcppStdVector::std_ivec_sxp>(SEXP s) {
  return RcppStdVector::from_sexp_inp<VECSXP>(s);
}

template<>
inline SEXP
wrap<RcppStdVector::std_ivec_chr>(const RcppStdVector::std_ivec_chr& x) {
  return RcppStdVector::get_sexp(x);
}

template<>
inline RcppStdVector::std_ivec_chr
as<RcppStdVector::std_ivec_chr>(SEXP s) {
  return RcppStdVector::from_sexp_inp<STRSXP>(s);
}

}; // namespace Rcpp

#include <Rcpp.h>

#endif // __RCPPSTDVECTOR_H__
