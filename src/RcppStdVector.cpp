#include "RcppStdVector.h"

#include "Rcpp.h"

// [[Rcpp::export]]
SEXP test_alloc()
{
  RcppStdVector::std_vec_real x;
  for (int i = 0; i != 1000; ++i) x.push_back(i);
  return Rcpp::wrap(x);
}

// [[Rcpp::export]]
SEXP test_modify(RcppStdVector::std_vec_real& x)
{
  for (int i = 0; i != x.size(); ++i)
    x[i] = 2 * x[i];
  return Rcpp::wrap(x);
}

// [[Rcpp::export]]
SEXP test_list(RcppStdVector::std_vec_sxp& x)
{
  x.push_back(Rf_allocVector(INTSXP, 10));
  return Rcpp::wrap(x);
}

// [[Rcpp::export]]
SEXP test_char()
{
  RcppStdVector::std_vec_chr x;
  x.push_back(Rf_mkChar("test"));
  return Rcpp::wrap(x);
}

// [[Rcpp::export]]
SEXP test_copy_chr(Rcpp::CharacterVector& x) {
  RcppStdVector::std_vec_chr y;
  auto oi = std::back_inserter(y);
  std::copy(x.begin(), x.end(), oi);
  return Rcpp::wrap(y);
}

// [[Rcpp::export]]
SEXP test_copy_rcpp_chr(Rcpp::CharacterVector& x) {
  Rcpp::CharacterVector y;
  auto oi = std::back_inserter(y);
  std::copy(x.begin(), x.end(), oi);
  return Rcpp::wrap(y);
}

// [[Rcpp::export]]
RcppStdVector::std_vec_int test_native(RcppStdVector::std_vec_int& x) {
  return x;
}

template <int RTYPE>
void dup_vec(SEXP& s) {
  auto y = RcppStdVector::from_sexp<RTYPE>(s);
  auto oi = std::back_inserter(y);
  y.reserve(2 * y.size());
  std::copy(RcppStdVector::begin<RTYPE>(s),
            RcppStdVector::end<RTYPE>(s), oi);
  s = PROTECT(Rcpp::wrap(y));
}

// [[Rcpp::export]]
SEXP test_double_it(RcppStdVector::std_vec_sxp& x) {
  for (auto s = x.begin(); s != x.end(); ++s) {
    switch(TYPEOF(*s)) {
    case REALSXP: dup_vec<REALSXP>(*s); break;
    case INTSXP:   dup_vec<INTSXP>(*s); break;
    case LGLSXP:   dup_vec<LGLSXP>(*s); break;
    case STRSXP:   dup_vec<STRSXP>(*s); break;
    case VECSXP:   dup_vec<VECSXP>(*s); break;
    default: Rcpp::stop("Unsupported column type");
    }
  }
  UNPROTECT(x.size());
  return Rcpp::wrap(x);
}

// [[Rcpp::export]]
void test_inplace(RcppStdVector::std_ivec_int& x) {
  std::transform(std::begin(x), std::end(x),
                 std::begin(x), [](int a){ return 2 * a; });
}

// [[Rcpp::export]]
void test_no_copy_ivec() {
  SEXP s1, s2;
  PROTECT(s1 = Rf_allocVector(REALSXP, 10));
  PROTECT(s2 = Rf_allocVector(REALSXP, 10));
  auto v1 = RcppStdVector::from_sexp_inplace<REALSXP>(s1),
    v2 = RcppStdVector::from_sexp_inplace<REALSXP>(s2);
  v1 = v2;
}

// [[Rcpp::export]]
void test_no_copy_construct_ivec(RcppStdVector::std_ivec_int& x) {
  RcppStdVector::std_ivec_int a(x);
}
