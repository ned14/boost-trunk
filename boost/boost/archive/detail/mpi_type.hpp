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
 : mpl::int_<MPITYPE>                           \
{}                                              \
                                                \
template <>                                     \
struct is_mpi_type<T>                           \
 : public mpl::bool_<true>                      \
{};


BOOST_SPECIALIZE_MPI_TYPE( char                , MPI_CHAR               );
BOOST_SPECIALIZE_MPI_TYPE( short               , MPI_SHORT              );
BOOST_SPECIALIZE_MPI_TYPE( int                 , MPI_INT                );
BOOST_SPECIALIZE_MPI_TYPE( long                , MPI_LONG               );
BOOST_SPECIALIZE_MPI_TYPE( unsigned char       , MPI_UNSIGNED_CHAR      );
BOOST_SPECIALIZE_MPI_TYPE( unsigned short      , MPI_UNSIGNED_SHORT     );
BOOST_SPECIALIZE_MPI_TYPE( unsigned int        , MPI_UNSIGNED_INT       );
BOOST_SPECIALIZE_MPI_TYPE( unsigned long       , MPI_UNSIGNED_LONG      );
BOOST_SPECIALIZE_MPI_TYPE( float               , MPI_FLOAT              );
BOOST_SPECIALIZE_MPI_TYPE( double              , MPI_DOUBLE             );
BOOST_SPECIALIZE_MPI_TYPE( long double         , MPI_LONG_DOUBLE        );

#ifdef BOOST_HAS_LONG_LONG
BOOST_SPECIALIZE_MPI_TYPE( long long           , MPI_LONG_LONG          );
BOOST_SPECIALIZE_MPI_TYPE( unsigned long long  , MPI_UNSIGNED_LONG_LONG );
#endif

} // namespace boost

#endif // BOOST_ARCHIVE_MPI_TYPE_HPP
