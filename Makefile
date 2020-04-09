#Makefile

TOPDIR = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BINDIR = $(TOPDIR)bin
INCDIR = $(TOPDIR)include
OBJDIR = $(TOPDIR)obj
SRCDIR = $(TOPDIR)src
SOURCES := $(wildcard $(SRCDIR)/*.cc)
OBJECTS := $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE1 := $(BINDIR)/IncidenceAngleAnalysis
EXECUTABLE2 := $(BINDIR)/PlotTest
EXECUTABLE3 := $(BINDIR)/AnnotationViewer
EXE1_OBJS := $(OBJDIR)/AnalysisSelection.o $(OBJDIR)/CheckOverlap.o $(OBJDIR)/Checkpoint.o $(OBJDIR)/DataPreparation.o $(OBJDIR)/DataRetrieval.o $(OBJDIR)/EquirectangularProjection.o $(OBJDIR)/Images.o $(OBJDIR)/ImageSets.o $(OBJDIR)/IncidenceAngleAnalysis.o $(OBJDIR)/IncidenceAngles.o $(OBJDIR)/LeastSquares.o $(OBJDIR)/Marks.o $(OBJDIR)/MySQLConnection.o $(OBJDIR)/OverlappedImages.o $(OBJDIR)/Plot.o $(OBJDIR)/ProjectiveTransformation.o $(OBJDIR)/Quadrilateral.o $(OBJDIR)/ReadAuxilaryData.o $(OBJDIR)/SphericalLawofCosines.o $(OBJDIR)/Utilities.o
#EXE2_OBJS := $(OBJDIR)/PlotTest.o
#EXE3_OBJS := $(OBJDIR)/AnnotationViewer.o $(OBJDIR)/CheckOverlap.o $(OBJDIR)/DataPreparation.o $(OBJDIR)/DataRetrieval.o $(OBJDIR)/EquirectangularProjection.o $(OBJDIR)/Images.o $(OBJDIR)/ImageSets.o $(OBJDIR)/IncidenceAngles.o $(OBJDIR)/Marks.o $(OBJDIR)/MySQLConnection.o $(OBJDIR)/OverlappedImages.o $(OBJDIR)/ProjectiveTransformation.o $(OBJDIR)/Quadrilateral.o $(OBJDIR)/SearchImages.o $(OBJDIR)/SearchImageSets.o $(OBJDIR)/SearchIncidenceAngles.o $(OBJDIR)/SearchMarks.o $(OBJDIR)/SortImages.o $(OBJDIR)/SortImageSets.o $(OBJDIR)/SortIncidenceAngles.o $(OBJDIR)/SortMarks.o $(OBJDIR)/SortOverlappedImages.o $(OBJDIR)/Utilities.o

CC = g++
#CFLAGS = -g -Wshadow -Wall -Wextra -O3 -march=native -mavx -std=c++11
CFLAGS = -g -Wall -Wextra -Wno-unused-parameter -O3 -march=native -mavx -std=c++11
MYSQLINCDIR = $(MYSQLCONNECTORPATH)/include
MYSQLLIBDIR = $(MYSQLCONNECTORPATH)/lib
MYSQLCONFIG = -L$(MYSQLLIBDIR) -lmysqlcppconn
LDFLAGS = -lm
ROOT = $(ROOTSYS)
ROOTINCDIR = $(ROOT)/include/root
ROOTLIBDIR = $(ROOT)/lib/root
ROOTCONFIG = -L$(ROOTLIBDIR) -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lASImage

# all : $(OBJECTS) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

all : $(OBJECTS) $(EXECUTABLE1)

$(EXECUTABLE1) : $(EXE1_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MYSQLCONFIG) $(ROOTCONFIG) $(EXE1_OBJS) -o $@

# $(EXECUTABLE2) : $(EXE2_OBJS)
#	$(CC) $(CFLAGS) $(LDFLAGS) $(ROOTCONFIG) $(EXE2_OBJS) -o $@

# $(EXECUTABLE3) : $(EXE3_OBJS)
#	$(CC) $(CFLAGS) $(LDFLAGS) $(ROOTCONFIG) $(EXE3_OBJS) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) -c $(CFLAGS) -I$(INCDIR) -I$(MYSQLINCDIR) -I$(ROOTINCDIR) -MMD $< -o $@

.PHONY : clean

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) $(OBJDIR)/*.d $(OBJDIR)/*.o
