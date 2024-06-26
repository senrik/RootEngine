#include <data_struct.h>

// Internal functions
void rt_string_resize(rt_string*);

void rt_string_init(rt_string* _str) {
	if (_str == NULL) {
		_str = (rt_string*)malloc(sizeof(rt_string));
		_str->data = (char*)malloc(INITIAL_STRING_SIZE * sizeof(char));
		
	}
	else {
		_str->data = (char*)malloc(INITIAL_STRING_SIZE * sizeof(char));
		
	}
	_str->data[0] = '\0';
	_str->length = 0;
	_str->size = INITIAL_STRING_SIZE;
}

void rt_string_append(rt_string* _str, const rt_string* _app) {
	rt_string_char_append(_str, _app->data, _app->length);
}

void rt_string_char_append(rt_string* _str, const char* s, uint _length) {
	if (_length > _str->size / 2 || _str->length + _length > _str->size) {
		rt_string_resize(_str);
	}

	for (int i = _str->length; i < _str->length + _length; i++) {
		_str->data[i] = s[i - _str->length];
	}
	_str->length += _length;
	_str->data[_str->length] = '\0';
}

void rt_string_clear(rt_string* _str) {
	if (_str != NULL) {
		free(_str->data);
		_str->data = (char*)malloc(INITIAL_STRING_SIZE * sizeof(char));
		_str->length = 0;
		_str->size = INITIAL_STRING_SIZE;
	}
	
}

void rt_string_terminate(rt_string* _str) {
	if (_str->data != NULL) {
		free(_str->data);
	}
	free(_str);
}

/// <summary>
/// Increases the potential length of the string to twice its current length.
/// </summary>
/// <param name="_str"></param>
void rt_string_resize(rt_string* _str) {
	if (_str->data != NULL) {
		_str->data = (char*)realloc(_str->data, sizeof(char)*_str->size * 2);
		_str->size *= 2;
	}
}