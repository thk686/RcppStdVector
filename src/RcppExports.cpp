// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/RcppStdVector.h"
#include <Rcpp.h>

using namespace Rcpp;

// test_alloc
SEXP test_alloc();
RcppExport SEXP _RcppStdVector_test_alloc() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(test_alloc());
    return rcpp_result_gen;
END_RCPP
}
// test_modify
SEXP test_modify(RcppStdVector::std_vec_real& x);
RcppExport SEXP _RcppStdVector_test_modify(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RcppStdVector::std_vec_real& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_modify(x));
    return rcpp_result_gen;
END_RCPP
}
// test_list
SEXP test_list(RcppStdVector::std_vec_sxp& x);
RcppExport SEXP _RcppStdVector_test_list(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RcppStdVector::std_vec_sxp& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_list(x));
    return rcpp_result_gen;
END_RCPP
}
// test_char
SEXP test_char();
RcppExport SEXP _RcppStdVector_test_char() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(test_char());
    return rcpp_result_gen;
END_RCPP
}
// test_copy_chr
SEXP test_copy_chr(Rcpp::CharacterVector& x);
RcppExport SEXP _RcppStdVector_test_copy_chr(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::CharacterVector& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_copy_chr(x));
    return rcpp_result_gen;
END_RCPP
}
// test_copy_rcpp_chr
SEXP test_copy_rcpp_chr(Rcpp::CharacterVector& x);
RcppExport SEXP _RcppStdVector_test_copy_rcpp_chr(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::CharacterVector& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_copy_rcpp_chr(x));
    return rcpp_result_gen;
END_RCPP
}
// test_native
RcppStdVector::std_vec_int test_native(RcppStdVector::std_vec_int& x);
RcppExport SEXP _RcppStdVector_test_native(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RcppStdVector::std_vec_int& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_native(x));
    return rcpp_result_gen;
END_RCPP
}
// test_double_it
SEXP test_double_it(RcppStdVector::std_vec_sxp& x);
RcppExport SEXP _RcppStdVector_test_double_it(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RcppStdVector::std_vec_sxp& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_double_it(x));
    return rcpp_result_gen;
END_RCPP
}
// test_inplace
void test_inplace(RcppStdVector::std_ivec_int& x);
RcppExport SEXP _RcppStdVector_test_inplace(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RcppStdVector::std_ivec_int& >::type x(xSEXP);
    test_inplace(x);
    return R_NilValue;
END_RCPP
}
// test_no_copy_ivec
void test_no_copy_ivec();
RcppExport SEXP _RcppStdVector_test_no_copy_ivec() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test_no_copy_ivec();
    return R_NilValue;
END_RCPP
}
// test_no_copy_construct_ivec
void test_no_copy_construct_ivec(RcppStdVector::std_ivec_int& x);
RcppExport SEXP _RcppStdVector_test_no_copy_construct_ivec(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RcppStdVector::std_ivec_int& >::type x(xSEXP);
    test_no_copy_construct_ivec(x);
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_RcppStdVector_test_alloc", (DL_FUNC) &_RcppStdVector_test_alloc, 0},
    {"_RcppStdVector_test_modify", (DL_FUNC) &_RcppStdVector_test_modify, 1},
    {"_RcppStdVector_test_list", (DL_FUNC) &_RcppStdVector_test_list, 1},
    {"_RcppStdVector_test_char", (DL_FUNC) &_RcppStdVector_test_char, 0},
    {"_RcppStdVector_test_copy_chr", (DL_FUNC) &_RcppStdVector_test_copy_chr, 1},
    {"_RcppStdVector_test_copy_rcpp_chr", (DL_FUNC) &_RcppStdVector_test_copy_rcpp_chr, 1},
    {"_RcppStdVector_test_native", (DL_FUNC) &_RcppStdVector_test_native, 1},
    {"_RcppStdVector_test_double_it", (DL_FUNC) &_RcppStdVector_test_double_it, 1},
    {"_RcppStdVector_test_inplace", (DL_FUNC) &_RcppStdVector_test_inplace, 1},
    {"_RcppStdVector_test_no_copy_ivec", (DL_FUNC) &_RcppStdVector_test_no_copy_ivec, 0},
    {"_RcppStdVector_test_no_copy_construct_ivec", (DL_FUNC) &_RcppStdVector_test_no_copy_construct_ivec, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_RcppStdVector(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
