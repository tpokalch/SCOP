
#include <glad/glad.h>
//GLAD should be included before GLFW
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>

void	framebuffer_size_callback(GLFWwindow *window, int w, int h);
void	processInput(GLFWwindow *window);
void	cursor_position_callback(GLFWwindow* window, double x, double y);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
char	**ft_strsplit(char const *s, char c);
/*
const char *geometryShaderSource = 
	"#version 330 core\n"
	"layout (triangles) in;\n"
	"layout (points, max_vertices = 1) out;\n"

	"void main() {\n"
		"gl_Position = gl_in[0].gl_Position;\n"
		"EmitVertex();\n"
		"EndPrimitive();\n"
	"}\0";
*/

////////////////////////////////////////////////////////////////////////////////////
	const char *vertexShaderSource =
			"#version 330 core\n" //the version matches if GLSL matches the version of OpenGL
// The vertex shader differs in its input, in that it receives its input straight from the vertex data. 
			"layout (location = 0) in vec3 aPos;\n" //declare all input vertex attr
//location = 0 allows as to specify vertex attributes (stride, length)
//of aPos through vertexAttributePointer by passing 0 
//as the first param
//I think that every time the shader is called, the aPos is searched location = 0,
//but the each time the stride is added to offset
			"layout (location = 1) in vec3 color;\n"
			"layout (location = 2) in vec3 aNormal;\n"
//comment to test if compiles geomShader
			"out vec3 outColor;\n"
			"out vec3 FragPos;\n"
			"out vec3 Normal;\n"
			"out vec3 campos;\n"

			"uniform mat4 matrix;\n"
			"uniform vec4 p;\n"

//for geomShader1

/*
"out VS_OUT {\n" 
"	vec3 color;\n"
"} vs_out;\n"
*/

//for other geom shader

"out VS_OUT {\n" 
"	vec4 normalEnd;\n"
"} vs_out;\n"



//need to get address from render loop
//			"uniform float f;\n"

			"void main()\n"
			"{\n"
				"gl_Position =  (vec4(aPos, 1));\n"

//				"vs_out.matrix = matrix;\n"
	//			"vs_out.color = color;\n"
				//if straight to fragment shader

				"outColor = color;\n"
				"gl_Position = matrix * gl_Position;\n"
				"FragPos = aPos;\n"
				"Normal = aNormal;\n"
				"campos = vec3(p);\n"

				/////////////
//				"vs_out.normalEnd =  matrix * (vec4(aPos + aNormal * 0.4, 1))\n;"

#if 0
				"vec3 lightPos = vec3(100, 100, 100);\n"
				"vec3 hitli = lightPos - aPos;\n"
				"hitli = normalize(hitli);\n"
				"float brightness = max(0.3, dot(aNormal, hitli));\n"
				"outColor = color * brightness;\n"
				"if (brightness < 0.3)\n"
				"	return ;\n" //no light spots when to dark
////////////////////////// for light spots

				"vec3 hitcam = normalize(vec3(p) - aPos);\n"
				"vec3 newNormal = dot(hitcam, aNormal) * aNormal;\n"
				"vec3 reflray = newNormal + (newNormal - hitcam);\n"


				"reflray = normalize(reflray);\n"
				"float coef = dot(reflray, hitli);\n"
				"if (coef < 0)\n"
				"{\n"
					"return ;\n"
				"}\n"


				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"


				"outColor = (1 -coef) * outColor + (coef )* vec3(1, 1, 1);\n"

#endif
			"}\0";





///////////////////////////////////////////////////////////////////////////
//to enable geometry shader comment outColor = color in vertex shader and change
//custom color to 1 1 1 1 color in fragment shader
//also compile this shader with the sahder program
//	this shader program will draw normals!!!


const char *vertexShaderSourceNormal = 

"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 color;\n"
"layout (location = 2) in vec3 aNormal;\n"

"uniform mat4 matrix;\n"
"uniform vec4 p;\n"


"out VS_OUT {\n" 
"	vec4 normalEnd;\n"
"	vec3 outColor;\n"
"} vs_out;\n"

"void main()\n"
"{\n"
	"gl_Position = matrix * vec4(aPos, 1);\n"
	"vs_out.normalEnd =  matrix * (vec4(aPos + aNormal * 0.4, 1))\n;"
	"vs_out.outColor =  vec3(1, 0, 0)\n;"

///////////////for lighting
/*
	"vec3 lightPos = vec3(100, 100, 100);\n"
	"vec3 hitli = lightPos - aPos;\n"
	"hitli = normalize(hitli);\n"
	"float brightness = max(0.3, dot(aNormal, hitli));\n"
	"vs_out.outColor = color * brightness;\n"

/////////////////////for light spots

	"if (brightness == 0.3)\n"
	"	return ;\n"
	"vec3 hitcam = normalize(vec3(p) - aPos);\n"
	"vec3 newNormal = dot(hitcam, aNormal) * aNormal;\n"
	"vec3 reflray = newNormal + (newNormal - hitcam);\n"


	"reflray = normalize(reflray);\n"
	"float coef = dot(reflray, hitli);\n"
	"if (coef < 0)\n"
	"{\n"
		"return ;\n"
	"}\n"


	"coef = coef * coef;\n"
	"coef = coef * coef;\n"
	"coef = coef * coef;\n"
	"coef = coef * coef;\n"


	"vs_out.outColor = (1 -coef) * vs_out.outColor + (coef )* vec3(1, 1, 1);\n"
*/
"}\0";




const char *geometryShaderSourceNormal = 

"#version 330 core\n"
"layout (triangles) in;\n"
"layout (line_strip, max_vertices = 6) out;\n"
"out vec3 outColor;\n"

"in VS_OUT {\n"
"	vec4 normalEnd;\n"
"	vec3 outColor;\n"
"} gs_in[];\n"

"void GenerateLine(int index)\n"
"{\n"
"	gl_Position = gl_in[index].gl_Position;\n"
"	outColor = gs_in[index].outColor;\n"//need to specify color for every vertex 
"	EmitVertex();\n"

"	gl_Position = vec4(gs_in[index].normalEnd);\n"
"	outColor = gs_in[index].outColor;\n"//here too
"	EmitVertex();\n"

"	EndPrimitive();\n"
"}\n"

