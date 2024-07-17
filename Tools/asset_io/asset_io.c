#include <asset_io.h>

rt_string read_textfile(const char* _filePath) {
	FILE* _filePtr = fopen(_filePath, "r");
	char _textBuffer[120];

	rt_string _out;
	rt_string_init(&_out);

	while (fgets(_textBuffer, 120, _filePtr) != NULL) {
		int i = 0;
		for (; i < 120; i++) {
			if (_textBuffer[i] == '\n') {
				i++;
				break;
			}
		}
		rt_string_char_append(&_out, _textBuffer, i);
	}
	fclose(_filePtr);
	return _out;
}

char* load_image(const char* _textureName, int* _width, int* _height, int* _nrChannels, int i) {
	return stbi_load(_textureName, _width, _height, _nrChannels, i);
}