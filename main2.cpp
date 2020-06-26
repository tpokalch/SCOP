
#include <glad/glad.h>
//GLAD should be included before GLFW
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>

/*
float vertices[] = {
-5, -5, 5, 1, 0, 0, //0, 1, 0,
5, -5, 5, 1, 0, 0, //0, 1, 0,
5, 5, 5, 1, 0, 0, //0, 1, 0,
-5, 5, 5, 1, 0, 0, //0, 1, 0,

-5, -5, -5, 0, 0, 1, //1, 0, 0,
5, -5, -5, 0, 0, 1, //1, 0, 0,
5, 5, -5, 0, 0, 1, //1, 0, 0,
-5, 5, -5, 0, 0, 1, //1, 0, 0

//,
0, 1, 0,
0, 1, 0,
0, 1, 0,
0, 1, 0,

1, 0, 0,
1, 0, 0,
1, 0, 0, 
1, 0, 0

};

unsigned int indices[] = {

0, 1, 2,
2, 3, 0,

0, 1, 4,
1, 4, 5,

1, 2, 5,
2, 5, 6,

0, 4, 3,
4, 3, 7,

4, 5, 6,
6, 7, 4,

3, 6, 7,
6, 3, 2

};
*/

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
			"uniform mat4 P;\n"
			"uniform mat4 xRotate;\n"
			"uniform mat4 yRotate;\n"
			"uniform mat4 Rotate;\n"	
			"uniform mat4 cR;\n"
			"uniform mat4 translate;\n"
			"uniform mat4 matrix;\n"
			"uniform vec4 p;\n"

//for geomShader1


"out VS_OUT {\n" 
"	mat4 matrix;\n"
"} vs_out;\n"


//for other geom shader
/*
"out VS_OUT {\n" 
"	vec4 normalEnd;\n"
"} vs_out;\n"
*/


//need to get address from render loop
//			"uniform float f;\n"

			"void main()\n"
			"{\n"
				"gl_Position =  (vec4(aPos, 1));\n"
				"vs_out.matrix = matrix;\n"
				//if straight to fragment shader
				"outColor = vec3(1, 1, 1);\n"
//				"gl_Position = matrix * gl_Position;\n"
				/////////////
//				"vs_out.normalEnd =  matrix * (vec4(aPos + aNormal * 0.4, 1))\n;"

//				"vs_out.light = matrix * (vec4(100, 100, 100, 1));\n"

#if 0
				"vec3 lightPos = vec3(100, 100, 100);\n"
				"vec3 hitli = lightPos - aPos;\n"
				"hitli = normalize(hitli);\n"
				"float brightness = max(0.3, dot(aNormal, hitli));\n"
				"outColor = vec3(0, 0.5, 1) * brightness;\n"


				"vec3 hitcam = normalize(vec3(p) - aPos);\n"
				"vec3 newNormal = dot(hitcam, aNormal) * aNormal;\n"
				"vec3 reflray = newNormal + (newNormal - hitcam);\n"

				"hitli = normalize(hitli);\n"

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
				"coef = coef * coef;\n"
				"outColor = (1 -coef) * outColor + (coef )* vec3(1, 1, 1);\n"
#endif
			"}\0";





///////////////////////////////////////////////////////////////////////////
//to enable geometry shader comment outColor = color in vertex shader and change
//custom color to 1 1 1 1 color in fragment shader
//also compile this shader with the sahder program
//	this shader will draw normals!!!

/*
const char *geometryShaderSource1 = 
"#version 330 core\n"
"layout (triangles) in;\n"
"layout (line_strip, max_vertices = 6) out;\n"
"out vec3 outColor;\n"

"in VS_OUT {\n"
"	vec4 normalEnd;\n"
"} gs_in[];\n"

//"const float MAGNITUDE = 0.004;\n"

"void GenerateLine(int index)\n"
"{\n"
"	gl_Position = gl_in[index].gl_Position;\n"
"	outColor = vec3(1, 1, 1);\n"//need to specify color for every vertex 
"	EmitVertex();\n"

"	gl_Position = vec4(gs_in[index].normalEnd);\n"
"	outColor = vec3(1, 1, 1);\n"//here too
"	EmitVertex();\n"

"	EndPrimitive();\n"
"}\n"

"void main()\n"
"{\n"
"	GenerateLine(0);\n"  
"	GenerateLine(1);\n"
"	GenerateLine(2);\n"
"}\0";
*/
///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//this shader calculates normals. takes vertice's coordinates in global space and the matrix.
const char *geometryShaderSource1 = 
"#version 330 core\n"
"layout (triangles) in;\n"
"layout (triangle_strip, max_vertices = 3) out;\n"
"out vec3 outColor;\n"

