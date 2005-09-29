// (C) Copyright 2005 Matthias Troyer . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_MPI_TYPE_HPP
#define BOOST_ARCHIVE_MPI_TYPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <mpi.h>
#include <boost/config.hpp>
#include <boost/mpl/int.hpp>
#include <complex>

namespace boost {

/// @brief Traits class to obtain MPI data types or fundamental types
///
/// The value member contains the MPI data type for the type given
/// as template argument. The default, for types without a corresponding
/// MPI data type has no value member, and trying to access it will thus cause
/// a compile time error

template <class T>
struct mpi_type
{};

/// @brief Traits class to check whether a type is a fundamental MPI type

template <class T>
struct is_mpi_type
 : public mpl::bool_<false>
{};

#define BOOST_SPECIALIZE_MPI_TYPE(TYPE,MPITYPE) \
template <>                                     \
struct mpi_type<TYPE>                           \
{                                               \
  static MPI_Datatype value;                    \
};                                              \
                                                \
MPI_Datatype mpi_type<TYPE>::value = MPITYPE;   \
                                                \
template <>                                     \
struct is_mpi_type<TYPE>                        \
 : public mpl::bool_<true>                      \
{}


BOOST_SPECIALIZE_MPI_TYPE( bool                      , MPI::BOOL                 );
BOOST_SPECIALIZE_MPI_TYPE( char                      , MPI::CHAR                 );
BOOST_SPECIALIZE_MPI_TYPE( short                     , MPI::SHORT                );
BOOST_SPECIALIZE_MPI_TYPE( int                       , MPI::INT                  );
BOOST_SPECIALIZE_MPI_TYPE( long                      , MPI::LONG                 );
//BOOST_SPECIALIZE_MPI_TYPE( signed char               , MPI::SIGNED_CHAR          );
BOOST_SPECIALIZE_MPI_TYPE( unsigned char             , MPI::UNSIGNED_CHAR        );
BOOST_SPECIALIZE_MPI_TYPE( unsigned short            , MPI::UNSIGNED_SHORT       );
BOOST_SPECIALIZE_MPI_TYPE( unsigned int              , MPI::UNSIGNED             );
BOOST_SPECIALIZE_MPI_TYPE( unsigned long             , MPI::UNSIGNED_LONG        );
BOOST_SPECIALIZE_MPI_TYPE( float                     , MPI::FLOAT                );
BOOST_SPECIALIZE_MPI_TYPE( double                    , MPI::DOUBLE               );
BOOST_SPECIALIZE_MPI_TYPE( long double               , MPI::LONG_DOUBLE          );
BOOST_SPECIALIZE_MPI_TYPE( std::complex<float>       , MPI::COMPLEX              );
BOOST_SPECIALIZE_MPI_TYPE( std::complex<double>      , MPI::DOUBLE_COMPLEX       );
BOOST_SPECIALIZE_MPI_TYPE( std::complex<long double> , MPI::LONG_DOUBLE_COMPLEX  );

#ifdef BOOST_HAS_LONG_LONG
//BOOST_SPECIALIZE_MPI_TYPE( long long                 , MPI::LONG_LONG            );
BOOST_SPECIALIZE_MPI_TYPE( unsigned long long        , MPI::UNSIGNED_LONG_LONG   );
#endif

} // namespace boost

#endif // BOOST_ARCHIVE_MPI_TYPE_HPP
