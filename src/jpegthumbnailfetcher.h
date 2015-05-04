#pragma once
 
#include <QIODevice>
#include <QImage>
#include <QIcon>
 
class JpegThumbnailFetcher {
public:
    JpegThumbnailFetcher() {}
    ~JpegThumbnailFetcher() {}
 
    static QImage fetchThumbnail(QIODevice &jpegFile);
    static QImage fetchThumbnail(QString filePath);

    static QIcon *fetchThumbnailAsIcon(QIODevice &jpegFile);
    static QIcon *fetchThumbnailAsIcon(QString filePath);
 
protected:
    static bool readWord( QIODevice &sdevice, unsigned short *target, bool invert=true );
    static bool exifScanloop( QIODevice &jpegFile, unsigned int &tnOffset, unsigned int &tnLength );
};
 
