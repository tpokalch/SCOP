
#include <glad/glad.h>
//GLAD should be included before GLFW
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

void	framebuffer_size_callback(GLFWwindow *window, int w, int h);
void	processInput(GLFWwindow *window);
void	cursor_position_callback(GLFWwindow* window, double x, double y);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
char	**ft_strsplit(char const *s, char c);

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


/*
float vertices[] = {
    -5, -5, -5,  0.0f, 0.0f, 1,
     5, -5, -5,  1.0f, 0.0f, 1,
     5,  5, -5,  1.0f, 1.0f, 1,
     5,  5, -5,  1.0f, 1.0f, 1,
    -5,  5, -5,  0.0f, 1.0f, 1,
    -5, -5, -5,  0.0f, 0.0f, 1,


    -5, -5,  5,  0.0f, 0.0f, 1,
     5, -5,  5,  1.0f, 0.0f, 1,
     5,  5,  5,  1.0f, 1.0f, 1,
     5,  5,  5,  1.0f, 1.0f, 1,
    -5,  5,  5,  0.0f, 1.0f, 1,
    -5, -5,  5,  0.0f, 0.0f, 1,

    -5,  5,  5,  1.0f, 0.0f, 1,
    -5,  5, -5,  1.0f, 1.0f, 1,
    -5, -5, -5,  0.0f, 1.0f, 1,
    -5, -5, -5,  0.0f, 1.0f, 1,
    -5, -5,  5,  0.0f, 0.0f, 1,
    -5,  5,  5,  1.0f, 0.0f, 1,

     5,  5,  5,  1.0f, 0.0f, 1,
     5,  5, -5,  1.0f, 1.0f, 1,
     5, -5, -5,  0.0f, 1.0f, 1,
     5, -5, -5,  0.0f, 1.0f, 1,
     5, -5,  5,  0.0f, 0.0f, 1,
     5,  5,  5,  1.0f, 0.0f, 1,

    -5, -5, -5,  0.0f, 1.0f, 1,
     5, -5, -5,  1.0f, 1.0f, 1,
     5, -5,  5,  1.0f, 0.0f, 1,
     5, -5,  5,  1.0f, 0.0f, 1,
    -5, -5,  5,  0.0f, 0.0f, 1,
    -5, -5, -5,  0.0f, 1.0f, 1,

    -5,  5, -5,  0.0f, 1.0f, 1,
     5,  5, -5,  1.0f, 1.0f, 1,
     5,  5,  5,  1.0f, 0.0f, 1,
     5,  5,  5,  1.0f, 0.0f, 1,
    -5,  5,  5,  0.0f, 0.0f, 1,
    -5,  5, -5,  0.0f, 1.0f, 1
};
*/


/*
float	vertices[] = {
-5.00f, -5.00f, 1090/(float)111,       1, 0, 0,
5.00f, -5.00f,  1090/(float)111,       0, 1, 0,
-5.00f, 5.00f,    1090/(float)111,       0, 0, 1//,


//0.5f, 0.5f, 50,     1, 1, 1,
//0.5f, -0.5f, 50,    0, 1, 0,
//-0.5, 0.5f, 50,     0, 0, 1//,
//-0.5f, -0.5f, 1, 1, 0, 0
		};

*/
/*
float	vertices[] = {
-0.500f, -0.500f, 1090/(float)1110,       1, 0, 0,
0.500f, -0.500f,  1090/(float)1110,       0, 1, 0,
-0.500f, 0.500f,    1090/(float)1110,       0, 0, 1//,


//0.5f, 0.5f, 50,     1, 1, 1,
//0.5f, -0.5f, 50,    0, 1, 0,
//-0.5, 0.5f, 50,     0, 0, 1//,
//-0.5f, -0.5f, 1, 1, 0, 0
		};

*/

int numberoffloats = 0;



int anglex = 0;
int angley = 0;

vec4 campos(
0, 0, 30, 0
);

vec4 cambasex(
0.4, 0, 0, 0
);

