# -*- makefile -*-

DVIPS		= dvips
LATEX		= pdflatex
LATEXOUT	= pdf
RESULT		= pdf

#LATEX		= latex
#LATEXOUT	= dvi
#RESULT		= ps

.SUFFIXES: .tex .dvi .ps .pdf .c .lg .eps

.c.lg:
	lgrind -i -o $*.lg -a -lc++ $*.c

.eps.pdf:
	epstopdf $*.eps

.tex.pdf:
	@ if test ! -f $*.ind; then echo "" > $*.ind; fi
	@ $(LATEX) $*
	@ if ( grep 'Writing index file' $*.log > /dev/null ); \
	then makeindex $* ; $(LATEX) $* ; fi
	@ if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null ); \
	then $(LATEX) $* ; fi
	@ if ( grep 'LaTeX Warning: Citation' $*.log > /dev/null ); \
	then bibtex $* ; $(LATEX) $* ; fi
	@ if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null ); \
	then $(LATEX) $* ; fi
	@ if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null ); \
	then $(LATEX) $* ; fi
	@ if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null ); \
	then $(LATEX) $* ; fi

.dvi.ps:
	$(DVIPS) -o $*.ps $*

.ps.pdf:
	distill -v -maxsubsetpct 99 -subsetfonts on -pairs $*.ps $*.pdf


SRCCODE	= 


#
# Default rule
#

default: mpl.$(RESULT)


#
# LaTeX stuff
#
TEX	= mpl.tex

mpl.dvi: $(TEX) $(SRCCODELG)
mpl.ps: mpl.dvi
mpl.pdf: $(PDFPICT) $(TEX) $(SRCCODELG) 

dist:	mpl.ps mpl.pdf
	mkdir -p mpl
	cp $(TEX) $(SRCCODELG) $(EPS) $(PS) \
	  mpl.bbl mpl.ps mpl.pdf \
          mpl
	tar cvf - ./mpl | gzip > mpl.tar.gz

#
# Standard rules
#

clean:
	/bin/rm -f *.dvi *.o *.ps *.pdf *.log *.blg *.bbl *.aux *~ *.out *.ind

