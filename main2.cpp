
#include <glad/glad.h>
//GLAD should be included before GLFW
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
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
			"uniform mat4 cR;\n"

			"uniform vec4 p;\n"

//for geomShader

"out VS_OUT {\n" 
"   vec4 normalEnd;\n"
"} vs_out;\n"

"vec3 norm(vec3 v)\n"
"{\n"
	"vec3 ret = v;\n"
	"ret = ret / sqrt(dot(v, v));\n"
	"return (ret);\n"
"}\n"

//need to get address from render loop
//			"uniform float f;\n"

			"void main()\n"
			"{\n"
//				"vec3 lightPos = vec3(20, 20, 20);\n"
//				"aPos = aPos + aNormal;\n"

				"gl_Position =  P * (xRotate * yRotate * (vec4(aPos, 1) - p));\n"

  //  "mat3 normalMatrix = mat3(transpose(inverse(view * model)));\n"
//    "vs_out.normal = normalize(vec3(projection * vec4(normalMatrix * aNormal, 0.0)));\n"


				"vs_out.normalEnd =  P * (xRotate * yRotate * (vec4(aPos + aNormal * 0.4, 1) - p))\n;"

//				"vs_out.normal =  vec3(P * (xRotate * yRotate * (vec4(aNormal.x, aNormal.y, aNormal.z, 1) - p)));\n"



//geomShader
	/*


				"vec3 lightPos = vec3(p.x, p.y, p.z);\n"


				"vec3 hitli = lightPos - aPos;\n"
				"hitli = hitli / sqrt(hitli * hitli);\n"



				"float brightness = dot(aNormal, hitli);\n"
				"if (brightness >= 0)\n"
					"outColor = (brightness) * color;\n"


				"if (brightness < 0)\n"
					"outColor = vec3(1, 0, 0);\n" // red
				"if (aNormal == vec3(0, 0, 0))\n"
					"outColor = vec3(0, 1, 0);\n" // green
				"if (brightness > 1)\n"
					"outColor = vec3(0, 0, 1);\n" // blue

*/


//				"vec3 lightPos = vec3(p.x, p.y, p.z);\n"

				"vec3 lightPos = vec3(100, 100, 100);\n"


				"vec3 hitli = lightPos - aPos;\n"
				"hitli = norm(hitli);\n"
				"float brightness = dot(aNormal, hitli);\n"	
				"if (brightness < 0.3)\n"
					"brightness = 0.3;\n"
//				"if (brightness < 0)\n"
//					"brightness = dot(aNormal, -hitli);\n;"

				"outColor = vec3(0.5, 0.5, 1) * brightness;\n"


				"vec3 hitcam = norm(vec3(p) - aPos);\n"
				"vec3 newNormal = dot(hitcam, aNormal) * aNormal;\n"
				"vec3 reflray = newNormal + (newNormal - hitcam);\n"

				"hitli = norm(hitli);\n"

				"if (dot(hitli, hitli) > 1.1)\n"
				"{\n"
					"outColor = vec3(1, 0, 1);\n"
					"return ;\n"
				"}\n"


				"reflray = norm(reflray);\n"
				"float coef = dot(reflray, hitli);\n"

				"if (coef > 1 || coef < -1)\n"
				"{\n"
					"outColor = vec3(1, 0, 0);\n"
					"return ;\n"
				"}\n"


				"if (coef < 0)\n"
				"{\n"
			//		"outColor = vec3(0, 1, 0);\n"
					"return ;\n"
				"}\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
/*				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"

*/

				"outColor = (1 -coef) * outColor + (coef )* vec3(1, 1, 1);\n"


			"}\0";





///////////////////////////////////////////////////////////////////////////
//to enable geometry shader comment outColor = color in vertex shader and change
//custom color to 1 1 1 1 color in fragment shader

const char *geometryShaderSource = 
"#version 330 core\n"
"layout (triangles) in;\n"
"layout (line_strip, max_vertices = 6) out;\n"

"in VS_OUT {\n"
"    vec4 normalEnd;\n"
"} gs_in[];\n"

//"const float MAGNITUDE = 0.004;\n"

