#############################################################################
# Makefile for building: cameleon
# Generated by qmake (3.0) (Qt 5.5.1)
# Project:  Cameleon-sniffer.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile Cameleon-sniffer.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = clang
CXX           = clang++
DEFINES       = -DQT_NO_DEBUG -DQT_NETWORK_LIB -DQT_TESTLIB_LIB -DQT_CORE_LIB -DQT_TESTCASE_BUILDDIR='"/home/aschen/data/projets/Cameleon-Sniffer"'
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -I../../apps/QT/5.5/gcc_64/include -I../../apps/QT/5.5/gcc_64/include/QtNetwork -I../../apps/QT/5.5/gcc_64/include/QtTest -I../../apps/QT/5.5/gcc_64/include/QtCore -Itmp -I../../apps/QT/5.5/gcc_64/mkspecs/linux-g++
QMAKE         = /usr/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = cameleon1.0.0
DISTDIR = /home/aschen/data/projets/Cameleon-Sniffer/tmp/cameleon1.0.0
LINK          = g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/home/aschen/data/apps/QT/5.5/gcc_64 -Wl,-rpath,/home/aschen/data/apps/QT/5.5/gcc_64/lib
LIBS          = $(SUBLIBS) -ltins -L/home/aschen/data/apps/QT/5.5/gcc_64/lib -lQt5Network -lQt5Test -lQt5Core -lpthread 
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = tmp/

####### Files

SOURCES       = main.cpp 
OBJECTS       = tmp/main.o
DIST          = ../../apps/QT/5.5/gcc_64/mkspecs/features/spec_pre.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/unix.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/linux.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/sanitize.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/gcc-base.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/gcc-base-unix.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/g++-base.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/g++-unix.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/qconfig.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcollision.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcollision_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcore.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcore_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dinput.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dinput_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dlogic.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dlogic_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquick.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquick_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquickrenderer.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquickrenderer_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3drenderer.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3drenderer_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bluetooth.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bluetooth_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bootstrap_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_clucene_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_concurrent.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_concurrent_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_core.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_core_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_dbus.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_dbus_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_declarative.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_declarative_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designer.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designer_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designercomponents_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_enginio.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_enginio_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_gui.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_gui_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_help.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_help_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_location.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_location_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimedia.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimedia_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimediawidgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_network.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_network_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_nfc.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_nfc_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_opengl.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_opengl_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_openglextensions.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_openglextensions_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_platformsupport_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_positioning.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_positioning_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_printsupport.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_printsupport_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qml.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qml_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmltest.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmltest_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quick.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quick_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickparticles_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickwidgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_script.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_script_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_scripttools.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_scripttools_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sensors.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sensors_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_serialport.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_serialport_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sql.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sql_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_svg.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_svg_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_testlib.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_testlib_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uiplugin.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uitools.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uitools_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webchannel.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webchannel_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webengine.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webengine_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginecore.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginecore_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginewidgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginewidgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkit.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkit_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkitwidgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_websockets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_websockets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webview_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_widgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_widgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_x11extras.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_x11extras_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xml.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xml_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xmlpatterns.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/features/qt_functions.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/qt_config.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/linux-g++/qmake.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/spec_post.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/exclusive_builds.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/default_pre.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/resolve_config.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/default_post.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/c++11.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/warn_on.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/qt.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/resources.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/moc.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/testlib_defines.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/unix/thread.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/testcase_targets.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/exceptions.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/yacc.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/lex.prf \
		Cameleon-sniffer.pro  main.cpp
QMAKE_TARGET  = cameleon
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = cameleon


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Cameleon-sniffer.pro ../../apps/QT/5.5/gcc_64/mkspecs/linux-g++/qmake.conf ../../apps/QT/5.5/gcc_64/mkspecs/features/spec_pre.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/unix.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/linux.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/sanitize.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/gcc-base.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/gcc-base-unix.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/g++-base.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/common/g++-unix.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/qconfig.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcollision.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcollision_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcore.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcore_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dinput.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dinput_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dlogic.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dlogic_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquick.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquick_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquickrenderer.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquickrenderer_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3drenderer.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3drenderer_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bluetooth.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bluetooth_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bootstrap_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_clucene_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_concurrent.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_concurrent_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_core.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_core_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_dbus.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_dbus_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_declarative.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_declarative_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designer.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designer_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designercomponents_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_enginio.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_enginio_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_gui.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_gui_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_help.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_help_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_location.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_location_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimedia.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimedia_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimediawidgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_network.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_network_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_nfc.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_nfc_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_opengl.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_opengl_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_openglextensions.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_openglextensions_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_platformsupport_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_positioning.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_positioning_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_printsupport.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_printsupport_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qml.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qml_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmltest.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmltest_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quick.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quick_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickparticles_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickwidgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_script.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_script_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_scripttools.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_scripttools_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sensors.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sensors_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_serialport.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_serialport_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sql.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sql_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_svg.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_svg_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_testlib.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_testlib_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uiplugin.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uitools.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uitools_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webchannel.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webchannel_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webengine.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webengine_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginecore.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginecore_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginewidgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginewidgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkit.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkit_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkitwidgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_websockets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_websockets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webview_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_widgets.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_widgets_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_x11extras.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_x11extras_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xml.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xml_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xmlpatterns.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		../../apps/QT/5.5/gcc_64/mkspecs/features/qt_functions.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/qt_config.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/linux-g++/qmake.conf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/spec_post.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/exclusive_builds.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/default_pre.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/resolve_config.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/default_post.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/c++11.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/warn_on.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/qt.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/resources.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/moc.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/testlib_defines.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/unix/thread.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/testcase_targets.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/exceptions.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/yacc.prf \
		../../apps/QT/5.5/gcc_64/mkspecs/features/lex.prf \
		Cameleon-sniffer.pro \
		/home/aschen/data/apps/QT/5.5/gcc_64/lib/libQt5Network.prl \
		/home/aschen/data/apps/QT/5.5/gcc_64/lib/libQt5Test.prl \
		/home/aschen/data/apps/QT/5.5/gcc_64/lib/libQt5Core.prl
	$(QMAKE) -o Makefile Cameleon-sniffer.pro
