
CC = clang
SHELL = /bin/sh
PREF = ../
FLAGS = -pipe -Wall -pthread -O2
WXFLAGS = `wx-config --cxxflags`

all: GetCurve-1.0

GetCurve-1.0: GetCurveApp.o GetCurveMain.o GetCurveMainReports.o \
              GetCurveMainIO.o PolynomialWindow.o \
              PictureScaler.o CustomScale.o ColorSettings.o CFunctionName.o AboutWindow.o \
              imageCurve.o wxCurvePanel.o wxPanelGraph.o OdtCreator.o OdtCreatorArch.o OdtCreatorDriver.o \
              OdtCreatorTemplates.o OdtFormula.o OdtImages.o OdtTable.o polynom.o
	$(CC) -o  $(PREF)bin/GetCurve-1.0 $(PREF)obj/GetCurveApp.o $(PREF)obj/GetCurveMain.o $(PREF)obj/GetCurveMainReports.o \
              $(PREF)obj/GetCurveMainIO.o $(PREF)obj/PolynomialWindow.o $(PREF)obj/PictureScaler.o $(PREF)obj/CustomScale.o \
              $(PREF)obj/ColorSettings.o $(PREF)obj/CFunctionName.o $(PREF)obj/AboutWindow.o \
              $(PREF)obj/imageCurve.o $(PREF)obj/wxCurvePanel.o $(PREF)obj/wxPanelGraph.o $(PREF)obj/OdtCreator.o \
              $(PREF)obj/OdtCreatorArch.o $(PREF)obj/OdtCreatorDriver.o $(PREF)obj/OdtCreatorTemplates.o \
              $(PREF)obj/OdtFormula.o $(PREF)obj/OdtImages.o $(PREF)obj/OdtTable.o $(PREF)obj/polynom.o -s \
              -pthread `wx-config --libs` -lm -lc++

polynom.o: $(PREF)calc/polynom.cpp $(PREF)calc/polynom.h
	$(CC) -c $(PREF)calc/polynom.cpp $(FLAGS) -o $(PREF)obj/polynom.o

wxPanelGraph.o: $(PREF)controls/wxPanelGraph.cpp $(PREF)controls/wxPanelGraph.h
	$(CC) -c $(PREF)controls/wxPanelGraph.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/wxPanelGraph.o

wxCurvePanel.o: $(PREF)controls/wxCurvePanel.cpp $(PREF)controls/wxCurvePanel.h
	$(CC) -c $(PREF)controls/wxCurvePanel.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/wxCurvePanel.o

imageCurve.o: $(PREF)controls/imageCurve.cpp $(PREF)controls/imageCurve.h
	$(CC) -c $(PREF)controls/imageCurve.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/imageCurve.o

AboutWindow.o: $(PREF)dialogues/AboutWindow.cpp $(PREF)dialogues/AboutWindow.h $(PREF)res/picsAboutWindow.h
	$(CC) -c $(PREF)dialogues/AboutWindow.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/AboutWindow.o

CFunctionName.o: $(PREF)dialogues/CFunctionName.cpp $(PREF)dialogues/CFunctionName.h
	$(CC) -c $(PREF)dialogues/CFunctionName.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/CFunctionName.o

ColorSettings.o: $(PREF)dialogues/ColorSettings.cpp $(PREF)dialogues/ColorSettings.h
	$(CC) -c $(PREF)dialogues/ColorSettings.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/ColorSettings.o

CustomScale.o: $(PREF)dialogues/CustomScale.cpp $(PREF)dialogues/CustomScale.h
	$(CC) -c $(PREF)dialogues/CustomScale.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/CustomScale.o

PictureScaler.o: $(PREF)dialogues/PictureScaler.cpp $(PREF)dialogues/PictureScaler.h $(PREF)res/iconsScaleDialog.h
	$(CC) -c $(PREF)dialogues/PictureScaler.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/PictureScaler.o

GetCurveApp.o: $(PREF)main/GetCurveApp.cpp $(PREF)main/GetCurveApp.h
	$(CC) -c $(PREF)main/GetCurveApp.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/GetCurveApp.o

GetCurveMain.o: $(PREF)main/GetCurveMain.cpp $(PREF)main/GetCurveMain.h $(PREF)res/icons.h
	$(CC) -c $(PREF)main/GetCurveMain.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/GetCurveMain.o

GetCurveMainIO.o: $(PREF)main/GetCurveMainIO.cpp $(PREF)main/GetCurveMain.h $(PREF)dialogues/PictureScaler.h 
	$(CC) -c $(PREF)main/GetCurveMainIO.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/GetCurveMainIO.o

GetCurveMainReports.o: $(PREF)main/GetCurveMainReports.cpp $(PREF)main/GetCurveMain.h $(PREF)dialogues/CFunctionName.h
	$(CC) -c $(PREF)main/GetCurveMainReports.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/GetCurveMainReports.o

PolynomialWindow.o: $(PREF)toolboxes/PolynomialWindow.cpp $(PREF)toolboxes/PolynomialWindow.h
	$(CC) -c $(PREF)toolboxes/PolynomialWindow.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/PolynomialWindow.o

OdtCreator.o: $(PREF)odt_creator/src/OdtCreator.cpp
	$(CC) -c $(PREF)odt_creator/src/OdtCreator.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/OdtCreator.o

OdtCreatorArch.o: $(PREF)odt_creator/src/OdtCreatorArch.cpp
	$(CC) -c $(PREF)odt_creator/src/OdtCreatorArch.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/OdtCreatorArch.o

OdtCreatorDriver.o: $(PREF)odt_creator/src/OdtCreatorDriver.cpp
	$(CC) -c $(PREF)odt_creator/src/OdtCreatorDriver.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/OdtCreatorDriver.o

OdtCreatorTemplates.o: $(PREF)odt_creator/src/OdtCreatorTemplates.cpp
	$(CC) -c $(PREF)odt_creator/src/OdtCreatorTemplates.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/OdtCreatorTemplates.o

OdtFormula.o: $(PREF)odt_creator/src/OdtFormula.cpp
	$(CC) -c $(PREF)odt_creator/src/OdtFormula.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/OdtFormula.o

OdtImages.o: $(PREF)odt_creator/src/OdtImages.cpp
	$(CC) -c $(PREF)odt_creator/src/OdtImages.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/OdtImages.o

OdtTable.o: $(PREF)odt_creator/src/OdtTable.cpp
	$(CC) -c $(PREF)odt_creator/src/OdtTable.cpp  $(FLAGS) $(WXFLAGS) -o $(PREF)obj/OdtTable.o

clean:
	rm -rf $(PREF)obj/*.o $(PREF)bin/GetCurve-1.0
