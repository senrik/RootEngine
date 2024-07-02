#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_VERT_CODE "#version 330 core\nlayout(location = 0) in vec3 aPos;\nlayout(location = 1) in vec2 aTexCoord;\nout vec2 TexCoord;\n	uniform mat4 model;\nuniform mat4 view;\nuniform mat4 projection;\nvoid main() { gl_Position = projection * view * model * vec4(aPos, 1.0f);\nTexCoord = aTexCoord;\n}\0"
#define DEFAULT_FRAG_CODE "#version 330 core\nout vec4 FragColor;\nin vec2 TexCoord;\nuniform sampler2D texture1;\nuniform sampler2D texture2;\nvoid main() {	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);}\0"

	typedef unsigned int uint;

#ifdef __cplusplus
}
#endif
#endif // !DATA_TYPES_H