vec4 cambasez(
0, 0, -0.4, 0
);
#if 0
float	vertices[] = {
-5, -5, 20,      1, 0, 0, //left bottom
5, 5,  20,       0, 1, 0, //right top
-5, 5, 20,       0, 0, 1, //left top

5, -5, 20,    1, 1, 1, //right bottom
5, 5, 20,     0, 1, 0, //right top
-5, -5, 20,     1, 0, 0 //left bottom

/*
-5, -10, 10,      1, 0, 0, //left bottom
-5, -10,  20,       0, 1, 0, //right top
5, -10, 20,       0, 0, 1, //left top

-5, -10, 10,    1, 1, 1, //right bottom
5,-10, 10,     0, 1, 0, //right top
5, -10, 20,     1, 0, 0 //left bottom
*/

		};
#endif

// 1234 -> 123 + 234
/*
unsigned int indices[] = {
16, 2, 3,
2, 3, 17,
5, 8, 7,
8, 7, 6,
29, 30, 23,
9, 6, 7,
6, 7, 10,
14, 13, 17,
11, 1, 4,
1, 4, 13,
2, 9, 10,
9, 10, 3,
5, 12, 14,
12, 14, 8,
12, 11, 13,
11, 13, 14,
1, 15, 18,
15, 18, 4,
15, 16, 17,
16, 17, 18,
38, 42, 21,
42, 21, 20,
33, 39, 25,
39, 25, 32,
34, 27, 19,
27, 19, 22,
19, 20, 21,
20, 21, 22,
26, 25, 24,
25, 24, 23,
26, 23, 30,
23, 30, 31,
31, 30, 29,
30, 29, 32,
32, 29, 28,
29, 28, 33,
33, 28, 27,
28, 27, 34,
24, 25, 39,
25, 39, 35,
35, 39, 40,
39, 40, 36,
36, 40, 41,
40, 41, 37,
37, 41, 42,
41, 42, 38,
26, 31, 32,
37, 38, 20,
21, 42, 41,
12, 5, 6,
25, 26, 32,
22, 21, 41,
8, 14, 7,
28, 36, 27,
10, 14, 17,
14, 17, 3,
33, 40, 39,
40, 33, 34,
11, 16, 15,
16, 15, 1,
14, 10, 7,
2, 16, 12,
16, 12, 9,
11, 12, 16,
40, 34, 22,
34, 22, 41,
12, 6, 9,
18, 17, 13,
17, 13, 4,
36, 28, 35,
37, 20, 19,
29, 23, 24,
19, 27, 36,
27, 36, 37,
24, 35, 28,
35, 28, 29
};
*/

//propeller
/*
unsigned int indices[] = {
16, 2, 3,
16, 3, 17,
5, 8, 7,
5, 7, 6,
29, 30, 23,
9, 6, 7,
9, 7, 10,
14, 13, 17,
11, 1, 4,
11, 4, 13,
2, 9, 10,
2, 10, 3,
5, 12, 14,
5, 14, 8,
12, 11, 13,
12, 13, 14,
1, 15, 18,
1, 18, 4,
15, 16, 17,
15, 17, 18,
38, 42, 21,
38, 21, 20,
33, 39, 25,
33, 25, 32,
34, 27, 19,
34, 19, 22,
19, 20, 21,
19, 21, 22,
26, 25, 24,
26, 24, 23,
26, 23, 30,
26, 30, 31,
31, 30, 29,
31, 29, 32,
32, 29, 28,
32, 28, 33,
33, 28, 27,
33, 27, 34,
24, 25, 39,
24, 39, 35,
35, 39, 40,
35, 40, 36,
36, 40, 41,
36, 41, 37,
37, 41, 42,
37, 42, 38,
26, 31, 32,
37, 38, 20,
21, 42, 41,
12, 5, 6,
25, 26, 32,
22, 21, 41,
8, 14, 7,
28, 36, 27,
10, 14, 17,
10, 17, 3,
33, 40, 39,
40, 33, 34,
11, 16, 15,
11, 15, 1,
14, 10, 7,
2, 16, 12,
2, 12, 9,
11, 12, 16,
40, 34, 22,
40, 22, 41,
12, 6, 9,
18, 17, 13,
18, 13, 4,
36, 28, 35,
37, 20, 19,
29, 23, 24,
19, 27, 36,
19, 36, 37,
24, 35, 28,
24, 28, 29
};
*/

