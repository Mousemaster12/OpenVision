#include"Object.h"
#include"Math.h"
#include"Settings.h"
#include"IMGUITheme.h"
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <filesystem>
#include"PhysicsWorld.h"
#include <thread>
#include"Console.h"
#include"OVscriptHandaling.h"
#include"Presave.h"
#include"Script.h"
#include"Newsc.h"
#include"EpicNewScript.h"
Script script;
Newsc Newscscr;
EpicNewScript EpicNewScriptscr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Console con;

double scroll_offset = 45.0;

int PythonIndex = 1;


Camera camera(width, height, glm::vec3(0.0f, 0.0f, 80.0f));



std::string executeCommandAndGetOutput(const char* command) {
	std::string outputFileName = "command_output.txt";
	std::string commandWithOutputRedirect = std::string(command) + " > \"" + outputFileName + "\"";

	std::system(commandWithOutputRedirect.c_str());

	std::ifstream outputFile(outputFileName);
	if (!outputFile.is_open()) {
		std::cerr << "Failed to open output file." << std::endl;
		return "";
	}

	std::stringstream output;
	output << outputFile.rdbuf();
	outputFile.close();

	std::remove(outputFileName.c_str());

	return output.str();
}
std::string getPythonLocationByLine(int line) {
	std::string whereCommand = "where python";
	std::string pythonLocations = executeCommandAndGetOutput(whereCommand.c_str());

	std::stringstream ss(pythonLocations);
	std::string location;
	std::vector<std::string> locations;

	while (std::getline(ss, location, '\n')) {
		locations.push_back(location);
	}

	if (line < 0)
		line = 0;
	if (line >= locations.size()) {
		line = locations.size() - 1;
	}

	return locations[line];
}
void rebuild(GLFWwindow* window, bool localPython) {
	std::cout << "python locations " << endl << executeCommandAndGetOutput("where python") << endl;
	std::cout << getPythonLocationByLine(PythonIndex) << endl;
	std::system((getPythonLocationByLine(PythonIndex) + std::string(" -m pip install watchdog")).c_str());
	std::string command = std::string("start /B python builder.py");

	if (!localPython) {
		std::filesystem::path pythonPath = getPythonLocationByLine(PythonIndex);
		std::string pythonPathStr = pythonPath.string();

		for (size_t i = 0; i < pythonPathStr.size(); i++) {
			if (pythonPathStr[i] == '\\') {
				pythonPathStr.insert(i, 1, '\\');
				i++;
			}
		}

		command = std::string("start /B ") + pythonPathStr + " builder.py";
	}

	std::cout << "command: " << command << std::endl;

	std::system(command.c_str());

	std::chrono::seconds wait_time(1);
	std::this_thread::sleep_for(wait_time);
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}



void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll_offset += yoffset;
	printf("Scrolled by %f units\n", scroll_offset);
}