"void main()\n"
"{\n"
"	GenerateLine(0);\n"  
"	GenerateLine(1);\n"
"	GenerateLine(2);\n"
"}\0";

const char *fragmentShaderSourceNormal =
	"#version 330 core\n"
	"out vec4 FragColor;\n"

	"in vec3 outColor;\n"

	"void main()\n"
	"{\n"
		"FragColor = vec4(outColor, 1);\n"
	"}\0";



///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//this shader calculates normals. takes vertice's coordinates in global space and the matrix.

/*
const char *geometryShaderSource1 = 
"#version 330 core\n"
"layout (triangles) in;\n"
"layout (triangle_strip, max_vertices = 3) out;\n"
"out vec3 outColor;\n"

"uniform mat4 matrix;\n"

"in VS_OUT {\n"
//"	mat4 matrix;\n"
"	vec3 color;\n"
"} gs_in[];\n"


"void GenerateLine(int index, vec3 normal)\n"
"{\n"
"	vec3 hitli = normalize(vec3(100, 100, 100) - vec3(gl_in[index].gl_Position));\n"
"	float bri = max(abs(dot(hitli, normal)), 0.3);\n"
"	outColor = gs_in[index].color * bri;\n"
"	gl_Position = matrix * gl_in[index].gl_Position;\n"
"	EmitVertex();\n"
"}\n"

"void main()\n"
"{\n"
"   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);\n"
"   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);\n"
"   vec3 normal = normalize(cross(b, a));\n"


"	GenerateLine(0, normal);\n"  
"	GenerateLine(1, normal);\n"
"	GenerateLine(2, normal);\n"
"	EndPrimitive();\n"


"}\0";
*/


//////////////////////////////////////////////////////////////////////
//Fragment shader:
	const char *fragmentShaderSource =
				"#version 330 core\n"
				"out vec4 FragColor;\n" // has to have out vec4 type as output (but vec3 works too?)

				"in vec3 FragPos;\n"
				"in vec3 Normal;\n"
				"in vec3 campos;\n"

//geomShader
//				"in vec3 normal;\n" //from geom shader
				"in vec3 outColor;\n"

				"void main()\n"
				"{\n"



				"vec3 Color = outColor;\n"

				"vec3 lightPos = vec3(100, 100, 100);\n"
				"vec3 hitli = lightPos - FragPos;\n"
				"hitli = normalize(hitli);\n"
				"float brightness = dot(Normal, hitli);\n"
				"brightness = max(0.3, abs(brightness));\n"
				"Color *= brightness;\n"
				"FragColor = vec4(Color, 1);\n"


////////////////////////// for light spots

				"vec3 hitcam = normalize(campos - FragPos);\n"
				"vec3 newNormal = dot(hitcam, Normal) * Normal;\n"
				"vec3 reflray = newNormal + (newNormal - hitcam);\n"


				"reflray = normalize(reflray);\n"
				"float coef = dot(reflray, hitli);\n"
				"if (coef < 0)\n"
				"{\n"
					"FragColor = vec4(Color, 1);\n"
					"return ;\n"
				"}\n"


				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"



				"FragColor = vec4((1 -coef) * Color + (coef )* vec3(1, 1, 1), 1);\n"


				"}\0";




class	vec4
{
	public:
		vec4()
		{
			array[0] = 0; array[1] = 0; array[2] = 0; array[3] = 0;
		}
		vec4(float xx, float yy, float zz, float ww)
		{
			array[0] = xx; array[1] = yy; array[2] = zz; array[3] = ww;
		}
		float array[4];
/*		float operator*(vec4 &rhs)
		{
			return (rhs[0] * array[0] + rhs[1] * array[1] + rhs[2] * array[2] + rhs[3] * array[3]);
		}
*/		float &operator[] (int index) { return array[index]; }

		float operator*(vec4 &rhs)
		{
			float ret = 
				rhs[0] * array[0] +
				rhs[1] * array[1] +
				rhs[2] * array[2] +
				rhs[3] * array[3];
			return ret;
		}


		vec4 operator+(vec4 &rhs)
		{
			vec4 ret(
				rhs[0] + array[0],
				rhs[1] + array[1],
				rhs[2] + array[2],
				rhs[3] + array[3]
			);
			return ret;
		}

		vec4 operator-(vec4 &rhs)
		{
			vec4 ret(
				array[0] - rhs[0],
				array[1] - rhs[1],
				array[2] - rhs[2],
				array[3] - rhs[3]
			);
			return ret;
		}
		vec4 operator+=(vec4 rhs)
		{
			return (*this + rhs);
		}


};

class mat4
{
	public:
		mat4()
			 {
			array[0] = 1; array[1] = 0, array[2] = 0, array[3] = 0;
			array[4] = 0; array[5] = 1, array[6] = 0, array[7] = 0;
			array[8] = 0; array[9] = 0, array[10] = 1, array[11] = 0;
			array[12] = 0; array[13] = 0, array[14] = 0, array[15] = 1;
			 }
	
		mat4(float x11, float x12, float x13, float x14,
			 float x21, float x22, float x23, float x24,
			 float x31, float x32, float x33, float x34,
			 float x41, float x42, float x43, float x44)
			 {
			array[0] = x11; array[1] = x12, array[2] = x13, array[3] = x14;
			array[4] = x21; array[5] = x22, array[6] = x23, array[7] = x24;
			array[8] = x31; array[9] = x32, array[10] = x33, array[11] = x34;
			array[12] = x41; array[13] = x42, array[14] = x43, array[15] = x44;
			 }
		mat4(vec4 &column1, vec4 &column2, vec4 &column3, vec4 &column4)
			 {
			array[0] = column1[0]; array[1] = column2[0], array[2] = column3[0], array[3] = column4[0];
			array[4] = column1[1]; array[5] = column2[1], array[6] = column3[1], array[7] = column4[1];
			array[8] = column1[2]; array[9] = column2[2], array[10] = column3[2], array[11] = column4[2];
			array[12] = column1[3]; array[13] = column2[3], array[14] = column3[3], array[15] = column4[3];
			 }