"in VS_OUT {\n"
"	mat4 matrix;\n"
"} gs_in[];\n"


"void GenerateLine(int index, vec3 normal)\n"
"{\n"
"	vec3 hitli = normalize(vec3(100, 100, 100) - vec3(gl_in[index].gl_Position));\n"
"	float bri = max(abs(dot(hitli, normal)), 0.3);\n"
"	outColor = vec3(1, 1, 1) * bri;\n"
"	gl_Position = gs_in[index].matrix * gl_in[index].gl_Position;\n"
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



//////////////////////////////////////////////////////////////////////
//Fragment shader:
	const char *fragmentShaderSource =
				"#version 330 core\n"
				"out vec4 FragColor;\n" // has to have out vec4 type as output (but vec3 works too?)

//geomShader
//				"in vec3 normal;\n" //from geom shader
				"in vec3 outColor;\n"
				"void main()\n"
				"{\n"
					"FragColor = vec4(outColor, 1);\n"
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


};


void	Model::initConections()
{
	conections.resize(lround(vertices.size() / 3));
	forces.resize(lround(vertices.size() / 3));
	speeds.resize(lround(vertices.size() / 3));
	original_vertices = vertices;
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
		printf("\n%d vertex is %f, %f, %f", i, vertices[3 * i + 0], vertices[3 * i + 1], vertices[3 * i + 2]);
	}
	printf("size of vertices %lu\n", vertices.size());
	printf("size of indices %lu\n",vertex_indices.size());
	printf("size of conections %lu\n",conections.size());



/////////////////////////		INIT FORCES ORIGINAL
	original_forces.resize(vertices.size() / 3);

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
//	vertices[1200] += 1;
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



		for (int j = 0; j < conectionssize; j++)
		{
		//	printf("i is %d\n", i);
//		printf("index is %d\n", index);
	
			float original_length[3];
			original_length[0] = (original_vertices[3 * conections[i][j] + 0] - original_vertices[3 * i + 0]) * 1;
			original_length[1] = (original_vertices[3 * conections[i][j] + 1] - original_vertices[3 * i + 1]) * 1;
			original_length[2] = (original_vertices[3 * conections[i][j] + 2] - original_vertices[3 * i + 2]) * 1;


			float curent_length[3];
			curent_length[0] = (vertices[3 * conections[i][j] + 0] - vertices[3 * i + 0]);
			curent_length[1] = (vertices[3 * conections[i][j] + 1] - vertices[3 * i + 1]);
			curent_length[2] = (vertices[3 * conections[i][j] + 2] - vertices[3 * i + 2]);


			forces[i][0] +=  -(original_length[0] - curent_length[0]);
			forces[i][1] +=  -(original_length[1] - curent_length[1]);
			forces[i][2] +=  -(original_length[2] - curent_length[2]);

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

		speeds[i][0] += force[0] * 0.1;
		speeds[i][1] += force[1] * 0.1;
		speeds[i][2] += force[2] * 0.1;
//		printf("length of force is %f\n", length_of_force);
//		printf("%d force is %f, %f, %f\n", i, force[0], force[1], force[2]);
//		printf("%d speed is %f, %f, %f\n", i, speeds[i][0], speeds[i][1], speeds[i][2]);


	}

//	return (0);
//	printf("speeds done\n");
	int verticessize = vertices.size() / 3;
	for (int i = 0; i < verticessize; i++)
	{
		//ith vertex is connected to some j, j+1... other vetices
//		int index = vertex_indices[i];	


		vertices[i * 3 + 0] += speeds[i][0] * 0.1;
		vertices[i * 3 + 1] += speeds[i][1] * 0.1;
		vertices[i * 3 + 2] += speeds[i][2] * 0.1;
/*
		vertices[i * 3 + 0] += forces[i][0] * 0.01;
		vertices[i * 3 + 1] += forces[i][1] * 0.01;
		vertices[i * 3 + 2] += forces[i][2] * 0.01;
*/

	}
