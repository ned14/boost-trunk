include(FindMPI)

if (MPI_FOUND)
  boost_library_project(
    MPI
    SRCDIRS src
    TESTDIRS test
    DEPENDS serialization
    )
endif(MPI_FOUND)