		float array[16];
		vec4 operator*(vec4&& rhs)
		{
			vec4 ret(
				array[0] * rhs[0] + array[1] * rhs[1] + array[2] * rhs[2] + array[3] * rhs[3],
				array[4] * rhs[0] + array[5] * rhs[1] + array[6] * rhs[2] + array[7] * rhs[3],
				array[8] * rhs[0] + array[9] * rhs[1] + array[10] * rhs[2] + array[11] * rhs[3],
				array[12] * rhs[0] + array[13] * rhs[1] + array[14] * rhs[2] + array[15] * rhs[3]
				);
			return (ret);
		}
		vec4 operator*(vec4& rhs)
		{
			return (*this * std::move(rhs));
		}	
		mat4 operator*(mat4 &&rhs)
		{
			vec4 column1(*this * vec4(rhs[0], rhs[4], rhs[8], rhs[12]));
			vec4 column2(*this * vec4(rhs[1], rhs[5], rhs[9], rhs[13]));
			vec4 column3(*this * vec4(rhs[2], rhs[6], rhs[10], rhs[14]));
			vec4 column4(*this * vec4(rhs[3], rhs[7], rhs[11], rhs[15]));

			mat4 ret(column1, column2, column3, column4);
			return (ret);
		}
		mat4 operator*(mat4 &rhs)
		{
//			printf("___________mult matrix\n");
			return (*this * std::move(rhs));
		}

	mat4 invert() {mat4 ret(*this); ret[2] = -ret[2]; ret[8] = -ret[8]; ret[6] = -ret[6]; ret[9] = -ret[9]; return ret;}
		float &operator[] (int index) { return array[index]; }
		operator float *() {return array;};
};		


int numberoffloats = 0;



int anglex = 0;
int angley = 0;

/*
vec4 campos(
0, 0, 30, 0
);

vec4 cambasex(
0.2, 0, 0, 0
);

vec4 cambasez(
0, 0, -0.2, 0
);
*/
float	n = 0.20f;
float	f = 400.0f;
float	h = 0.10f;

mat4	projectionMatrix(
n / h, 0.0f, 0.0f, 0.0f,
0.0f, n / h, 0.0f, 0.0f,
0.0f, 0.0f, -(f + n) / (f - n), -2 * f * n / (f - n),
0.0f, 0.0f, -1.0f, 0.0f  //positive z dir is outwards when = 1
			);
/*
mat4	yRotate(
1.0f, 0.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f, 0.0f,
0.0f, 0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f
		);

mat4	xRotate(
1.0f, 0.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f, 0.0f,
0.0f, 0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f
		);

*/

float	translate[] = {
1.0f, 0.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f, 0.0f,
0.0f, 0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f
		};

static int	getFile(std::fstream &myfile)
{
	if (myfile.is_open())
		return (1);
	std::cerr << "Error: " << std::strerror(errno) << std::endl;
	return (0);
}

class Model
{
	public:
		void loadData(char *path);
		void pushBackNormals();
		void createNormals();
		void initBuffers();
		void draw();

		std::vector<unsigned int>vertex_indices;
		std::vector<float>vertices;
		std::vector<float>normals;
		std::vector<unsigned int>normal_indices;


		unsigned int offset_to_normals;
		unsigned int	VAO;	
		unsigned int	VBO;


//		for physics
		std::vector<std::vector<int>>	conections;
		std::vector<std::array<float, 3> > forces;
		std::vector<std::array<float, 3> > speeds;

		void	updateVertices();
		void	initConections();

		std::vector<float> original_vertices;
		std::vector<std::array<float, 3> >original_forces;

		int stride; //stride on vertices (can be 3, or 6 if with rgb colors)
};


void	Model::initConections()
{

	conections.resize(lround(vertices.size() / stride));
	forces.resize(lround(vertices.size() / stride));
//	bzero(&forces[0], sizeof(forces) * sizeof(float));
	speeds.resize(lround(vertices.size() / stride));
//	bzero(&speeds[0], sizeof(forces) * sizeof(float));

	original_vertices = vertices; // for use in pdateVertices

	printf("vertices size is %lu\n", vertices.size());
	printf("forces size is %lu\n", forces.size());
//	return ;
	for (int i = 0; i < vertex_indices.size(); i += 3)

	{
		printf("\n\npushing connections\n");
		printf("i is %d\n", i);
		printf("vertex index is %d", vertex_indices[i]);
		int first_index = vertex_indices[i];
		int second_index = vertex_indices[i + 1];
		int third_index = vertex_indices[i + 2];


		conections[first_index].push_back(second_index);
		conections[first_index].push_back(third_index);

		conections[second_index].push_back(first_index);
		conections[second_index].push_back(third_index);

		conections[third_index].push_back(first_index);
		conections[third_index].push_back(second_index);

//		printf("\nBEFORE___________________________________________");
/*		printf("\n%d: vertex %d is connected to vertices ", i, first_index);
		for (int j = 0; j < conections[first_index].size(); j++)
		{
			printf("%d, ", conections[first_index][j]);
		}

		printf("\n%d: vertex %d is connected to vertices ", i + 1, second_index);
		for (int j = 0; j < conections[second_index].size(); j++)
		{
			printf("%d, ", conections[second_index][j]);
		}

		printf("\n%d: vertex %d is connected to vertices ", i + 2, third_index);
		for (int j = 0; j < conections[third_index].size(); j++)
		{
			printf("%d, ", conections[third_index][j]);
		}
		printf("\nAFTER__________________________________________");

*/
		std::vector<int> v = conections[first_index];
		std::sort(v.begin(), v.end());
		std::vector<int>::iterator ip = std::unique(v.begin(), v.end());
		v.resize(std::distance(v.begin(), ip)); 
		conections[first_index] = v;

		v = conections[second_index];
		std::sort(v.begin(), v.end());
		ip = std::unique(v.begin(), v.end());
		v.resize(std::distance(v.begin(), ip)); 
		conections[second_index] = v;

		v = conections[third_index];
		std::sort(v.begin(), v.end());
		ip = std::unique(v.begin(), v.end());
		v.resize(std::distance(v.begin(), ip)); 
		conections[third_index] = v;




		printf("\n%d: vertex %d is connected to vertices ", i, first_index);
/*		for (int j = 0; j < conections[first_index].size(); j++)
		{
			printf("%d, ", conections[first_index][j]);
		}

		printf("\n%d: vertex %d is connected to vertices ", i + 1, second_index);
		for (int j = 0; j < conections[second_index].size(); j++)
		{
			printf("%d, ", conections[second_index][j]);
		}

		printf("\n%d: vertex %d is connected to vertices ", i + 2, third_index);
		for (int j = 0; j < conections[third_index].size(); j++)
		{
			printf("%d, ", conections[third_index][j]);
		}
*/	}

//	printf("\ndone pushing connections\n");
//	printf("size of vertices %lu\n", myModel.vertices.size());
//	printf("size of indices %lu\n", myModel.vertex_indices.size());


	for (int i = 0; i < conections.size(); i++)
	{
		if (conections[i].size() == 0)
			continue ;
		printf("\ni = %d. index - %d, conections - ", i, vertex_indices[i]);
		for (int j = 0; j < conections[i].size(); j++)
		{
			printf("%d, ", conections[i][j]);
		}
//		printf("\n%d vertex is %f, %f, %f", i, vertices[3 * i + 0], vertices[3 * i + 1], vertices[3 * i + 2]);
	}
	printf("size of vertices %lu\n", vertices.size());
	printf("size of indices %lu\n",vertex_indices.size());
	printf("size of conections %lu\n",conections.size());



/////////////////////////		INIT FORCES ORIGINAL
#if 0
	original_forces.resize(vertices.size() / stride);

	for (int i = 0; i < forces.size(); i++)
	{


//		printf("creating forces\n");
//		int index = myModel.vertex_indices[i];
		int conectionssize = conections[i].size();
		//ith vertex is connected to some j, j+1... other vetices
		original_forces[i][0] = 0;
		original_forces[i][1] = 0;
		original_forces[i][2] = 0;



		for (int j = 0; j < conectionssize; j++)
		{
		//	printf("i is %d\n", i);
//		printf("index is %d\n", index);
	
			original_forces[i][0] +=  (vertices[3 * conections[i][j] + 0] - vertices[3 * i + 0]);
			original_forces[i][1] +=  (vertices[3 * conections[i][j] + 1] - vertices[3 * i + 1]);
			original_forces[i][2] +=  (vertices[3 * conections[i][j] + 2] - vertices[3 * i + 2]);

/*			if (index == 1)
			{
				printf("_____________________index 1 coresponds to i = %d\n", i);
				printf("force on 1 vertex is %f, %f, %f\n", forces[i][0], forces[i][1], forces[i][2]);
			}
*/
		}
//		printf("final force on %d vertex is %f, %f, %f\n", i, forces[i][0], forces[i][1], forces[i][2]);
	}
#endif
//	vertices[1200] += 1;

///////////////////////////////////////////

}

