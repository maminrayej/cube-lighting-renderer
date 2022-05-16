#ifndef OPENGL_IO_H
#define OPENGL_IO_H

#include <string>

using std::string;

string readContent(const string &filePath);

unsigned char *loadImage(const string &imagePath,
                         int &width,
                         int &height,
                         int &numChannels,
                         bool flipVertical = false);

#endif //OPENGL_IO_H
