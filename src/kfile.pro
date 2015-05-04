######################################################################
# Automatically generated by qmake (2.01a) Mon Sep 10 16:15:43 2012
######################################################################

TEMPLATE = app
TARGET = kfile
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += kfilebrowser.h mainwindow.h ktexteditor.h fileclipboard.h kfilestyle.h kfilelist.h kfilewidget.h kfiledialogs.h kfilesettingsdialog.h kfilesettings.h kfileinfo.h jpegthumbnailfetcher.h kineticscroller.h
SOURCES += kfilebrowser.cpp main.cpp mainwindow.cpp ktexteditor.cpp fileclipboard.cpp kfilelist.cpp kfilewidget.cpp kfiledialogs.cpp kfilesettingsdialog.cpp kfilesettings.cpp kfileinfo.cpp jpegthumbnailfetcher.cpp kineticscroller.cpp

package.target = $${TARGET}.bar
package.depends = $$TARGET
package.commands = blackberry-nativepackager \
    #-devMode -debugToken ~/.rim/debugtoken1.bar \
    -package $${TARGET}.bar -arg -platform -arg blackberry \
    blackberry-tablet.xml $$TARGET \
    -e icon.png res/icon.png \
    -e splashscreen.png res/splashscreen.png \
    -e exit_icon.png res/exit_icon.png \
    -e open_icon.png res/open_icon.png \
    -e up_icon.png res/up_icon.png \
    -e home_icon.png res/home_icon.png \
    -e view_icon.png res/view_icon.png \
    -e file_icon.png res/file_icon.png \
    -e dir_icon.png res/dir_icon.png \
    -e dirlink_icon.png res/dirlink_icon.png \
    -e newbrowser_icon.png res/newbrowser_icon.png \
    -e newfile_icon.png res/newfile_icon.png \
    -e newdir_icon.png res/newdir_icon.png \
    -e save_icon.png res/save_icon.png \
    -e delete_icon.png res/delete_icon.png \
    -e copy_icon.png res/copy_icon.png \
    -e paste_icon.png res/paste_icon.png \
    -e cut_icon.png res/cut_icon.png \
    -e refresh_icon.png res/refresh_icon.png \
    -e audio_icon.png res/audio_icon.png \
    -e video_icon.png res/video_icon.png \
    -e zip_icon.png res/zip_icon.png \
    -e pdf_icon.png res/pdf_icon.png \
    -e office_icon.png res/office_icon.png \
    -e ebook_icon.png res/ebook_icon.png \
    -e html_icon.png res/html_icon.png \
    -e txt_icon.png res/txt_icon.png \
    -e image_icon.png res/image_icon.png \
    -e search_icon.png res/search_icon.png \
    -e settings_icon.png res/settings_icon.png \
    -e help_icon.png res/help_icon.png \
    -e about_icon.png res/about_icon.png \
    -e manual_icon.png res/manual_icon.png \
    -e kfile_manual.htm res/kfile_manual.htm \
    -e rename_icon.png res/rename_icon.png \
    -e selectall_icon.png res/selectall_icon.png \
    -e selectnone_icon.png res/selectnone_icon.png \
    -e $$[QT_INSTALL_LIBS]/libQtCore.so.4 lib/libQtCore.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtGui.so.4 lib/libQtGui.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtOpenGL.so.4 lib/libQtOpenGL.so.4 \
    -e $$[QT_INSTALL_LIBS]/libQtNetwork.so.4 lib/libQtNetwork.so.4 \
#    -e $$[QT_INSTALL_LIBS]/libbbsupport.so.4 lib/libbbsupport.so.4 \
    -e $$[QT_INSTALL_PLUGINS]/platforms/libblackberry.so lib/platforms/libblackberry.so \
    -e $$[QT_INSTALL_PLUGINS]/imageformats/libqjpeg.so plugins/imageformats/libqjpeg.so 

QMAKE_EXTRA_TARGETS += package

