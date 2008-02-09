#
# Configuration Default
#
ifeq ($(CFG),)
	CFG = Release
endif

IncludeDir = -I../Include 

LibDir     = -L../../Lib 

#
# Configuration Release
#
ifeq ($(CFG), Release)
	Libraries   += -lKSCommonMT
	ProductDir   = ../../DevTools
	ObjectDir    = LRelease
	MocFile      = $(ObjectDir)/temp.moc.cpp
	Product      = ../../DevTools/mks
	CFlags       = $(Defines) -fwritable-strings -fPIC -D__SPARC__ -D__SOLS__ -DSOLARIS -DNDEBUG -O2 -D_MT -fno-rtti -fexceptions 
	CXXFlags     = $(CFlags)
	CXX          = g++ -c $(IncludeDir) $(CXXFlags) -o $@
	CompileC     = @gcc -c $(IncludeDir) $(CFlags) -o $@ $<
	CompileCXX   = @$(CXX) $<
	CompileMoc   = @moc $< -o $(MocFile) && $(CXX) $(MocFile) && rm -f $(MocFile)
	Link         = @g++ $(LibDir) -ldl -o $(Product)
endif

#
# Configuration Debug
#
ifeq ($(CFG), Debug)
	Libraries   += -lKSCommonMTD
	ProductDir   = ../../DevToolsD
	ObjectDir    = LDebug
	MocFile      = $(ObjectDir)/temp.moc.cpp
	Product      = ../../DevToolsD/mksD
	CFlags       = $(Defines) -fwritable-strings -fPIC -D__SPARC__ -D__SOLS__ -DSOLARIS -D_DEBUG -g3 -D_MT -fno-rtti -fexceptions 
	CXXFlags     = $(CFlags)
	CXX          = g++ -c $(IncludeDir) $(CXXFlags) -o $@
	CompileC     = @gcc -c $(IncludeDir) $(CFlags) -o $@ $<
	CompileCXX   = @$(CXX) $<
	CompileMoc   = @moc $< -o $(MocFile) && $(CXX) $(MocFile) && rm -f $(MocFile)
	Link         = @g++ $(LibDir) -ldl -o $(Product)
endif

#
# Making...
#
all : $(ProductDir) $(ObjectDir) StartMake $(Product) EndMake

$(ProductDir) :
	@mkdir -p $(ProductDir)

ifneq ($(ProductDir),$(ObjectDir))
$(ObjectDir) :
	@mkdir -p $(ObjectDir)
endif

clean :
	@rm -f $(ObjectDir)/*.o
	@rm -f $(Product)

StartMake :
	@echo "-------------- Configuration:" $(PROJ) $(CFG) "--------------"

EndMake :
	@echo ">>> Success <<<"

#
# Source Files, Objects & Product
#
$(ObjectDir)/mks.o :	\
	mks.cpp
	@echo "---> Compiling" $< "..."
	$(CompileCXX)


Objects =	\
	$(ObjectDir)/mks.o

$(Product) : $(Objects) $(Libs)
	@echo "---> Creating" $@ "..."
	@rm -f $@
	$(Link) $(Objects) $(Libraries)
	$(CheckLink)