void	Model::updateVertices()
{
	int forcessize = forces.size(); 
//	printf("forces size %lu\n", forces.size());
	for (int i = 0; i < forcessize; i++)
	{
//		printf("creating forces\n");
//		int index = myModel.vertex_indices[i];
		int conectionssize = conections[i].size();
		//ith vertex is connected to some j, j+1... other vetices
		forces[i][0] = 0;
		forces[i][1] = 0;
		forces[i][2] = 0;



		int stridei = stride * i;

		for (int j = 0; j < conectionssize; j++)
		{
		//	printf("i is %d\n", i);
//		printf("index is %d\n", index);
	
//			this for real approx equation

			int strideconections = stride * conections[i][j];


			float original_length[3];
			original_length[0] = (original_vertices[stride * conections[i][j] + 0] - original_vertices[stride * i + 0]) * 0.8;
			original_length[1] = (original_vertices[stride * conections[i][j] + 1] - original_vertices[stride * i + 1]) * 0.8;
			original_length[2] = (original_vertices[stride * conections[i][j] + 2] - original_vertices[stride * i + 2]) * 0.8;



	


			forces[i][0] += vertices[strideconections + 0] - vertices[stridei + 0] - original_length[0];
			forces[i][1] += vertices[strideconections + 1] - vertices[stridei + 1] - original_length[1];
			forces[i][2] += vertices[strideconections + 2] - vertices[stridei + 2] - original_length[2];


//			this is for real wave equation
/*
			forces[i][0] += vertices[strideconections + 0] - vertices[stridei + 0];
			forces[i][1] += vertices[strideconections + 1] - vertices[stridei + 1];
			forces[i][2] += vertices[strideconections + 2] - vertices[stridei + 2];
*/

/*			if (index == 1)
			{
				printf("_____________________index 1 coresponds to i = %d\n", i);
				printf("force on 1 vertex is %f, %f, %f\n", forces[i][0], forces[i][1], forces[i][2]);
			}
*/
		}
//		printf("final force on %d vertex is %f, %f, %f\n", i, forces[i][0], forces[i][1], forces[i][2]);
	}

//	printf("done\n");
//	return (0);
//#if 0
	int speedssize = speeds.size();
	for (int i = 0; i < speedssize; i++)
	{
		//ith vertex is connected to some j, j+1... other vetices
//		int index = myModel.vertex_indices[i];
		std::array<float, 3> &force = forces[i];
/*		std::array<float, 3> original_force = original_forces[i];


		float length_of_original_force = sqrt(original_force[0] * original_force[0] + original_force[1] * original_force[1] + original_force[2] * original_force[2]);

		float length_of_force = sqrt(force[0] * force[0] + force[1] * force[1] + force[2] * force[2]);
		float equilibrium_length = 0.9 * length_of_original_force;
		float normed_force[3] = {force[0] / length_of_force,
					force[1] / length_of_force,
					force[2] / length_of_force};
		force[0] = (length_of_force - equilibrium_length) * normed_force[0];
		force[1] = (length_of_force - equilibrium_length) * normed_force[1];
		force[2] = (length_of_force - equilibrium_length) * normed_force[2];

*/



		speeds[i][0] += force[0] * 0.5;
		speeds[i][1] += force[1] * 0.5;
		speeds[i][2] += force[2] * 0.5;


//		printf("length of force is %f\n", length_of_force);
//		printf("%d force is %f, %f, %f\n", i, force[0], force[1], force[2]);
//		printf("%d speed is %f, %f, %f\n", i, speeds[i][0], speeds[i][1], speeds[i][2]);


	}
//#endif
//	return (0);
//	printf("speeds done\n");
	int verticessize = vertices.size() / stride;
	for (int i = 0; i < verticessize; i++)
	{
		//ith vertex is connected to some j, j+1... other vetices
//		int index = vertex_indices[i];	

		int stridei = stride * i;


		vertices[i * stride + 0] += speeds[i][0] * 0.5;
		vertices[i * stride + 1] += speeds[i][1] * 0.5;
		vertices[i * stride + 2] += speeds[i][2] * 0.5;

/*
		vertices[stridei + 0] += forces[i][0] * 0.01;
		vertices[stridei + 1] += forces[i][1] * 0.01;
		vertices[stridei + 2] += forces[i][2] * 0.01;
*/

	}

/////////////////////////// UPDATE NORMALS

	createNormals();
/*
	for (int i = 0; i < vertex_indices.size(); i = i + 3)
	{
		int first_index =  vertex_indices[i];
		int second_index = vertex_indices[i + 1];
		int third_index =   vertex_indices[i + 2];

		float first_vertex[3];
		first_vertex[0] = vertices[stride * vertex_indices[i] + 0];
		first_vertex[1] = vertices[stride * vertex_indices[i] + 1];
		first_vertex[2] = vertices[stride * vertex_indices[i] + 2];


		float second_vertex[3];
		second_vertex[0] = vertices[stride * vertex_indices[(i + 1)] + 0];
		second_vertex[1] = vertices[stride * vertex_indices[(i + 1)] + 1];
		second_vertex[2] = vertices[stride * vertex_indices[(i + 1)] + 2];

		float third_vertex[3];
		third_vertex[0] = vertices[stride * vertex_indices[(i + 2)] + 0];
		third_vertex[1] = vertices[stride * vertex_indices[(i + 2)] + 1];
		third_vertex[2] = vertices[stride * vertex_indices[(i + 2)] + 2];

		float dif1[3];
		dif1[0] = first_vertex[0] - second_vertex[0];
		dif1[1] = first_vertex[1] - second_vertex[1];
		dif1[2] = first_vertex[2] - second_vertex[2];

		float dif2[3];
		dif2[0] = first_vertex[0] - third_vertex[0];
		dif2[1] = first_vertex[1] - third_vertex[1];
		dif2[2] = first_vertex[2] - third_vertex[2];


		float normal[3];
//cross(dif1, dif2)
		normal[0] = (dif1[1] * dif2[2] - dif1[2] * dif2[1]);
		normal[1] = (dif1[2] * dif2[0] - dif1[0] * dif2[2]);
		normal[2] = (dif1[0] * dif2[1] - dif1[1] * dif2[0]);

		float normallen = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

		normal[0] /= normallen;
		normal[1] /= normallen;
		normal[2] /= normallen;


//// may need for models that don't have normals

		vertices[offset_to_normals + 3 * first_index + 0] = normal[0];
		vertices[offset_to_normals + 3 * first_index + 1] = normal[1];
		vertices[offset_to_normals + 3 * first_index + 2] = normal[2];

		vertices[offset_to_normals + 3 * second_index + 0] = normal[0];
		vertices[offset_to_normals + 3 * second_index + 1] = normal[1];
		vertices[offset_to_normals + 3 * second_index + 2] = normal[2];

		vertices[offset_to_normals + 3 * third_index + 0] = normal[0];
		vertices[offset_to_normals + 3 * third_index + 1] = normal[1];
		vertices[offset_to_normals + 3 * third_index + 2] = normal[2];

//		printf("vertices[%d] multily by 0\n", stride * first_index + 3);
//		printf("vertices[%d] multily by 0\n", stride * first_index + 4);
//		printf("vertices[%d] multily by 0\n", stride * first_index + 5);

	}

*/
///////////////////////////////////////////////////////////////////////////
//		THIS IS UPDATING BRIGHTNESS

#if 0
	for (int i = 0; i < vertices.size() / 9; i += 1)
	{
		float first_vertex[3];
		first_vertex[0] = vertices[stride * i + 0];
		first_vertex[1] = vertices[stride * i + 1];
		first_vertex[2] = vertices[stride * i + 2];



		float hitli[3];
		hitli[0] = first_vertex[0] - 100;
		hitli[1] = first_vertex[1] - 100;
		hitli[2] = first_vertex[2] - 100;

		float hitlilen = sqrt(hitli[0] * hitli[0] + hitli[1] * hitli[1] + hitli[2] * hitli[2]);

		hitli[0] /= hitlilen;
		hitli[1] /= hitlilen;
		hitli[2] /= hitlilen;

		double normal[3];

		normal[0] = vertices[offset_to_normals + 3 * i + 0];
		normal[1] = vertices[offset_to_normals + 3 * i + 1];	
		normal[2] = vertices[offset_to_normals + 3 * i + 2];

		
		printf("normals is %f,%f,%f\n", normal[0], normal[1], normal[2]);	
//		usleep(10000);
		float bri;
		bri = fmax(fabs(normal[0] * hitli[0] + normal[1] * hitli[1] + normal[2] * hitli[2]), 0.3);
		printf("bri is %f\n", bri);
//		if (bri < 0.5)
//			bri = 1;
		if (bri <= 0.3 )
			printf("aaaaaaaaaaaaaaaaaaaaaa\n");

//		bri = 0.8;


		vertices[stride * i + 3] *= bri;
		vertices[stride * i + 4] *= bri;
		vertices[stride * i + 5] *= bri;

		printf("updating normals\n");
	}

#endif

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
}

