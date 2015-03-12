#ifndef BMPLOADER
#define BMPLOADER
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>


class BMPFILE{

private:

    unsigned char header[54];   // Der Header jedes BMP ist 54-Byte groß
    unsigned int dataPos;       // Position innerhalb der Datei, an der der tatsächliche Payload beginnt
    unsigned int width, height; // Größenbeschreibung des verwendeten Bildes
    unsigned int imageSize;     // Breite * Höhe * 3 (für die RGB-Daten)

    // RGB-Daten
    unsigned char *data;

public:

    // Constructor
    BMPFILE(const char* imagepath){
        // Die Datei öffnen

        FILE *file = fopen(imagepath, "rb");
        if(!file)
            std::cerr << "Die Datei " << imagepath << " konnte nicht geoffnet werden!" << std::endl;

        // Prüfen ob 54-Byte für den Header vorhanden sind
        if(fread(header, 1, 54, file) != 54){
            std::cerr << imagepath << " ist keine BMP-Datei!" << std::endl;
        }

        // Prüfen, ob der Anfang der Datei aus B & M besteht

        if(header[0] != 'B' || header[1] != 'M'){
            std::cerr << imagepath << " ist keine BMP-Datei!" << std::endl;
        }

        // Die entsprechenden Daten aus dem Byte-Array lesen
        dataPos    = *(int*)&(header[0x0A]);
        imageSize  = *(int*)&(header[0x22]);
        width      = *(int*)&(header[0x12]);
        height     = *(int*)&(header[0x16]);

        // Daten nachliefern, falls welche fehlen sollten
        if(imageSize == 0)
            imageSize = width * height * 3; // 3 für jeden RGB-Kanal
        if(dataPos == 0)
            dataPos = 54; // Ab hier ist der Header zu Ende


        // Buffer erstellen
        data = new unsigned char [imageSize];

        // Lese die kompletten in den Buffer
        fread(data, 1, imageSize, file);

        // Datei schließen
        fclose(file);
    }

    unsigned int getDataPos(){
        return dataPos;
    }

    unsigned int getWidth(){
        return width;
    }

    unsigned int getHeight(){
        return height;
    }

    unsigned int getImageSize(){
        return imageSize;
    }

    unsigned char *getData(){
        return data;
    }

};

#endif
