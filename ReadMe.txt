================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : BLACK_SCREEN Project Overview
===============================================================================

The application wizard has created this BLACK_SCREEN application for 
you.  This application not only demonstrates the basics of using the Microsoft 
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your BLACK_SCREEN application.

BLACK_SCREEN.vcproj
    This is the main project file for VC++ projects generated using an application wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    application wizard.

BLACK_SCREENApp.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CBLACK_SCREENApp application class.

BLACK_SCREENApp.cpp
    This is the main application source file that contains the application
    class CBLACK_SCREENApp.

BLACK_SCREEN.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\BLACK_SCREEN.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file BLACK_SCREEN.rc.

res\BLACK_SCREEN.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++. You should place all resources not editable by
    the resource editor in this file.

/////////////////////////////////////////////////////////////////////////////

The application wizard creates one dialog class:
BLACK_SCREENDlg.h, BLACK_SCREENDlg.cpp - the dialog
    These files contain your CBLACK_SCREENDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's template is
    in BLACK_SCREEN.rc, which can be edited in Microsoft Visual C++.
/////////////////////////////////////////////////////////////////////////////

Other Features:

ActiveX Controls
    The application includes support to use ActiveX controls.

Printing and Print Preview support
    The application wizard has generated code to handle the print, print setup, and print preview
    commands by calling member functions in the CView class from the MFC library.
/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named BLACK_SCREEN.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

BLACK_SCREEN.manifest
	Application manifest files are used by Windows XP to describe an applications 
	dependency on specific versions of Side-by-Side assemblies. The loader uses this 
	information to load the appropriate assembly from the assembly cache or private 
	from the application. The Application manifest  maybe included for redistribution 
	as an external .manifest file that is installed in the same folder as the application 
	executable or it may be included in the executable in the form of a resource. 
/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is in a 
language other than the operating system's current language, you will need 
to copy the corresponding localized resources MFC70XXX.DLL from the Microsoft
Visual C++ CD-ROM under the Win\System directory to your computer's system or 
system32 directory, and rename it to be MFCLOC.DLL.  ("XXX" stands for the 
language abbreviation.  For example, MFC70DEU.DLL contains resources 
translated to German.)  If you don't do this, some of the UI elements of 
your application will remain in the language of the operating system.

/////////////////////////////////////////////////////////////////////////////