void	Model::createNormals()
{
	for (int i = 0; i < vertex_indices.size(); i = i + 3)
	{
		int first_index =  vertex_indices[i];
		int second_index = vertex_indices[i + 1];
		int third_index =   vertex_indices[i + 2];

		float first_vertex[3];
		first_vertex[0] = vertices[stride * vertex_indices[i] + 0];
		first_vertex[1] = vertices[stride * vertex_indices[i] + 1];
		first_vertex[2] = vertices[stride * vertex_indices[i] + 2];


		float second_vertex[3];
		second_vertex[0] = vertices[stride * vertex_indices[(i + 1)] + 0];
		second_vertex[1] = vertices[stride * vertex_indices[(i + 1)] + 1];
		second_vertex[2] = vertices[stride * vertex_indices[(i + 1)] + 2];

		float third_vertex[3];
		third_vertex[0] = vertices[stride * vertex_indices[(i + 2)] + 0];
		third_vertex[1] = vertices[stride * vertex_indices[(i + 2)] + 1];
		third_vertex[2] = vertices[stride * vertex_indices[(i + 2)] + 2];

		float dif1[3];
		dif1[0] = first_vertex[0] - second_vertex[0];
		dif1[1] = first_vertex[1] - second_vertex[1];
		dif1[2] = first_vertex[2] - second_vertex[2];

		float dif2[3];
		dif2[0] = first_vertex[0] - third_vertex[0];
		dif2[1] = first_vertex[1] - third_vertex[1];
		dif2[2] = first_vertex[2] - third_vertex[2];


		float normal[3];
//cross(dif1, dif2)
		normal[0] = -(dif1[1] * dif2[2] - dif1[2] * dif2[1]);
		normal[1] = -(dif1[2] * dif2[0] - dif1[0] * dif2[2]);
		normal[2] = -(dif1[0] * dif2[1] - dif1[1] * dif2[0]);

		float normallen = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

		normal[0] /= normallen;
		normal[1] /= normallen;
		normal[2] /= normallen;

//// may need for models that don't have normals

//	may not need if
		if (vertices[offset_to_normals + 3 * first_index + 0] == 0 &&
		vertices[offset_to_normals + 3 * first_index + 1] == 0 &&
		vertices[offset_to_normals + 3 * first_index + 2] == 0)
		{
		vertices[offset_to_normals + 3 * first_index + 0] = normal[0];
		vertices[offset_to_normals + 3 * first_index + 1] = normal[1];
		vertices[offset_to_normals + 3 * first_index + 2] = normal[2];
		}
		if (vertices[offset_to_normals + 3 * second_index + 0] == 0 &&
		vertices[offset_to_normals + 3 * second_index + 1] == 0 &&
		vertices[offset_to_normals + 3 * second_index + 2] == 0)
		{
		vertices[offset_to_normals + 3 * second_index + 0] = normal[0];
		vertices[offset_to_normals + 3 * second_index + 1] = normal[1];
		vertices[offset_to_normals + 3 * second_index + 2] = normal[2];
		}
		if (vertices[offset_to_normals + 3 * third_index + 0] == 0 &&
		vertices[offset_to_normals + 3 * third_index + 1] == 0 &&
		vertices[offset_to_normals + 3 * third_index + 2] == 0)
		{
		vertices[offset_to_normals + 3 * third_index + 0] = normal[0];
		vertices[offset_to_normals + 3 * third_index + 1] = normal[1];
		vertices[offset_to_normals + 3 * third_index + 2] = normal[2];
		}

//		printf("vertices[%d] multily by 0\n", stride * first_index + 3);
//		printf("vertices[%d] multily by 0\n", stride * first_index + 4);
//		printf("vertices[%d] multily by 0\n", stride * first_index + 5);

	}
}