"void GenerateLine(int index)\n"
"{\n"
"    gl_Position = gl_in[index].gl_Position;\n"
"    EmitVertex();\n"
//"    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE;\n"
"    gl_Position = vec4(gs_in[index].normalEnd);\n"


"    EmitVertex();\n"
"    EndPrimitive();\n"
"}\n"

"void main()\n"
"{\n"
"    GenerateLine(0);\n"  
"    GenerateLine(1);\n"
"    GenerateLine(2);\n"
"}\0";



//////////////////////////////////////////////////////////////////////
//Fragment shader:
	const char *fragmentShaderSource =
				"#version 330 core\n"
				"out vec4 FragColor;\n" // has to have out vec4 type as output (but vec3 works too?)

//geomShader
				"in vec3 outColor;\n"
				"in vec3 aPos;\n"
				"void main()\n"
				"{\n"
//geomShader

/*

				"vec3 hitcam = norm(vec3(p) - aPos);\n"
				"vec3 newNormal = dot(hitcam, aNormal) * aNormal;\n"
				"vec3 reflray = newNormal + (newNormal - hitcam);\n"

				"hitli = norm(hitli);\n"
				"reflray = norm(reflray);\n"
				"float coef = dot(reflray, hitli);\n"
				"if (coef < 0)\n"
				"{\n"
					"outColor = vec3(0, 1, 0);\n"
					"return ;\n"
				"}\n"
				"if (coef > 2.5 || coef < -2.5)\n"
				"{\n"
					"outColor = vec3(1, 0, 0);\n"
					"return ;\n"
				"}\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"
				"coef = coef * coef;\n"



				"outColor = (coef) * outColor + (1 - coef )* vec3(1, 1, 1);\n"

*/


					"FragColor = vec4(outColor, 1);\n"
//					"FragColor = vec4(1, 1, 1, 1);\n"


				"}\0";



class	vec4
{
	public:
		vec4() {}
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
		float array[16];
		vec4 operator*(vec4 &rhs)
		{
			vec4 ret(
				array[0] * rhs[0] + array[1] * rhs[1] + array[2] * rhs[2] + array[3] * rhs[3],
				array[4] * rhs[0] + array[5] * rhs[1] + array[6] * rhs[2] + array[7] * rhs[3],
				array[8] * rhs[0] + array[9] * rhs[1] + array[10] * rhs[2] + array[11] * rhs[3],
				array[12] * rhs[0] + array[13] * rhs[1] + array[14] * rhs[2] + array[15] * rhs[3]
				);
			return (ret);
		}
		mat4 invert() {mat4 ret(*this); ret[2] = -ret[2]; ret[8] = -ret[8]; ret[6] = -ret[6]; ret[9] = -ret[9]; return ret;}
		float &operator[] (int index) { return array[index]; }
		operator float *() {return array;};
};		


int numberoffloats = 0;



int anglex = 0;
int angley = 0;

vec4 campos(
0, 0, 30, 0
);

vec4 cambasex(
0.2, 0, 0, 0
);

vec4 cambasez(
0, 0, -0.2, 0
);

float	n = 0.20f;
float	f = 400.0f;
float	h = 0.10f;

float	projectionMatrix[] = {
n / h, 0.0f, 0.0f, 0.0f,
0.0f, n / h, 0.0f, 0.0f,
0.0f, 0.0f, -(f + n) / (f - n), -2 * f * n / (f - n),
0.0f, 0.0f, -1.0f, 0.0f  //positive z dir is outwards when = 1
			};


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


		std::vector<unsigned int>vertex_indices;
		std::vector<float>vertices;
		std::vector<float>normals;
		std::vector<unsigned int>normal_indices;


		unsigned int offset_to_normals;

	
};

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

