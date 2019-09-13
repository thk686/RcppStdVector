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
value_t<RTYPE>* begin(SEXP x) {
  return static_cast<value_t<RTYPE>*>(DATAPTR(x));
}

template <int RTYPE>
value_t<RTYPE>* end(SEXP x) {
  return static_cast<value_t<RTYPE>*>(DATAPTR(x)) + Rf_xlength(x);
}

template <int RTYPE>
struct Rallocator {
  SEXP s;
  int count = 0;
  using value_type = value_t<RTYPE>;
  value_type* get_ptr() {
    return begin<RTYPE>(s);
  }
  value_type* allocate(std::size_t n) {
    s = Rf_allocVector(RTYPE, n);
    PROTECT(s); ++count;
    return get_ptr();
  }
  void deallocate(value_type* p, std::size_t n) {
    if (count > 0) {
      UNPROTECT(count);
      count = 0;
    }
  }
};

template <int RTYPE1, int RTYPE2>
bool operator==(Rallocator<RTYPE1> const& a1, Rallocator<RTYPE2> const& a2) {
  if (RTYPE1 != RTYPE2 || a1.get_ptr() != a2.get_ptr()) return false;
  return true;
}

template <int RTYPE1, int RTYPE2>
bool operator!=(Rallocator<RTYPE1> const& a1, Rallocator<RTYPE2> const& a2) {
  return !(a1 == a1);
}

template <int RTYPE>
struct RInplaceAlloc {
  SEXP s;
  RInplaceAlloc() = default;
  RInplaceAlloc(SEXP t) : s(t) {}
  using value_type = value_t<RTYPE>;
  value_type* get_ptr() {
    return begin<RTYPE>(s);
  }
  value_type* allocate(std::size_t n) {
    if (n != Rf_xlength(s))
      Rcpp::stop("Cannot resize inplace vector");
    return get_ptr();
  }
  void deallocate(value_type* p, std::size_t n) {}
  void construct(value_type* p) {}
};

template <int RTYPE1, int RTYPE2>
bool operator==(RInplaceAlloc<RTYPE1> const& a1, RInplaceAlloc<RTYPE2> const& a2) {
  if (RTYPE1 != RTYPE2 || a1.get_ptr() != a2.get_ptr()) return false;
  return true;
}

template <int RTYPE1, int RTYPE2>
bool operator!=(RInplaceAlloc<RTYPE1> const& a1, RInplaceAlloc<RTYPE2> const& a2) {
  return !(a1 == a1);
}

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
using std_ivec_int  = std_ivec_t<INTSXP>;
using std_ivec_lgl  = std_ivec_t<LGLSXP>;
using std_ivec_sxp  = std_ivec_t<VECSXP>;
using std_ivec_chr  = std_ivec_t<STRSXP>;

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
std_vec_t<RTYPE>
from_sexp(SEXP s) {
  if (TYPEOF(s) != RTYPE) Rcpp::stop("Invalid type");
  return std_vec_t<RTYPE>(begin<RTYPE>(s), end<RTYPE>(s));
}

template <int RTYPE>
std_ivec_t<RTYPE>
from_sexp_inplace(SEXP s) {
  if (TYPEOF(s) != RTYPE) Rcpp::stop("Invalid type");
  return std_ivec_t<RTYPE>(Rf_xlength(s), RInplaceAlloc<RTYPE>(s));
}

}; // namespace RcppStdVector

namespace Rcpp
{

#define gen_wrap_as(T, U)                                      \
template<>                                                     \
inline SEXP                                                    \
wrap<RcppStdVector::std_vec_##T>(const RcppStdVector::std_vec_##T& x) { \
  return RcppStdVector::get_sexp(x);                           \
}                                                              \
template<>                                                     \
inline RcppStdVector::std_vec_##T                              \
as<RcppStdVector::std_vec_##T>(SEXP s) {                       \
  return RcppStdVector::from_sexp<U>(s);                       \
}                                                              \
template<>                                                     \
inline SEXP                                                    \
wrap<RcppStdVector::std_ivec_##T>(const RcppStdVector::std_ivec_##T& x) { \
  return RcppStdVector::get_sexp(x);                           \
}                                                              \
template<>                                                     \
inline RcppStdVector::std_ivec_##T                             \
as<RcppStdVector::std_ivec_##T>(SEXP s) {                      \
  return RcppStdVector::from_sexp_inplace<U>(s);               \
}

gen_wrap_as(real, REALSXP);
gen_wrap_as(int,  INTSXP);
gen_wrap_as(lgl,  LGLSXP);
gen_wrap_as(chr,  STRSXP);
gen_wrap_as(sxp,  VECSXP);

}; // namespace Rcpp

#define set_no_copy(T)                                         \
template<>                                                     \
inline RcppStdVector::std_ivec_##T&                            \
RcppStdVector::std_ivec_##T::operator=(const RcppStdVector::std_ivec_##T& x) { \
  Rcpp::stop("Cannot copy in-place vectors");                  \
}                                                              \
template<> inline                                              \
RcppStdVector::std_ivec_##T::vector(const RcppStdVector::std_ivec_##T& x) { \
  Rcpp::stop("Cannot copy construct in-place vectors");        \
}

set_no_copy(real);
set_no_copy(int);
set_no_copy(lgl);
set_no_copy(sxp);
set_no_copy(chr);

#include <Rcpp.h>

#endif // __RCPPSTDVECTOR_H__