void	Model::pushBackNormals()
{

//	if with color
	stride = 6; 

//#if 0
	int i = 0;
	int j = 0;
	//j is the index of the vertex
	//j ranges from 0th vertex to last vertex

//	int numberOfVertices = vertices.size() / 2;

	//i is an index of the vertex indices

	printf("vertices count %lu\n", vertices.size() / stride);

	//SEGFULTS HERE IF 12//1 type of faces
	if (normals.size() == 0)
	{
		printf("no model normals\n");
		vertices.resize(vertices.size() + vertices.size() / stride * 3);
		createNormals();
		return ;
	}

	while (i < vertex_indices.size())
	//for every vertex_index search for normal_index which references jth vertex
	{
		//if we found an index, which tells us to draw jth vertex
		
		if (vertex_indices[i] == j)
		{
			printf("j is %d\n", j);
			printf("i is %d\n", i);
			printf("normal indices size is %lu\n", normal_indices.size());
			vertices.push_back(normals[6 * normal_indices[i]]);
			vertices.push_back(normals[6 * normal_indices[i] + 1]);
			vertices.push_back(normals[6 * normal_indices[i] + 2]);
			j++;
			i = 0;
			continue;
		}
		//if no i references the jth vertex, then no face references jth vertex, so
		//the connection with the the normal cannot be established. the search ends
		i++;
	}
//	createNormals();
	printf("added vectors %lu\n", vertices.size()/6 - 7752/6);
//#endif
}


static void	free_double_pointer(char **explode)
{
	int i = 0;

	while (explode[i])
	{
		free(explode[i]);
		i++;
	}
	free(explode);
}


static void	loadVectors(std::vector<float> &vertices, char **explode)
{
	srand(time(0));
	printf("after explode %s, %s, %s\n", explode[1], explode[2], explode[3]);

	vertices.push_back(atof(explode[1]) * 1);
	vertices.push_back(atof(explode[2]) * 1);
	vertices.push_back(atof(explode[3]) * 1);

	float r = 0,g = 0,b = 0;

	while (r == 0
		&& g == 0
		&& b == 0) //no black points

	{
			r = 1;
			g = fmod((vertices.size() / 100.0), 1);
			b = 0.5;

/*		r = 0.5;
		g = 0.5;
		b = 1;
*/
/*		r = rand() % 2;
		g = rand() % 2;
		b = rand() % 2;
*/	}
//uncomment return for colors
//	return ;
	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

}

static void	loadIndices(char **explode, std::vector<unsigned int> &vertex_indices, std::vector<unsigned int> &normal_indices)
{
	printf("___________________\n");
	//explode is the face line split by spaces
	//explode[0] is the letter f
	//exlode[] = {f, v/vt/vn, v/vt/vn, v/vt/vn}
	//xindices = {v, vt, vn} 
	char **xindices = ft_strsplit(explode[1], '/');
	char **yindices = ft_strsplit(explode[2], '/'); 
	char **zindices = ft_strsplit(explode[3], '/');

	printf("push vertex indices\n");
	vertex_indices.push_back(atoi(xindices[0]) - 1);
	vertex_indices.push_back(atoi(yindices[0]) - 1);
	vertex_indices.push_back(atoi(zindices[0]) - 1);

	if (xindices[1]) //check if there is something after vertex indices
	{
		printf("push normal indices\n");
		int index = 2;
		if (!xindices[2]) //if v//vn
			index = 1;
		normal_indices.push_back(atoi(xindices[index]) - 1);
		normal_indices.push_back(atoi(yindices[index]) - 1);
		normal_indices.push_back(atoi(zindices[index]) - 1);
	}
	if (explode[4])
	{
		printf("the answer to why explode 4 is possible\n");
		char **windices = ft_strsplit(explode[4], '/');

		vertex_indices.push_back(atoi(xindices[0]) - 1);
		vertex_indices.push_back(atoi(zindices[0]) - 1);
		vertex_indices.push_back(atoi(windices[0]) - 1);

		if (xindices[1]) //check if there is 2
		{
			int index = 2;
			if (!xindices[2]) //if v//vn
				index = 1;
			// normals may be written into indices[1] if the texture indices are missing
			normal_indices.push_back(atoi(xindices[index]) - 1);
			normal_indices.push_back(atoi(zindices[index]) - 1);
			normal_indices.push_back(atoi(windices[index]) - 1);
		}
		free_double_pointer(windices);
	}
	free_double_pointer(xindices);	
	free_double_pointer(yindices);	
	free_double_pointer(zindices);
	printf("DONE LOADING INDICES\n");
}