../../apps/QT/5.5/gcc_64/mkspecs/features/spec_pre.prf:
../../apps/QT/5.5/gcc_64/mkspecs/common/unix.conf:
../../apps/QT/5.5/gcc_64/mkspecs/common/linux.conf:
../../apps/QT/5.5/gcc_64/mkspecs/common/sanitize.conf:
../../apps/QT/5.5/gcc_64/mkspecs/common/gcc-base.conf:
../../apps/QT/5.5/gcc_64/mkspecs/common/gcc-base-unix.conf:
../../apps/QT/5.5/gcc_64/mkspecs/common/g++-base.conf:
../../apps/QT/5.5/gcc_64/mkspecs/common/g++-unix.conf:
../../apps/QT/5.5/gcc_64/mkspecs/qconfig.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcollision.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcollision_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcore.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dcore_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dinput.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dinput_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dlogic.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dlogic_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquick.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquick_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquickrenderer.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3dquickrenderer_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3drenderer.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_3drenderer_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bluetooth.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bluetooth_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_bootstrap_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_clucene_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_concurrent.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_concurrent_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_core.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_core_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_dbus.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_dbus_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_declarative.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_declarative_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designer.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designer_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_designercomponents_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_enginio.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_enginio_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_gui.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_gui_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_help.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_help_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_location.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_location_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimedia.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimedia_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimediawidgets.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_network.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_network_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_nfc.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_nfc_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_opengl.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_opengl_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_openglextensions.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_openglextensions_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_platformsupport_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_positioning.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_positioning_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_printsupport.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_printsupport_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qml.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qml_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmldevtools_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmltest.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qmltest_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quick.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quick_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickparticles_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickwidgets.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_quickwidgets_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_script.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_script_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_scripttools.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_scripttools_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sensors.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sensors_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_serialport.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_serialport_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sql.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_sql_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_svg.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_svg_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_testlib.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_testlib_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uiplugin.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uitools.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_uitools_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webchannel.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webchannel_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webengine.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webengine_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginecore.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginecore_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginewidgets.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webenginewidgets_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkit.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkit_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkitwidgets.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_websockets.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_websockets_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_webview_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_widgets.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_widgets_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_x11extras.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_x11extras_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xml.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xml_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xmlpatterns.pri:
../../apps/QT/5.5/gcc_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
../../apps/QT/5.5/gcc_64/mkspecs/features/qt_functions.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/qt_config.prf:
../../apps/QT/5.5/gcc_64/mkspecs/linux-g++/qmake.conf:
../../apps/QT/5.5/gcc_64/mkspecs/features/spec_post.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/exclusive_builds.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/default_pre.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/resolve_config.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/default_post.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/c++11.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/warn_on.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/qt.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/resources.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/moc.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/testlib_defines.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/unix/thread.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/testcase_targets.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/exceptions.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/yacc.prf:
../../apps/QT/5.5/gcc_64/mkspecs/features/lex.prf:
Cameleon-sniffer.pro:
/home/aschen/data/apps/QT/5.5/gcc_64/lib/libQt5Network.prl:
/home/aschen/data/apps/QT/5.5/gcc_64/lib/libQt5Test.prl:
/home/aschen/data/apps/QT/5.5/gcc_64/lib/libQt5Core.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile Cameleon-sniffer.pro

qmake_all: FORCE


all: Makefile $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents main.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

tmp/main.o: main.cpp ../../apps/QT/5.5/gcc_64/include/QtCore/QCoreApplication \
		../../apps/QT/5.5/gcc_64/include/QtCore/qcoreapplication.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qglobal.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qconfig.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qfeatures.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qsystemdetection.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qprocessordetection.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qcompilerdetection.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qtypeinfo.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qtypetraits.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qsysinfo.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qlogging.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qflags.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qbasicatomic.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_bootstrap.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qgenericatomic.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_cxx11.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_gcc.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_msvc.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_armv7.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_armv6.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_armv5.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_ia64.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_mips.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_x86.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qatomic_unix.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qglobalstatic.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qmutex.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qnumeric.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qstring.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qchar.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qbytearray.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qrefcount.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qnamespace.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qarraydata.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qstringbuilder.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qobject.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qobjectdefs.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qobjectdefs_impl.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qlist.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qalgorithms.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qiterator.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qbytearraylist.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qstringlist.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qregexp.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qstringmatcher.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qcoreevent.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qscopedpointer.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qmetatype.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qvarlengtharray.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qcontainerfwd.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qisenum.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qobject_impl.h \
		../../apps/QT/5.5/gcc_64/include/QtCore/qeventloop.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/main.o main.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