/*
float	vertices[] = {
2.324060, -12.166300, 11.338180, 0.000000, 0.000000, 1.000000,
2.324060, -7.455040, 28.430981, 1.000000, 1.000000, 1.000000,
-2.274750, -7.455040, 28.430981, 0.000000, 1.000000, 1.000000,
-2.274750, -12.166300, 11.338180, 1.000000, 0.000000, 1.000000,
2.324070, 11.199820, 11.338190, 1.000000, 1.000000, 1.000000,
2.324060, 11.199820, 16.028139, 1.000000, 1.000000, 1.000000,
-2.274750, 11.199820, 16.028130, 1.000000, 1.000000, 1.000000,
-2.274750, 11.199820, 11.338180, 1.000000, 1.000000, 1.000000,
2.324060, -3.403160, 28.430981, 1.000000, 1.000000, 1.000000,
-2.274750, -3.403160, 28.430981, 1.000000, 1.000000, 1.000000,
2.324070, -3.051930, 11.338190, 1.000000, 1.000000, 1.000000,
2.324070, -2.944960, 22.979370, 1.000000, 1.000000, 0.000000,
-2.274750, -3.051930, 11.338180, 1.000000, 0.000000, 1.000000,
-2.274750, -2.944960, 22.979370, 0.000000, 1.000000, 1.000000,
2.324060, -12.225690, 14.971950, 0.000000, 1.000000, 1.000000,
2.324060, -7.455040, 14.777310, 1.000000, 1.000000, 0.000000,
-2.274750, -7.455040, 14.777310, 1.000000, 1.000000, 1.000000,
-2.274750, -12.225690, 14.971940, 1.000000, 1.000000, 1.000000,
-2.274030, -7.311780, 9.014770, 1.000000, 1.000000, 1.000000,
-2.274030, -7.311780, -0.376200, 1.000000, 1.000000, 1.000000,
2.237040, -7.311780, -0.376200, 1.000000, 0.000000, 1.000000,
2.237040, -7.311780, 9.014770, 1.000000, 1.000000, 1.000000,
-2.274030, 11.193770, 9.014770, 1.000000, 0.000000, 1.000000,
-2.274030, 11.193770, -0.376200, 1.000000, 0.500000, 0.5000000,
2.237040, 11.193770, -0.376200, 1.000000, 1.000000, 1.000000,
2.237040, 11.193770, 9.014770, 0.000000, 1.000000, 1.000000,
-2.274030, -1.297720, 9.014770, 1.000000, 1.000000, 1.000000,
-2.274030, 5.514920, 3.844870, 1.000000, 1.000000, 1.000000,
-2.274030, 11.042680, 4.085010, 1.000000, 0.000000, 1.000000,
-2.274030, 5.073360, 9.014770, 0.000000, 1.000000, 1.000000,
2.237040, 5.073360, 9.014770, 1.000000, 1.000000, 1.000000,
2.237040, 11.042690, 4.085010, 1.000000, 1.000000, 1.000000,
2.237040, 5.514920, 3.844870, 1.000000, 1.000000, 0.000000,
2.237040, -1.297720, 9.014770, 1.000000, 1.000000, 1.000000,
-2.274030, 6.341340, -0.376200, 0.500000, 0.500000, 1.000000,
-2.274030, -0.667680, 3.985750, 0.000000, 1.000000, 1.000000,
-2.274030, -6.846490, 3.896810, 1.000000, 1.000000, 0.000000,
-2.274030, -0.755230, -0.376200, 1.000000, 1.000000, 0.000000,
2.237040, 6.341340, -0.376200, 1.000000, 1.000000, 1.000000,
2.237040, -0.667680, 3.985750, 1.000000, 1.000000, 1.000000,
2.237040, -6.846490, 3.896810, 1.000000, 1.000000, 1.000000,
2.237040, -0.755230, -0.376200, 0.000000, 1.000000, 1.000000
};
*/