//	printf("vertices done\n");
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
}


void	Model::pushBackNormals()
{
//	vertices.push_back(normals[normal_indices[0]]);

//#if 0
	int i = 0;
	int j = 0;
	//j is the index of the vertex
	//j ranges from 0th vertex to last vertex

//	int numberOfVertices = vertices.size() / 2;

/*	while (j < vertexSize)
	{
		vertices.push_back(0.3f);
		j++;
	}
*/
	//i is an index of the vertex indices
	printf("vertices count %lu\n", vertices.size() / 6);

	//SEGFULTS HERE IF 12//1 type of faces
	if (normals.size() == 0)
	{
		printf("no model normals\n");
		return ;
	}

	while (i < vertex_indices.size())
	//for every vertex_index search for normal_index which references jth vertex
	{
		//if we found an index, which tells us to draw jth vertex
		
		if (vertex_indices[i] == j)
		{
			vertices.push_back(normals[6 * normal_indices[i]]);
			vertices.push_back(normals[6 * normal_indices[i] + 1]);
			vertices.push_back(normals[6 * normal_indices[i] + 2]);
/*
			vertices.push_back(normals[3 * normal_indices[i]]);
			vertices.push_back(normals[3 * normal_indices[i] + 1]);
			vertices.push_back(normals[3 * normal_indices[i] + 2]);
			*/
//			printf("normal vector is %f,%f,%f\n", normals[3 * normal_indices[i]],  normals[3 * normal_indices[i] + 1], normals[3 * normal_indices[i] + 2]);

/*			printf("lenght2 is %f\n", normals[3 * normal_indices[i]] * 
						normals[3 * normal_indices[i]] + 

						normals[3 * normal_indices[i] + 1] *
 						normals[3 * normal_indices[i] + 1] + 

						normals[3 * normal_indices[i] + 2] * 
						normals[3 * normal_indices[i] + 2]);

*/
			j++;
			i = 0;
			continue;
		}
		//if no i references the jth vertex, then no face references jth vertex, so
		//the connection with the the normal cannot be established. the search ends
		i++;
	}
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
	printf("after explode %s, %s, %s\n", explode[1], explode[2], explode[3]);

	vertices.push_back(atof(explode[1]) * 1);
	vertices.push_back(atof(explode[2]) * 1);
	vertices.push_back(atof(explode[3]) * 1);

	int r = 0,g = 0,b = 0;

	while (r == 0
		&& g == 0
		&& b == 0) //no black points

	{
		r = rand() % 2;
		g = rand() % 2;
		b = rand() % 2;

//		r = g = b = 1;
	}
//uncomment return for colors
	return ;
	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
}

static void	loadIndices(char **explode, std::vector<unsigned int> &vertex_indices, std::vector<unsigned int> &normal_indices)
{
	printf("___________________\n");

	char **xindices = ft_strsplit(explode[1], '/');
	char **yindices = ft_strsplit(explode[2], '/'); 
	char **zindices = ft_strsplit(explode[3], '/');

	printf("push vertex indices\n");
	vertex_indices.push_back(atoi(xindices[0]) - 1);
	vertex_indices.push_back(atoi(yindices[0]) - 1);
	vertex_indices.push_back(atoi(zindices[0]) - 1);

	if (xindices[1] && xindices[2]) //check if there is 2 / /
	{
		printf("push normal indices\n");
/*		normal_indices.push_back(atoi(xindices[2]) - 1);
		normal_indices.push_back(atoi(yindices[2]) - 1);
		normal_indices.push_back(atoi(zindices[2]) - 1);
*/
	}
	if (explode[4])
	{
		char **windices = ft_strsplit(explode[4], '/');

		vertex_indices.push_back(atoi(xindices[0]) - 1);
		vertex_indices.push_back(atoi(zindices[0]) - 1);
		vertex_indices.push_back(atoi(windices[0]) - 1);

		if (xindices[1] && xindices[2]) //check if there is 2 / /
		{
/*			normal_indices.push_back(atoi(xindices[2]) - 1);
			normal_indices.push_back(atoi(zindices[2]) - 1);
			normal_indices.push_back(atoi(windices[2]) - 1);
*/
		}
		free_double_pointer(windices);
	}
	free_double_pointer(xindices);	
	free_double_pointer(yindices);	
	free_double_pointer(zindices);
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
//			if (strcmp(explode[0], "vn") == 0)
//				loadVectors(normals, explode);
			if (strcmp(explode[0], "v") == 0)
				loadVectors(vertices, explode);
			else if (strcmp(explode[0], "f") == 0)
				loadIndices(explode, vertex_indices, normal_indices);
			free_double_pointer(explode);
		}
	}
	offset_to_normals = vertices.size() * sizeof(float);
