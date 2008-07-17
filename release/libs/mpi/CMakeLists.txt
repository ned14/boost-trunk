include(FindMPI)

if (MPI_FOUND)
  boost_library_project(
    MPI
    SRCDIRS src
    TESTDIRS test
    DOCDIRS doc
    HEADERS mpi.hpp mpi
    MODULARIZED
    )
endif(MPI_FOUND)

