clean:
	/bin/rm -fr *.log *.aux *.bbl *.blg *.dvi *.pdf #*.idx *.lot *.lof *.out *.toc

show: tese.pdf
	xpdf tese.pdf

compile: tese.tex
	latex $< ; latex $< ; bibtex $(<:.tex=) ; latex $< ; latex $< ; dvipdfm -p a4 -o $(<:.tex=.pdf) $(<:.tex=.dvi)
