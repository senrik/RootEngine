#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_VERT_PATH "#version 330 core\nlayout(location = 0) in vec3 aPos;\nlayout(location = 1) in vec2 aTexCoord;\nout vec2 TexCoord;\n	uniform mat4 model;\nuniform mat4 view;\nuniform mat4 projection;\nvoid main() { gl_Position = projection * view * model * vec4(aPos, 1.0f);\nTexCoord = aTexCoord;\n}\0"
#define DEFAULT_FRAG_PATH "#version 330 core\nout vec4 FragColor;\nin vec2 TexCoord;\nuniform sampler2D texture1;\nuniform sampler2D texture2;\nvoid main() {	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);}\0"

	typedef unsigned int uint;

#define MESHES_PER_RENDEROBJ 4
#define DEFAULT_CUBE_VERT_COUNT 64
#define DEFAULT_CUBE_INDEX_COUNT 36
	extern float defaultCubeVerts[];
	uint defaultCubeIndices[];

#define DEFAULT_DIAMOND_VERT_COUNT 48
#define DEFAULT_DIAMOND_INDEX_COUNT 24
	extern float defaultDiamondVerts[];
	extern uint defaultDiamondIndices[];

#define DEFAULT_PLANE_VERT_COUNT 32
#define DEFAULT_PLANE_INDEX_COUNT 6
	extern float defaultPlaneVerts[];
	extern uint defaultPlaneIndices[];
	
#ifdef __cplusplus
}
#endif
#endif // !DATA_TYPES_H