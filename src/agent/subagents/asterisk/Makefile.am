SUBAGENT = asterisk

pkglib_LTLIBRARIES = asterisk.la
asterisk_la_SOURCES = ami.cpp channels.cpp events.cpp main.cpp rtcp.cpp sip.cpp system.cpp taskproc.cpp ua.cpp
asterisk_la_CPPFLAGS=-I@top_srcdir@/include
asterisk_la_LDFLAGS = -module -avoid-version -export-symbols ../subagent.sym
asterisk_la_LIBADD = ../../libnxagent/libnxagent.la ../../../libnetxms/libnetxms.la @ASTERISK_LIBS@

EXTRA_DIST = asterisk.h

if !STATIC_BUILD
install-exec-hook:
	if test "x`uname -s`" = "xAIX" ; then OBJECT_MODE=@OBJECT_MODE@ $(AR) x $(DESTDIR)$(pkglibdir)/$(SUBAGENT).a $(DESTDIR)$(pkglibdir)/$(SUBAGENT)@SHLIB_SUFFIX@ ; rm -f $(DESTDIR)$(pkglibdir)/$(SUBAGENT).a ; fi
	mv -f $(DESTDIR)$(pkglibdir)/$(SUBAGENT)@SHLIB_SUFFIX@ $(DESTDIR)$(pkglibdir)/$(SUBAGENT).nsm
	rm -f $(DESTDIR)$(pkglibdir)/$(SUBAGENT).la
	rm -f $(DESTDIR)$(libdir)/libnsm_$(SUBAGENT)@SHLIB_SUFFIX@
	ln -s netxms/$(SUBAGENT).nsm $(DESTDIR)$(libdir)/libnsm_$(SUBAGENT)@SHLIB_SUFFIX@
endif