/*
    float vertices[] = {
         5,  5, 20, 1, 0, 0,// top right
         5, -5, 20, 1, 1, 0,// bottom right
        -5, -5, 20, 0, 1, 1,// bottom left
        -5,  5,  20, 1, 1, 1// top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
*/
/*
float	plane[] = {
-5, -10, -10,      1, 0, 0, //left bottom
-5, -10,  -20,       0, 1, 0, //right top
5, -10, -20,       0, 0, 1, //left top

-5, -10, -10,    1, 1, 1, //right bottom
5,-10, -10,     0, 1, 0, //right top
5, -10, -20,     1, 0, 0 //left bottom
		};

*/

float	n = 2.0f;
float	f = 400.0f;
float	h = 1.0f;

/*
float	projectionMatrix[] = {
n / h, 0.0f, 0.0f, 0.0f,
0.0f, n / h, 0.0f, 0.0f,
0.0f, 0.0f, -(f + n) / (f - n), 2 * f * n / (f - n),
0.0f, 0.0f, 1.0f, 0.0f  //positive z dir is outwards when = 1
			};
*/


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

/*
float *getProjection(float near, float far, float halfheight)
{
	float n = near;
	float f = far;
	float h = halfheight;

	float	projectionMatrix[] = {
	n / h, 0.0f, 0.0f, 0.0f,
	0.0f, n / h, 0.0f, 0.0f,
	0.0f, 0.0f, - (f + n) / (f - n), -2 * f * n / (f - n),
	0.0f, 0.0f, -1.0f, 0.0f  //positive z dir is outwards when = 1
				};
	return (projectionMatrix);
}
*/
//float	f;

int	getFile(std::fstream &myfile)
{
	if (myfile.is_open())
		return (1);
	std::cerr << "Error: " << std::strerror(errno) << std::endl;
	return (0);
}

#define INDEX_MEM 9999

void	getData(char *path, std::vector<float> &ret/*float ret[]*/, std::vector<unsigned int> &indices/*unsigned int *&indices*/)
{
	std::fstream myfile(path);
		if (getFile(myfile) == 0)
			return ;
//	ret = (float *)malloc(sizeof(float) * 9999);

//	if (!(indices = (unsigned int *)malloc(sizeof(unsigned int) * (INDEX_MEM))))
	{
//		std::cout << "COULDN'T ALLOCATE MEMORY\n";
//		return ;
	}
	char **explode;
	std::string line;

	int i = 0;
	int j = 0;
	while (getline(myfile, line))
	{

			printf("writing vertex\n");
			printf("filled %d vertices\n", i);
		if (line[0] == 'v' || line[0] == 'f')
		{
			explode = ft_strsplit(line.c_str(), ' ');
			if (strcmp(explode[0], "v") == 0 /*&& i < 99999*/)
			{
				std::cout << line << std::endl;
				printf("after explode %s, %s, %s\n", explode[1], explode[2], explode[3]);

				ret.push_back(atof(explode[1]) * 1);
				ret.push_back(atof(explode[2]) * 1);
				ret.push_back(atof(explode[3]) * 1);

//for skull
/*				ret.push_back(atof(explode[1]) * 10);
				ret.push_back(atof(explode[3]) * 10 - 100);
				ret.push_back(atof(explode[2]) * 10);
*/

/*				ret[i + 0] = atof(explode[1]) * 10;
				ret[i + 1] = atof(explode[2]) * 10;
				ret[i + 2] = atof(explode[3]) * 10;
*/
//				while (ret[i + 3] == 0 && ret[i + 4] == 0 && ret[i + 5] == 0) //no black points
				{
/*					ret[i + 3] = rand() % 2;
					ret[i + 4] = rand() % 2;
					ret[i + 5] = rand() % 2;*/
					ret.push_back(rand() % 2);
					ret.push_back(rand() % 2);
					ret.push_back(rand() % 2);
				}
//				i = i + 6;
			}
			else if (strcmp(explode[0], "f") == 0)
			{
				printf("___________________\n");
				printf("filled %d indices\n", j);
				std::cout << line << std::endl;
/*				indices[j + 0] = atoi(explode[1]) - 1;
				indices[j + 1] = atoi(explode[2]) - 1;
				indices[j + 2] = atoi(explode[3]) - 1;
*/
				indices.push_back(atoi(explode[1]) - 1);
				indices.push_back(atoi(explode[2]) - 1);
				indices.push_back(atoi(explode[3]) - 1);



//				printf("explode 4 is %p\n", explode[4]);
				if (explode[4])
				{
					printf("||||||||||||||||||||\n");
//					j = j + 3;
/*					indices[j + 0] = atoi(explode[1]) - 1;
					indices[j + 1] = atoi(explode[3]) - 1;
					indices[j + 2] = atoi(explode[4]) - 1;

*/					indices.push_back(atoi(explode[1]) - 1);
					indices.push_back(atoi(explode[3]) - 1);
					indices.push_back(atoi(explode[4]) - 1);

					free (explode[4]);
				}
//				j = j + 3;
			}
			free (explode[0]);
			free (explode[1]);
			free (explode[2]);
			free (explode[3]);
			free (explode);
		}
	}
	printf("number of floats is %d\n", i);
	printf("file read\n");
}


