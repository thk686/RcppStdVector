#include "RcppStdVector.h"

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
