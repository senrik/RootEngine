#include <asset_io.h>

void read_textfile(rt_string* _str, const char* _filePath) {
	FILE* _filePtr = fopen(_filePath, "r");
	char _textBuffer[120];
	if (_filePtr != NULL) {
		while (fgets(_textBuffer, 120, _filePtr) != NULL) {
			int i = 0;
			for (; i < 120; i++) {
				if (_textBuffer[i] == '\n') {
					i++;
					break;
				}
			}
			rt_string_char_append(_str, _textBuffer, i);
			
		}
		fclose(_filePtr);
	}
	else {
		printf_s("ERROR::ASSET_IO::TEXT_FILE_NOT_FOUND");
	}
	
	
}

unsigned char* load_image(const char* _textureName, int* _width, int* _height, int* _nrChannels, int i) {
	unsigned char* _textureData = stbi_load(_textureName, _width, _height, _nrChannels, i);
	if (_textureData != NULL) {
		return _textureData;
	}
	else {
		printf_s("ERROR::ASSET_IO::IMAGE_FILE_NOT_FOUND");
	}
	
}