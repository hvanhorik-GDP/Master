Author: Henry Van Horik
Student Number: 0966956
Class: INFO-6025-01-19F
Due: Sep 19, 2019 11:59 PM

NOTE - Everything is contained in a single SLN file

To run:

Navigate to directory: "Project1"
Open: "Project1.sln"
Set Target to "Project1 - Build All"
Select "Build All"
Set Target to "WhiteBox"
"F5"
Set Target to "BlackBox"
"F5"

NOTE - I adjusted all of the projects so that they build without the need for any copying of header, library
or DLL files. This includes the gtest solution. I wasn't a big fan of having to copy stuff since it is error
prone and a pain in the butt. You will also notice that all configurations are the same, so this can be set
for all configurations and platforms.

General:			OutPut Diretory:		$(SolutionDir)$(Platform)\$(Configuration)\
VC+ Directories:	Include Dirctories:		$(ProjectDir)include\;$(ProjectDir);$(IncludePath)
					Library Directories:	$(SolutionDir)$(Platform)\$(Configuration)\;$(LibraryPath)
Build Events:		Post Build Event: gtest	xcopy /S /D /Y "$(ProjectDir)include\*" "$(SolutionDir)inc\*"
					Post Build Event: DLLL	xcopy /S /D /Y "$(ProjectDir)*.h" "$(SolutionDir)inc\$(ProjectName)\*.h"
Linker/Input:		Additional Dependencies: BlackDLL.lib;gtest.lib;%(AdditionalDependencies)	

How it works

This simplifies the creation of new projects, especially when you have to add external projects libraries such
as gtest. 

When Creating a new project:
	- Create the project
	- Adjust newly created project with instructions above (for all platforms and targets)
	- Add any subprojects
	- Set Build Dependencies to build libraries first.
	- Hit build

On building a project:
	- All Output files are targeted to		$(SolutionDir)$(Platform)\$(Configuration)\
	- All external headers get copied to	$(SolutionDir)inc\$(ProjectName)\

Optional, after everything works
	- You could optionally remove the subprojects. The created libraries will stay in the build folders and 
	  not be removed by subsequent cleans of the main project.
	- Or, just leave them in which I find is easier for my sanity.

If you create a new solution in another area and add the same libraries there is not conflict since all of the
build libraries will be targeted to the new solution directory hierachy. 