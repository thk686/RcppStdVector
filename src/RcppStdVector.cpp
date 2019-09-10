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
SEXP test_double_it(RcppStdVector::std_vec_sxp& x) {
  for (auto s = x.begin(); s != x.end(); ++s) {
    switch(TYPEOF(*s)) {
    case REALSXP: {
      RcppStdVector::std_vec_real y;
      y.reserve(2 * LENGTH(*s));
      auto oi = std::back_inserter(y);
      std::copy(REAL(*s), REAL(*s) + LENGTH(*s), oi);
      std::copy(REAL(*s), REAL(*s) + LENGTH(*s), oi);
      *s = Rcpp::wrap(y);
      break;
    }
    case INTSXP: {
      RcppStdVector::std_vec_int y;
      y.reserve(2 * LENGTH(*s));
      auto oi = std::back_inserter(y);
      std::copy(INTEGER(*s), INTEGER(*s) + LENGTH(*s), oi);
      std::copy(INTEGER(*s), INTEGER(*s) + LENGTH(*s), oi);
      *s = Rcpp::wrap(y);
      break;
    }
    case LGLSXP: {
      RcppStdVector::std_vec_lgl y;
      y.reserve(2 * LENGTH(*s));
      auto oi = std::back_inserter(y);
      std::copy(LOGICAL(*s), LOGICAL(*s) + LENGTH(*s), oi);
      std::copy(LOGICAL(*s), LOGICAL(*s) + LENGTH(*s), oi);
      *s = Rcpp::wrap(y);
      break;
    }
    case STRSXP: {
      RcppStdVector::std_vec_chr y;
      y.reserve(2 * LENGTH(*s));
      for (int i = 0; i != LENGTH(*s); ++i)
        y.push_back(STRING_ELT(*s, i));
      for (int i = 0; i != LENGTH(*s); ++i)
        y.push_back(STRING_ELT(*s, i));
      *s = Rcpp::wrap(y);
      break;
    }
    case VECSXP: {
      RcppStdVector::std_vec_sxp y;
      y.reserve(2 * LENGTH(*s));
      for (int i = 0; i != LENGTH(*s); ++i)
        y.push_back(VECTOR_ELT(*s, i));
      for (int i = 0; i != LENGTH(*s); ++i)
        y.push_back(VECTOR_ELT(*s, i));
      *s = Rcpp::wrap(y);
      break;
    }
    default: Rcpp::stop("Unsupported column type");
    }
  }
  return Rcpp::wrap(x);
}

