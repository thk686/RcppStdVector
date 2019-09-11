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
  auto y = Rcpp::as<RcppStdVector::std_vec_t<RTYPE>>(s);
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