/*
	indices.push_back(atoi(explode[1]) - 1);
	indices.push_back(atoi(explode[2]) - 1);
	indices.push_back(atoi(explode[3]) - 1);
	if (explode[4])
	{
		indices.push_back(atoi(explode[1]) - 1);
		indices.push_back(atoi(explode[3]) - 1);
		indices.push_back(atoi(explode[4]) - 1);
	}
*/

	vertex_indices.push_back(atoi(xindices[0]) - 1);
	vertex_indices.push_back(atoi(yindices[0]) - 1);
	vertex_indices.push_back(atoi(zindices[0]) - 1);

	if (xindices[1] && xindices[2]) //check if there is 2 / /
	{
		normal_indices.push_back(atoi(xindices[2]) - 1);
		normal_indices.push_back(atoi(yindices[2]) - 1);
		normal_indices.push_back(atoi(zindices[2]) - 1);
	}

	if (explode[4])
	{
		char **windices = ft_strsplit(explode[4], '/');

		vertex_indices.push_back(atoi(xindices[0]) - 1);
		vertex_indices.push_back(atoi(zindices[0]) - 1);
		vertex_indices.push_back(atoi(windices[0]) - 1);

		if (xindices[1] && xindices[2]) //check if there is 2 / /
		{
			normal_indices.push_back(atoi(xindices[2]) - 1);
			normal_indices.push_back(atoi(zindices[2]) - 1);
			normal_indices.push_back(atoi(windices[2]) - 1);
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
			if (strcmp(explode[0], "vn") == 0)
				loadVectors(normals, explode);
			if (strcmp(explode[0], "v") == 0)
				loadVectors(vertices, explode);
			else if (strcmp(explode[0], "f") == 0)
				loadIndices(explode, vertex_indices, normal_indices);
			free_double_pointer(explode);
		}
	}
	offset_to_normals = vertices.size() * sizeof(float);
	pushBackNormals();
	printf("file read\n");
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
				  //1 string               //ignore
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


int	main(int argc, char **argv)
{
	srand(0);
//	GLFW is a library that manages operation-//system specific tasks, that OpenGL
//	abstracts itself from. GLFW implements the specifications of OpenGL. It allows
//	us to create window context, manage user input, define window parameters.

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
//must do in mac, othrwise window == NULL
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	Model myModel;

	if (argc == 2)
		myModel.loadData(argv[1]);

//	printOpbject(myModel);


/*
	glfwWindowHints configure the options that we specify. major version = 3, minor version = 3,
	Profile = core. Unlike Immediate mode, core profile is harder to use but allows for more flexibility
	Immediate mode hides functionality behind curtains
*/
	GLFWwindow *window = glfwCreateWindow(600, 600, "Learn OpenGL", NULL, NULL);


//	this function returns window object. inside this object will be all the
//	windowing data. it will be used by other functions

	if (window == NULL)
	{
		std::cout << "Couldn't open window" << std::endl;
		glfwTerminate();
		return (-1);
	}

//	without this glad fails
	glfwMakeContextCurrent(window);


//	GLAD is a library that loads implementations of OpenGL functions written by graphics card manufacturers
//	otherwise it would be hard to do by myself
//	Glad should be initialized before calling any OpenGL
//	function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD FAILED\n" << std::endl;
		return (-1);
	}
	// glViewport tells OpenGL the size of the rendering window
//	this transforms 0,5 , 0.5 to 300, 300 behind the scenes
	    glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 600, 600);


//	this function is called every time the window is resize.
//	we have to implement the framebuffer_size_callback func.
//	must be after glfwInint() and before render loop

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetKeyCallback(window, key_callback);


//	coordinates will be transformed via data in glViewport() later, to screen coordinates


//	these coordinates will be bound(?) with the buffre object, which will be sent to the GPU.
//	after that, the GPU will have almost instant acces to the data "in" the buffer

//comment to make global
/*
	float	vertices[] = {
	-0.5f, -0.5f, 0,
	0.5f, -0.5f, 0,
	0, 0.5, 0
			};
*/


	unsigned int VBO, VAO, EBO;

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
	glBufferData(GL_ARRAY_BUFFER, /*sizeof(vertices), */myModel.vertices.size() * sizeof(float), &myModel.vertices[0] /*vertices*/, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	glBufferData(GL_ELEMENT_ARRAY_BUFFER, /*sizeof(indices)*/sizeof(unsigned int) * myModel.vertex_indices.size(), &myModel.vertex_indices[0] /*indices*/, GL_STATIC_DRAW);


			//because vec3			//how many bytes in a line/line = 1 vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0); // 0 = location of the vertex attribute

// color  //how much does location = 1 take space in a line	          //offset for the second location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1); // 1 = location of the vertex attribute

//add normals for this

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)/*(48 * sizeof(float)) */(myModel.offset_to_normals));
	glEnableVertexAttribArray(2);

	std::vector<const char *>shaders{vertexShaderSource, fragmentShaderSource/*, geometryShaderSource*/};
	Shader myShader(shaders);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.

    glBindVertexArray(0); 	//unbinds VAO. comment this if you want to tomment glBindVertexArray in llop