void	printOpbject(unsigned int *object)
{
	int i = 0;
	while (object[i] != 0)
	{
		printf("%d, ", object[i]);
		if ((i + 1) % 3 == 0)
			printf("\n");
		i++;
	}
}

//unsigned int *indices;

std::vector<unsigned int>indices;
std::vector<float> vertices;

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

//these are for 42
//	float vertices[43 * 6];

//don't forget ti give arguments!
//	unsigned int indices[76 * 3];

//	float vertices[/*99999 * 6*/800000];
//	unsigned int indices[9999];

// this much for teapot 2
//	unsigned int indices[99999];

//	unsigned int *indices;


	if (argc == 2)
		getData(argv[1], vertices, indices);

	//printOpbject(indices);


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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);


	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);


							//how many bytes in a line
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0); // 0 = location of the vertex attribute

// color  //how much does location = 1 take space in a line	          //offset for the second location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1); // 1 = location of the vertex attribute

/*	unsigned int planeVBO;
	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0); // 0 = location of the vertex attribute
*/
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
//	glEnableVertexAttribArray(1); // 1 = location of the vertex attribute




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
			"out vec3 outColor;\n"
			"uniform mat4 P;\n"
			"uniform mat4 M1;\n"
			"uniform mat4 M;\n"
			"uniform mat4 T;\n"
			"uniform mat4 cR;\n"

			"uniform vec4 p;\n"


//need to get address from render loop
//			"uniform float f;\n"

			"void main()\n"
			"{\n"
//				"gl_Position = M1 * M * vec4(aPos.x, aPos.y, aPos.z, 1);\n" //output of the vertex shader. // here coordinates can be transformed to lie in (-1, 1)


				"gl_Position =  P * (M1 * M * (cR * vec4(aPos.x, aPos.y, aPos.z, 1) - p));\n"


//				"if (gl_Position == vec4(-5, -5, -10, 1))\n"
//				"{gl_Position += vec4(0.5, 0.5, 0.5, 0);}\n"
//				"gl_Position =  vec4(-10, -10, 38839/999, 39);\n"



				"outColor = color;\n"
//				"gl_Position.x = f.x;\n"
//				"gl_Position.y = f.y;\n"
			"}\0";




	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //no, don't send reference here :( no glBindBuffer
							// GL_VERTEX_SAHDER is a new argument;

	// atach shader source to the shader object so we can pass only object to compiler
				  //1 string               //ignore
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // atach
	glCompileShader(vertexShader);
	


//check for errors during compilation
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

//end check

//Fragment shader:
	const char *fragmentShaderSource =
				"#version 330 core\n"
				"out vec4 FragColor;\n" // has to have out vec4 type as output (but vec3 works too?)
//				"uniform vec4 ourColor;\n
//				"uniform mat4 M;\n"
				"in vec3 outColor;\n"
				"void main()\n"
				"{\n"
//				"	FragColor = vec4(0.1f, 0.4f, 1.0f, 1.0f);\n" //1.0f is opaque
//				"	FragColor = ourColor;\n"
//					"FragColor =  M * vec4(outColor, 1);\n"

					"FragColor = vec4(outColor, 1);\n"

				"}\0";


//Same thing as vertex shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