//NO NORMAS FOR NOW
//	pushBackNormals();
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0); // 0 = location of the vertex attribute
// color  //how much does location = 1 take space in a line			  //offset for the second location


/*	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1); // 1 = location of the vertex attribute

//add normals for this

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)offset_to_normals);
	glEnableVertexAttribArray(2);
*/
	printf("Buffers enabled\n");
}


void	Model::draw()
{
	if (vertex_indices.size())
	{
		numberoffloats = vertex_indices.size(); 
		printf("numberoffloats is %d\n", numberoffloats);
		glDrawElements(GL_TRIANGLES, round(numberoffloats), GL_UNSIGNED_INT, 0);
	}
	else
	{
		numberoffloats = vertices.size();
		glDrawArrays(GL_TRIANGLES, 0, round(numberoffloats));
	}

}




void	printOpbject(Model &myModel)
{
	printf("vertices!\n");
	int i = 0;
	auto iter = myModel.vertices.begin();
	auto end = myModel.vertices.end();

	while (iter != end)
	{
		printf("%f, ", *iter);

		if ((i + 1) % 3 == 0)
			printf("\n");
		iter++;
		i++;
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
		width = height = 600;
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
	std::vector<const char *>shaders{vertexShaderSource, fragmentShaderSource, geometryShaderSource1};
	Shader myShader(shaders);
	printf("shaders compiled\n");
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

		int newVertexLocation = glGetUniformLocation(myShader.ID, "yRotate");
		glUniformMatrix4fv(newVertexLocation, 1, GL_TRUE, cam.yRotate);

		int newVertexLocation2 = glGetUniformLocation(myShader.ID, "xRotate");
		glUniformMatrix4fv(newVertexLocation2, 1, GL_TRUE, cam.xRotate);


		int newVertexLocation1 = glGetUniformLocation(myShader.ID, "P");
		glUniformMatrix4fv(newVertexLocation1, 1, GL_TRUE, projectionMatrix);

		mat4 translate;


		translate[3] = -cam.pos[0];
		translate[7] = -cam.pos[1];
		translate[11] = -cam.pos[2];

		int newVertexLocation6 = glGetUniformLocation(myShader.ID, "translate");
		glUniformMatrix4fv(newVertexLocation6, 1, GL_TRUE, translate);
		mat4 b =  cam.xRotate * cam.yRotate;
		mat4 c = projectionMatrix * b * translate;  

		mat4 matrix = c;

		int newVertexLocation7 = glGetUniformLocation(myShader.ID, "matrix");
		glUniformMatrix4fv(newVertexLocation7, 1, GL_TRUE, matrix);

		int newVertexLocation8 = glGetUniformLocation(myShader.ID, "Rotate");
		glUniformMatrix4fv(newVertexLocation8, 1, GL_TRUE, b);




		int newVertexLocation5 = glGetUniformLocation(myShader.ID, "p");
		glUniform4f(newVertexLocation5, cam.pos[0], cam.pos[1], cam.pos[2], cam.pos[3]);

		glUseProgram(myShader.ID);


		// this draws according to indices, or 1 after 1, depending on indices.size()
		printf("drawing\n");
		myModel.draw();

		glfwSwapBuffers(opengl.window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &myModel.VAO);
	glDeleteBuffers(1, &myModel.VBO);

	if (argc == 2)
//		delete object;
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
}


//shaders are programs run by the gpu at each step of the graphics pipeline
//there are default shaders and custom developer shaders
//custom shaders can be written for: *vertex shader* -> *geometry shader* -> *fragment shader*