void	Model::loadData(char *path)
{
	std::fstream myfile(path);
		if (getFile(myfile) == 0)
			return ;

	char **explode;
	std::string line;
	while (getline(myfile, line))
	{
		if (line[0] == 'v' || line[0] == 'f')
		{
			explode = ft_strsplit(line.c_str(), ' ');
//this will load colors to normals from loadVertices
			if (strcmp(explode[0], "vn") == 0)
				loadVectors(normals, explode);
			if (strcmp(explode[0], "v") == 0)
				loadVectors(vertices, explode);
			else if (strcmp(explode[0], "f") == 0)
				loadIndices(explode, vertex_indices, normal_indices);
			free_double_pointer(explode);
		}
	}

//	normals will be pushed to the end of the vertices vector
//	vector[offset_to_normals + 0] is the x coordinate of the first normal
	offset_to_normals = vertices.size();
	printf("pushing back normals\n");

//	Will create normals if normals.size() == 0
	pushBackNormals();

	printf("file read\n");
}

void	Model::initBuffers()
{

	unsigned int EBO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO); // generates 1 buffer, which we can reference throug VBO
	glGenBuffers(1, &EBO);
//put in the midddle
   glBindVertexArray(VAO);
//

//	binds buffer to a type. GL_ARRAY_BUFFER - buffer type of the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // after this each time we call GL_ARRAY_BUFFER, VBO will be called
//	this function loads vertices into VBO. (it knows it's vbo, because it is bound to the GL_ARRAY
//	_BUFFER. GL_STATIC_DRAW is specified for optimization. could be DYNAMIC (data changes), could be STREAM (data is used not a lot)
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	if (vertex_indices.size())
	{
		printf("Drawing according to indices\n");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vertex_indices.size(), &vertex_indices[0], GL_STATIC_DRAW);
	}



		//because vec3			//how many bytes in a line/line = 1 vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0); // 0 = location of the vertex attribute

// color  //how much does location = 1 take space in a line			  //offset for the second location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1); // 1 = location of the vertex attribute

//	add normals for this
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(offset_to_normals * sizeof(float)));
	glEnableVertexAttribArray(2);

	printf("Buffers enabled\n");
}


void	Model::draw()
{
	if ((numberoffloats = vertex_indices.size()))
		glDrawElements(GL_TRIANGLES, round(numberoffloats), GL_UNSIGNED_INT, 0);
	else
	{
		numberoffloats = vertices.size();
		glDrawArrays(GL_TRIANGLES, 0, round(numberoffloats));
	}
}

class	Shader
{
	public:
		Shader(std::vector<const char *>shaders/*, const char *fragment*/);

		char *vertexShader;
		char *fragmentShader;

		unsigned int ID;
};

unsigned int	compileShader(const unsigned int &type, const char* &source)
{
	unsigned int thisShader;
	thisShader = glCreateShader(type); //no, don't send reference here :( no glBindBuffer
							// GL_VERTEX_SAHDER is a new argument;

	// atach shader source to the shader object so we can pass only object to compiler
				  //1 string			   //ignore
	glShaderSource(thisShader, 1, &source, NULL); // atach
	glCompileShader(thisShader);
	


//check for errors during compilation
	int  success;
	char infoLog[512];
	glGetShaderiv(thisShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(thisShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::";

		if (type == GL_VERTEX_SHADER)
			std::cout << "VERTEX";
		else if (type == GL_FRAGMENT_SHADER)
			std::cout << "FRAGMENT";
		else if (type == GL_GEOMETRY_SHADER)
			std::cout << "GEOMETRY";
		else
			std::cout << "UNKNOWN_TYPE";

		std::cout << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return (thisShader);
}


Shader::Shader(std::vector<const char *>shaders/*const char *vertex, const char *fragment*/)
{
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, shaders[0]);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaders[1]);

	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);


	unsigned int geometryShader; //for visibility to delete
	if (shaders.size() == 3)
	{
		geometryShader = compileShader(GL_GEOMETRY_SHADER, shaders[2]);
		glAttachShader(ID, geometryShader);
	}
//use map here later for assigning 0 to vShader 1 to fShader 2 to gShader in a cycle

	glLinkProgram(ID);

//was defined previously in shaders
	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
///////////////////////////////////////////////////////////////////////////////

	glUseProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (shaders.size() == 3)
		glDeleteShader(geometryShader);
}

class	OpenGL
{
public:
	OpenGL() {
//		GLFW is a library that manages operation system specific tasks, that OpenGL
//		abstracts itself from. GLFW implements the specifications of OpenGL. It allows
//		us to create window context, manage user input, define window parameters.

//		this causes a leak
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
//		must do in mac, othrwise window == NULL
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//		glfwWindowHints configure the options that we specify. major version = 3, minor version = 3,
//		Profile = core. Unlike Immediate mode, core profile is harder to use but allows for more flexibility
//		Immediate mode hides functionality behind curtains
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	

//		this function returns window object. inside this object
//		will be all the windowing data. it will be used by other functions
		width = height = 700;
		window = glfwCreateWindow(width, height, "Learn OpenGL", NULL, NULL);
	
		if (window == NULL)
		{
			glfwTerminate();
			throw "Couldn't open window";
		}

//		without this glad fails
		glfwMakeContextCurrent(window);

//		GLAD is a library that loads implementations of OpenGL
//		functions written by graphics card manufacturers.
//		Otherwise it would be hard to do by myself
//		Glad should be initialized before calling any OpenGL function
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw "GLAD failed";
		}
		glEnable(GL_DEPTH_TEST);

//		this transforms 0,5 , 0.5 to 300, 300 behind the scenes
		glViewport(0, 0, width, height);

//		this function is called every time the window is resized.
//		we have to implement the framebuffer_size_callback func.
//		must be after glfwInint() and before render loop
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetKeyCallback(window, key_callback);	

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	GLFWwindow *window;
	int width;
	int height;
};