//end


//		int newVertexLocation = glGetUniformLocation(shaderProgram, "f");
//		glUseProgram(shaderProgram);


	//render loop
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f); state setting function
//		glClear(GL_COLOR_BUFFER_BIT); //state using function
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//start setting up uniform variable

		int newVertexLocation = glGetUniformLocation(myShader.ID, "yRotate");
		glUniformMatrix4fv(newVertexLocation, 1, GL_TRUE, yRotate);

		int newVertexLocation2 = glGetUniformLocation(myShader.ID, "xRotate");
		glUniformMatrix4fv(newVertexLocation2, 1, GL_TRUE, xRotate);


		int newVertexLocation1 = glGetUniformLocation(myShader.ID, "P");
		glUniformMatrix4fv(newVertexLocation1, 1, GL_TRUE, projectionMatrix);

		int newVertexLocation5 = glGetUniformLocation(myShader.ID, "p");
		glUniform4f(newVertexLocation5, campos[0], campos[1], campos[2], campos[3]);

		double time = glfwGetTime();

		mat4 constantRotation;

		constantRotation[0] = cos(time * 70/ (float)175);
		constantRotation[2] = sin(time * 70  / (float)175);
		constantRotation[8] = -sin(time * 70 / (float)175);
		constantRotation[10] = cos(time * 70 / (float)175);


		int newVertexLocation6 = glGetUniformLocation(myShader.ID, "cR");
		glUniformMatrix4fv(newVertexLocation6, 1, GL_TRUE, constantRotation);

		glUseProgram(myShader.ID);

//end


//        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


//	       glDrawArrays(GL_TRIANGLES, 0, 43);

//	       glDrawArrays(GL_POINTS, 0, numberoffloats);


	
//for 42
//		glDrawElements(GL_TRIANGLES, 83, GL_UNSIGNED_INT, 0);
//fo teapot


//		glDrawElements(GL_TRIANGLES, 9999, GL_UNSIGNED_INT, 0);

//		if (numberoffloats < myModel.indices.size())
//			numberoffloats += 20 /*6319 * 3*/;

//uncomment for argument model
//		numberoffloats = myModel.vertex_indices.size();
//		printf("here1\n");
		numberoffloats = /*sizeof(indices) / sizeof(indices[0]);*/myModel.vertex_indices.size();

//		printf("here3\n");
		glDrawElements(GL_TRIANGLES, round(numberoffloats) /*6319* 3*//* * 3 * 1*/, GL_UNSIGNED_INT, 0);
//		printf("here2\n");

		//put image to window
		//prevents flickering
		glfwSwapBuffers(window);
		//checks for input
		//updates the window state
		//corresponding to the input
		//and the defined behaviour
		//after such input
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

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

float	yaw = 0, pitch = 0;


vec4		rotate(vec4 ray, vec4 angle)
{
	vec4 ret;
	vec4 cxcycz;
	vec4 sxsysz;
	vec4 opt;
	vec4 row[3];

	if (angle[0] == 0 && angle[1] == 0 && angle[2] == 0)
		return (ray);
	cxcycz = vec4(cos(angle[0]), cos(angle[1]), cos(angle[2]), 0);

	sxsysz = vec4(sin(angle[0]), sin(angle[1]), sin(angle[2]), 0);

	opt = vec4(cxcycz[2] * sxsysz[0],
	cxcycz[2] * cxcycz[0], sxsysz[2] * sxsysz[1], 0);

	row[0] = vec4(cxcycz[2] * cxcycz[1],  -sxsysz[2] * cxcycz[0]
	+ opt[0] * sxsysz[1], sxsysz[2] * sxsysz[0] + opt[1] * sxsysz[1], 0);

	row[1] = vec4(sxsysz[2] * cxcycz[1], opt[1]
	+ opt[2] * sxsysz[0], -opt[0] + opt[2] * cxcycz[0], 0);

	row[2] = vec4(-sxsysz[1], cxcycz[1] * sxsysz[0], cxcycz[1] * cxcycz[0], 0);

	ret = vec4(row[0] * ray, row[1] * ray, row[2] * ray, 0);

	return (ret);
}


