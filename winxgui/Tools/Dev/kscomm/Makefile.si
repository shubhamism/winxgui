#
# Configuration Default
#
ifeq ($(CFG),)
	CFG = Release
endif

IncludeDir = -I../Include -I. 

LibDir     = -L../../Lib 

#
# Configuration Release
#
ifeq ($(CFG), Release)
	ProductDir   = ../../Lib
	ObjectDir    = LRelease
	MocFile      = $(ObjectDir)/temp.moc.cpp
	Product      = ../../Lib/libKSCommonMT.a
	CFlags       = $(Defines) -fwritable-strings -fPIC -D__SOLS__ -DNDEBUG -O2 -D_MT -fno-rtti -fexceptions 
	CXXFlags     = $(CFlags)
	CXX          = g++ -c $(IncludeDir) $(CXXFlags) -o $@
	CompileCXX   = @$(CXX) $<
	CompileC     = @gcc -c $(IncludeDir) $(CFlags) -o $@ $<
	CompileMoc   = @moc $< -o $(MocFile) && $(CXX) $(MocFile) && rm -f $(MocFile)
	Link         = @ar cr $(Product)
endif

#
# Configuration Debug
#
ifeq ($(CFG), Debug)
	ProductDir   = ../../Lib
	ObjectDir    = LDebug
	MocFile      = $(ObjectDir)/temp.moc.cpp
	Product      = ../../Lib/libKSCommonMTD.a
	CFlags       = $(Defines) -fwritable-strings -fPIC -D__SOLS__ -D_DEBUG -g3 -D_MT -fno-rtti -fexceptions 
	CXXFlags     = $(CFlags)
	CXX          = g++ -c $(IncludeDir) $(CXXFlags) -o $@
	CompileCXX   = @$(CXX) $<
	CompileC     = @gcc -c $(IncludeDir) $(CFlags) -o $@ $<
	CompileMoc   = @moc $< -o $(MocFile) && $(CXX) $(MocFile) && rm -f $(MocFile)
	Link         = @ar cr $(Product)
endif

#
# Making...
#
all : $(ProductDir) $(ObjectDir) StartMake $(Product) EndMake

$(ProductDir) :
	@mkdir $(ProductDir)

ifneq ($(ProductDir),$(ObjectDir))
$(ObjectDir) :
	@mkdir $(ObjectDir)
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
$(ObjectDir)/fileext.o :	\
	fileext.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/gendeffile.o :	\
	gendeffile.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/makepath.o :	\
	makepath.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/makepath2.o :	\
	makepath2.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/mergepath.o :	\
	mergepath.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/rmpathsep.o :	\
	rmpathsep.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/searchpath.o :	\
	searchpath.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/splitpat.o :	\
	splitpat.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/splitpat2.o :	\
	splitpat2.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/stdpath.o :	\
	stdpath.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/stratom.o :	\
	stratom.cpp
	@echo "---> Compiling" $< "..."
	$(CompileCXX)

$(ObjectDir)/stricmp.o :	\
	stricmp.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/string.o :	\
	string.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/switch.o :	\
	switch.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/linux_finddir.o :	\
	linux/linux_finddir.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/win32_finddir.o :	\
	win32/win32_finddir.c
	@echo "---> Compiling" $< "..."
	$(CompileC)

$(ObjectDir)/scandir.o :	\
	scandir.c
	@echo "---> Compiling" $< "..."
	$(CompileC)


Objects =	\
	$(ObjectDir)/fileext.o	\
	$(ObjectDir)/gendeffile.o	\
	$(ObjectDir)/makepath.o	\
	$(ObjectDir)/makepath2.o	\
	$(ObjectDir)/mergepath.o	\
	$(ObjectDir)/rmpathsep.o	\
	$(ObjectDir)/searchpath.o	\
	$(ObjectDir)/splitpat.o	\
	$(ObjectDir)/splitpat2.o	\
	$(ObjectDir)/stdpath.o	\
	$(ObjectDir)/stratom.o	\
	$(ObjectDir)/stricmp.o	\
	$(ObjectDir)/string.o	\
	$(ObjectDir)/switch.o	\
	$(ObjectDir)/linux_finddir.o	\
	$(ObjectDir)/win32_finddir.o	\
	$(ObjectDir)/scandir.o

$(Product) : $(Objects) $(Libs)
	@echo "---> Creating" $@ "..."
	@rm -f $@
	$(Link) $(Objects) $(Libraries)
	$(CheckLink)
