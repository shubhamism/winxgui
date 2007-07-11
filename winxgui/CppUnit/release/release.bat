@set RIF=c:\GreenSoft\RemoveIntermedialFiles.exe
@set CPY=xcopy /S
@cd..
%RIF% examples
if not exist "release" md "release"
if not exist "release\cppunit" md "release\cppunit"
%CPY% bin release\cppunit\bin\
%CPY% lib release\cppunit\lib\
%CPY% include release\cppunit\include\
%CPY% examples release\cppunit\examples\
@pause
