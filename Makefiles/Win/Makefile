
CC = C:\Program Files (x86)\TDM-GCC-32\bin\mingw32-g++
CRES = C:\Program Files (x86)\TDM-GCC-32\bin\windres.exe
FLAGS = -pipe -Wall -mthreads -D__GNUWIN64__ -D__WXMSW__ -DwxUSE_UNICODE_MSLU -O2

LIBINCLUDE = C:\wxWidgets-binaries\3.0.4\include
LIBDLL = C:\wxWidgets-binaries\3.0.4\lib\gcc492TDM_dll\mswu
LIBA = C:\wxWidgets-binaries\3.0.4\lib\gcc492TDM_dll

all:GetCurve-1.0

GetCurve-1.0: GetCurveApp.o GetCurveMain.o GetCurveMainReports.o GetCurveMainIO.o PolynomialWindow.o \
              PictureScaler.o CustomScale.o ColorSettings.o CFunctionName.o AboutWindow.o \
              imageCurve.o wxCurvePanel.o wxPanelGraph.o OdtCreator.o OdtCreatorArch.o OdtCreatorDriver.o \
              OdtCreatorTemplates.o OdtFormula.o OdtImages.o OdtTable.o polinom.o resource.res
	$(CC) -o bin/GetCurve-1.0.exe obj\GetCurveApp.o obj\GetCurveMain.o obj\GetCurveMainReports.o obj\GetCurveMainIO.o obj\PolynomialWindow.o \
              obj\PictureScaler.o obj\CustomScale.o obj\ColorSettings.o obj\CFunctionName.o obj\AboutWindow.o \
              obj\imageCurve.o obj\wxCurvePanel.o obj\wxPanelGraph.o obj\OdtCreator.o obj\OdtCreatorArch.o obj\OdtCreatorDriver.o \
              obj\OdtCreatorTemplates.o obj\OdtFormula.o obj\OdtImages.o obj\OdtTable.o obj\polinom.o obj\resource.res -s\
              -mthreads -mthreads \
              $(LIBA)\libwxexpat.a \
              $(LIBA)\libwxjpeg.a \
              $(LIBA)\libwxbase30u.a \
              $(LIBA)\libwxbase30u_net.a \
              $(LIBA)\libwxbase30u_xml.a \
              $(LIBA)\libwxbase30ud.a \
              $(LIBA)\libwxbase30ud_net.a \
              $(LIBA)\libwxbase30ud_xml.a \
              $(LIBA)\libwxexpat.a \
              $(LIBA)\libwxexpatd.a \
              $(LIBA)\libwxjpeg.a \
              $(LIBA)\libwxjpegd.a \
              $(LIBA)\libwxmsw30u_adv.a \
              $(LIBA)\libwxmsw30u_aui.a \
              $(LIBA)\libwxmsw30u_core.a \
              $(LIBA)\libwxmsw30u_gl.a \
              $(LIBA)\libwxmsw30u_html.a \
              $(LIBA)\libwxmsw30u_media.a \
              $(LIBA)\libwxmsw30u_propgrid.a \
              $(LIBA)\libwxmsw30u_ribbon.a \
              $(LIBA)\libwxmsw30u_richtext.a \
              $(LIBA)\libwxmsw30u_stc.a \
              $(LIBA)\libwxmsw30u_webview.a \
              $(LIBA)\libwxmsw30u_xrc.a \
              $(LIBA)\libwxpng.a \
              $(LIBA)\libwxregexu.a \
              $(LIBA)\libwxscintilla.a \
              $(LIBA)\libwxtiff.a \
              $(LIBA)\libwxzlib.a \
              -mwindows

polinom.o: calc/polinom.cpp
	$(CC) -c calc/polinom.cpp -pipe -Wall -mthreads -O2 -o obj\polinom.o

wxPanelGraph.o: controls/wxPanelGraph.cpp
	$(CC) -c controls/wxPanelGraph.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\wxPanelGraph.o

wxCurvePanel.o: controls/wxCurvePanel.cpp
	$(CC) -c controls/wxCurvePanel.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\wxCurvePanel.o

imageCurve.o: controls/imageCurve.cpp
	$(CC) -c controls/imageCurve.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\imageCurve.o

AboutWindow.o: dialogues/AboutWindow.cpp
	$(CC) -c dialogues/AboutWindow.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\AboutWindow.o

CFunctionName.o: dialogues/CFunctionName.cpp
	$(CC) -c dialogues/CFunctionName.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\CFunctionName.o

ColorSettings.o: dialogues/ColorSettings.cpp
	$(CC) -c dialogues/ColorSettings.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\ColorSettings.o

CustomScale.o: dialogues/CustomScale.cpp
	$(CC) -c dialogues/CustomScale.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\CustomScale.o

PictureScaler.o: dialogues/PictureScaler.cpp
	$(CC) -c dialogues/PictureScaler.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\PictureScaler.o

GetCurveApp.o: main/GetCurveApp.cpp
	$(CC) -c main/GetCurveApp.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj/GetCurveApp.o

GetCurveMain.o: main/GetCurveMain.cpp
	$(CC) -c main/GetCurveMain.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\GetCurveMain.o

GetCurveMainIO.o: main/GetCurveMainIO.cpp
	$(CC) -c main/GetCurveMainIO.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\GetCurveMainIO.o

GetCurveMainReports.o: main/GetCurveMainReports.cpp
	$(CC) -c main/GetCurveMainReports.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\GetCurveMainReports.o

PolynomialWindow.o: toolboxes/PolynomialWindow.cpp
	$(CC) -c toolboxes/PolynomialWindow.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\PolynomialWindow.o

OdtCreator.o: odt_creator/src/OdtCreator.cpp
	$(CC) -c odt_creator/src/OdtCreator.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\OdtCreator.o

OdtCreatorArch.o: odt_creator/src/OdtCreatorArch.cpp
	$(CC) -c odt_creator/src/OdtCreatorArch.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\OdtCreatorArch.o

OdtCreatorDriver.o: odt_creator/src/OdtCreatorDriver.cpp
	$(CC) -c odt_creator/src/OdtCreatorDriver.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\OdtCreatorDriver.o

OdtCreatorTemplates.o: odt_creator/src/OdtCreatorTemplates.cpp
	$(CC) -c odt_creator/src/OdtCreatorTemplates.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\OdtCreatorTemplates.o

OdtFormula.o: odt_creator/src/OdtFormula.cpp
	$(CC) -c odt_creator/src/OdtFormula.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\OdtFormula.o

OdtImages.o: odt_creator/src/OdtImages.cpp
	$(CC) -c odt_creator/src/OdtImages.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\OdtImages.o

OdtTable.o: odt_creator/src/OdtTable.cpp
	$(CC) -c odt_creator/src/OdtTable.cpp  $(FLAGS) -I$(LIBINCLUDE) -I$(LIBDLL) -o obj\OdtTable.o

resource.res:
	$(CRES) -I$(LIBINCLUDE) -I$(LIBDLL) -J rc -O coff -i resource.rc -o obj\resource.res

clean:
	del /Q obj
	del /Q bin