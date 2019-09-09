
<!-- README.md is generated from README.Rmd. Please edit that file -->

# RcppStdVector

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
<!-- badges: end -->

The `std::vector` container is the cornerstone of the C++ Standard
Library. When used with Rcpp however, there is an inherent cost in using
`std::vector` as memory must be copied both from and to R internal data
structures. The RcppStdVector package allows users to write Rcpp code
using the Standard Library `std::vector` container without incurring an
extra container copy operation. Consider the
    following:

    std::vector<double> my_func(std::vector<double>& x) { // copy from REALSXP to std::vector here
      ...
      return x; // additional copy from std::vector to REALSXP here
    }

For large vectors, this entails a large overhead. Rcpp native vectors
avoid these copies by holding an `SEXP`, which will be only copied on
demand. Recall however that unless an Rcpp vector is duplicated,
functions can modify the vector in-place, which violates the
no-side-effects rule. This can be useful or problematic in cases where
the `SEXP` is aliased to several R variables. Using RcppStdVector, we
can
    write:

    SEXP my_func(RcppStdVector::std_vec_real& x) { // copy here from REALSXP to std::vector
      ...
      return Rcpp::wrap(x); // zero-overhead, no-copy return of REALSXP
    }

The zero-overhead return is achieved by using a custom allocator that
allocates an R vector instead of general heap memory. This R vector is
simply retrieved from the allocator at the end. Special consideration is
taken when the capacity of the `std::vector` is greater than its size so
that there are no dangling elements. It may furthermore be possible to
implement in-place operations using C++ placement new although this has
not been explored.

There are several reasons one might wish to use `std::vector` over the
native Rcpp vector types. First, as part of the Standard Library,
relying on `std::vector` minimizes code rewrites when moving C++ code
into Rcpp. Second, `std::vector` is simple and well-documented. Compare
[this](https://en.cppreference.com/w/cpp/container/vector) to
[this](http://dirk.eddelbuettel.com/code/rcpp/html/classRcpp_1_1Vector.html).
Third, `std::vector` supports amortized-constant appending elements.
This is a very common idiom in C++ coding and its absense in Rcpp is a
source of frustration. Consider the following functions:

    SEXP test_copy_chr(Rcpp::CharacterVector& x) { // no copy
      RcppStdVector::std_vec_chr y;     // this IS a std::vector
      auto oi = std::back_inserter(y); // amortized-constant insertion
      std::copy(x.begin(), x.end(), oi);
      return Rcpp::wrap(y);  // no copy
    }
    
    SEXP test_copy_rcpp_chr(Rcpp::CharacterVector& x) { // no copy
      Rcpp::CharacterVector y;    // Rcpp type
      auto oi = std::back_inserter(y); // copies entire vector on each insertion
      std::copy(x.begin(), x.end(), oi);
      return Rcpp::wrap(y); // no copy
    }

On my system, I
    get:

    > microbenchmark(r1 <- test_copy_chr(x), r2 <- test_copy_rcpp_chr(x))
    Unit: microseconds
                            expr        min         lq         mean      median           uq         max
          r1 <- test_copy_chr(x)     94.811    102.117     124.4515    125.6335     129.7775     218.154
     r2 <- test_copy_rcpp_chr(x) 935634.546 975367.489 1012093.6482 996092.4005 1023481.6770 1228233.548

where `x` contains 1e4 character strings. The sole drawback of this
idiom is that up to 50% of the memory allocated to the `std::vector` may
be unused.
