Running Boost Regression Tests
==============================

Requirements
------------

* Python 2.3

Installation
------------

* Download regression driver ``regression.py`` from here__ (http://tinyurl.com/4fp4g)
  and put it in the directory where you want all the regression 
  test files to be placed.

__ http://cvs.sourceforge.net/viewcvs.py/*checkout*/boost/boost/tools/regression/xsl_reports/runner/regression.py


* **Optional**: If you already have ``bjam`` and/or ``process_jam_log`` executables
  you'd like to use, just put them in the same directory with ``regression.py``, e.g.::

   my_boost_regressions/
      regression.py
      bjam.exe


Running tests
-------------

* To start a regression run, simply run ``regression.py`` providing it with the 
  only required option, runner id. For example::

    python regression.py --runner=Metacomm

  If you are interested in seeing all available options, run ``python regression.py``
  or ``python regression.py --help``.
  

Details
-------

The regression run procedure will:

* Download the most recent tarball from http://www.boost-consulting.com, 
  unpack it in the subdirectory ``boost``.

* Build ``bjam`` and ``process_jam_log`` if needed. (``process_jam_log`` is an
  utility, which extracts the test results from the log file produced by 
  Boost.Build)

* Run regression tests, process and collect the results.

* Upload the results to ftp://fx.meta-comm.com/boost-regression.


The report merger process running on MetaCommunications site every 2 hours will 
merge all submitted test runs and publish them at 
http://boost.sourceforge.net/regression-logs/developer.

