#include "weendow.hpp"
#include <cassert>

Weendow::Weendow(void)
{
    this->Width = 800;
    this->Height = 800;
    init(this->Window, this->Width, this->Height, "");
}

Weendow::Weendow(const char* title)
{
    this->Width = 800;
    this->Height = 800;
    init(this->Window, this->Width, this->Height, title);
}

Weendow::Weendow(int squareWindowSideLength)
{
    this->Width = this->Height = squareWindowSideLength;
    init(this->Window, this->Width, this->Height, "");
}

Weendow::Weendow(int squareWindowSideLength, const char* title)
{
    this->Width = this->Height = squareWindowSideLength;
    init(this->Window, this->Width, this->Height, title);
}

Weendow::Weendow(int width, int height)
{
    this->Width = width;
    this->Height = height;
    init(this->Window, this->Width, this->Height, "");
}

Weendow::Weendow(int width, int height, const char* title)
{
    this->Width = width;
    this->Height = height;
    init(this->Window, this->Width, this->Height, title);
}

Weendow::~Weendow(void)
{
    glfwDestroyWindow(this->Window);
    glfwTerminate();
}

bool Weendow::close(void) const
{
    return glfwWindowShouldClose(this->Window);
}

bool Weendow::glfwSetWindowCenter(GLFWwindow* window)
{
    if (!window)
        return false;

    int sx = 0, sy = 0;
    int px = 0, py = 0;
    int mx = 0, my = 0;
    int monitor_count = 0;
    int best_area = 0;
    int final_x = 0, final_y = 0;

    glfwGetWindowSize(window, &sx, &sy);
    glfwGetWindowPos(window, &px, &py);

    // Iterate throug all monitors
    GLFWmonitor** m = glfwGetMonitors(&monitor_count);
    if (!m)
        return false;

    for (int j = 0; j < monitor_count; ++j)
    {

        glfwGetMonitorPos(m[j], &mx, &my);
        const GLFWvidmode* mode = glfwGetVideoMode(m[j]);
        if (!mode)
            continue;

        // Get intersection of two rectangles - screen and window
        int minX = std::max(mx, px);
        int minY = std::max(my, py);

        int maxX = std::min(mx + mode->width, px + sx);
        int maxY = std::min(my + mode->height, py + sy);

        // Calculate area of the intersection
        int area = std::max(maxX - minX, 0) * std::max(maxY - minY, 0);

        // If its bigger than actual (window covers more space on this monitor)
        if (area > best_area)
        {
            // Calculate proper position in this monitor
            final_x = mx + (mode->width - sx) / 2;
            final_y = my + (mode->height - sy) / 2;

            best_area = area;
        }

    }

    // We found something
    if (best_area)
        glfwSetWindowPos(window, final_x, final_y);

    // Something is wrong - current window has NOT any intersection with any monitors. Move it to the default one.
    else
    {
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        if (primary)
        {
            const GLFWvidmode* desktop = glfwGetVideoMode(primary);

            if (desktop)
                glfwSetWindowPos(window, (desktop->width - sx) / 2, (desktop->height - sy) / 2);
            else
                return false;
        }
        else
            return false;
    }

    return true;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        GLint polygonMode[2] = { 0 };
        glGetIntegerv(GL_POLYGON_MODE, polygonMode);
        if (polygonMode[0] == GL_FILL && polygonMode[1] == GL_FILL) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else if (polygonMode[0] == GL_LINE && polygonMode[1] == GL_LINE) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

static void framebuffersize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Weendow::init(GLFWwindow* &window, int width, int height, const char* title)
{
    int ret = 0;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);
    ret = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(ret);
    glfwSetWindowCenter(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffersize_callback);
}
