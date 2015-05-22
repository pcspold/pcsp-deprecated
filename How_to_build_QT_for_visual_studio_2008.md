update for 4.5.3 version

Step 1:

Download the following from the QT site

http://get.qt.nokia.com/qtsdk/qt-sdk-win-opensource-2009.04.exe

http://download.qt.nokia.com/vsaddin/qt-vs-addin-1.1.0.exe

Step 2:

Run the qt installer and install it to the default location. (c:\QT\2009.04)

Step 3:

Open the visual studio 2008 command prompt
It can be found from
Start Menu->All Programs->Microsoft Visual Studio 2008->Visual Studio Tools->Visual Studio 2008 command prompt

Once you open it browse to the following directory

c:\QT\2009.04\qt

Once you are there type the following

`configure -no-webkit`

At the time of this article had written it seems that there are problems with webkit linking so we leave it out.

Once that finished you must type

`nmake`

in order to build Visual Studio lib files and dlls
Note: building will take 2 to 5 hours depending on your machine

Step 4:

Install the Visual Studio plugin (the second file you downloaded)

Open Visual studio 2008

In the menu there should be a new option labeled "QT"

Go There and select

`QT Options`

On the first tab Press

`Add`

and put

version name:

`qt4.5.3`

path :

`c:\QT\2009.04\qt`

You are now done!
You should now be able to create and compile QT applications!