int main()
{
	Presave<float> myData;

	myData = Presave < float >();
	myData.SafeOperation();
	
	bool vsync = myData.data[0];
	int msaa = myData.data[1];
	float screenR = myData.data[2];
	float screenG = myData.data[3];
	float screenB = myData.data[4];
	bool LocalPy = myData.data[5];


	std::vector<std::string> lines;
	std::ifstream inputFile("scripts.ov");
	if (!inputFile.is_open()) {
		std::cerr << "Failed to open input file." << std::endl;
		return 1;
	}
	std::string line;
	while (std::getline(inputFile, line)) {
		lines.emplace_back(line);
	}
	inputFile.close();

	PhysicsWorld world(vec3(0, 5.0f, 0), 10);


	const std::filesystem::path directory_path = std::filesystem::current_path();




	for (int i = 0; i < 4; i++) {
		vertices[i].position.x *= GlobalWorldScale;
		vertices[i].position.y *= GlobalWorldScale;
		vertices[i].position.z *= GlobalWorldScale;
	}

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, msaa);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "Loading...", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//load Icon
	int wid, hei;
	int channels;
	unsigned char* pixels = stbi_load("OpenVisionIcon.png", &wid, &hei, &channels, 4);

	GLFWimage images[1];
	images[0].width = wid;
	images[0].height = hei;
	images[0].pixels = pixels;
	glfwSetWindowIcon(window, 1, images);

	gladLoadGL();
	glViewport(0, 0, width, height);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLuint unlitFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(unlitFragmentShader, 1, &UnlitFragment, NULL);
	glCompileShader(unlitFragmentShader);

	GLuint unlitProgram = glCreateProgram();
	glAttachShader(unlitProgram, vertexShader);
	glAttachShader(unlitProgram, unlitFragmentShader);
	glLinkProgram(unlitProgram);



	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));



	float ndcMouseX;
	float ndcMouseY;
	double mouseX;
	double mouseY;
	double beforeMouseX;
	double beforeMouseY;
	bool run = false;
	bool StartPhase = false;
	bool no_resize = true;
	bool no_move = true;



	std::vector<Texture> textures;
	std::filesystem::path dir_path = "Assets/";

	for (const auto& file : std::filesystem::directory_iterator(dir_path)) {
		std::string ext = file.path().extension().string();
		if (ext == ".jpg" || ext == ".png" || ext == ".jpeg") {
			std::string filepath = file.path().string();
			Texture tex(filepath.c_str());
			tex.ImageFile = tex.ImageFile = file.path().stem().string();
			tex.FullImageFile = filepath;
			textures.push_back(tex);
		}
	}


	std::vector<Object> sceneObjects;
	std::vector<Object> PresceneObjects;

	std::ifstream ovEnvFile("OV_ENV.ov");
	while (std::getline(ovEnvFile, line)) {
		float posx, posy, scalex, scaley, angle;
		std::string texture;
		std::string delimiter = ",";
		std::istringstream iss(line);

		std::string token;
		std::getline(iss, token, ',');
		posx = std::stof(token);
		std::getline(iss, token, ',');
		posy = std::stof(token);
		std::getline(iss, token, ',');
		scalex = std::stof(token);
		std::getline(iss, token, ',');
		scaley = std::stof(token);
		std::getline(iss, token, ',');
		angle = std::stof(token);
		std::getline(iss, token, ',');
		texture = token.c_str();

		std::cout << posx;
		std::cout << posy;
		std::cout << scalex;
		std::cout << scaley;
		std::cout << angle;
		std::cout << texture;

		Object obj = Object(verts, ind);
		obj.position->x = posx;
		obj.position->y = posy;
		obj.scenePosition.x = posx;
		obj.scenePosition.y = posy;
		obj.scale->x = scalex;
		obj.scale->y = scaley;
		obj.sceneScale.x = scalex;
		obj.sceneScale.y = scaley;
		obj.angle = angle;
		obj.texChar = texture;

		obj.tex = Texture((texture).c_str());
		PresceneObjects.push_back(obj);
	}
	ovEnvFile.close();

	Object blackbox = Object(verts, ind);
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;
	int selectedObject = 0;
	float fov = 45;
	char addedfile[256] = "";

	const float fixed_timestep = 1.0f / 60.0;
	DefaultTheme();
	glEnable(GL_MULTISAMPLE);

	for (size_t i = 0; i < sceneObjects.size(); i++) {
		sceneObjects[i].scenePosition = *PresceneObjects[i].position;
		sceneObjects[i].sceneScale = *PresceneObjects[i].scale;
	}
	sceneObjects = PresceneObjects;

	while (!glfwWindowShouldClose(window))
	{

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			run = false;
		}
		glClearColor(screenR, screenG, screenB, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapInterval(vsync);
		camera.updateMatrix(fov, 0.1f, 100.0f);



		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		static bool show_selected_pop = false;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			if (!show_selected_pop) 
			{
				ImVec2 mouse_pos = ImVec2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
				ImGui::SetNextWindowPos(mouse_pos, ImGuiCond_Appearing, ImVec2(0, 1));
				ImGui::OpenPopup("Selected Object Settings");
			}
			show_selected_pop = true;
		}

		if (ImGui::BeginPopup("Selected Object Settings"))
		{
			if (ImGui::Button(("Delete Object")))
			{
				PresceneObjects[selectedObject].deleted = true;

			}



			ImGui::InputFloat("Position X", &PresceneObjects[selectedObject].position->x, 0.3f, 1, "%.3f", 0);
			ImGui::InputFloat("Position Y", &PresceneObjects[selectedObject].position->y, 0.3f, 1, "%.3f", 0);

			ImGui::InputFloat("Scale X", &PresceneObjects[selectedObject].scale->x, 0.3f, 1, "%.3f", 0);

			ImGui::InputFloat("Scale Y", &PresceneObjects[selectedObject].scale->y, 0.3f, 1, "%.3f", 0);

			ImGui::InputFloat("Angle", &PresceneObjects[selectedObject].angle, 0.3f, 1, "%.3f", 0);
			ImGui::EndPopup();
		}
		if (ImGui::IsMouseReleased(GLFW_MOUSE_BUTTON_RIGHT))
		{
			show_selected_pop = false;
		}




		if (!run) {

			if (!StartPhase) {
				fov = 45;
				glfwSetWindowTitle(window, "OpenVision *(Universal Editor)");
				for (size_t i = 0; i < PresceneObjects.size(); i++)
				{
					*sceneObjects[i].position = PresceneObjects[i].scenePosition;
					*sceneObjects[i].scale = PresceneObjects[i].sceneScale;
					sceneObjects[i].Body->velocity = vec2(0, 0);
					PresceneObjects[i].Body->velocity = vec2(0, 0);
				}
				sceneObjects[0].Body->GetCollider()->CalculateAABB();

				StartPhase = true;
			}
			sceneObjects = PresceneObjects;

			ImGui::Begin("Execute", 0, (no_resize ? ImGuiWindowFlags_NoResize : 0) | (no_move ? ImGuiWindowFlags_NoMove : 0));
			if (ImGui::Button("Run"))
			{
				if (run == false) {

					run = true;
				}
				else if (run == true)
				{

					run = false;
				}
			}
			if (ImGui::Button("Rebuild"))
			{
				rebuild(window, LocalPy);
			}
			ImGui::Checkbox("Local-Python (not recommended)", &LocalPy);

			if (ImGui::Button("Exit OV"))
			{
				std::system("taskkill /f /im python.exe");
				glfwSetWindowShouldClose(window, GLFW_TRUE);

			}

			ImGui::End();

			con.Draw(no_resize,no_move);

			ImGui::Begin("Sources", 0, (no_resize ? ImGuiWindowFlags_NoResize : 0) | (no_move ? ImGuiWindowFlags_NoMove : 0));
			if (ImGui::BeginTabBar("TabBar"))
			{
				if (ImGui::BeginTabItem("Textures"))
				{
					if (ImGui::Button("Add Texture"))
					{
						textures.push_back(Texture(addedfile));
					}

					ImGui::InputText("Path : ", addedfile, sizeof(addedfile));

					for (size_t k = 0; k < textures.size(); k++)
					{
						ImGui::Separator();

						if (ImGui::Selectable(("Bind : " + std::string(textures[k].ImageFile)).c_str()))
						{
							PresceneObjects[selectedObject].tex = textures[k];
							PresceneObjects[selectedObject].texChar = textures[k].FullImageFile;
						}

						ImGui::Separator();
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Graphics"))
				{
					ImGui::Checkbox("Vertical-Synchronization", &vsync);
					ImGui::InputInt("MSAA Samples", &msaa);
					ImGui::Separator();

					ImGui::Text("Backround Color");
					ImGui::Columns(3);
					ImGui::InputFloat("(R)", &screenR);
					ImGui::NextColumn();
					ImGui::InputFloat("(G)", &screenG);
					ImGui::NextColumn();
					ImGui::InputFloat("(B)", &screenB);
					ImGui::Separator();
					ImGui::Columns(1);
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::End();


			static char scriptName[128] = "";

			ImGui::Begin("Scripts", 0, (no_resize ? ImGuiWindowFlags_NoResize : 0) | (no_move ? ImGuiWindowFlags_NoMove : 0));
			ImGui::Columns(2, nullptr, true);
			ImGui::InputText("Script Name", scriptName, IM_ARRAYSIZE(scriptName));

			if (ImGui::Button("Add Script"))
			{
				std::ofstream outputFile("SCRIPTS.ov", std::ios::app);
				outputFile << scriptName << std::endl;
				outputFile.close();
				addOVscript(scriptName);
				memset(scriptName, 0, sizeof(scriptName));
				rebuild(window, LocalPy);
			}

			if (ImGui::Button("Remove Script"))
			{
				if (scriptName != "Script" && 
					scriptName != "Camera" &&
					scriptName != "CircleCollider" &&
					scriptName != "CollisionManager" &&
					scriptName != "Console" &&
					scriptName != "EBO" &&
					scriptName != "IMGUITheme" &&
					scriptName != "Math" &&
					scriptName != "Object" &&
					scriptName != "OVscriptHandaling" &&
					scriptName != "PhysicsBody" &&
					scriptName != "PhysicsWorld" &&
					scriptName != "PolygonCollider" &&
					scriptName != "Settings" &&
					scriptName != "Tex" &&
					scriptName != "VAO" &&
					scriptName != "Presave" &&
					scriptName != "VBO"
					) {
					std::string scriptname_str = scriptName;
					std::ifstream inputFile("SCRIPTS.ov");
					std::ofstream tempFile("temp.txt");
					std::string line;

					while (std::getline(inputFile, line)) {
						if (line.find(scriptname_str) != std::string::npos) {
							continue;
						}
						tempFile << line << std::endl;
					}

					inputFile.close();
					tempFile.close();
					std::remove("SCRIPTS.ov");
					std::rename("temp.txt", "SCRIPTS.ov");

					removeOVscript(scriptName);
					memset(scriptName, 0, sizeof(scriptName));
					rebuild(window, LocalPy);
				}
			}

			if (ImGui::Button("Open Script"))
			{
				std::string command = "start " + std::string(scriptName) + ".cpp";
				system(command.c_str());
				memset(scriptName, 0, sizeof(scriptName));
			}
			ImGui::NextColumn();
			if (ImGui::Button("Script (gloabl ov script)")) {
				std::string command = "start Script.cpp";
				system(command.c_str());
			}
			for (const auto& line : lines) {
				if (ImGui::Button(line.c_str())) {
					std::string command = "start " + std::string(line) + ".cpp";
					system(command.c_str());
				}
			}
			ImGui::End();

			ImGui::Begin("Window Control", 0, (no_resize ? ImGuiWindowFlags_NoResize : 0) | (no_move ? ImGuiWindowFlags_NoMove : 0));
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			ImGui::Text("Values here will not be saved.");
			ImGui::PopStyleColor();
			ImGui::Checkbox("No Window Moving", &no_move);
			ImGui::Checkbox("No Window Resize", &no_resize);
			ImGui::EndTabItem();
			ImGui::End();


			ImGui::Begin("Object Inspector", 0, (no_resize ? ImGuiWindowFlags_NoResize : 0) | (no_move ? ImGuiWindowFlags_NoMove : 0));



			if (ImGui::Button("Add object"))
			{

				PresceneObjects.push_back(Object(verts, ind));

			}
			{
				for (size_t i = 0; i < PresceneObjects.size(); i++)
				{

					if (PresceneObjects[i].selected)
					{

						selectedObject = i;

					}

					if (PresceneObjects[i].deleted == false) {

						if (ImGui::CollapsingHeader(("Object" + std::to_string(i)).c_str())) {
							if (ImGui::Button(("Delete Object##" + std::to_string(i)).c_str()))
							{
								PresceneObjects[i].deleted = true;

							}


							ImGui::Columns(2, nullptr, true);

							ImGui::InputFloat(("Pos X##" + std::to_string(i)).c_str(), &PresceneObjects[i].position->x, 0.3f, 1, "%.3f", 0);
							ImGui::NextColumn();
							ImGui::InputFloat(("Pos Y##" + std::to_string(i)).c_str(), &PresceneObjects[i].position->y, 0.3f, 1, "%.3f", 0);

							ImGui::Columns(1, nullptr, true);
							ImGui::Columns(2, nullptr, true);
							ImGui::InputFloat(("Scale X##" + std::to_string(i)).c_str(), &PresceneObjects[i].scale->x, 0.3f, 1, "%.3f", 0);
							ImGui::NextColumn();

							ImGui::InputFloat(("Scale Y##" + std::to_string(i)).c_str(), &PresceneObjects[i].scale->y, 0.3f, 1, "%.3f", 0);

							ImGui::Columns(1, nullptr, true);
							ImGui::InputFloat(("Angle ##" + std::to_string(i)).c_str(), &PresceneObjects[i].angle, 0.3f, 1, "%.3f", 0);







						}
						ImGui::Separator();


						glfwGetCursorPos(window, &mouseX, &mouseY);
						ndcMouseX = (float)mouseX / (float)width * 2.0f - 1.0f;
						ndcMouseY = (float)mouseY / (float)height * 2.0f - 1.0f;
						ndcMouseX *= rattio.x * 3.7;
						ndcMouseY *= rattio.y * 3.7;
						if ((PresceneObjects[i].position->x - PresceneObjects[i].scale->x / 3) - camera.Position.x < ndcMouseX &&
							(PresceneObjects[i].position->x + PresceneObjects[i].scale->x / 3) + camera.Position.x > ndcMouseX &&
							(PresceneObjects[i].position->y + PresceneObjects[i].scale->y / 3) - camera.Position.y > ndcMouseY &&
							(PresceneObjects[i].position->y - PresceneObjects[i].scale->y / 3) + camera.Position.y < ndcMouseY
							&& glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
						{
							if (!PresceneObjects[i].selected) {
								beforeMouseX = ndcMouseX;
								beforeMouseY = ndcMouseY;
							}
							else {
								float dx = ndcMouseX - beforeMouseX;
								float dy = ndcMouseY - beforeMouseY;

								PresceneObjects[i].position->x += dx;
								PresceneObjects[i].position->y += dy;

								beforeMouseX = ndcMouseX;
								beforeMouseY = ndcMouseY;
							}

							PresceneObjects[i].selected = true;
						}
						else {
							PresceneObjects[i].selected = false;
						}



						PresceneObjects[i].Draw(window, shaderProgram, camera, glm::vec3(0, 0, 1), width, height, rattio);
						glUseProgram(unlitProgram);
						glUniform4f(glGetUniformLocation(unlitProgram, "color"), 1.00, 0.56, 0.13, 1);

						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						glLineWidth(3.0f);
						PresceneObjects[selectedObject].Draw(window, unlitProgram, camera, glm::vec3(0, 0, 1), width, height, rattio);
						glLineWidth(0.0f);
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


					}
				}
			}
		}
		blackbox.DrawTMP(window, shaderProgram, camera, glm::vec2(0, (-36 / 1.5) / 1.5), glm::vec2(114, 0.5));
		blackbox.DrawTMP(window, shaderProgram, camera, glm::vec2(0,( 36 / 1.5) / 1.5), glm::vec2(114, 0.5));

		blackbox.DrawTMP(window, shaderProgram, camera, glm::vec2((61.7 / 1.445) / 1.5, 0), glm::vec2(0.5, 64));
		blackbox.DrawTMP(window, shaderProgram, camera, glm::vec2((-61.7 / 1.445) / 1.5,0), glm::vec2(0.5, 64));
		if (run) {
			if (StartPhase)
			{

				for (size_t i = 0; i < PresceneObjects.size(); i++) {
					sceneObjects[i].scenePosition = *sceneObjects[i].position;
					sceneObjects[i].sceneScale = *sceneObjects[i].scale;
				}
				PresceneObjects = sceneObjects;
				con.CLEAR_CONSOLE();
				fov = 22.45;
				script.Start(con, window, world, sceneObjects);
				Newscscr.Start(con, window, world, sceneObjects);
				EpicNewScriptscr.Start(con, window, world, sceneObjects);
				StartPhase = false;
			}
			if (timeDiff >= fixed_timestep) {
				std::string FPS = std::to_string((1.0 / timeDiff) * counter);
				std::string newTitle = "OpenVision - periidev & itaymadeit ~" + FPS + "FPS";
				glfwSetWindowTitle(window, newTitle.c_str());
				prevTime = crntTime;
				counter = 0;



			
				script.Update(con, window, world, sceneObjects);
				Newscscr.Update(con, window, world, sceneObjects);
				EpicNewScriptscr.Update(con, window, world, sceneObjects);


				world.Step(fixed_timestep);
			}

			
			for (size_t i = 0; i < sceneObjects.size(); i++)
			{
				if (!sceneObjects[i].deleted) {
					glLineWidth(0.0f);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glUseProgram(unlitProgram);
					glUniform4f(glGetUniformLocation(unlitProgram, "color"), sceneObjects[i].OutlineColor.x, sceneObjects[i].OutlineColor.y, sceneObjects[i].OutlineColor.z, 1);
					glLineWidth(sceneObjects[i].outlineWidth);
					if (sceneObjects[i].outlineWidth > 0) {
						sceneObjects[i].Draw(window, unlitProgram, camera, glm::vec3(0, 0, 1), width, height, rattio);
					}
					glLineWidth(0.0f);
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					sceneObjects[i].Draw(window, shaderProgram, camera, glm::vec3(0, 0, 1), width, height, rattio);
				}
			}
			
		}


		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
		//enable when final build
		//run = true;

	}
	
	std::ofstream outfile("OV_ENV.ov");
	for (const auto& obj : sceneObjects) {
		if (obj.deleted == false) {
			outfile << obj.position->x << "," << obj.position->y << "," << obj.scale->x << ","
				<< obj.scale->y << "," << obj.angle << "," << obj.texChar << "\n";
		}
	}
	outfile.close();




	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glfwDestroyWindow(window);
	glfwTerminate();


	myData.data = { float(vsync), float(msaa), screenR, screenG, screenB, float(LocalPy)};

	myData.saveData();

	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
