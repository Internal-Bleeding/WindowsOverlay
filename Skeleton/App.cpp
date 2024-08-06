#include "App.h"
#include "json.hpp"
#include "fstream"
#include <sstream>
#include "MyTexture.h"

const char* const vertexSource = R"(
	#version 330				// Shader 3.3
	precision highp float;		// normal floats, makes no difference on desktop computers

	uniform mat4 MVP;			// uniform variable, the Model-View-Projection transformation matrix
	layout(location = 0) in vec2 vp;	// Varying input: vp = vertex position is expected in attrib array 0

	out float distance;

	void main() {
		distance = length(vp);
		gl_Position = vec4(vp.x, vp.y, 0, 1) * MVP;		// transform vp from modeling space to normalized device space
	}
)";

// fragment shader in GLSL
const char* const fragmentSource = R"(
	#version 330			// Shader 3.3
	precision highp float;	// normal floats, makes no difference on desktop computers
	
	uniform vec3 color;		// uniform variable, the color of the primitive
	in float distance;
	out vec4 outColor;		// computed color of the current pixel

	void main() {
		outColor = vec4(color.x, color.y, color.z , 1);	// computed color is the color of the primitive
	}
)";

const char* const  backgroundVertexShader = R"(
	#version 330
	precision highp float;

	layout(location = 0) in vec2 vp;
	layout(location = 1) in vec2 tx;

	uniform vec2 ratio;

	out vec2 texCoord;
	
	void main() {
		gl_Position = vec4(vp.x, vp.y, 0.1f, 1);
		texCoord = tx * ratio;
	}

)";

const char* const  backgroundFragmentShader = R"(
	#version 330
	precision highp float;

	uniform sampler2D myTexture;

	in vec2 texCoord;
	out vec4 outColor;

	void main() {
		outColor =  texture(myTexture, texCoord); 
	}

)";

App::App() : foregroundColor(vec3(1, 1, 0)), backgroundColor(vec3(0, 0, 0)), rotationSpeed(1.0f),
rotationMat(mat4{ 1, 0, 0, 0,    // MVP matrix, 
                0, 1, 0, 0,    // row-major!
                0, 0, 1, 0,
                0, 0, 0, 0.6 })
{
    std::cout << "Created" << std::endl;
}

void App::create()
{
    background.create(backgroundVertexShader, backgroundFragmentShader, "outColor");
    foreground.create(vertexSource, fragmentSource, "outColor");
    spiral.create();
    //textures.create();

    //textures.add(MyTexture("loser.jpg"));
}

void App::loadFromFile(const char* filePath)
{
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;

        return;
    }

    nlohmann::json jsonData;
    try {
        inputFile >> jsonData;
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }   
    // Extract data
    try {
        std::string color = jsonData.at("foregroundcolor").get<std::string>();
        rotationSpeed = jsonData.at("speed").get<float>();
        float width = jsonData.at("width").get<float>();
        float pitch = jsonData.at("pitch").get<float>();
        float turn = jsonData.at("turn").get<float>();
        int alpha = jsonData.at("transparency").get<int>();
        size_t res = jsonData.at("resolution").get<size_t>();

        spiral.update(turn, width + 1, pitch, res);

        makeWindowTransparent(alpha);

        float x, y, z;
        std::stringstream ss(color);
        char com = ',';
        ss >> x >> com >> y >> com >> z;
        std::cout << x << y << z;
        foregroundColor = vec3(x, y, z);

        color = jsonData.at("backgroundcolor").get<std::string>();

        ss = std::stringstream(color);
        ss >> x >> com >> y >> com >> z;
        std::cout << x << y << z;
        backgroundColor = vec3(x, y, z);
    }
    catch (nlohmann::json::out_of_range& e)
    {
        std::cerr << "Error extracting data: " << e.what() << std::endl;
    }
}

void App::render()
{
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 0);     // background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear frame buffer

    glUseProgram(background.getId());

    //float aspectRatio = textures.current().GetRatio() / (9.0f / 16.0f);

    //int location = glGetUniformLocation(background.getId(), "ratio");	// Get the GPU location of uniform variable MVP
    //glUniform2f(location, aspectRatio, 1.0f);

    //textures.render();

    glUseProgram(foreground.getId());

    int location = glGetUniformLocation(foreground.getId(), "color");
    glUniform3f(location, foregroundColor.x, foregroundColor.y, foregroundColor.z); // 3 floats

    rotationMat = rotationMat * RotationMatrix(rotationSpeed * M_PI / 180, vec3(0, 0, 1));

    mat4 MVP = rotationMat * mat4{ 0.9f, 0, 0, 0,    // MVP matrix, 
                            0, 1.6f, 0, 0,    // row-major!
                            0, 0, 1, 0,
                            0, 0, 0, 1 };
    location = glGetUniformLocation(foreground.getId(), "MVP");	// Get the GPU location of uniform variable MVP
    glUniformMatrix4fv(location, 1, GL_TRUE, &MVP[0][0]);	// Load a 4x4 row-major float matrix to the specified location

    spiral.render();
}

void App::makeWindowTransparent(int alpha)
{
    if (!hwnd) {
        std::cout << "ERROR no window handle set" << std::endl;
        //hwnd = FindWindow(NULL, "SPIRAL");
        return;
    }

    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA);
    //SetLayeredWindowAttributes(hwnd, 0, 100, LWA_ALPHA);

    // Make the window click-through
    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    exStyle |= WS_EX_LAYERED | WS_EX_TRANSPARENT;
    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);
}

App::~App() 
{
    std::cout << "App deleted";
   // delete spiral;
}