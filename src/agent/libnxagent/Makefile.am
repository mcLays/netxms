SOURCES = bridge.cpp dfile_info.cpp lora_device_data.cpp main.cpp \
          procexec.cpp registry.cpp smbios.cpp tools.cpp

lib_LTLIBRARIES = libnxagent.la

libnxagent_la_SOURCES = $(SOURCES)
libnxagent_la_CPPFLAGS=-I@top_srcdir@/include -DLIBNXAGENT_EXPORTS
libnxagent_la_LDFLAGS = -release $(NETXMS_LIBRARY_VERSION)
libnxagent_la_LIBADD = ../../db/libnxdb/libnxdb.la ../../libnetxms/libnetxms.la

EXTRA_DIST = Makefile.w32 libnxagent.h libnxagent.vcxproj libnxagent.vcxproj.filters