void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//	printf("action is %d\n", action);

	if (action == 0)
		return;
/*
	mat4 invertedy = yRotate.invert();
	vec4 difx = invertedy * cambasex;
	vec4 difz = invertedy * cambasez;


//this changes in the standart coordinates. should
//change in the new coordinates

	mat4 invertedx = xRotate.invert();

	difx = invertedx * difx;
	difz = invertedx * difz;

*/



	mat4 invertedx = xRotate.invert();

	vec4 difx = invertedx * cambasex;
	vec4 difz = invertedx * cambasez;


	mat4 invertedy = yRotate.invert();
	difx = invertedy * difx;
	difz = invertedy * difz;




//	vec4 difz(sin(yaw) * cos(pitch), sin(pitch), -cos(yaw) * cos(pitch), 0);
//	vec4 difz(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch), 0);

//	vec4 difx = rotate(cambasex, vec4(yaw, pitch, 0, 0));

//	vec4 difz = rotate(cambasez, vec4(yaw, pitch, 0, 0));

	if (GLFW_KEY_W == key)
	{
//		translate[3] += 0.1;
//		translate[7] += 0.1;


//		normal += xRotate * temp;
//		normal = normal + temp;
		campos = campos + difz;
	}
	else if (GLFW_KEY_S == key)
	{
		campos = campos - difz;
	}
	else if (GLFW_KEY_A == key)
	{
		campos = campos - difx;
	}
	else if (GLFW_KEY_D == key)
	{
		campos = campos + difx;
	}
	else if (GLFW_KEY_UP == key)
	{
		anglex += 2;
		xRotate[5] = cos(anglex / (float)175);
		xRotate[6] = sin(anglex / (float)175);
		xRotate[9] = -sin(anglex / (float)175);
		xRotate[10] = cos(anglex / (float)175);
	
	}
	else if (GLFW_KEY_DOWN == key)
	{
		anglex -= 2;
		xRotate[5] = cos(anglex / (float)175);
		xRotate[6] = sin(anglex / (float)175);
		xRotate[9] = -sin(anglex / (float)175);
		xRotate[10] = cos(anglex / (float)175);
	}
	else if (GLFW_KEY_LEFT == key)
	{
		angley--;
		yRotate[0] = cos(-angley / (float)175);
		yRotate[2] = sin(-angley / (float)175);
		yRotate[8] = -sin(-angley / (float)175);
		yRotate[10] = cos(-angley / (float)175);
	}

	else if (GLFW_KEY_RIGHT == key)
	{
		angley++;
		yRotate[0] = -cos(angley / (float)175);
		yRotate[2] = -sin(angley / (float)175);
		yRotate[8] = -sin(angley / (float)175);
		yRotate[10] = cos(angley / (float)175);
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
//	printf("campos is %f, %f, %f, %f\n", campos[0], campos[1], campos[2], campos[3]);
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

	yaw = y;
	pitch = x;

//	for debugging


	mat4 invertedx = xRotate.invert();

	vec4 difx = invertedx * cambasex;
	vec4 difz = invertedx * cambasez;


	mat4 invertedy = yRotate.invert();
	difx = invertedy * difx;
	difz = invertedy * difz;



	printf("difz is %f, %f, %f\n", difz[0], difz[1], difz[2]);


//

//y rotation

	yRotate[0] = cos(x);
	yRotate[2] = sin(x);
	yRotate[8] = -sin(x);
	yRotate[10] = cos(x);

// x rotation


	xRotate[5] = cos(y);
	xRotate[6] = -sin(y);
	xRotate[9] = sin(y);
	xRotate[10] = cos(y);
}


//shaders are programs run by the gpu at each step of the graphics pipeline
//there are default shaders and custom developer shaders
//custom shaders can be written for: *vertex shader* -> *geometry shader* -> *fragment shader*