class	Camera
{
public:
	Camera(){};
	vec4 pos{0, 4, 15, 0};
	vec4 basex{0.2, 0, 0, 0};
	vec4 basez{0, 0, -0.2, 0};

	mat4	yRotate{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
		};

	mat4	xRotate{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
		};
};

Camera cam;
mat4 matrix;

int	main(int argc, char **argv)
{
	if (argc == 1) {
		printf("Need input\n");
		return (0);
	}


	OpenGL	opengl;
	Model	myModel;

	myModel.loadData(argv[1]);
	myModel.initBuffers();
	myModel.initConections();
//#if 0
	std::vector<const char *>shaders{vertexShaderSource, fragmentShaderSource/*, geometryShaderSource1*/};

//#endif


//	This will draw normals. To use this also uncomment uniform variables and glUseProgram in 
//	loop
/*
	std::vector<const char *>normalShaders{vertexShaderSourceNormal, fragmentShaderSourceNormal, geometryShaderSourceNormal};
	Shader normalShader(normalShaders);
*/


	Shader myShader(shaders);
	printf("shaders compiled\n");

	mat4 translate;


	translate[3] = -cam.pos[0];
	translate[7] = -cam.pos[1];
	translate[11] = -cam.pos[2];

	mat4 b =  cam.xRotate * cam.yRotate;
	mat4 c = projectionMatrix * b * translate;  

	matrix = c;


	while (!glfwWindowShouldClose(opengl.window))
	{

////////////////////////////////////////////////
		// only after init conections
		// will draw wave model
		myModel.updateVertices();
/////////////////////////////////////////////////////////////
		processInput(opengl.window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//start setting up uniform variable

		int campos = glGetUniformLocation(myShader.ID, "p");
		glUniform4f(campos, cam.pos[0], cam.pos[1], cam.pos[2], cam.pos[3]);


		int wholematrix = glGetUniformLocation(myShader.ID, "matrix");
		glUniformMatrix4fv(wholematrix, 1, GL_TRUE, matrix);


		glUseProgram(myShader.ID);
		// this draws according to indices, or 1 after 1, depending on indices.size()
		myModel.draw();

/*		glUniform4f(campos, cam.pos[0], cam.pos[1], cam.pos[2], cam.pos[3]);
		glUniformMatrix4fv(wholematrix, 1, GL_TRUE, matrix);

		glUseProgram(normalShader.ID);
		myModel.draw();
*/
		glfwSwapBuffers(opengl.window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &myModel.VAO);
	glDeleteBuffers(1, &myModel.VBO);

	system("leaks -q a.out");

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------

	glfwTerminate();
}


void	processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);		
	//returns GLFW_RELEASE otherwise
}

void	framebuffer_size_callback(GLFWwindow *window, int w, int h)
{
	glViewport(0, 0, w, h);
}
void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//	printf("action is %d\n", action);

	if (action == 0)
		return;

	mat4 invertedx = cam.xRotate.invert();
	mat4 invertedy = cam.yRotate.invert();


	vec4 difx = invertedy * (invertedx * cam.basex);
	vec4 difz = invertedy * (invertedx * cam.basez);

	if (GLFW_KEY_W == key)
	{
		cam.pos = cam.pos + difz;
	}
	else if (GLFW_KEY_S == key)
	{
		cam.pos = cam.pos - difz;
	}
	else if (GLFW_KEY_A == key)
	{
		cam.pos = cam.pos - difx;
	}
	else if (GLFW_KEY_D == key)
	{
		cam.pos = cam.pos + difx;
	}
	if (numberoffloats < 6319 * 3) {
	if (GLFW_KEY_R == key)
	{
		printf("number of floats is %d\n", numberoffloats);
		numberoffloats++;
	}
	else if (GLFW_KEY_T == key)
	{
		numberoffloats--;
	}
					}



	else
		std::cout << "unknown key" << std::endl;
//	printf("cam.pos is %f, %f, %f, %f\n", cam.pos[0], cam.pos[1], cam.pos[2], cam.pos[3]);
//	printf("normal is %f, %f, %f, %f\n", difz[0], difz[1], difz[2], difz[3]);
////////////////////////////////////
	mat4 translate;


	translate[3] = -cam.pos[0];
	translate[7] = -cam.pos[1];
	translate[11] = -cam.pos[2];



	mat4 b =  cam.xRotate * cam.yRotate;
	mat4 c = projectionMatrix * b * translate;  

	matrix = c;


}


void cursor_position_callback(GLFWwindow* window, double x, double y)
{
//	printf("x, y is %f, %f\n", x, y);

	x -= 300;
	y -= 600;

	x = x / (float)100;
	y = y / (float)100;
//	printf("after translate is %f, %f\n", x, y);

	//	for debugging


	mat4 invertedx = cam.xRotate.invert();
	mat4 invertedy = cam.yRotate.invert();


	vec4 difx = invertedy * (invertedx * cam.basex);
	vec4 difz = invertedy * (invertedx * cam.basez);



	printf("difz is %f, %f, %f\n", difz[0], difz[1], difz[2]);


//

//y rotation

	cam.yRotate[0] = cos(x);
	cam.yRotate[2] = sin(x);
	cam.yRotate[8] = -sin(x);
	cam.yRotate[10] = cos(x);

// x rotation


	cam.xRotate[5] = cos(y);
	cam.xRotate[6] = -sin(y);
	cam.xRotate[9] = sin(y);
	cam.xRotate[10] = cos(y);
/////////////////////////////////////
	mat4 translate;


	translate[3] = -cam.pos[0];
	translate[7] = -cam.pos[1];
	translate[11] = -cam.pos[2];



	mat4 b =  cam.xRotate * cam.yRotate;
	mat4 c = projectionMatrix * b * translate;  

	matrix = c;
}


//shaders are programs run by the gpu at each step of the graphics pipeline
//there are default shaders and custom developer shaders
//custom shaders can be written for: *vertex shader* -> *geometry shader* -> *fragment shader*