//	int  success;
//	char infoLog[512]; aleady defined
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

//end
//create program from two shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glUseProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);


//end
//Linking vertex attribute pointers

	         //location = 0 vec3    //normalise?     //distance between consective vertix attr in buffer
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
//	glEnableVertexAttribArray(0); // 0 = location of the vertex attribute


//don't know what this does	//unbinds our VBO
//works without this	// glVertexAttribPointer
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

		int newVertexLocation = glGetUniformLocation(shaderProgram, "M");
//		glUseProgram(shaderProgram);
		glUniformMatrix4fv(newVertexLocation, 1, GL_TRUE, yRotate);

		int newVertexLocation2 = glGetUniformLocation(shaderProgram, "M1");
//		glUseProgram(shaderProgram);
		glUniformMatrix4fv(newVertexLocation2, 1, GL_TRUE, xRotate);


		int newVertexLocation1 = glGetUniformLocation(shaderProgram, "P");
//		glUseProgram(shaderProgram);
		glUniformMatrix4fv(newVertexLocation1, 1, GL_TRUE, projectionMatrix);

		int newVertexLocation3 = glGetUniformLocation(shaderProgram, "T");
//		glUseProgram(shaderProgram);
		glUniformMatrix4fv(newVertexLocation3, 1, GL_TRUE, translate);

		int newVertexLocation5 = glGetUniformLocation(shaderProgram, "p");
//		glUseProgram(shaderProgram);
		glUniform4f(newVertexLocation5, campos[0], campos[1], campos[2], campos[3]);

		double time = glfwGetTime();

		mat4 constantRotation;

		constantRotation[0] = cos(time * 70/ (float)175);
		constantRotation[2] = sin(time * 70  / (float)175);
		constantRotation[8] = -sin(time * 70 / (float)175);
		constantRotation[10] = cos(time * 70 / (float)175);


		int newVertexLocation6 = glGetUniformLocation(shaderProgram, "cR");
		glUniformMatrix4fv(newVertexLocation6, 1, GL_TRUE, constantRotation);

		glUseProgram(shaderProgram);



//		glUniform1f(newVertexLocation, f);


//end


//        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


//	       glDrawArrays(GL_TRIANGLES, 0, 43);

//	       glDrawArrays(GL_POINTS, 0, numberoffloats);


	
//for 42
//		glDrawElements(GL_TRIANGLES, 83, GL_UNSIGNED_INT, 0);
//fo teapot


//		glDrawElements(GL_TRIANGLES, 9999, GL_UNSIGNED_INT, 0);

		if (numberoffloats < indices.size())
			numberoffloats += 20 /*6319 * 3*/;
//		numberoffloats = indices.size();
		glDrawElements(GL_TRIANGLES, round(numberoffloats) /*6319* 3*//* * 3 * 1*/, GL_UNSIGNED_INT, 0);


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
	if (argc == 2)
//		delete object;
	system("leaks -q a.out");
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
//		printf("unpress!\n");

//		return;
//	printf("action is %d\n", action);
	if (action == 0)
		return;
	mat4 invertedy = yRotate.invert();
	vec4 difx = invertedy * cambasex;
	vec4 difz = invertedy * cambasez;

/*
	mat4 invertedx = xRotate.invert();

	vec4 difx = invertedx * cambasex;
	vec4 difz = invertedx * cambasez;
*/
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
		printf("index %d is %d\n", numberoffloats, indices[numberoffloats]);
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
//	printf("after translate is %f, %f\n", x, y);


//y rotation

	yRotate[0] = cos(x / (float)175);
	yRotate[2] = sin(x / (float)175);
	yRotate[8] = -sin(x / (float)175);
	yRotate[10] = cos(x / (float)175);


// x rotation
/*
	xRotate[5] = cos(y / (float)175);
	xRotate[6] = sin(y / (float)175);
	xRotate[9] = -sin(y / (float)175);
	xRotate[10] = cos(y / (float)175);
*/
}


//shaders are programs run by the gpu at each step of the graphics pipeline
//there are default shaders and custom developer shaders
//custom shaders can be written for: *vertex shader* -> *geometry shader* -> *fragment shader*

